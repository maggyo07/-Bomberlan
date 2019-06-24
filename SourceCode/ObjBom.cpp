//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjBom.h"

//使用するネームスペース
using namespace GameL;

CObjBom::CObjBom(float x, float y)
{
	//ｘ、ｙの位置を40*40の中央あたりにする。
	x += 20;
	y += 20;

	//ｘ、ｙの要素番号
	int x_element_number = ((int)x) / BOM_SIZE;
	int y_element_number = ((int)y) / BOM_SIZE;

	m_y = y_element_number * BOM_SIZE;
	m_x = x_element_number * BOM_SIZE;

}

//イニシャライズ
void CObjBom::Init()
{
	m_ani_time = 0;		//アニメーションフレーム動作間隔初期化
	m_ani_frame = 0;	//描画フレーム初期化

	m_ani_max_time = 10;	//アニメーション動作間隔最大値初期化

	m_ani_frame_change = 3; //アニメーション切り替え用初期化

	m_time = 0;	//時間初期化

	//主人公情報を持ってくる
	CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);

	//主人公オブジェクトが存在していたら
	if(hero != nullptr)
	{
		m_hero_bom_power = hero->GetBomPower();
	}
	else
	{
		m_hero_bom_power = 1;
	}

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this,m_x + (block->GetScroll()),m_y,BOM_SIZE, BOM_SIZE,ELEMENT_RED,OBJ_BOM,1);

	


}
//アクション
void CObjBom::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	block->GetMap(m_map);//マップ情報更新

	//主人公情報を持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公オブジェクトが存在していたら。
	if(hero != nullptr)
	{
		//主人公のリモコン機能がONの場合
		if(hero->GetRemoteController() == true)
		{
			//時間ストップ
			m_time = 0;
			//アニメーションを最初に戻す
			m_ani_frame_change = 3;
		}
		else
		{
			m_time++;
		}
	}
	else
	{
		m_time++;
	}
	m_ani_time++;

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + (block->GetScroll()), m_y);

	//主人公オブジェクトに接触していなかったら && 敵オブジェクトに接触していなかったら
	if(hit->CheckObjNameHit(OBJ_HERO) == nullptr && hit->CheckElementHit(ELEMENT_ENEMY) == false)
	{

		int x = ((int)m_x) / BOM_SIZE;//Xの要素番号
		int y = ((int)m_y) / BOM_SIZE;//Yの要素番号
		//当たり判定用に4を代入
		m_map[y][x] = 4;

		block->MapChange(m_map);//マップの更新

	}

	//早く切り替え(フレーム)防止
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame++;
		m_ani_time = 0;
	}

	//最後のフレームに行ったら最初のフレームに戻す
	if(m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//アニメーション切り替え
	if(m_time == 80)
	{
		//次のアニメーションへ
		m_ani_frame_change++;
	}
	else if(m_time == 150)
	{
		//次のアニメーションへ
		m_ani_frame_change++;
	}

	bool hero_remote_controller;//主人公のリモコン情報(true:ON false:OFF)

	//主人公オブジェクトが存在していたら
	if(hero != nullptr)
	{
		//ON
		hero_remote_controller = hero->GetRemoteController();
	}
	else
	{
		//OFF
		hero_remote_controller = false;
	}

	//時間　｜｜　爆風に当たっていたら || (主人公のリモコン機能がONの場合 && Zが押されていたら)
	if(m_time > 180 || hit->CheckObjNameHit(OBJ_BLAST) != nullptr || (hero_remote_controller == true && Input::GetVKey('Z') == true))
	{
		//６０　*　３　で爆発
		//180
		//主人公オブジェクトが存在していたら
		if(hero != nullptr)
		{
			//ボムが爆発したのでHeroのbom_numをデクリメント
			hero->SetBomNum();
		}

		//その場の爆風オブジェクト作成
  		CObjBlast* obj_blast = new CObjBlast(m_x , m_y,IN_SITU,1);	//爆風オブジェクト作成
		Objs::InsertObj(obj_blast, OBJ_BLAST, 10);	//爆風オブジェト登録

		//爆風情報を持ってくる
		CObjBlast* blast = (CObjBlast*) Objs::GetObj(OBJ_BLAST);

		//主人公情報を持ってくる
		CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);

		//主人公オブジェクトが存在していたら
		if(hero != nullptr)
		{
			m_hero_bom_power = hero->GetBomPower();
		}

		//爆風作成
		for(int direction = 0; direction < 4; direction++)
		{
			for(int bom_power = 0; bom_power < m_hero_bom_power; bom_power++)
			{
				//							右				左				上			 下   
				int direction_x[4] = {1 + bom_power,-1 - bom_power, 0			 ,0			   };
				int direction_y[4] = {0			   , 0			  ,-1 - bom_power,1 + bom_power};

				//x,yの要素番号
				int x = ((int)m_x) / BLAST_SIZE + direction_x[direction];
				int y = ((int)m_y) / BLAST_SIZE + direction_y[direction];
				
				block->GetMap(m_map);//マップ情報獲得

				//おこうとしている場所にブロック
				if (m_map[y][x] == 1 ||
					m_map[y][x] == 10||
					m_map[y][x] == 11
					)
				{
					//破壊可能ブロックの判定だけのもの(10)の場合
					if (m_map[y][x] == 10)
					{
						//破壊したブロックの当たり判定を消去
						m_map[y][x] = 11;
						block->MapChange(m_map);//マップ情報更新
					}
					//爆風停止
					break;
				}

				//置こうとしている場所に爆風があれば処理をしない
				else if(m_map[y][x] == -1);

				else
				{
					//爆風オブジェクト作成
					CObjBlast* obj_blast = new CObjBlast(m_x, m_y, direction, bom_power + 1);	//爆風オブジェクト作成
					Objs::InsertObj(obj_blast, OBJ_BLAST, 10);	//爆風オブジェト登録
					//爆風の先端
					if (bom_power == m_hero_bom_power - 1)
					{
						//先端の爆風だと教える；
						obj_blast->SetLastBlast(true);
					}
				}
			}
		}
		//消去する前に当たり判定を消去
		int x = ((int)m_x) / BOM_SIZE;//Xの要素番号
		int y = ((int)m_y) / BOM_SIZE;//Yの要素番号
		//当たり判定を消す
		m_map[y][x] = 0;
		block->MapChange(m_map);//マップの更新

		Audio::Start(1); //音楽スタート
		this->SetStatus(false);		//自身に消滅命令を出す。
		Hits::DeleteHitBox(this);	//敵機が所有するHitBoxに消滅する。
	}
	
}
//ドロー
void CObjBom::Draw()
{
	//描画カラー情報
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//動くアニメーション情報を登録
	int AniData[4] =
	{
		 0 , 1 , 2 , 1
	};

	//切り取り位置の設定
	src.m_top	= IMAAGE_CUT_SIZE * m_ani_frame_change;
	src.m_left	= IMAAGE_CUT_SIZE * AniData[m_ani_frame];
	src.m_right	= src.m_left + IMAAGE_CUT_SIZE;
	src.m_bottom= IMAAGE_CUT_SIZE + src.m_top;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top	= m_y;
	dst.m_left =  m_x + block->GetScroll();
	dst.m_right = BOM_SIZE + m_x + block->GetScroll();
	dst.m_bottom= BOM_SIZE + m_y;

	//描画
	Draw::Draw(0,&src,&dst,c,0.0f);

}
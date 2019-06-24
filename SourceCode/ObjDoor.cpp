//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"
#include "Trace.h"

#include "UtilityModule.h"
#include "GameHead.h"
#include "ObjDoor.h"

//使用するネームスペース
using namespace GameL;

CObjDoor::CObjDoor(float x, float y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjDoor::Init()
{
	m_opening_and_closing = false;
	m_door_hit_test_time = 0;
	m_door_hit_test_max_time =150;
	m_hit_blast = false;
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this,m_x,m_y,DOOR_SIZE, DOOR_SIZE,ELEMENT_WHITE,OBJ_DOOR,1);
}
//アクション
void CObjDoor::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//敵が完全にいなくなったら
	if(((UserData*)Save::GetData())->mEnemyNumber == 0)
	{
		//ドア開
		m_opening_and_closing = true;
	}
	//敵が残っていたら
	else
	{
		//ドア閉
		m_opening_and_closing = false;
	}

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + block->GetScroll(),m_y);

	//ドアの当たり判定時間が０
	if(m_door_hit_test_time == 0)
	{
		//爆風オブジェクトに当たっていたら。
		if(hit->CheckObjNameHit(OBJ_BLAST) != nullptr)
		{
			m_hit_blast = true;
			Audio::Start(4);//4番曲をスタート
		}
	}

	//爆風に当たったら
	if(m_hit_blast == true)
	{
		//ドアから敵が出てくるまでの時間を加算
		m_door_hit_test_time++;
	}

	//時間切れになったら
	if(m_door_hit_test_time > m_door_hit_test_max_time)
	{
		//１～１００の間でランダムに値を代入
		int random = GetRandom(1,100);
		//敵が大量に出現
		for(int enemy_num = 0; enemy_num < 4; enemy_num++)
		{
			//９０％の確立でバロンが出現
			if (random < 90)
			{
				//バロン(敵)作成
				CObjBarom* obj_barom = new CObjBarom(m_x, m_y);
				Objs::InsertObj(obj_barom, OBJ_BAROM, 10);
			}
			//１０％の確立でポンタンが出現
			else
			{
				//ポンタン(敵)作成
				CObjPontan* obj_pontan = new CObjPontan(m_x, m_y);
				Objs::InsertObj(obj_pontan, OBJ_PONTAN, 10);
			}

			//敵追加
			((UserData*)Save::GetData())->mEnemyNumber++;
		}
		
		m_hit_blast = false;
		m_door_hit_test_time = 0;
	}

	//ドアが開いていたら
	if(m_opening_and_closing == true)
	{
		//主人公に触れていたら
		if(hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			//ドアに爆風があたていなかったら
			if (m_hit_blast == false)
			{
				//指定したステージをクリアしたらゲームクリア
				if (((UserData*)Save::GetData())->mStageNumber == MAX_STAGE)
				{
					//シーン(ゲームクリア)呼び出し
					Scene::SetScene(new CSceneGameClear());
				}
				else
				{
					//ステージクリアしたので次のステージへ
					((UserData*)Save::GetData())->mStageNumber++;
					//シーン(ステージ変更)呼び出し
					Scene::SetScene(new CSceneStageChange());
				}
			}
		}
	}

	
}
//ドロー
void CObjDoor::Draw()
{
	//描画カラー情報
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//ドアが開いていないときの切り取り値
	if (m_opening_and_closing == false)
	{
		//切り取り位置の設定
		src.m_top = 0;
		src.m_left = 0;
		src.m_right = src.m_left + 40.0f;
		src.m_bottom = 40.0f + src.m_top;
	}
	else 
	{
		//切り取り位置の設定
		src.m_top = 0;
		src.m_left = 40.0f;
		src.m_right = src.m_left + 40.0f;
		src.m_bottom = 40.0f + src.m_top;
	}


	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top	= m_y;
	dst.m_left =  m_x + block->GetScroll();
	dst.m_right = BOM_SIZE + m_x + block->GetScroll();
	dst.m_bottom= BOM_SIZE + m_y;

	//描画
	Draw::Draw(6,&src,&dst,c,0.0f);

}
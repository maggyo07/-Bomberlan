//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "Trace.h"

#include "UtilityModule.h"
#include "GameHead.h"
#include "ObjBarom.h"

//使用するネームスペース
using namespace GameL;

CObjBarom::CObjBarom(float x, float y)
{
	m_x = x;	//位置
	m_y = y;
}
//イニシャライズ
void CObjBarom::Init()
{
	m_vx = 0.0f;	//ベクトル
	m_vy = 0.0f;

	m_posture = 1.0f; //右向き1.0f 左向き0.0f

	m_ani_time = 0;
	m_ani_frame = 0;	//静止フレームを初期にする

	m_speed_power = 1.0f;//通常速度

	m_ani_max_time = 10;	//アニメーション間隔幅

	m_death_flag = false; //死亡フラグ　true:爆風に触れたとき	false:爆風に触れていない時

	m_death_time = 0;	//死亡フラグがたった後の時間

	//blockとの衝撃状態確認用
	m_hit_up	=false;
	m_hit_down	=false;
	m_hit_left	=false;
	m_hit_right	=false;

	m_bom_hit_test = true;//ボム判定健在

	m_breakable_block_hit_test = true;//破壊可能ブロック判定健在

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this,m_x,m_y,BAROM_SIZE, BAROM_SIZE,ELEMENT_ENEMY,OBJ_BAROM,1);

	m_time = BLOCK_SIZE / m_speed_power * 2;
}
//アクション
void CObjBarom::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	m_time++;
	m_ani_time++;

	//当たり判定情報更新
	HitTestInformation(m_x,m_y,&m_hit_up,&m_hit_down,&m_hit_left,&m_hit_right,m_bom_hit_test,m_breakable_block_hit_test);
	
	//2ブロック分移動したら
	if(m_time >= BLOCK_SIZE / m_speed_power * 2)
	{
		//移動できる方向にランダムで移動
		MovableTargetRandomByMove(&m_vx,&m_vy,m_speed_power,m_hit_up,m_hit_down,m_hit_left,m_hit_right);
		m_time = 0;
	}

	//ブロックとの当たり判定実行
	block->BlockHit(&m_x, &m_y, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		m_bom_hit_test,m_breakable_block_hit_test,&m_speed_power
	);

	//HitBoxの情報
	CHitBox* hit = Hits::GetHitBox(this);

	//爆風に触れていなかったら
	if(m_death_flag == false)
	{
		m_x += m_vx;
		m_y += m_vy;

		//x方向への移動量が０より小さかったら
		if(m_vx < 0)
		{
			//左向き
			m_posture = 0.0f;
		}
		//x方向への移動量が0より大きかったら
		else if(m_vx > 0)
		{
			//右向き
			m_posture = 1.0f;
		}

		//アニメーションーーーー
		if(m_ani_time > m_ani_max_time)
		{
			m_ani_time = 0;
			m_ani_frame++;
		}

		if(m_ani_frame >= 4)
		{
			m_ani_frame = 0;
		}
		//－－－－－－－－－－－
		//HitBoxの位置の変更
		hit->SetPos(m_x + block->GetScroll(),m_y);
	}
	//爆風に触れていたら
	else
	{
		//死亡フラグが立ったので
		m_death_time++;
		//HitBoxの位置の変更
		hit->SetPos(-50,0);//HetBoxなんていらない

		if(m_death_time == 50)
		{
			m_ani_frame++;
		}
		else if(m_death_time == 60)
		{
			m_ani_frame++;
		}
		else if(m_death_time == 70)
		{
			m_ani_frame++;
		}
		else if(m_death_time == 80)
		{
			m_ani_frame++;
		}
		else if(m_death_time == 90)
		{
			((UserData*)Save::GetData())->mEnemyNumber--;
			((UserData*)Save::GetData())->mScore += BAROM_SCORE;

			//スコアオブジェクト作成
			CObjScore* obj_score = new CObjScore(BAROM_SCORE,m_x, m_y);
			Objs::InsertObj(obj_score, OBJ_SCORE, 10);

			this->SetStatus(false);		//自身に消滅命令を出す。
			Hits::DeleteHitBox(this);	//敵機が所有するHitBoxに消滅する。
		}

	}

	//爆風に接触していたら
	if(hit->CheckObjNameHit(OBJ_BLAST) != nullptr)
	{
		m_death_flag = true;//爆風に触れたので
		m_ani_frame = 0;
	}

}
//ドロー
void CObjBarom::Draw()
{
	//歩く、走るアニメーション情報を登録
	int AniData[4];
	//死亡フラグが立っていなかったら
	if(m_death_flag == false)
	{
		//死亡フラグOFFのときのアニメーション情報
		AniData[0] = 0;
		AniData[1] = 1;
		AniData[2] = 2;
		AniData[3] = 1;
	}
	//死亡フラグが立っていたら
	else
	{
		//死亡フラグONのときのアニメーション情報
		AniData[0] = 3;
		AniData[1] = 4;
		AniData[2] = 5;
		AniData[3] = 6;
	}

	//描画カラー情報
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top	= ENEMY_CUT_SIZE * 0;
	src.m_left	= ENEMY_CUT_SIZE * AniData[m_ani_frame];
	src.m_right	= ENEMY_CUT_SIZE + src.m_left;
	src.m_bottom= src.m_top + ENEMY_CUT_SIZE;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	//表示位置の設定
	dst.m_top	= 0.0f + m_y;
	dst.m_left	= (BAROM_SIZE * m_posture )+ m_x + block->GetScroll();
	dst.m_right	= (BAROM_SIZE - BAROM_SIZE * m_posture )+ m_x + block->GetScroll();
	dst.m_bottom= BAROM_SIZE + m_y;

	//描画
	Draw::Draw(4,&src,&dst,c,0.0f);

}
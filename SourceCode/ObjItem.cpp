//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "Trace.h"

#include "UtilityModule.h"
#include "GameHead.h"
#include "ObjItem.h"

//使用するネームスペース
using namespace GameL;

CObjItem::CObjItem(float x, float y,ITEM id)
{
	m_x = x;
	m_y = y;

	//アイテムの種類
	m_item_id = id;
}

//イニシャライズ
void CObjItem::Init()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//オブジェクトの種類代入用
	OBJ_NAME obj_id;

	//各IDごとのオブジェクト種類代入
	if(m_item_id == FIRE_UP)
	{
		obj_id = OBJ_FIRE_UP;
	}
	else if(m_item_id == BOM_UP)
	{
		obj_id = OBJ_BOM_UP;
	}
	else if(m_item_id == REMOTE_CONTROLLER)
	{
		obj_id = OBJ_REMOTE_CONTROLLER;
	}
	else if(m_item_id == SKATE)
	{
		obj_id = OBJ_SKATE;
	}
	else if(m_item_id == BOM_SLIPPING_THROUGH)
	{
		obj_id = OBJ_BOM_SLIPPING_THROUGH;
	}
	else if(m_item_id == DESTRUCTALE_BLOCK_SLIPPING_THROUGH)
	{
		obj_id = OBJ_DESTRUCTALE_BLOCK_SLIPPING_THROUGH;
	}
	else if(m_item_id == FIRE_MAN)
	{
		obj_id = OBJ_FIRE_MAN;
	}
	else if(m_item_id == PERFECT_MAN)
	{
		obj_id = OBJ_PERFECT_MAN;
	}

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this,m_x + (block->GetScroll()),m_y,ITEM_SIZE, ITEM_SIZE,ELEMENT_ITEM,obj_id,1);

	m_ani_time = 0;
	m_ani_frame = 0;
	m_ani_start = false;
}
//アクション
void CObjItem::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//HitBox情報
	CHitBox* hit = Hits::GetHitBox(this);

	//爆風オブジェクトに接触していたら
	if(hit->CheckObjNameHit(OBJ_BLAST) != nullptr)
	{
		//アニメーションスタート
		m_ani_start = true;
	}

	//アニメーションスタートフラグが立っていたら
	if(m_ani_start == true)
	{
		//アニメーションタイム加算
		m_ani_time++;
		//HitBoxの位置の変更
		//HitBoxがあったらアニメーション中に取れてしまうのでどっかに移動
		hit->SetPos(-50, 0);
	}
	//アニメーションスタートフラグが立っていなかったら
	else
	{
		//HitBoxの位置の変更
		//通常の位置にHitBoxを配置
		hit->SetPos(m_x + block->GetScroll(), m_y);
	}

	//アニメーション----------
	//アニメーションタイムが１のとき(最初のアニメーション)
	if(m_ani_time == 1)
	{
		m_ani_frame++;
	}
	//アニメーションタイムが２０になったら(２回目のアニメーション)
	else if(m_ani_time == 20)
	{
		m_ani_frame++;
	}
	//アニメーションタイムが３０になったら(３回目のアニメション)
	else if(m_ani_time == 30)
	{
		m_ani_frame++;
	}
	//アニメーションタイムが50になったら
	else if(m_ani_time == 50)
	{
		//１～１００の間でランダムに値を入れる
		int random = GetRandom(1,100);

		//約２０％の確率で敵が出てくる(アイテムを燃やしたので天罰)
		if(random <= 20)
		{
			//パース(敵)作成
			CObjPerth* obj_perth = new CObjPerth(m_x, m_y);
			Objs::InsertObj(obj_perth, OBJ_PERTH, 10);

			//敵追加
			((UserData*)Save::GetData())->mEnemyNumber++;
		}

		//破棄
		this->SetStatus(false);		//自身に消滅命令を出す。
		Hits::DeleteHitBox(this);	//自身が所有するHitBoxに消滅する。
	}
	
	//------------------------

	//主人公に取られたら
	if(hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		//アイテムのスコア加算
		((UserData*)Save::GetData())->mScore += ITEM_SCORE;

		//スコアオブジェクト作成
		CObjScore* obj_score = new CObjScore(ITEM_SCORE,m_x, m_y);
		Objs::InsertObj(obj_score, OBJ_SCORE, 10);

		this->SetStatus(false);		//自身に消滅命令を出す。
		Hits::DeleteHitBox(this);	//自身が所有するHitBoxに消滅する。
	}
	
}
//ドロー
void CObjItem::Draw()
{
	//描画カラー情報
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top	= ITEM_CUT_SIZE * m_item_id;
	src.m_left	= ITEM_CUT_SIZE * m_ani_frame;
	src.m_right	= src.m_left + ITEM_CUT_SIZE;
	src.m_bottom= ITEM_CUT_SIZE + src.m_top;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top	= m_y;
	dst.m_left =  m_x + block->GetScroll();
	dst.m_right = ITEM_SIZE + m_x + block->GetScroll();
	dst.m_bottom= ITEM_SIZE + m_y;

	//描画
	Draw::Draw(2,&src,&dst,c,0.0f);

}
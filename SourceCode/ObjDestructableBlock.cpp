//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "UtilityModule.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjDestructableBlock.h"

//使用するネームスペース
using namespace GameL;

CObjDestructableBlock::CObjDestructableBlock(float x, float y,bool door, ITEM id)
{
	m_x = x;	//位置
	m_y = y;
	
	TRACE(L"コンストラクタ\nm_x=%f\nm_y=%f\ndoor=%d\n", m_x, m_y,door);
	m_with_door = door;//ドア付かどうか true:ドア付	false:ドア無し
	m_item_id = id;	//何のアイテムを出すブロックかどうか
}
//イニシャライズ
void CObjDestructableBlock::Init()
{
	TRACE(L"アクション\nm_x=%f\nm_y=%f\n",m_x,m_y);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_FIELD, OBJ_DESTRUCTADLE_BLOCK, 1);

	m_hit_erase = false;//当たり判定を消さない

	m_ani_time = 0;//アニメーションフレーム動作間隔
	m_ani_frame = 0;//描画フレーム
	m_ani_max_time = 10;	//アニメーション動作間隔最大値

}
//アクション
void CObjDestructableBlock::Action()
{

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + block->GetScroll(), m_y);

	block->GetMap(m_map);//マップ情報習得

	int x = ((int)m_x) / BLOCK_SIZE;
	int y = ((int)m_y) / BLOCK_SIZE;
	
	//自身の場所が11だったらアニメーションスタート
	if (m_map[y][x] == 11)
	{
		m_ani_time++;

	}

	if(m_ani_time >= m_ani_max_time)
	{
		m_ani_time = 0;
		m_ani_frame++;

	}

	if(m_ani_frame >= 4)
	{
		//アイテムが出るブロックであればアイテムを出す。
		if(m_item_id != NOT_ITEM)
		{
			
			//爆弾アップ(アイテム)オブジェクト作成
			CObjItem* obj_item = new CObjItem(m_x, m_y,m_item_id);//爆弾アップ(アイテム)オブジェクト作成
			Objs::InsertObj(obj_item, OBJ_BOM_UP, 10);	//爆弾アップ(アイテム)オブジェクト登録
			
		}

		block->GetMap(m_map);//マップ情報習得
		m_map[y][x] = 0;	//消すので自身のマップ情報(11)を消す。
		block->MapChange(m_map);//マップ情報更新

		//ドア付だった場合
		if(m_with_door == true)
		{
			//ドア作成
			CObjDoor* obj_door = new CObjDoor(m_x,m_y);
			Objs::InsertObj(obj_door, OBJ_CONDORIA, 10);
		}
		this->SetStatus(false);		//自身に消滅命令を出す。
		Hits::DeleteHitBox(this);	//敵機が所有するHitBoxに消滅する。
	}

}
//ドロー
void CObjDestructableBlock::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 432.0f - (BLOCK_SIZE * m_ani_frame);
	src.m_right = IMAAGE_CUT_SIZE + src.m_left;
	src.m_bottom = src.m_top + IMAAGE_CUT_SIZE;
	
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//表示位置の設定
	dst.m_top = m_y;
	dst.m_left = m_x + block->GetScroll();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//描画
	Draw::Draw(0, &src, &dst, c, 0.0f);

}
#pragma once
#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：破壊可能ブロック
class CObjDestructableBlock : public CObj
{
public:
	
	CObjDestructableBlock(float x, float y,bool door, ITEM id);
	/*CObjDestructableBlock(float x, float y, bool door) { CObjDestructableBlock(x,y,door,NOT_ITEM); }
	CObjDestructableBlock(float x, float y, ITEM id) { CObjDestructableBlock(x, y, false, id); }//使えねー
	CObjDestructableBlock(float x, float y) { CObjDestructableBlock(x, y, false, NOT_ITEM); }*/
	~CObjDestructableBlock() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	bool GetHitErase() { return m_hit_erase; }//消すかどうかを判定用

private:
	float m_x;//位置
	float m_y;
	bool m_hit_erase;//当たり判定を消す

	int m_map[MAP_Y][MAP_X];

	int m_ani_time; //アニメーションフレーム動作間隔
	int m_ani_frame;//描画フレーム

	float m_ani_max_time;	//アニメーション動作間隔最大値

	bool m_with_door;		//扉が隠れているかどうか

	ITEM m_item_id;		//何のアイテムを出すブロックか。-1＝アイテムを出さない　
};
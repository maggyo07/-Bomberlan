#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：アイテム
class CObjItem : public CObj
{
public :
	CObjItem(float x,float y,ITEM id);
	~CObjItem(){};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

private:
	float m_x;//位置
	float m_y;

	int m_ani_time;		//アニメーションフレーム動作間隔
	int m_ani_frame;	//描画フレーム

	bool m_ani_start;//アニメーションスタート

	int m_item_id;	//アイテムの種類
};
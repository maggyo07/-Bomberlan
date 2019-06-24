#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;



//オブジェクト：ボム
class CObjBom : public CObj
{
public :
	CObjBom(float x, float y);
	~CObjBom(){};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	float m_x;		//位置
	float m_y;

	int m_ani_time;		//アニメーションフレーム動作間隔
	int m_ani_frame;	//描画フレーム

	int m_time;	//時間

	float m_ani_max_time;	//アニメーション動作間隔最大値

	int m_ani_frame_change; //アニメーション切り替え用

	int m_hero_bom_power; //主人公のボムパワー

	int m_map[MAP_Y][MAP_X];
};
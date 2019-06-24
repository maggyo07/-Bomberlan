#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

#define RECTANGLE 5.0//どれぐらい細くするか


enum DIRECTION
	{
		RIGHT,
		LEFT,
		UP,
		DOWN,
		IN_SITU,
	};

//オブジェクト：爆風
class CObjBlast : public CObj
{
public :
	CObjBlast(float x, float y,int direction, int magnification);
	~CObjBlast(){};
	void SetLastBlast(bool last_blast){m_last_blast = last_blast;}
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

private:
	float m_x;//位置
	float m_y;
	int m_direction;//方向
	bool m_last_blast;//最後の爆風
	int m_ani_data;//動くアニメーションの動き

	int m_ani_time;		//アニメーションフレーム動作間隔
	int m_ani_max_time;		//アニメーションフレーム動作間隔最大値

	int m_map[MAP_Y][MAP_X];

};
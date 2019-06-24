#pragma once
#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：方向(ダイクストラ法のノード方向確認用)
class CObjDirection : public CObj
{
public:
	CObjDirection(float x,float y,int directon_x, int directon_y);
	~CObjDirection() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	float m_x;
	float m_y;
	int m_directon_x;	//方向
	int m_directon_y;
	int m_posture;//姿
	int m_time;
};
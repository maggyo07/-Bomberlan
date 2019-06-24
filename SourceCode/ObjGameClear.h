#pragma once
#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ゲームクリア
class CObjGameClear : public CObj
{
public:
	CObjGameClear() {};
	~CObjGameClear() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

private:
	float m_x;
	float m_y;

	float m_vx;
	float m_vy;

	int m_time;

	int m_ani_time;
	int m_ani_max_time;
	int m_ani_frame;

	bool m_stop;//移動・アニメーション停止用	true：停止	false：通常

	int m_posture;

};
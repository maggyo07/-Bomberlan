#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//指定値のステージをクリアするとゲームクリア
#define MAX_STAGE 10

//オブジェクト：ドア(扉)
class CObjDoor : public CObj
{
public :
	CObjDoor(float x,float y);
	~CObjDoor(){};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

private:
	//位置
	float m_x;
	float m_y;

	//敵の数
	int m_enemy_number;

	//ドアの開閉	true:開	false:閉
	bool m_opening_and_closing;

	//ドアの当たり判定時間
	int m_door_hit_test_time;
	//ドアの当たり判定時間の最大値
	int m_door_hit_test_max_time;
	//爆風オブジェクトに当たっているかどうか
	bool m_hit_blast;//true:当たっている　false:当たっていない
};
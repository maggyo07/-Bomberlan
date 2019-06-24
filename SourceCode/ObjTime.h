#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：時間
class CObjTime : public CObj
{
public :
	CObjTime(int max_time);
	~CObjTime(){};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	int GetTime(){return m_time;}

private:
	int m_time;		//時間
	bool m_out_put_enemy;//敵を出すかどうか	true：出す	false:出さない
	int m_enemy_time; //敵を出すと判断してからの時間経過

	void AllocablePosition(float* x,float* y);
};
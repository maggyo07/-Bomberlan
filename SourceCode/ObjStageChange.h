#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ステージ変更
class CObjStageChange : public CObj
{
public :
	CObjStageChange(){};
	~CObjStageChange(){};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

private:
	int m_time;
};
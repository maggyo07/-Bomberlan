#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：説明
class CObjDescription : public CObj
{
public :
	CObjDescription(){};
	~CObjDescription(){};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
};
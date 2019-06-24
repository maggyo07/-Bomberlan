#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjTitle:public CObj
{
public:
	CObjTitle(){};
	~CObjTitle(){};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	bool m_key_flag;	//キーフラグ
	bool m_start_or_continue;//現在のカーソルの位置　true = start::false = description
};
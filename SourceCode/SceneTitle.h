#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームメイン
class CSceneTitle:public CScene
{
public:
	CSceneTitle();
	~CSceneTitle();
	void InitScene();//ゲームメイン初期化メソッド
	void Scene();   //ゲームメインの実行中メソッド
private:
};
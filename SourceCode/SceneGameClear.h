#pragma once
#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームクリア
class CSceneGameClear :public CScene
{
public:
	CSceneGameClear();
	~CSceneGameClear();
	void InitScene();//ゲームクリア初期化メソッド
	void Scene();   //ゲームクリアの実行中メソッド
private:
};
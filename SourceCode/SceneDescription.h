#pragma once
#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：説明
class CSceneDescription :public CScene
{
public:
	CSceneDescription();
	~CSceneDescription();
	void InitScene();//ゲームクリア初期化メソッド
	void Scene();   //ゲームクリアの実行中メソッド
private:
};
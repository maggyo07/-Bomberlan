#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//MAP_Y、MAP_XはBlockオブジェクトのを採用
#include "ObjBlock.h"

//使用するネームスペース
using namespace GameL;

//シーン：ステージ変更
class CSceneStageChange:public CScene
{
public:
	CSceneStageChange();
	~CSceneStageChange();
	void InitScene();//ステージ変更初期化メソッド
	void Scene();   //ステージ変更の実行中メソッド
private:
};
#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//MAP_Y、MAP_XはBlockオブジェクトのを採用
#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームメイン
class CSceneMain :public CScene
{
public:
	CSceneMain();
	~CSceneMain();
	void InitScene();//ゲームメイン初期化メソッド
	void Scene();   //ゲームメインの実行中メソッド
private: 
	void WorldDataCreation();
	void MapRandomByValueAssignment(int place_locate, int locate_object, int locate_count);
	int m_map[MAP_Y][MAP_X];
};
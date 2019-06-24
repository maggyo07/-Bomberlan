//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"


//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneDescription.h"
#include "GameHead.h"

//コントラスト
CSceneDescription::CSceneDescription()
{
}
//デストラスト
CSceneDescription::~CSceneDescription()
{
}

//ゲームメイン初期化メソッド
void CSceneDescription::InitScene()
{
	//外部グラフィックファイルを読み込み0番に登録(320*320ピクセル)
	Draw::LoadImageW(L"item.png",0, TEX_SIZE_320);

	//ゲームクリアオブジェクト作成
	CObjDescription* obj = new CObjDescription();
	Objs::InsertObj(obj, OBJ_DESCRIPTION, 2);
}

//ゲームメイン実行中メソッド
void CSceneDescription::Scene()
{
}
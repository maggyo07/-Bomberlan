//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"
//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneStageChange.h"
#include "GameHead.h"

//コントラスト
CSceneStageChange::CSceneStageChange()
{

}
//デストラスト
CSceneStageChange::~CSceneStageChange()
{

}

//ゲームメイン初期化メソッド
void CSceneStageChange::InitScene()
{
	Audio::LoadAudio(0, L"StageChange.wav",EFFECT);
	Audio::Start(0);//0番曲をスタート

	//ステージ変更オブジェクト作成
	CObjStageChange* obj_stage_change= new CObjStageChange();	//ステージ変更オブジェクト作成
	Objs::InsertObj(obj_stage_change,OBJ_STAGE_CHANGE,10);	//ステージ変更オブジェト登録
}

//ゲームメイン実行中メソッド
void CSceneStageChange::Scene()
{
	
}
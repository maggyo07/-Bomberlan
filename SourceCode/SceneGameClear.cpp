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
#include "SceneGameClear.h"
#include "GameHead.h"

//コントラスト
CSceneGameClear::CSceneGameClear()
{
}
//デストラスト
CSceneGameClear::~CSceneGameClear()
{

}

//ゲームメイン初期化メソッド
void CSceneGameClear::InitScene()
{
	//外部グラフィックファイルを読み込み0番に登録（800*800ﾋﾟｸｾﾙ）
	Draw::LoadImage(L"GameClearBack.png", 0, TEX_SIZE_800);

	//外部グラフィックファイルを読み込み1番に登録（512*512ﾋﾟｸｾﾙ）
	Draw::LoadImage(L"image.png", 1, TEX_SIZE_512);

	//外部グラフィックファイルを読み込み2番に登録（120*120ﾋﾟｸｾﾙ）
	Draw::LoadImage(L"LoadRunnerHero.png", 2, TEX_SIZE_120);

	//音楽情報を0番に読み込み
	Audio::LoadAudio(0, L"GameClear.wav", BACK_MUSIC);

	//バックミュージックスタート
	Audio::Start(0); //音楽スタート

	//ゲームクリアオブジェクト作成
	CObjGameClear* obj_game_clear = new CObjGameClear();
	Objs::InsertObj(obj_game_clear, OBJ_GAME_CLEAR, 2);
}

//ゲームメイン実行中メソッド
void CSceneGameClear::Scene()
{
}
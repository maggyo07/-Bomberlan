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
#include "SceneTitle.h"
#include "GameHead.h"

//コントラスト
CSceneTitle::CSceneTitle()
{

}
//デストラスト
CSceneTitle::~CSceneTitle()
{

}

//ゲームメイン初期化メソッド
void CSceneTitle::InitScene()
{
	//ロードするとスコアが変わってしまうのでその前に記録
	int score = ((UserData*)Save::GetData())->mScore;

	//ロード
	Save::Open();//同フォルダ「UserData」からデータ取得
	//過去のスコアより現在のスコアのほうが高ければ更新
	if (score > ((UserData*)Save::GetData())->mMaxScore)
	{
		//スコア更新　
		((UserData*)Save::GetData())->mMaxScore = score;
	}
	//セーブ
	Save::Seve();//UserDataの情報を同フォルダ「UserData」を作成
	
	//UserDataの情報を初期化------
	((UserData*)Save::GetData())->mScore = 0;
	((UserData*)Save::GetData())->mStageNumber = 1;
	((UserData*)Save::GetData())->mBomUpNum = 0;
	((UserData*)Save::GetData())->mFireUpNum = 0;
	((UserData*)Save::GetData())->mSkateNum = 0;
	((UserData*)Save::GetData())->mBomSlippingThrough = false;
	((UserData*)Save::GetData())->mDestructableBlockSlippingThrough = false;
	((UserData*)Save::GetData())->mFireMan = false;
	((UserData*)Save::GetData())->mRemoteController = false;
	//----------------------------

	//外部グラフィックファイルを読み込み0番に登録（512*512ﾋﾟｸｾﾙ）
	Draw::LoadImage(L"Title.png", 0, TEX_SIZE_256);

	//音楽情報を0番に読み込み
	Audio::LoadAudio(0, L"Title.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(1, L"CursorSelection.wav", SOUND_TYPE::EFFECT);

	//バックミュージックスタート
	float Volume = Audio::VolumeMaster(0.8f);//マスターボリュームを0.8下げる
	Audio::Start(0); //音楽スタート

	//タイトルオブジェクト作成
	CObjTitle* obj= new CObjTitle();	//タイトルオブジェクト作成
	Objs::InsertObj(obj,OBJ_TITLE,10);	//タイトルオブジェト登録
	

}

//ゲームメイン実行中メソッド
void CSceneTitle::Scene()
{
	
}
//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"
#include "Trace.h"


//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"
#include "UtilityModule.h"
#include <time.h>
//コントラスト
CSceneMain::CSceneMain()
{
}
//デストラスト
CSceneMain::~CSceneMain()
{

}

//ゲームメイン初期化メソッド
void CSceneMain::InitScene()
{
	//敵の数初期化
	((UserData*)Save::GetData())->mEnemyNumber = 0;

	//ワールドデータ作成
	CSceneMain::WorldDataCreation();

	//外部グラフィックファイルを読み込み0番に登録（512*512ﾋﾟｸｾﾙ）
	Draw::LoadImage(L"image.png", 0, TEX_SIZE_512);

	//外部グラフィックファイルを読み込み１番に登録(128*128ピクセル)
	Draw::LoadImageW(L"blast.png",1, TEX_SIZE_128);

	//外部グラフィックファイルを読み込み２番に登録(320*320ピクセル)
	Draw::LoadImageW(L"item.png",2, TEX_SIZE_320);

	//外部グラフィックファイルを読み込み3番に登録(800*800ピクセル)
	Draw::LoadImageW(L"Background_03.png",3, TEX_SIZE_800);

	//外部グラフィックファイルを読み込み4番に登録(320*320ピクセル)
	Draw::LoadImageW(L"enemy.png",4, TEX_SIZE_320);

	//外部グラフィックファイルを読み込み5番に登録(128*128ピクセル)
	Draw::LoadImageW(L"direction.png", 5, TEX_SIZE_128);

	//外部グラフィックファイルを読み込み6番に登録(80*80ピクセル)
	Draw::LoadImageW(L"door.png", 6, TEX_SIZE_80);

	//音楽情報を読み込み
	Audio::LoadAudio(0, L"main.wav", BACK_MUSIC);
	Audio::LoadAudio(1, L"BomBursting.wav", EFFECT);
	Audio::LoadAudio(2, L"mainTimeOver.wav", BACK_MUSIC);
	Audio::LoadAudio(3, L"ItemsObtain.wav", EFFECT);
	Audio::LoadAudio(4, L"DoorBlastHit.wav", EFFECT);
	Audio::LoadAudio(5, L"InvincibleState.wav", BACK_MUSIC);
	Audio::LoadAudio(6, L"DeadMoment.wav", EFFECT);
	Audio::LoadAudio(7, L"DeadAfter.wav", EFFECT);
	//バックミュージックスタート
	Audio::Start(0); //音楽スタート

	//ブロックオブジェクト作成
	CObjBlock* obj_block = new CObjBlock(m_map);
	Objs::InsertObj(obj_block, OBJ_BLOCK, 9);

	//主人公オブジェクト作成
	CObjHero* obj_hero = new CObjHero();	//主人公オブジェクト作成
	Objs::InsertObj(obj_hero, OBJ_HERO, 10);	//主人公オブジェト登録

	//バックグラフィックオブジェクト作成
	CObjBackground* obj_background = new CObjBackground();
	Objs::InsertObj(obj_background, OBJ_BACKGROUND, 1);

	//時間オブジェクト作成
	CObjTime* obj_time = new CObjTime(200);
	Objs::InsertObj(obj_time, OBJ_TIME, 2);

	//スコアオブジェクト作成
	CObjScore* obj_score = new CObjScore();
	Objs::InsertObj(obj_score, OBJ_SCORE, 2);
}

//ゲームメイン実行中メソッド
void CSceneMain::Scene()
{
}
//関数　ワールドデータ作成
void CSceneMain::WorldDataCreation()
{
	//外部データの読み込み(ステージ情報)
	unique_ptr<wchar_t> p;//ステージ情報ポインター
	int size;			  //ステージ情報の大きさ

	p = Save::ExternalDataOpen(L"Debug.csv", &size);//外部データ読み込み：デバック用

	int count = 1;

	for (int map_y = 0; map_y < MAP_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_X; map_x++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			m_map[map_y][map_x] = w;
				count += 2;
		}
	}

	//主人公の初期位置またはその周辺に-2を入れる
	//(これがなければシーンメインのMapRandomByValueAssignment関数で空白が指定場所となった場合主人公の初期位置に設置されてしまうので-2が入っている)
	m_map[5][1] = -2;//主人公の初期位置
	m_map[6][1] = -2;//主人公の初期位置の下
	m_map[5][2] = -2;//主人公の初期位置の右

	//ランダムで値を入れる用
	int random;

	//空白の中から破壊可能ブロックをランダムで配置
	random = GetRandom(70, 90);
	MapRandomByValueAssignment(0, 2, random);

	//破壊可能ブロックの中からドア付き破壊可能ブロックをランダムで決める
	MapRandomByValueAssignment(2, 3, 1);

	//空白ブロックの中から敵をランダムで配置する前に
	//主人公の近くに敵がいたら困るので主人公の初期位置の周囲5ます分に-2を入れる
	//＊この処理は破壊可能ブロック設置後にする
	for (int map_y = 5; map_y <= 5 + 5; map_y++)
	{
		for (int map_x = 1; map_x <= 1 + 5; map_x++)
		{
			if (m_map[map_y][map_x] == 0)
			{
				m_map[map_y][map_x] = -2;
			}
		}
	}

	//ステージごとの処理
	//アイテムブロックと敵の配置を決める
	switch (((UserData*)Save::GetData())->mStageNumber)
	{
	case 1:
		//破壊可能ブロックの中からファイアーアップ(アイテム)が出るブロックランダムで決める
		random = GetRandom(3, 5);
		MapRandomByValueAssignment(2, 12, random);

		//空白ブロックの中からバロン(敵）をランダムで配置する
		random = GetRandom(4, 6);
		MapRandomByValueAssignment(0, 20, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 2:
		//破壊可能ブロックの中からファイアーアップ(アイテム)が出るブロックランダムで決める
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 12, random);
		//破壊可能ブロックの中からボムアップ(アイテム)が出るブロックランダムで決める
		random = GetRandom(2, 3);
		MapRandomByValueAssignment(2, 13, random);

		//空白ブロックの中からバロン(敵）をランダムで配置する
		random = GetRandom(5, 8);
		MapRandomByValueAssignment(0, 20, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 3:
		//破壊可能ブロックの中からファイアーアップ(アイテム)が出るブロックランダムで決める
		random = GetRandom(0, 1);
		MapRandomByValueAssignment(2, 12, random);
		//破壊可能ブロックの中からボムアップ(アイテム)が出るブロックランダムで決める
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 13, random);

		//空白ブロックの中からバロン(敵）をランダムで配置する
		random = GetRandom(5, 8);
		MapRandomByValueAssignment(0, 20, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//空白ブロックの中からダル(敵）をランダムで配置する
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(0, 22, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 4:
		//破壊可能ブロックの中からボムアップ(アイテム)が出るブロックランダムで決める
		random = GetRandom(2, 3);
		MapRandomByValueAssignment(2, 13, random);
		//破壊可能ブロックの中からスケート(アイテム)が出るブロックランダムで決める
		random = GetRandom(2, 4);
		MapRandomByValueAssignment(2, 15, random);

		//空白ブロックの中からバロン(敵）をランダムで配置する
		random = GetRandom(5, 7);
		MapRandomByValueAssignment(0, 20, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//空白ブロックの中からダル(敵）をランダムで配置する
		random = GetRandom(2, 5);
		MapRandomByValueAssignment(0, 22, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 5:
		//破壊可能ブロックの中からボムすり抜け(アイテム)が出るブロックランダムで決める
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 16, random);
		//破壊可能ブロックの中から破壊可能ブロックすり抜け(アイテム)が出るブロックランダムで決める
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 17, random);

		//空白ブロックの中からダル(敵）をランダムで配置する
		random = GetRandom(3, 5);
		MapRandomByValueAssignment(0, 22, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//空白ブロックの中からミンボー(敵）をランダムで配置する
		random = GetRandom(2, 5);
		MapRandomByValueAssignment(0, 23, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 6:
		//破壊可能ブロックの中からファイアーアップ(アイテム)が出るブロックランダムで決める
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 12, random);
		//破壊可能ブロックの中からリモコン(アイテム)が出るブロックランダムで決める
		MapRandomByValueAssignment(2, 14, 1);

		//空白ブロックの中からミンボー(敵）をランダムで配置する
		random = GetRandom(3, 7);
		MapRandomByValueAssignment(0, 23, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//空白ブロックの中からコンドリア(敵）をランダムで配置する
		random = GetRandom(2, 5);
		MapRandomByValueAssignment(0, 24, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 7:
		//破壊可能ブロックの中からファイアーマン(アイテム)が出るブロックランダムで決める
		MapRandomByValueAssignment(2, 18, 1);
		//破壊可能ブロックの中からパーフェクトマン(アイテム)が出るブロックランダムで決める
		MapRandomByValueAssignment(2, 19, 1);

		//空白ブロックの中からコンドリア(敵）をランダムで配置する
		random = GetRandom(3, 7);
		MapRandomByValueAssignment(0, 24, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//空白ブロックの中からパース(敵）をランダムで配置する
		random = GetRandom(2, 3);
		MapRandomByValueAssignment(0, 26, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 8:
		//破壊可能ブロックの中からボムすり抜け(アイテム)が出るブロックランダムで決める
		MapRandomByValueAssignment(2, 16, 1);
		//破壊可能ブロックの中から破壊可能ブロックすり抜け(アイテム)が出るブロックランダムで決める
		MapRandomByValueAssignment(2, 17, 1);

		//空白ブロックの中からパース(敵）をランダムで配置する
		random = GetRandom(2, 3);
		MapRandomByValueAssignment(0, 26, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//空白ブロックの中からオバピー(敵）をランダムで配置する
		random = GetRandom(3, 4);
		MapRandomByValueAssignment(0, 25, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 9:
		//破壊可能ブロックの中からファイアーアップ(アイテム)が出るブロックランダムで決める
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 12, random);

		//空白ブロックの中からオバピー(敵）をランダムで配置する
		random = GetRandom(4, 6);
		MapRandomByValueAssignment(0, 25, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//空白ブロックの中からオニール(敵）をランダムで配置する
		random = GetRandom(3, 4);
		MapRandomByValueAssignment(0, 21, random);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 10:
		//破壊可能ブロックの中からボムアップ(アイテム)が出るブロックランダムで決める
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 13, random);

		//空白ブロックの中からバロン(敵）をランダムで配置する
		MapRandomByValueAssignment(0, 20, 2);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//空白ブロックの中からオニール(敵）をランダムで配置する
		MapRandomByValueAssignment(0, 21, 2);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//空白ブロックの中からダル(敵）をランダムで配置する
		MapRandomByValueAssignment(0, 22, 2);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//空白ブロックの中からミンボー(敵）をランダムで配置する
		MapRandomByValueAssignment(0, 23, 2);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//空白ブロックの中からコンドリア(敵）をランダムで配置する
		MapRandomByValueAssignment(0, 24, 2);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//空白ブロックの中からオバピー(敵）をランダムで配置する
		MapRandomByValueAssignment(0, 25, 2);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//空白ブロックの中からパース(敵）をランダムで配置する
		MapRandomByValueAssignment(0, 26, 2);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//空白ブロックの中からポンタン(敵）をランダムで配置する
		MapRandomByValueAssignment(0, 27, 1);
		//敵を配置した分加算
		((UserData*)Save::GetData())->mEnemyNumber += 1;
		break;

	}
}

//関数　マップにランダムで指定場所に指定物を指定した数代入する
//引数１	int place_locate	:指定場所(指定物を入れる場所)
//引数２	int locate_object	:指定物(指定した場所にランダムで指定物を指定数代入)
//引数３	int locate_count	:指定数(指定物を何個入れるか)
void CSceneMain::MapRandomByValueAssignment(int place_locate, int locate_object, int locate_count)
{
	//設置場所の数
	int place_locate_count = 0;

	//マップの中から指定されたオブジェクトの数を数える
	for(int y = 5;y < MAP_Y; y++)
	{
		for(int x = 0; x < MAP_X; x++)
		{
			//設置場所だと加算
			if(m_map[y][x] == place_locate)
			{
				place_locate_count++;
			}
		}
	}

	//ランダムで設置する場所を決めてその値を入れる
	int random_place_locate[100] = {0};
	int a;
	//設置場所よりも指定数(引数)が多かったら
	if (locate_count > place_locate_count)
	{
		//設置場所の数を入れる
		a = place_locate_count;
	}
	else
	{
		a = locate_count;
	}
	//設置する数分回す
	for(int i = 0; i < a; i++)
	{
		//設置可能場所をランダムで決める
		int random_place_locate_count = GetRandom(1, place_locate_count);

		//一度求めた値でないかを調べる
		for(int j = 0; j < 100; j++)
		{
			//一度求めた値だったらループを抜ける
			if(random_place_locate_count == random_place_locate[j])
			{
				i--;
				break;
			}

			//初めての値だと代入
			if (j == 99)
			{
				random_place_locate[i] = random_place_locate_count;
			}
		}
	}

	//設置場所の数を初期化
	place_locate_count = 0;

	
	for(int map_y = 5; map_y < MAP_Y; map_y++)
	{
		for(int map_x = 0; map_x < MAP_X; map_x++)
		{
			//設置するオブジェクトであれば
			if(m_map[map_y][map_x] == place_locate)
			{
				//加算
				place_locate_count++;

				for(int i = 0; i < 100 ; i++)
				{
					//同じ数値だったら
					if(place_locate_count == random_place_locate[i])
					{
						//その場所に設置するオブジェクトを代入
						m_map[map_y][map_x] = locate_object;
					}
				}
			}
		}
	}
}
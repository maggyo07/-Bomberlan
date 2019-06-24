#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_TITLE,
	OBJ_HERO,
	OBJ_BLOCK,
	OBJ_BACKGROUND,
	OBJ_TIME,
	OBJ_SCORE,
	OBJ_STAGE_CHANGE,
	OBJ_BOM,
	OBJ_BLAST,
	OBJ_DESTRUCTADLE_BLOCK,
	OBJ_MING_BO,
	OBJ_OBAPY,
	OBJ_DOOR,
	OBJ_GAME_CLEAR,
	OBJ_DESCRIPTION,
	
	//アイテムオブジェクト
	OBJ_FIRE_UP,
	OBJ_BOM_UP,
	OBJ_REMOTE_CONTROLLER,
	OBJ_SKATE,
	OBJ_BOM_SLIPPING_THROUGH,
	OBJ_DESTRUCTALE_BLOCK_SLIPPING_THROUGH,
	OBJ_FIRE_MAN,
	OBJ_PERFECT_MAN,
	//--------------------

	//敵オブジェクト
	OBJ_BAROM,
	OBJ_O_NEAL,
	OBJ_DULL,
	OBJ_CONDORIA,
	OBJ_PERTH,
	OBJ_PONTAN,
	//--------------------


};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	//セーブ＆ロードはシーンタイトル

	int mSeveData;	//サンプルセーブデータ　((UserData*)Save::GetData())->

	int mEnemyNumber;//敵の数		：初期化はシーンメイン

	int mScore;		//スコア		：初期化はシーンタイトル
	int mMaxScore;	//過去最大スコア：初期化はシーンタイトル

	int mStageNumber;//ステージ番号	：初期化はシーンタイトル

	int mFireUpNum;							//ファイアアップを何個とったかの情報			：初期化はシーンタイトル
	int mBomUpNum;							//ボムアップを何個取ったかの情報				：初期化はシーンタイトル
	int mSkateNum;							//スケートを何個とったかの情報					：初期化はシーンタイトル
	bool mRemoteController;					//リモコンを取ったかどうかの情報				：初期化はシーンタイトル
	bool mFireMan;							//ファイアーマンをとったかどうかの情報			：初期化はシーンタイトル
	bool mBomSlippingThrough;				//ボムすり抜けをとったかどうかの情報			：初期化はシーンタイトル
	bool mDestructableBlockSlippingThrough;	//破壊可能ブロックすり抜けをとったかどうかの情報：初期化はシーンタイトル
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--

//ノード(ダイクストラ法に使う)
typedef struct Node
{
	int node_x;//移動するべき方向X

	int node_y;//移動するべき方向Y

	int cost;//移動にかかるコスト

	bool flag;//調べるか調べないか。
};

//アイテムの種類　列挙
enum ITEM
{
	NOT_ITEM=-1,
	FIRE_UP,
	BOM_UP,
	REMOTE_CONTROLLER,
	SKATE,
	BOM_SLIPPING_THROUGH,
	DESTRUCTALE_BLOCK_SLIPPING_THROUGH,
	FIRE_MAN,
	PERFECT_MAN,
};

//------------------------------------------------

//ゲーム内で使用するマクロ------------------------
#define BLOCK_SIZE 40.0f
#define HERO_SIZE 40.0f
#define BOM_SIZE 40.0f
#define BLAST_SIZE 40.0f
#define DOOR_SIZE 40.0f

//敵サイズーーーーーー
#define BAROM_SIZE 40.0f
#define O_NEAL_SIZE 40.0f
#define DULL_SIZE 40.0f
#define MING_BO_SIZE 40.0f
#define OBAPY_SIZE 40.0f
#define CONDORIA_SIZE 40.0f
#define PERTH_SIZE 40.0f
#define PONTAN_SIZE 40.0f
//－－－－－－－－－－
//アイテムサイズーーー
#define ITEM_SIZE 40.0f
//－－－－－－－－－－

//切り取りサイズーーー
#define BLAST_CUT_SIZE 32.0f
#define ENEMY_CUT_SIZE 40.0f
#define IMAAGE_CUT_SIZE 40.0f
#define ITEM_CUT_SIZE 40.0f
//－－－－－－－－－－

//スコア系ーーーーーー

//敵のスコア
#define	BAROM_SCORE		100
#define	O_NEAL_SCORE	200
#define	DULL_SCORE		400
#define	MING_BO_SCORE	800
#define	OBAPY_SCORE		2000
#define	CONDORIA_SCORE	1000
#define PERTH_SCORE		4000
#define PONTAN_SCORE	8000
//アイテムのスコア
//－－－－－－－－－－
#define ITEM_SCORE		1000
//ーーーーーーーーーー
#define MAP_X 51
#define MAP_Y 15
#define SKATE_SPEED_POWER 0.2f	//スケート一個当たりの増加スピード量
//------------------------------------------------

//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
#include "ObjTitle.h"
#include "ObjHero.h"
#include "ObjBlock.h"
#include "ObjBom.h"
#include "ObjBlast.h"
#include "ObjDestructableBlock.h"
#include "ObjBackground.h"
#include "ObjTime.h"
#include "ObjDull.h"
#include "ObjDoor.h"
#include "ObjScore.h"
#include "ObjStageChange.h"
#include "ObjGameClear.h"
#include "ObjDescription.h"

#include "ObjBarom.h"
#include "ObjO_Neal.h"
#include "ObjDull.h"
#include "ObjMingBo.h"
#include "ObjObapy.h"
#include "ObjCondoria.h"
#include "ObjPerth.h"
#include "ObjPontan.h"

#include "ObjItem.h"

#include "ObjDirection.h"
//------------------------------------------------

//ゲームシーンクラスヘッダ-----------------------
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneStageChange.h"
#include "SceneGameClear.h"
#include "SceneDescription.h"
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START CSceneTitle
//#define SET_GAME_START CSceneGameClear
//-----------------------------------------------
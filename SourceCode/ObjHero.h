#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
//使用するネームスペース
using namespace GameL;

#define RECTANGLE 5.0//どれぐらい細くするか

//オブジェクト：主人公
class CObjHero : public CObj
{
public :
	CObjHero() {};
	~CObjHero(){};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	float GetX(){return m_px;}
	float GetY(){return m_py;}
	float GetVY(){return m_vy;}
	float GetVX(){return m_vx;}
	int GetBomPower(){return m_bom_power;}
	bool GetRemoteController(){return m_remote_controller;}

	void SetX(float x){m_px = x;}
	void SetY(float y){m_py = y;}
	void SetVY(float vy){m_vy = vy;}
	void SetVX(float vx){m_vx = vx;}

	void SetBomNum() { m_bom_num--; }

private:
	float m_px;	//位置
	float m_py;
	float m_vx;	//移動ベクトル
	float m_vy;
	int m_posture;//姿

	int m_ani_time; //アニメーションフレーム動作間隔
	int m_ani_frame;//描画フレーム

	float m_ani_max_time;	//アニメーション動作間隔最大値

	//blockとの衝撃状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool m_death_flag; //死亡フラグ　true:敵や爆風に触れたとき	false:敵や爆風に触れていない時

	int m_death_time;	//死亡フラグがたった後の時間

	float m_speed_power;//スピードパワー

	int m_bom_num;//ステージにあるボムの数

	int m_bom_max_num;//おける最大数

	int m_bom_power;//ボムの威力

	bool m_remote_controller;//リモコンON・OFF

	bool m_bom_hit_test;//ボム当たり判定。true:判定有り	false:判定無し

	bool m_breakable_block_hit_test;//破壊可能ブロック当たり判定。true:判定有り	false:判定無し

	bool m_enemy_hit_test;//敵当たり判定。true:判定有り	false:判定無し

	bool m_blast_hit_test;//爆風当たり判定。true:判定有り	false:判定無し

	bool m_get_fire_man;//ファイアーマンを取ったかどうか判定。true:取った	false:取っていない

	int m_parfect_man_time;//パーフェクトマンを取った後のタイム。(30秒で終了)

	bool m_get_parfect_man;//パーフェクトマンを取ったかどうか判定。true:取った	false:取っていない

	void GetItemsInformation(CHitBox* hit);//アイテムをとったか判定

	void KeyInput(CHitBox* hit);//キー入力
};
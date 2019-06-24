#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;



//オブジェクト：オバピー(敵)
class CObjObapy : public CObj
{
public :
	CObjObapy(float x, float y);
	~CObjObapy(){};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

private:
	float m_x;		//位置
	float m_y;
	float m_vx;		//移動ベクトル
	float m_vy;
	float m_posture;//姿

	int m_ani_time;		//アニメーションフレーム動作間隔
	int m_ani_frame;	//描画フレーム

	float m_speed_power;	//スピードパワー
	float m_ani_max_time;	//アニメーション動作間隔最大値

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool m_death_flag; //死亡フラグ　true:爆風に触れたとき	false:爆風に触れていない時

	int m_death_time;	//死亡フラグがたった後の時間

	bool m_bom_hit_test;//ボム当たり判定。true:判定有り	false:判定無し

	bool m_breakable_block_hit_test;//破壊可能ブロック当たり判定。true:判定有り	false:判定無し

	//時間
	int m_time;

	//Xの要素番号
	int element_number_x;
	//Yの要素番号
	int element_number_y;

	Node m_node;
};
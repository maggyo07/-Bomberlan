#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック
class CObjBlock : public CObj
{
public :
	CObjBlock(int map[MAP_Y][MAP_X]);
	~CObjBlock(){};

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void SetScroll(float s)	{m_scroll = s;}
	float GetScroll()		{return m_scroll;}

	void GetMap(int map[MAP_Y][MAP_X]);

	//ブロックとの当たり判定
	void BlockHit(
	float *x,float *y,bool scroll_on,
	bool *up,bool *down,bool *left,bool *right,
	float *vx,float *vy,bool bom_hit_test,bool breakable_block_hit_test
	,const float *speed_power
	);

	//主人公と壁の交差判定
	bool HeroBlockCrossPoint(
		float x,float y,float vx,float vy,
		float *out_px,float *out_py,float* out_len
	);

	//マップ変更用関数
	void MapChange(int map[MAP_Y][MAP_X]);

private:
	void BlockDraw(float x, float y, RECT_F* dst, float c[]);
	
	int m_map[MAP_Y][MAP_X]; //マップ情報

	float m_scroll;		//左右スクリーン用

	float m_magma;		//マグマの切り取り地変更用

	float m_hero_x;	//主人公のX位置
	float m_hero_y;	//主人公のY位置

	float Dot(float ax, float ay, float bx, float by);	//内積
	float Cross(float ax, float ay, float bx, float by);//外積

	//線と線との交差判定
	bool CObjBlock::LineCrossPoint(
		float a1x,float a1y,float a2x,float a2y,
		float b1x,float b1y,float b2x,float b2y,
		float* out_px,float* out_py
		);

};
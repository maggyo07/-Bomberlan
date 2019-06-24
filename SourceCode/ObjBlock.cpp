//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjBlock.h"

//使用するネームスペース
using namespace GameL;

CObjBlock::CObjBlock(int map[MAP_Y][MAP_X])
{
	//マップデータコピー
	memcpy(m_map,map,sizeof(int) * (MAP_X*MAP_Y));

}
void CObjBlock::GetMap(int map[MAP_Y][MAP_X])
{
	//マップデータコピー
	memcpy(map, m_map, sizeof(int) * (MAP_X*MAP_Y));
}
//マップ変更用
void CObjBlock::MapChange(int map[MAP_Y][MAP_X])
{
	//マップデータコピー
	memcpy(m_map,map,sizeof(int) * (MAP_X*MAP_Y));
}
//イニシャライズ
void CObjBlock::Init()
{
	m_scroll = 0.0f;
	m_magma =192.0f;


	//主人公情報習得
	CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);

	//主人公オブジェクトが存在していたら
	if(hero != nullptr)
	{
		m_hero_x = hero->GetX();
		m_hero_y = hero->GetY();
	}
	else
	{
		m_hero_x = 0;
		m_hero_y = 0;
	}
	
}

//BlockDrawMethod関数
//引数１float　ｘ	：リソース切り取り位置ｘ
//引数２float　ｙ	：リソース切り取り位置ｙ
//引数３RECT_F＊ dst：描画位置
//引数４float　c[]	：カラー情報
//ブロックを40*40限定描画用。リソース切り取り位置のみｘ、ｙで
//設定できる
void CObjBlock::BlockDraw(float x, float y, RECT_F* dst, float c[])
{
	RECT_F src;
	src.m_top	= y;
	src.m_left	= x;
	src.m_right	= src.m_left + IMAAGE_CUT_SIZE;
	src.m_bottom= src.m_top + IMAAGE_CUT_SIZE;
	//描画
	Draw::Draw(0,&src,dst,c,0.0f);

}

//内積関数
//引数1,2	float ax , ay :Aベクトル
//引数3,4	float bx , by :Bベクトル
//戻り値　float　：射影
//内容　AベクトルとBベクトルで内積を行いを射影求める
float CObjBlock::Dot(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * bx + ay * by;

	return t;

}
//外積関数
//引数1,2	float ax , ay :Aベクトル
//引数3,4	float bx , by :Bベクトル
//戻り値　float　：射影
//内容　AベクトルとBベクトルで外積を行いを射影求める
float CObjBlock::Cross(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * by - ay * bx;

	return t;
}

//符号を求めるマクロ
#define SGN(x) 1 - (x <= 0) - (x < 0)

//線と線との交差判定
//引数 float 1,2	a1x , a1y
//引数 float 3,4	a2x , a2y
//引数 float 5,6	b1x , b1y
//引数 float 7,8	b2x , b2y
//引数 float 9,10	out_px,out_py
//戻り値　bool	:true交点有り false = 交点無し
//内容：引数のA・Bベクトルの交点を見つけ、out_pxとout_pyに返す
bool CObjBlock::LineCrossPoint(
		float a1x,float a1y,float a2x,float a2y,
		float b1x,float b1y,float b2x,float b2y,
		float* out_px,float* out_py
)
{
	//エラーコード
	*out_px =-99999.0f;
	*out_py =-99999.0f;

	//Aベクトル作成(a2←a1)
	float ax = a2x - a1x;
	float ay = a2y - a1y;

	//Bベクトル作成(b2←b1)
	float bx = b2x - b1x;
	float by = b2y - b1y;

	//Cベクトル作成(b1←a1)
	float cx = b1x - a1x;
	float cy = b1y - a1y;

	//Dベクトル作成(d2←a1)
	float dx = b2x - a1x;
	float dy = b2y - a1y;

	//A*Cの射影とA*Bの射影を求める
	float t1 = Cross(ax,ay,cx,cy);
	float t2 = Cross(ax,ay,dx,dy);

	//号が同じ方向になっているかをチェック
	if(SGN(t1) == SGN(t2))
	{
		return false;	//交点無し
	}

	//射影を絶対値化
	t1 = abs(t1);
	t2 = abs(t2);

	//交点を求める
	float px = bx * (t1 / (t1 + t2)) + b1x;
	float py = by * (t1 / (t1 + t2)) + b1y;

	//APベクトル(p←a1)
	float apx = px - a1x;
	float apy = py - a1y;

	//BPベクトル(p←a2)
	float bpx = px - a2x;
	float bpy = py - a2y;

	//A・APの射影とA・BPの射影を求める
	float w1 = Dot(ax,ay,apx,apy);
	float w2 = Dot(ax,ay,bpx,bpy);

	//符号チェック
	if(SGN(w1) == SGN(w2))
	{
		return false;	//交点が外
	}
	//交点を返す
	*out_px = px;
	*out_py = py;

	return true;
}

//主人公と壁の交差判定関数
//引数1,2
//引数3,4
//引数5,6
//引数7
//主人公の位置+移動ベクトルと各ブロックの辺で交差判定を行い
//最も近い交点の位置と距離を返す
bool CObjBlock::HeroBlockCrossPoint(
		float x,float y,float vx,float vy,
		float *out_px,float *out_py,float* out_len
	)
{
	bool pb = false;	//交点確認用
	float len = 99999.0f;//交点との距離
	//ブロックの辺ベクトル
	float edge[4][4]=
	{
		{ 0, 0,64, 0},//→
		{64, 0,64,64},//↓
		{64,64, 0,64},//←
		{ 0,64, 0, 0},//↑
	};

	//m_mapの全要素にアクセス
	for(int i = 0; i < 10 ; i++)
	{
		for(int j = 0 ; j < 100 ; j++)
		{
			if(m_map[i][j] != 0 )
			{
				//ブロックの４辺から交点を探す
				for(int k = 0; k < 4 ; k++)
				{
					//交点を探す
					float px,py;
					bool b;
					float l = 0.0f;
					b = LineCrossPoint(x,y,x+vx,y+vy,
						j*64+edge[k][0], i*64+edge[k][1],j*64+edge[k][2],i*64+edge[k][3],
						&px,&py);

					//交点チェック
					if(b == true)
					{
						//交点との間隔を求める
						l=sqrt((px - x) * (px - x) + (py - y) * (py - y));

						//見つけた交点の中で最も距離が短いものを探す
						if(len > l)
						{
							len = l;
							*out_px = px;
							*out_py = py;
							pb = true;
						}
					}
				}
			}
		}
	}

	*out_len = len;

	return pb;
}
//BlockHit関数
//引数１	float *x		:判定を行うobjectのX位置
//引数２	float *y		:判定を行うobjectのY位置
//引数３	bool scroll_on	:判定を行うobjectはスクリーンの影響を与えるかどうか(true=与える　false=与えない)
//引数４	bool *up		:上下左右判定の上部分に当たっているかどうかを返す
//引数５	bool *down		:上下左右判定の下部分に当たっているかどうかを返す
//引数６	bool *left		:上下左右判定の左部分に当たっているかどうかを返す
//引数７	bool *right		:上下左右判定の右部分に当たっているかどうかを返す
//引数８	float *rvx		:左右判定時の反発による移動方向・力の値を変えて返す
//引数９	float *rvy		:上下判定時による自由落下運動の移動方向・力の値を変えて返す
//引数１０	bool bom_hit_test			:ボムに当たり判定を付けるかどうか(true = 有り　false = 無し)
//引数１１	bool breakable_block_hit_test	:破壊可能ブロックに当たり判定を付けるかどうか(true = 有り　false = 無し)
//引数１２	const float *speed_power	:スピードのパワー

//判定を行うobjectとブロック40*40限定で、当たり判定と上下左右判定を行う。
//その結果は引数４～１０に返す
void CObjBlock::BlockHit(
	float *x,float *y,bool scroll_on,
	bool *up,bool *down,bool *left,bool *right,
	float *vx,float *vy,bool bom_hit_test,bool breakable_block_hit_test,const float *speed_power
	)
{
	//衝撃状態確認用フラグの初期化
	*up		=false;
	*down	=false;
	*left	=false;
	*right	=false;

	//主人公情報をもってくる
	CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);

	//持ってきたオブジェクト座標が主人公のものかどうか確認用
	bool hero_is_confirmation = false;//true:主人公のものと断定  false:主人公のもので無いと断定

	//主人公オブジェクトが存在していたら
	if(hero != nullptr)
	{
		//X位置を検索
		if(*x == hero->GetX())
		{
			//Y位置を検索
			if(*y == hero->GetY())
			{
				//持ってきたオブジェクトの座標が主人公の座標と一致
				hero_is_confirmation = true;
			}
		}
	}

	//m_maoの全要素にアクセス
	for(int i =0 ; i < MAP_Y ; i++)
	{
		for(int j = 0; j < MAP_X ; j++)
		{
			if(m_map[i][j] > 0)
			{
				//ボム判定がなくてかつ判定しようとしている場所にボムがあったら処理をしない
				if(bom_hit_test == false && m_map[i][j] == 4);
				//破壊可能ブロック判定がなくてかつ判定しようとしている場所に破壊可能ブロック(判定のみやアニメーション中)があったら処理しない
				else if(breakable_block_hit_test == false && (m_map[i][j] == 10 || m_map[i][j] == 11));

				else
				{
					//要素番号を座標に変更
					float bx = j * BLOCK_SIZE;
					float by = i * BLOCK_SIZE;

					//スクロールの影響
					float scroll = scroll_on ? m_scroll : 0 ;

					//オブジェクトとブロックのあたり判定
					if((*x + (-scroll)+BLOCK_SIZE > bx) && (*x+(-scroll) < bx+ BLOCK_SIZE) && (*y + BLOCK_SIZE > by) && (*y < by + BLOCK_SIZE))
					{
						//上下左右判定

						//vectorの作成
						float rvx = (*x + (-scroll)) - bx;
						float rvy = *y - by;

						//長さを求める
						float len = sqrt(rvx * rvx + rvy * rvy);

						//角度を求める
						float r = atan2( rvy , rvx);
						r = r * 180.0f / 3.14f;

						if(r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						if(len < 88.0)
						{
							//角度で上下左右を判定
							//右
							if((r < 45 && r >= 0) || r > 315)
							{
								if (!(*vx > 0))//右に移動していたら判定しない
								{
									*right = true;//オブジェクトの左の部分が衝突している
									*x = bx + BLOCK_SIZE + (scroll);//ブロックの位置　+　オブジェクトの幅

									//真右(真横)より上
									if ((r < 45 && 0 < r))
									{
										//主人公オブジェクトだったら規定のボタンを押した場合だけ処理。
										//主人公オブジェクトではなかったらそのまま処理
										if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetVKey('A') == true || Input::GetVKey(VK_LEFT) == true)))
										{
											//上に何も無かったら。ボム判定が無かったら判定なしにする。破壊可能ブロック判定が無かったら判定なしにする
											if (m_map[i - 1][j] == 0 || (bom_hit_test == false && m_map[i - 1][j] == 4) ||
												(breakable_block_hit_test == false && m_map[i - 1][j] == 10 || m_map[i - 1][j] == 11))
											{
												//上の上
												if (r <= 45 && r >= 44)
												{
													//今のYの位置の上の位置に移動
													*y = (i - 1) * BLOCK_SIZE;
													*x += -1.0f;
												}
												else
												{
													*vy = -*speed_power;
												}
											}
										}
									}
									//真右(真横)より下 && 下にブロックが無かったら
									else if (r > 315)
									{
										//主人公オブジェクトだったら規定のボタンを押した場合だけ処理。
										//主人公オブジェクトではなかったらそのまま処理
										if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetVKey('A') == true || Input::GetVKey(VK_LEFT) == true)))
										{
											//下に何も無かったら。ボム判定が無かったら判定なしにする。破壊可能ブロック判定が無かったら判定なしにする
											if (m_map[i + 1][j] == 0 || (bom_hit_test == false && m_map[i + 1][j] == 4) ||
												(breakable_block_hit_test == false && m_map[i + 1][j] == 10 || m_map[i + 1][j] == 11))
											{
												//下の下
												if (r >= 315 && r <= 316)
												{
													//今のYの位置の下の位置に移動
													*y = (i + 1) * BLOCK_SIZE;
													*x += -1.0f;
												}
												else
												{
													*vy = *speed_power;
												}
											}
										}
									}
									//下にも上にもブロックがあったら
									else if (m_map[i + 1][j] != 0 && m_map[i - 1][j] != 0)
									{
										*vx = -(*vx) * 0.1f;//-VX*反発係数
									}
								}
							}
							//上
							if(r > 45 && r < 135)
							{
								if (!(*vy < 0))//上に移動していたら判定しない
								{
									*down = true;//オブジェクトの下の部分が衝突している
									*y = by - BLOCK_SIZE;//ブロックの位置　-　主人公の幅
									*vy = 0.0f;
									//真上より右
									if (r > 45 && r < 90)
									{
										//右に何も無かったら。ボム判定が無かったら判定なしにする。破壊可能ブロック判定が無かったら判定なしにする
										if (m_map[i][j + 1] == 0 || (bom_hit_test == false && m_map[i][j + 1] == 4) ||
											(breakable_block_hit_test == false && m_map[i][j + 1] == 10 || m_map[i][j + 1] == 11))
										{
											//右の右
											if (r > 45 && r < 46)
											{
												*x = (j + 1) * BLOCK_SIZE + scroll;
												*y += 1.0f;
											}
											else
											{
												*vx = *speed_power;
											}
										}
									}
									//真上より左
									else if (r < 135 && r > 90)
									{
										//左に何も無かったら。ボム判定が無かったら判定なしにする。破壊可能ブロック判定が無かったら判定なしにする
										if (m_map[i][j - 1] == 0 || (bom_hit_test == false && m_map[i][j - 1] == 4) ||
											(breakable_block_hit_test == false && m_map[i][j - 1] == 10 || m_map[i][j - 1] == 11))
										{
											//左の左
											if (r < 135 && r > 134)
											{
												*x = (j - 1) * BLOCK_SIZE + scroll;
												*y += 1.0f;
											}
											else
											{
												*vx = -*speed_power;
											}
										}
									}
								}
							}
							//左
							if(r > 135 && r < 225)
							{
								if (!(*vx < 0))//左に移動していたら判定しない
								{
									*left = true;//オブジェクトの右の部分が衝突している
									*x = bx - BLOCK_SIZE + (scroll);//ブロックの位置　-　オブジェクト幅

									//真左より上
									if ((r > 135 && r < 180))
									{
										//主人公オブジェクトだったら規定のボタンを押した場合だけ処理。
										//主人公オブジェクトではなかったらそのまま処理
										if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetVKey('D') == true || Input::GetVKey(VK_RIGHT) == true)))
										{
											//上に何も無かったら。ボム判定が無かったら判定なしにする。破壊可能ブロック判定が無かったら判定なしにする
											if (m_map[i - 1][j] == 0 || (bom_hit_test == false && m_map[i - 1][j] == 4) ||
												(breakable_block_hit_test == false && m_map[i - 1][j] == 10 || m_map[i - 1][j] == 11))
											{
												//左の左
												if (r > 135 && r < 136)
												{
													*y = (i - 1) * BLOCK_SIZE;
													*x += 1.0f;
												}
												else
												{
													*vy = -*speed_power;
												}
											}
										}
									}
									//真左より下
									else if ((r < 225 || r > 180))
									{
										//主人公オブジェクトだったら規定のボタンを押した場合だけ処理。
										//主人公オブジェクトではなかったらそのまま処理
										if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetVKey('D') == true || Input::GetVKey(VK_RIGHT) == true)))
										{
											//下に何も無かったら。ボム判定が無かったら判定なしにする。破壊可能ブロック判定が無かったら判定なしにする
											if (m_map[i + 1][j] == 0 || (bom_hit_test == false && m_map[i + 1][j] == 4) ||
												(breakable_block_hit_test == false && m_map[i + 1][j] == 10 || m_map[i + 1][j] == 11))
											{
												//右の右
												if (r < 225 && r > 224)
												{
													*y = (i + 1) * BLOCK_SIZE;
													*x += 1.0f;
												}
												else
												{
													*vy = *speed_power;
												}
											}
										}
									}
									//上下にブロックがあったら
									else if (m_map[i + 1][j] != 0 && m_map[i + 1][j] != 0)
									{
										*vx = -(*vx) * 0.1f;//-VX*反発係数
									}
								}
							
							}
							//下
							if(r > 225 && r < 315)
							{
								if (!(*vy > 0))//下に移動していたら判定しない
								{
									*up = true;//主人公から見て上の部分が衝突している
									*y = by + BLOCK_SIZE;//ブロックの位置　+　主人公の幅
									*vy = 0.0f;
									//真下より左
									if (r > 225 && r < 275)
									{
										//左に何も無かったら。ボム判定が無かったら判定なしにする。破壊可能ブロック判定が無かったら判定なしにする
										if (m_map[i][j - 1] == 0 || (bom_hit_test == false && m_map[i][j - 1] == 4) ||
											(breakable_block_hit_test == false && m_map[i][j - 1] == 10 || m_map[i][j - 1] == 11))
										{
											//左の左
											if (r > 225 && r < 226)
											{
												*x = (j - 1) * BLOCK_SIZE + scroll;
												*y -= 1.0f;
											}
											else
											{
												*vx = -*speed_power;
											}
										}
									}
									//真下より右
									else if (r < 315 && r > 275)
									{
										//右に何も無かったら。ボム判定が無かったら判定なしにする。破壊可能ブロック判定が無かったら判定なしにする
										if (m_map[i][j + 1] == 0 || (bom_hit_test == false && m_map[i][j + 1] == 4) ||
											(breakable_block_hit_test == false && m_map[i][j + 1] == 10 || m_map[i][j + 1] == 11))
										{
											//右の右
											if (r < 315 && r > 314)
											{
												*x = (j + 1) * BLOCK_SIZE + scroll;
												*y -= 1.0f;
											}
											else
											{
												*vx = *speed_power;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
;
}

//アクション
void CObjBlock::Action()
{
	//主人公情報習得
	CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);
	//主人公オブジェクトが存在していたら
	if(hero != nullptr)
	{
		m_hero_x = hero->GetX();
		m_hero_y = hero->GetY();

		//後方スクロールライン
		if(m_hero_x < 300)
		{
			//スクロールの値が一番左の場合処理しない
			if(m_scroll >= 0);
			else
			{
				hero->SetX(300);			//主人公はラインを超えないようにする
				m_scroll-=hero->GetVX();//主人公が本来動くべき分の値をm_scrollに加える
			}
		}
		//前方スクロールライン
		else if(m_hero_x > 400)
		{
			//スクロールの値が一番右の場合処理しない
			if(m_scroll <=-1238);
			else
			{
				hero->SetX(400);
				m_scroll-=hero->GetVX();
			}
		}
	}
	//敵出現ライン
	//主人公の位置+600を敵出現ラインにする
	float line = m_hero_x + (-m_scroll) + 600;
	
	//敵出現ラインを要素番号
	int ex = ((int)line) / BLOCK_SIZE;

	//敵出現ラインの列を検索
	for(int i = 0 ; i < MAP_Y ; i++)
	{
		//ライン内から探す
		for (ex = ((int)line) / BLOCK_SIZE; ex >= 0; ex--)
		{
			
			//列の中から20を探す
			if (m_map[i][ex] == 20)
			{
				//バロン(敵)作成
				CObjBarom* obj_barom = new CObjBarom(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_barom, OBJ_BAROM, 10);

				m_map[i][ex] = 0;
				
			}
			//列の中から21を探す
			else if(m_map[i][ex] == 21)
			{
				//オニール(敵)作成
				CObjO_Neal* obj_o_neal = new CObjO_Neal(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_o_neal, OBJ_O_NEAL, 10);

				m_map[i][ex] = 0;
			}
			//列の中から22を探す
			else if(m_map[i][ex] == 22)
			{
				//ダル(敵)作成
				CObjDull* obj_dull = new CObjDull(ex * BLOCK_SIZE, i * BLOCK_SIZE);
				Objs::InsertObj(obj_dull, OBJ_DULL, 10);

				m_map[i][ex] = 0;
			}
			//列の中から23を探す
			else if(m_map[i][ex] == 23)
			{
				//ミンボー(敵)作成
				CObjMingBo* obj_ming_bo = new CObjMingBo(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_ming_bo, OBJ_MING_BO, 10);

				m_map[i][ex] = 0;
			}
			//列の中から24を探す
			else if(m_map[i][ex] == 24)
			{
				//コンドリア(敵)作成
				CObjCondoria* obj_condoria = new CObjCondoria(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_condoria, OBJ_CONDORIA, 10);

				m_map[i][ex] = 0;
			}
			//列の中から25を探す
			else if(m_map[i][ex] == 25)
			{
				//オバピー(敵)作成
				CObjObapy* obj_obapy = new CObjObapy(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_obapy, OBJ_OBAPY, 10);

				m_map[i][ex] = 0;
			}
			//列の中から26を探す
			else if(m_map[i][ex] == 26)
			{
				//パース(敵)作成
				CObjPerth* obj_perth = new CObjPerth(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_perth, OBJ_PERTH, 10);

				m_map[i][ex] = 0;
			}
			//列の中から27を探す
			else if(m_map[i][ex] == 27)
			{
				//ポンタン(敵)作成
				CObjPontan* obj_pontan = new CObjPontan(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_pontan, OBJ_PONTAN, 10);

				m_map[i][ex] = 0;
			}
			//列の中から2を探す
			else if (m_map[i][ex] == 2)
			{
				//破壊可能ブロック作成
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE,false,NOT_ITEM);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);

				//当たり判定だけある
				m_map[i][ex] = 10;
			}
			//列の中から３を探す
			else if(m_map[i][ex] == 3)
			{
				//破壊可能ブロック作成(ドア付)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE,true,NOT_ITEM);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);

				//当たり判定だけある
				m_map[i][ex] = 10;
			}
			//列の中から-2を探す
			else if (m_map[i][ex] == -2)
			{
				//主人公の初期位置または周辺

				m_map[i][ex] = 0;
			}
			//列の中から12を探す
			else if (m_map[i][ex] == 12)
			{
				//破壊可能ブロック作成(ファイアーアップ付)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, FIRE_UP);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//当たり判定だけある
				m_map[i][ex] = 10;
			}
			//列の中から13を探す
			else if (m_map[i][ex] == 13)
			{
				//破壊可能ブロック作成(ボムアップ付)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, BOM_UP);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//当たり判定だけある
				m_map[i][ex] = 10;
			}
			//列の中から14を探す
			else if (m_map[i][ex] == 14)
			{
				//破壊可能ブロック作成(リモコン付)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, REMOTE_CONTROLLER);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//当たり判定だけある
				m_map[i][ex] = 10;
			}
			//列の中から15を探す
			else if (m_map[i][ex] == 15)
			{
				//破壊可能ブロック作成(スケート付)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, SKATE);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//当たり判定だけある
				m_map[i][ex] = 10;
			}
			//列の中から16を探す
			else if (m_map[i][ex] == 16)
			{
				//破壊可能ブロック作成(ボムすり抜け付)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, BOM_SLIPPING_THROUGH);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//当たり判定だけある
				m_map[i][ex] = 10;
			}
			//列の中から17を探す
			else if (m_map[i][ex] == 17)
			{
				//破壊可能ブロック作成(破壊可能ブロックすり抜け付)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, DESTRUCTALE_BLOCK_SLIPPING_THROUGH);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//当たり判定だけある
				m_map[i][ex] = 10;
			}
			//列の中から18を探す
			else if (m_map[i][ex] == 18)
			{
				//破壊可能ブロック作成(ファイアーマン付)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, FIRE_MAN);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//当たり判定だけある
				m_map[i][ex] = 10;
			}
			//列の中から19を探す
			else if (m_map[i][ex] == 19)
			{
				//破壊可能ブロック作成(パーフェクトマン付)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, PERFECT_MAN);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//当たり判定だけある
				m_map[i][ex] = 10;
			}
		}
	}

}
//ドロー
void CObjBlock::Draw()
{
	
	//描画カラー情報
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//マップチップによるblock設置
	for(int i = 0; i < MAP_Y; i++)
	{
		for(int j = 0; j < MAP_X ; j++)
		{
			if(m_map[i][j] != 0)
			{

				//表示位置の設定
				dst.m_top	= i * BLOCK_SIZE;
				dst.m_left	= j * BLOCK_SIZE + m_scroll;
				dst.m_right	= dst.m_left+ BLOCK_SIZE;
				dst.m_bottom= dst.m_top + BLOCK_SIZE;

				//mapの２のときの切り取り
				if(m_map[i][j] == 2)
				{
					;
					
				}
				//mapの１のときの切り取り
				else if(m_map[i][j] == 1)
				{
					//破壊不可ブロック
					BlockDraw(433.0f + 40.0f,0.0f,&dst,c);

				}
				
			}
		}
	}
}
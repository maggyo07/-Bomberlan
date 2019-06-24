//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "Trace.h"
#include "UtilityModule.h"
#include "GameHead.h"
#include "ObjTime.h"

//使用するネームスペース
using namespace GameL;

CObjTime::CObjTime(int max_time)
{
	m_time = max_time * 60;
}
//イニシャライズ
void CObjTime::Init()
{
	//敵はまだ出さない
	m_out_put_enemy = false;

	m_enemy_time = 0;//敵時間初期化
}
//アクション
void CObjTime::Action()
{
	if(m_out_put_enemy == false)
	{
		m_time--;
	}

	if(m_time < 0)
	{
		m_time = 0;
		//時間切れなので敵を出す
		m_out_put_enemy = true;
		Audio::Stop(0);//0番曲をストップ
		Audio::Start(2);//2番曲をスタート
	}

	//敵を出すと判断したので時間を加算していく
	if (m_out_put_enemy == true)
	{
		m_enemy_time++;
	}
	//敵を出すときの座標取得変数
	float enemy_x;
	float enemy_y;

	//最初に一回と60*100(100秒)ごとに敵出現
	if ((m_enemy_time >= 1 && m_enemy_time % (60 * 100) == 0) || m_enemy_time == 1)
	{
		for (int enemy_num = 0; enemy_num < 1; enemy_num++)
		{
			//置ける場所からランダムで決める
			AllocablePosition(&enemy_x, &enemy_y);

			//ポンタン(敵)作成
			CObjPontan* obj_pontan = new CObjPontan(enemy_x, enemy_y);
			Objs::InsertObj(obj_pontan, OBJ_PONTAN, 10);

			//敵を出現したので
			((UserData*)Save::GetData())->mEnemyNumber++;
		}

	}

}
//ドロー
void CObjTime::Draw()
{
	//描画カラー情報

	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	wchar_t str[128];

	//秒の値を文字列化	
	swprintf_s(str,L"TIME		%d",(m_time / 60) );//整数を文字列化

	Font::StrDraw(str,10,10,30,c);

}

//関数　マップ情報の配置可能場所を求める
//引数１ float* x	:求めた後のX位置
//引数２ float* y	:求めた後のY位置
void CObjTime::AllocablePosition(float* x, float* y)
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公情報を持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//マップ情報
	int map[MAP_Y][MAP_X];
	//マップ情報更新
	block->GetMap(map);

	//主人公の要素数
	int hero_element_count_x = ((int)(hero->GetX() + (-block->GetScroll())) / BLOCK_SIZE);
	int hero_element_count_y = ((int)hero->GetY() / BLOCK_SIZE);

	//置ける場所が何個あるかを入れる変数
	int can_put_location = 0;

	//すべてのマップ情報を見る
	//置ける場所が何個あるかを数える
	for (int map_y = 0; map_y < MAP_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_X; map_x++)
		{
			//主人公のX位置＋5より右側もしくは主人公のX位置-5より左側
			//主人公のY位置＋5より下側もしくは主人公のY位置-5より上側
			if (map_x > hero_element_count_x + 5 || map_x < hero_element_count_x - 5 || 
				map_y > hero_element_count_y + 5 || map_y < hero_element_count_y - 5)
			{
				//マップの上の方は空白なのでその場所以外
				if (map_y > 3)
				{
					//置ける場所かどうか
					if (map[map_y][map_x] == 0)
					{
						//置ける場所があったので加算
						can_put_location++;
					}
				}
			}
		}
	}
	
	//置ける場所の中からランダムで決める
	int random = GetRandom(1, can_put_location);

	//すべてのマップ情報を見る
	//置ける場所が何個あるのかわかったのでrancom番目のところを配置場所として決める
	for (int map_y = 0; map_y < MAP_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_X; map_x++)
		{
			//主人公のX位置＋5より右側もしくは主人公のX位置-5より左側
			//主人公のY位置＋5より下側もしくは主人公のY位置-5より上側
			if (map_x > hero_element_count_x + 5 || map_x < hero_element_count_x - 5 ||
				map_y > hero_element_count_y + 5 || map_y < hero_element_count_y - 5)
			{
				//マップの上の方は空白なのでその場所以外
				if (map_y > 3)
				{
					//置ける場所かどうか
					if (map[map_y][map_x] == 0)
					{
						if (random == 1)
						{
							*x = map_x * BLOCK_SIZE;
							*y = map_y * BLOCK_SIZE;
							random--;
						}
						else
						{
							random--;
						}
					}
				}
			}
		}
	}
	
		
}
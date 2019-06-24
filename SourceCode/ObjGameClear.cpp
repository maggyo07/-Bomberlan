//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "Trace.h"
#include "GameHead.h"
#include "ObjGameClear.h"

//使用するネームスペース
using namespace GameL;
//イニシャライズ
void CObjGameClear::Init()
{
	m_vx = 1.9;
	m_vy = 0;
	m_x = 0;
	m_y = 480.0;
	m_time = 0;
	m_ani_time = 0;	
	m_ani_max_time = 10;	//アニメーション間隔幅
	m_ani_frame = 0;

	m_posture = 0;
	m_stop = false;
}
//アクション
void CObjGameClear::Action()
{
	m_time++;
	//早く切り替え(フレーム)防止
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame++;
		m_ani_time = 0;
	}

	//最後のフレームに行ったら最初のフレームに戻す
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//移動停止で無い場合
	if (m_stop == false)
	{
		m_ani_time++;
		m_x += m_vx;
		m_y += m_vy;
	}

	//右へ画面外にいったら左の画面外に移動
	if (m_x > 800)
	{
		m_x = -40.0f;
	}

	//時間が650になったらロードランナーの主人公の姿に変身
	if (m_time == 650)
	{
		m_posture = 1;
	}
	//時間が1050になったら音楽停止・移動停止
	if (m_time == 1050)
	{
		Audio::Stop(0);//0番曲を停止
		m_stop = true;
	}
	//時間が1150になったらタイトル画面へ
	if (m_time == 1150)
	{
		Scene::SetScene(new CSceneTitle());
	}

	
}
//ドロー
void CObjGameClear::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//背景-------
	//切り取り位置の設定
	src.m_top = 0;
	src.m_left = 0;
	src.m_right = 800;
	src.m_bottom = 600;

	//表示位置の設定
	dst.m_top = 0;
	dst.m_left = 0;
	dst.m_right = 800;
	dst.m_bottom = 600;

	//描画
	Draw::Draw(0, &src, &dst, c, 0.0f);
	//----------
	//上画面の文字------
	Font::StrDraw(L"CONGRATULATIONS", 200, 20, 50, c);
	Font::StrDraw(L"BOMBER RAN BECOMES RUNNER", 100, 80, 50, c);
	Font::StrDraw(L"SEE YOU AGAIN IN LODE RUNNER", 70, 140, 50, c);

	//------------------

	//主人公---------

	//表示位置の設定
	dst.m_top = m_y;
	dst.m_left = m_x + 40.0f;
	dst.m_right = dst.m_left - 40.0f;
	dst.m_bottom = dst.m_top + 40.0f;

	//歩く、走るアニメーション情報を登録
			int AniData[4] =
			{
				1 , 0 , 2 , 0
			};
		//ボンバーマンの主人公
		if (m_posture == 0)
		{
		
			//切り取り位置の設定
			src.m_top = IMAAGE_CUT_SIZE * 0;
			src.m_left = IMAAGE_CUT_SIZE * AniData[m_ani_frame];
			src.m_right = IMAAGE_CUT_SIZE + AniData[m_ani_frame] * IMAAGE_CUT_SIZE;
			src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;

			//描画
			Draw::Draw(1, &src, &dst, c, 0.0f);
		}
		//ロードランナーの主人公
		else
		{
			//切り取り位置の設定
			src.m_top = IMAAGE_CUT_SIZE * 0;
			src.m_left = IMAAGE_CUT_SIZE * AniData[m_ani_frame];
			src.m_right = IMAAGE_CUT_SIZE + src.m_left;
			src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;

			//描画
			Draw::Draw(2, &src, &dst, c, 0.0f);
		}
	//----------
}
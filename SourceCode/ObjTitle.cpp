//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjTitle::Init()
{
	m_key_flag = false;

	m_start_or_continue = true;

}

//アクション
void CObjTitle::Action()
{
	//エンターキーを押してシーン　：　ゲームメインに移動する
	if(Input::GetVKey(VK_RETURN)==true)
	{
		if(m_key_flag == true)
		{
			//STAREにカーソルが合っていたら
			if (m_start_or_continue == true)
			{
				Scene::SetScene(new CSceneStageChange());
			}
			//DESCRIPTIONにカーソルが合っていたら
			else 
			{
				Scene::SetScene(new CSceneDescription());
			}
		}
	}
	else
	{
		m_key_flag = true;
	}
	//上を押したら(W)
	if ((Input::GetVKey('W') == true || Input::GetVKey(VK_UP) == true) && m_start_or_continue == false)
	{
		Audio::Start(1); //音楽スタート
		//STARTにカーソルを合わせる
		m_start_or_continue = true;
	}
	//下を押したら(S)
	if ((Input::GetVKey('S') == true || Input::GetVKey(VK_DOWN) == true) && m_start_or_continue == true)
	{
		Audio::Start(1); //音楽スタート
		//CONTNUEにカーソルを合わせる
		m_start_or_continue = false;
	}
}

//ドロー
void CObjTitle::Draw()
{
	//描画カラー情報　R=RED　G=Green　B=Blue　A＝Alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 157.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 150.0f;
	dst.m_right = 256.0f * 2 + dst.m_left;
	dst.m_bottom = 157.0f * 2 + dst.m_top;
	//0番に登録したグラフィックをsrc ・das ・cno情報を元に描画
	Draw::Draw(0, &src, &dst, c, 0.0f);

	Font::StrDraw(L"START", 380, 350, 25, c);
	Font::StrDraw(L"DESCRIPTION", 380, 400, 25, c);
	Font::StrDraw(L"COPYRIGHT   1985   HUDSON   SOFT",220,500,25,c);
	Font::StrDraw(L"ENTER KEY PUSH!", 310, 550, 25, c);
	if (m_start_or_continue == true)
	{
		Font::StrDraw(L"-->",320,350,25,c);
	}
	else
	{
		Font::StrDraw(L"-->", 320, 400, 25, c);
	}
	//TOP表示ーーーー
	wchar_t str[128];

	//TOPの値を文字列化

	swprintf_s(str, L"TOP          %d", ((UserData*)Save::GetData())->mMaxScore);//整数を文字列化

	Font::StrDraw(str, 300, 450, 25, c);
	//－－－－－－－－
}
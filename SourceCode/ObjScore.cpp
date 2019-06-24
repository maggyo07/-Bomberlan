//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "ObjScore.h"

//使用するネームスペース
using namespace GameL;

CObjScore::CObjScore()
{
	//大きいほう
	m_big_or_small = true;
}

CObjScore::CObjScore(int score, float x, float y)
{
	//小さいほう
	m_big_or_small = false;

	m_score = score;
	m_x = x;
	m_y = y;
}
//イニシャライズ
void CObjScore::Init()
{
	m_time = 0;
}
//アクション
void CObjScore::Action()
{
	//小さいほう専用の処理
	if (m_big_or_small == false)
	{
		m_time++;

		if (m_time > 100)
		{
			this->SetStatus(false);		//自身に消滅命令を出す。
			Hits::DeleteHitBox(this);	//自身が所有するHitBoxに消滅する。
		}
	}
}
//ドロー
void CObjScore::Draw()
{

	

	//大きいほう専用のドロー
	if (m_big_or_small == true)
	{
		//描画カラー情報
		float c[4] = {1.0f,1.0f,1.0f,1.0f};

		wchar_t str[128];

		//秒の値を文字列化
		swprintf_s(str, L"Score:%d", ((UserData*)Save::GetData())->mScore);//整数を文字列化

		Font::StrDraw(str, 300, 50, 30, c);
	}
	//小さいほう専用のドロー
	else 
	{
		//ブロック情報を持ってくる
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//描画カラー情報
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		wchar_t str[128];

		//秒の値を文字列化
		swprintf_s(str, L"%d", m_score);//整数を文字列化

		Font::StrDraw(str, m_x + block->GetScroll() + 5, m_y + 10, 10, c);
	}

}
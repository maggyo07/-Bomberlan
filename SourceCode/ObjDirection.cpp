//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjDirection.h"

//使用するネームスペース
using namespace GameL;

CObjDirection::CObjDirection(float x, float y, int directon_x, int directon_y)
{
	m_x = x;
	m_y = y;
	m_directon_x = directon_x;
	m_directon_y = directon_y;
}
//イニシャライズ
void CObjDirection::Init()
{
	m_time = 0;
}
//アクション
void CObjDirection::Action()
{
	if (m_time >= 1)
	{
		this->SetStatus(false);		//自身に消滅命令を出す。
	}

	m_time++;

}
//ドロー
void CObjDirection::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 40.0 + (m_directon_y * 40.0);
	src.m_left = 40.0 + (m_directon_x * 40.0);
	src.m_right = src.m_left + 40.0;
	src.m_bottom = 40.0 + src.m_top;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = m_y;
	dst.m_left = m_x + block->GetScroll();
	dst.m_right = 40.0 + m_x + block->GetScroll();
	dst.m_bottom = 40.0 + m_y;

	//描画
	Draw::Draw(5, &src, &dst, c, 0.0f);
}
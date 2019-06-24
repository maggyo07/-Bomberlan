//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "ObjStageChange.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjStageChange::Init()
{
	m_time = 0;
}
//アクション
void CObjStageChange::Action()
{
	m_time ++;


	if(m_time >= 200)
	{
		Scene::SetScene(new CSceneMain());
	}

	//メインシーン前にスペースを押すと主人公が出た瞬間、スペースキーが押されているという判定になってしまって開始直後にボムが置かれてしまうので。
	if (Input::GetVKey(VK_SPACE));
}
//ドロー
void CObjStageChange::Draw()
{

	//描画カラー情報
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	wchar_t str[128];

	//秒の値を文字列化
	
	swprintf_s(str,L"ステージ%d",((UserData*)Save::GetData())->mStageNumber);//整数を文字列化
	
	Font::StrDraw(str,300,250,50,c);

}
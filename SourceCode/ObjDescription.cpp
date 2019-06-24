//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"
#include "Trace.h"
#include "GameHead.h"

#include "ObjDescription.h"
#include "ObjBom.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjDescription::Init()
{
}
//アクション
void CObjDescription::Action()
{	
	if(Input::GetVKey(VK_BACK) == true)
	{
		Scene::SetScene(new CSceneTitle());
	}
}
//ドロー
void CObjDescription::Draw()
{
	//描画カラー情報
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//アイテム画像表示・アイテム説明
	for(int item = 0; item < 8 ; item++)
	{
		//アイテム画像表示-----------
		//切り取り位置の設定
		src.m_top	= ITEM_SIZE * item;
		src.m_left	= 0;
		src.m_right	= src.m_left + ITEM_SIZE;
		src.m_bottom= ITEM_SIZE + src.m_top;

		//ブロック情報を持ってくる
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//表示位置の設定
		dst.m_top	= ITEM_SIZE * item;
		dst.m_left =  100;
		dst.m_right = dst.m_left + ITEM_SIZE;
		dst.m_bottom= dst.m_top + ITEM_SIZE;

		//描画
		Draw::Draw(0,&src,&dst,c,0.0f);
		//----------------------------

		//アイテムの説明-------------
		switch(item)
		{
			case 0:
				Font::StrDraw(L"ファイアーアップ：",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"取ると爆風の範囲が１マスずつ",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"広がります",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 1:

				Font::StrDraw(L"ボムアップ　　　：",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"１度にセットできる個数が増える。",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 2:

				Font::StrDraw(L"リモコン　　　　：",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"通常ボムは約３秒後に爆発するが",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"リモコンを取るとZキーで爆発する。",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 3:

				Font::StrDraw(L"スケート　　　　：",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"スピードが少し上昇します。",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 4:

				Font::StrDraw(L"ボムすり抜け　　：",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"ボムの上を通ることが出来る。",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 5:

				Font::StrDraw(L"レンガすり抜け　：",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"レンガの上を通ることが出来る。",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 6:

				Font::StrDraw(L"ファイアーマン　：",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"爆風に当たっても死亡しなくなる",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 7:

				Font::StrDraw(L"パーフェクトマン：",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"約３０秒間音楽が変わり敵・爆風に",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"当たっても死亡しなくなる。",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;
		}
		//---------------------------
	}

	//その他の説明--------------
	Font::StrDraw(L"To return, press the BACKSPACE key!",50,320,40,c);

	Font::StrDraw(L"・このゲームはステージ内の全ての敵を爆風を上手く使い全滅させ",50,360,20,c);
	Font::StrDraw(L"何処かのレンガに隠れている扉に入ると次のステージへ行き",70,380,20,c);
	Font::StrDraw(L"ステージ3をクリアするとゲームクリアです。",70,400,20,c);

	Font::StrDraw(L"・レンガは爆風で破壊できます。",50,440,20,c);

	Font::StrDraw(L"・扉に爆風を当てたり、左上の時間が０になったときと",50,480,20,c);
	Font::StrDraw(L"0になったときから100秒間隔で、敵が出てきます。",70,500,20,c);

	Font::StrDraw(L"・アイテムに爆風を当てると敵が出てくることがあります。",50,540,20,c);


	//--------------------------
}
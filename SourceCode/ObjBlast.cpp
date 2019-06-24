//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjBlast.h"

//使用するネームスペース
using namespace GameL;
//引数１：X位置
//引数２：Y位置
//引数３：方向
//引数４：倍率
CObjBlast::CObjBlast(float x, float y,int direction, int magnification)
{
	//X位置変更用
	int Direction_x[5] = 
	//	右、		左、	　上、下、その場
	{BLAST_SIZE * magnification,(-BLAST_SIZE) * magnification, 0,   0,     0};	//X位置

	//Y位置変更用
	int Direction_y[5] =
	//右、左		上			下	その場
	{  0,  0,(-BLAST_SIZE) * magnification,BLAST_SIZE * magnification,0};//Y位置

	m_x = x + Direction_x[direction];
	m_y = y + Direction_y[direction];
	//方向情報を入れる。
	m_direction = direction;
}

//イニシャライズ
void CObjBlast::Init()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	m_last_blast = false;
	
	m_ani_data = 3;//一番右の画像からスタート
	m_ani_time = 0;
	m_ani_max_time = 40;//アニメーション終了時間２秒(40*3)

	int element_x = ((int)m_x) / BLAST_SIZE;//Xの要素番号
	int element_y = ((int)m_y) / BLAST_SIZE;//Yの要素番号

	//マップ情報に-1を入れる。
	block->GetMap(m_map);
	m_map[element_y][element_x] = -1;
	block->MapChange(m_map);

	//方向別ヒットボックス
	if(m_direction == UP || m_direction == DOWN)
	{
		//少し縦長
		//当たり判定用のHitBoxを作成
		Hits::SetHitBox(this, m_x + (block->GetScroll()) + RECTANGLE, m_y,BLAST_SIZE - RECTANGLE * 2, BLAST_SIZE,ELEMENT_GREEN,OBJ_BLAST,1);

	}
	else if(m_direction == LEFT || m_direction == RIGHT)
	{
		//少し横長
		//当たり判定用のHitBoxを作成
		Hits::SetHitBox(this, m_x + (block->GetScroll()), m_y + RECTANGLE,BLAST_SIZE, BLAST_SIZE - RECTANGLE * 2,ELEMENT_GREEN,OBJ_BLAST,1);

	}
	else
	{
		//少し小さく
		//当たり判定用のHitBoxを作成
		Hits::SetHitBox(this,m_x + (block->GetScroll()) + RECTANGLE,m_y + RECTANGLE,BLAST_SIZE - RECTANGLE * 2,BLAST_SIZE - RECTANGLE * 2, ELEMENT_GREEN,OBJ_BLAST,1);
	}
	

}

//アクション
void CObjBlast::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//マップ情報更新
	block->GetMap(m_map);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	if(m_direction == UP || m_direction == DOWN)
	{
		hit->SetPos(m_x + (block->GetScroll()) + RECTANGLE , m_y);
	}
	else if(m_direction == LEFT || m_direction == RIGHT)
	{
		hit->SetPos(m_x + (block->GetScroll()) , m_y + RECTANGLE);
	}
	else
	{
		hit->SetPos(m_x + (block->GetScroll()) + RECTANGLE, m_y + RECTANGLE);
	}

	m_ani_time++;
	
	if(m_ani_time == 10 ||
	   m_ani_time == 20 ||
	   m_ani_time == 30)
	{
		m_ani_data--;
	}
	//ani_timeが最大値を超えたら
	else if(m_ani_time > m_ani_max_time)
	{

		int element_x = ((int)m_x) / BLAST_SIZE;//Xの要素番号
		int element_y = ((int)m_y) / BLAST_SIZE;//Yの要素番号

		
		//消すのでマップ情報の自分の-1も消す。
		m_map[element_y][element_x] = 0;
		block->MapChange(m_map);
		

		this->SetStatus(false);		//自身に消滅命令を出す。
		Hits::DeleteHitBox(this);	//敵機が所有するHitBoxに消滅する。
	}
}
//ドロー
void CObjBlast::Draw()
{
	//描画カラー情報
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//最後の爆風の時の切り取り位置
	if(m_last_blast == true)
	{
		//切り取り位置の設定
		src.m_top	= BLAST_CUT_SIZE * 0;
		src.m_left	= BLAST_CUT_SIZE * m_ani_data;
		src.m_right	= src.m_left	+ BLAST_CUT_SIZE;
		src.m_bottom= src.m_top		+ BLAST_CUT_SIZE;
	}
	//方向がその場のときの切り取り位置
	else if(m_direction == IN_SITU)
	{
		//切り取り位置の設定
		src.m_top	= BLAST_CUT_SIZE * 2;
		src.m_left	= BLAST_CUT_SIZE * m_ani_data;
		src.m_right	= src.m_left	+ BLAST_CUT_SIZE;
		src.m_bottom= src.m_top		+ BLAST_CUT_SIZE;
	}
	else
	{
		//切り取り位置の設定
		src.m_top	= BLAST_CUT_SIZE;
		src.m_left	= BLAST_CUT_SIZE * m_ani_data;
		src.m_right	= src.m_left	+ BLAST_CUT_SIZE;
		src.m_bottom= src.m_top		+ BLAST_CUT_SIZE;
	}
	

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top	= m_y;
	dst.m_left =  m_x + block->GetScroll();
	dst.m_right = BLAST_SIZE + m_x + block->GetScroll();
	dst.m_bottom= BLAST_SIZE + m_y;

	//方向別の描画
	switch(m_direction)
	{
		//右
	case RIGHT:
		Draw::Draw(1,&src,&dst,c,270.0f);
		break;
		//左
	case LEFT:
		Draw::Draw(1,&src,&dst,c,90.0f);
		break;
		//上
	case UP:
		Draw::Draw(1,&src,&dst,c,0.0f);
		break;
		//下
	case DOWN:
		Draw::Draw(1,&src,&dst,c,180.0f);
		break;
		//その場
	case IN_SITU:
		Draw::Draw(1,&src,&dst,c,0.0f);
		break;
	};
}
#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：スコア
class CObjScore : public CObj
{
public :
	CObjScore();
	CObjScore(int score,float x,float y);
	~CObjScore(){};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

private:
	bool m_big_or_small;//上のほうに大きく表示されているスコアか敵やアイテム獲得時にもらえるスコアか　true:大きいほう	false：小さいほう

	//小さく表示するスコア
	int m_score;
	//小さいほうの位置
	float m_x;
	float m_y;

	int m_time;//時間
};
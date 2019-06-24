//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjHero::Init()
{
	m_px = 40.0f;	//初期位置
	m_py = BLOCK_SIZE * 5;

	m_vx = 0.0f;	//ベクトル
	m_vy = 0.0f;

	m_posture = 0; //右向き0 左向き1 上向2　下向き3

	m_ani_time = 0;
	m_ani_frame = 0;	//静止フレームを初期にする

	m_ani_max_time = 4;	//アニメーション間隔幅

	m_speed_power = 0.5f + (SKATE_SPEED_POWER * ((UserData*)Save::GetData()) ->mSkateNum);//スピードパワー初期化

	//blockとの衝撃状態確認用
	m_hit_up	=false;
	m_hit_down	=false;
	m_hit_left	=false;
	m_hit_right	=false;
	 
	m_death_flag = false;//死亡フラグ初期化
	m_death_time = 0;	//死亡フラグ時間初期化

	m_remote_controller = ((UserData*)Save::GetData()) ->mRemoteController;//リモコン機能

	m_bom_power = 1 + ((UserData*)Save::GetData()) ->mFireUpNum;//ボムの威力初期化

	m_bom_num = 0;	//ステージ内にあるボムの数
	m_bom_max_num = 1 +((UserData*)Save::GetData()) ->mBomUpNum;//ステージ内における最大数

	//ボムすり抜けをとっていたら
	if (((UserData*)Save::GetData())->mBomSlippingThrough == true)
	{
		m_bom_hit_test = false;//ボム当たり判定無し
	}
	else
	{
		m_bom_hit_test = true;//ボム当たり判定あり
	}

	//破壊可能ブロックすり抜けをとったいたら
	if (((UserData*)Save::GetData())->mDestructableBlockSlippingThrough == true)
	{
		m_breakable_block_hit_test = false;//破壊可能ブロック当たり判定無し
	}
	else
	{
		m_breakable_block_hit_test = true;//破壊可能ブロック当たり判定あり
	}

	if (((UserData*)Save::GetData())->mFireMan == true)
	{
		m_blast_hit_test = false;//爆風当たり判定無し
	}
	else
	{
		m_blast_hit_test = true;//爆風当たり判定あり
	}

	m_enemy_hit_test = true;//敵判定健在

	m_get_fire_man = ((UserData*)Save::GetData())->mFireMan;	//ファイアーマンをとったどうか

	m_parfect_man_time = 0;

	m_get_parfect_man = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px + RECTANGLE, m_py + RECTANGLE, HERO_SIZE - RECTANGLE * 2, HERO_SIZE - RECTANGLE * 2, ELEMENT_PLAYER, OBJ_HERO, 1);


}
//アクション
void CObjHero::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + RECTANGLE, m_py + RECTANGLE);

	//死亡フラグが立っていなかったら
	if (m_death_flag == false)
	{
		//キー入力
		KeyInput(hit);

		//早く切り替え(フレーム)防止
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame++;
			m_ani_time = 0;
		}

		//最後のフレームに行ったら最初のフレームに戻す
		if(m_ani_frame == 4)
		{
			m_ani_frame = 0;
		}

		//摩擦
		m_vx += -(m_vx * 0.198);
		m_vy += -(m_vy * 0.198);

		//ブロック判定
		block->BlockHit(&m_px,&m_py,true,
			&m_hit_up,&m_hit_down,&m_hit_left,&m_hit_right,&m_vx,&m_vy,
			m_bom_hit_test,m_breakable_block_hit_test,&m_speed_power
			);
	
		//位置の更新
		m_py += m_vy;
		m_px += m_vx;

	}
	//死亡フラグが立っていたら
	else
	{
		m_death_time++;

		//死亡してからの時間単位のフレーム切り替え
		//１回目のフレーム切り替え
		if(m_death_time == 20)
		{
			Audio::Start(7); //7番曲をスタート
			m_ani_frame++;
		}
		//２回目のフレーム切り替え
		if (m_death_time == 60)
		{
			m_ani_frame++;
		}
		//3回目のフレーム切り替え
		if (m_death_time == 100)
		{
			m_ani_frame++;
		}

		//本当に消去
		if (m_death_time == 140)
		{
			this->SetStatus(false);		//自身に消滅命令を出す。
			Hits::DeleteHitBox(this);	//自身が所有するHitBoxに消滅する。

			//ステージ１からやり直し
			((UserData*)Save::GetData())->mStageNumber = 1;

			//シーン(ステージ変更)呼び出し
			//Scene::SetScene(new CSceneStageChange());
			//一回死んだら終了
			Scene::SetScene(new CSceneTitle());
		}

	}
	

	//爆風オブジェクトに接触していたら && 爆風判定があったら
	if(hit->CheckObjNameHit(OBJ_BLAST) != nullptr && m_blast_hit_test == true)
	{
		//すでに死亡フラグが立っていたら処理しない
		if (m_death_flag != true)
		{
			Audio::Start(6); //6番曲をスタート

			//どちらが流れているかわからないので２つストップ
			Audio::Stop(0);	//0番曲をストップ
			Audio::Stop(2);//2番曲をストップ

			m_death_flag = true;//爆風に触れた！
			m_ani_frame = 0;//フレーム数を０にする
		}
	}

	//ENEMENT_ENEMYを持つオブジェクトに接触していたら && 敵判定があったら
	if(hit->CheckElementHit(ELEMENT_ENEMY) == true && m_enemy_hit_test == true)
	{
		//すでに死亡フラグが立っていたら処理しない
		if (m_death_flag != true)
		{
			Audio::Start(6); //6番曲をスタート

			//どちらが流れているかわからないので２つストップ
			Audio::Stop(0);	//0番曲をストップ
			Audio::Stop(2);//2番曲をストップ
			m_death_flag = true; //敵に触れた！
			m_ani_frame = 0;//フレーム数を０にする
		}
	}

	//パーフェクトマンを取っていたら
	if(m_get_parfect_man == true)
	{
		//パーフェクトマンタイム加算
		m_parfect_man_time++;
		//どちらが流れているかわからないのでどちらも音楽をストップさせる
		Audio::Stop(0);//0番曲をストップ
		Audio::Stop(2);//2番曲をストップ

		//パーフェクトマンタイムが30秒(フレーム数*30)以上だったら
		//パーフェクト状態終了
		if(m_parfect_man_time >= 60*30)
		{
			Audio::Stop(5);//5番曲をストップ

			//Timeオブジェクト情報を持ってくる
			CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);

			//時間が０のとき
			if (time->GetTime() <= 0)
			{
				Audio::Start(2);//2番曲をスタート
			}
			else
			{
				Audio::Start(0);//0番曲をスタート
			}

			//パーフェクトマンフラグ消去
			m_get_parfect_man = false;
			//パーフェクトマンタイム初期化
			m_parfect_man_time = 0;
			//敵の当たり判定復活
			m_enemy_hit_test = true;

			//ファイアーマンを取っていなかったら
			if(m_get_fire_man == false)
			{

				m_blast_hit_test = true;
			}

		}
	}

	//アイテムをとったか判定
	GetItemsInformation(hit);

}
//ドロー
void CObjHero::Draw()
{
	

	//描画カラー情報
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置
	//死亡フラグが立っていなかったら
	if (m_death_flag == false)
	{
		//歩く、走るアニメーション情報を登録
		int AniData[4] =
		{
			 1 , 0 , 2 , 0
		};
		//右向き0 左向き1 上向き2　下向き3
		//上向き専用の切り取り位置
		if (m_posture == 2)
		{
			//切り取り位置の設定
			src.m_top = IMAAGE_CUT_SIZE * 1;
			src.m_left = IMAAGE_CUT_SIZE * AniData[m_ani_frame];
			src.m_right = IMAAGE_CUT_SIZE + AniData[m_ani_frame] * 40.0f;
			src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;
		}
		//下向き専用の切り取り位置
		else if (m_posture == 3)
		{
			//切り取り位置の設定
			src.m_top = IMAAGE_CUT_SIZE * 2;
			src.m_left = IMAAGE_CUT_SIZE * AniData[m_ani_frame];
			src.m_right = IMAAGE_CUT_SIZE + AniData[m_ani_frame] * 40.0f;
			src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;
		}
		//右・左向き専用の切り取り位置
		else
		{
			//切り取り位置の設定
			src.m_top = IMAAGE_CUT_SIZE * 0;
			src.m_left = IMAAGE_CUT_SIZE * AniData[m_ani_frame];
			src.m_right = IMAAGE_CUT_SIZE + AniData[m_ani_frame] * 40.0f;
			src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;
		}


		//右向き0 左向き1 上向き2　下向き3
		//上・下向き専用表示位置
		if (m_posture == 2 || m_posture == 3)
		{
			//表示位置の設定
			dst.m_top = 0.0f + m_py;
			dst.m_left = (HERO_SIZE * 0) + m_px;
			dst.m_right = (HERO_SIZE - HERO_SIZE * 0) + m_px;
			dst.m_bottom = HERO_SIZE + m_py;

		}
		//右・左向き専用の表示位置
		else
		{
			//表示位置の設定
			dst.m_top = 0.0f + m_py;
			dst.m_left = (HERO_SIZE * m_posture) + m_px;
			dst.m_right = (HERO_SIZE - HERO_SIZE * m_posture) + m_px;
			dst.m_bottom = HERO_SIZE + m_py;

		}


		//描画
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	//死亡フラグが立っていたら
	else
	{
		//切り取り位置の設定
		src.m_top = IMAAGE_CUT_SIZE;
		src.m_left = IMAAGE_CUT_SIZE * 3 + IMAAGE_CUT_SIZE * m_ani_frame;
		src.m_right = src.m_left + IMAAGE_CUT_SIZE;
		src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;

		//表示位置の設定
		dst.m_top = 0.0f + m_py;
		dst.m_left = (HERO_SIZE * 0) + m_px;
		dst.m_right = (HERO_SIZE - HERO_SIZE * 0) + m_px;
		dst.m_bottom = HERO_SIZE + m_py;

		//描画
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}

}

//関数　アイテムをとったかどうかの判定
//引数１　CHitBox* hit　：hittoboxの情報
void CObjHero::GetItemsInformation(CHitBox* hit)
{
		//ファイアーアップを取るとボムの火力アップ
		if(hit->CheckObjNameHit(OBJ_FIRE_UP) != nullptr)
		{
			Audio::Start(3);//3番曲をスタート
			//ファイアーアップは15個まで
			if(m_bom_power <15)
			{
				m_bom_power++; 
				((UserData*)Save::GetData())->mFireUpNum++;
			}
		}
		//爆弾アップを取るとボムの置ける最大数がアップ
		if(hit->CheckObjNameHit(OBJ_BOM_UP) != nullptr)
		{
			Audio::Start(3);//3番曲をスタート
			//爆弾アップは10個まで
			if(m_bom_max_num < 10)
			{
				m_bom_max_num++;
				((UserData*)Save::GetData())->mBomUpNum++;
			}
		}
		//リモコンを取るとリモコン機能ON
		if(hit->CheckObjNameHit(OBJ_REMOTE_CONTROLLER) != nullptr)
		{
			Audio::Start(3);//3番曲をスタート
			m_remote_controller = true;
			((UserData*)Save::GetData())->mRemoteController = true;
		}
		//スケートを取るとスピードパワーアップ
		if(hit->CheckObjNameHit(OBJ_SKATE) != nullptr)
		{
			Audio::Start(3);//3番曲をスタート
			m_speed_power+= SKATE_SPEED_POWER;
			((UserData*)Save::GetData())->mSkateNum++;
		}
		//爆弾すり抜けを取ると爆弾の判定無し
		if(hit->CheckObjNameHit(OBJ_BOM_SLIPPING_THROUGH) != nullptr)
		{
			Audio::Start(3);//3番曲をスタート
			m_bom_hit_test = false;
			((UserData*)Save::GetData())->mBomSlippingThrough = true;
		}
		//破壊可能ブロックすり抜けを取ると破壊可能ブロックの判定無し
		if(hit->CheckObjNameHit(OBJ_DESTRUCTALE_BLOCK_SLIPPING_THROUGH) != nullptr)
		{
			Audio::Start(3);//3番曲をスタート
			m_breakable_block_hit_test = false;
			((UserData*)Save::GetData())->mDestructableBlockSlippingThrough = true;
		}
		//ファイアーマンを取ると爆風の判定無し
		if(hit->CheckObjNameHit(OBJ_FIRE_MAN) != nullptr)
		{
			Audio::Start(3);//3番曲をスタート
			m_get_fire_man = true;
			m_blast_hit_test = false;
			((UserData*)Save::GetData())->mFireMan = true;
		}
		//パーフェクトマンを取ると爆風・敵の判定無し
		if(hit->CheckObjNameHit(OBJ_PERFECT_MAN) != nullptr)
		{
			Audio::Start(3);//3番曲をスタート

			Audio::Start(5);//5番曲をスタート

			m_get_parfect_man = true;
			m_enemy_hit_test = false;
			m_blast_hit_test = false;
		}

}

//関数　キー入力
//引数１　CHitBox* hit　:ヒットボックスの情報　スペースキー入力(ボム設置)の際にのみ使う
void CObjHero::KeyInput(CHitBox* hit)
{
	//ブロック情報を持ってくる
	//ボム設置の際に使う
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//キーの入力方向
	if (Input::GetVKey('D') == true || Input::GetVKey(VK_RIGHT) == true)
	{
		m_vx += m_speed_power;
		m_ani_time++;
		m_posture = 1; //右向き0 左向き1 上向2　下向き3
	}
	else if (Input::GetVKey('A') == true || Input::GetVKey(VK_LEFT) == true)
	{
		m_vx -= m_speed_power;
		m_ani_time++;
		m_posture = 0; //右向き0 左向き1 上向2　下向き3
	}
	else if (Input::GetVKey('W') == true || Input::GetVKey(VK_UP) == true)
	{
		m_vy -= m_speed_power;
		m_ani_time++;
		m_posture = 2; //右向き0 左向き1 上向き2　下向き3
	}
	else if (Input::GetVKey('S') == true || Input::GetVKey(VK_DOWN) == true)
	{
		m_vy += m_speed_power;
		m_ani_time++;
		m_posture = 3; //右向き0 左向き1 上向き2　下向き3
	}
	//キー入力が無い場合は静止フレームにする
	else
	{
		m_ani_frame = 1;
		m_ani_time = 0;
	}

	//スペールキー入力
	if (Input::GetVKey(VK_SPACE))
	{
		//ボムの最大数を超えていなかったら
		if (m_bom_num < m_bom_max_num)
		{
			//ボムオブジェクトに接触していなかったら
			if (hit->CheckObjNameHit(OBJ_BOM) == nullptr)
			{
				//爆風オブジェクトに接触っしていなかったら
				if (hit->CheckObjNameHit(OBJ_BLAST) == nullptr)
				{
					//破壊可能オブジェクトに接触していなかったら
					if (hit->CheckObjNameHit(OBJ_DESTRUCTADLE_BLOCK) == nullptr)
					{
						//ドアオブジェクトに接触していなかったら
						if (hit->CheckObjNameHit(OBJ_DOOR) == nullptr)
						{
							m_bom_num++;
							//ボムオブジェクト作成
							CObjBom* obj_bom = new CObjBom(m_px - block->GetScroll(), m_py);	//ボムオブジェクト作成
							Objs::InsertObj(obj_bom, OBJ_BOM, 10);	//ボムオブジェト登録
							
						}
					}
				}
			}
		}
	}

}
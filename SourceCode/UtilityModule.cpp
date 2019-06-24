
#include <math.h>
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include <time.h>
//使用するネームスペース
using namespace GameL;

//関数ダイクストラ法
//引数１	float start_object_x			:スタート地点X位置
//引数２	float start_object_y			:スタート地点Y位置
//引数３	float goal_object_x				:ゴール地点X位置
//引数４	float goal_object_y				:ゴール地点Y位置
//引数５	float bom_hit_test				:ボムの当たり判定
//引数６	float breakable_block_hit_test	:破壊可能ブロックの当たり判定
//戻り値	スタートオブジェクトにどの方向へ行けばいいかの芳香情報など
Node Dijkstra(float start_object_x,float start_object_y,float goal_object_x,float goal_object_y,bool bom_hit_test,bool breakable_block_hit_test)
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	int map[MAP_Y][MAP_X];//マップ情報
	block->GetMap(map);

	//原点を中心にする
	start_object_x += 20;
	start_object_y += 20;
	goal_object_x += 20;
	goal_object_y += 20;

	//方向の情報
	int  direction[4][2]={
		//ｘ、ｙ
		{ 1, 0},//右方向
		{-1, 0},//左方向
		{ 0,-1},//上方向
		{ 0, 1}};//下方向
	
	//nodeをマップ配列分作る
	Node node[MAP_Y][MAP_X];

	//全てのnodeの情報を初期化
	for(int map_y = 0; map_y < MAP_Y; map_y++)
	{
		for(int map_x = 0; map_x < MAP_X; map_x++)
		{
			node[map_y][map_x].cost = 99;//初期化
			node[map_y][map_x].flag = false;
			node[map_y][map_x].node_x = 0;
			node[map_y][map_x].node_y = 0;
		}
	}

	//ゴールオブジェクトの要素数
	int goal_object_element_count_x = ((int)(goal_object_x + (-block->GetScroll())) / BLOCK_SIZE);//ゴールオブジェクトのX位置の要素数
	int goal_object_element_count_y = ((int)goal_object_y / BLOCK_SIZE);//ゴールオブジェクトのY位置の要素数

	//スタートオブジェクトの要素数
	int start_object_element_count_x = ((int)(start_object_x + (-block->GetScroll())) / BLOCK_SIZE);//スタートオブジェクトのX位置の要素数
	int start_object_element_count_y = ((int)start_object_y / BLOCK_SIZE);//スタートオブジェクトのY位置の要素数

	node[goal_object_element_count_y][goal_object_element_count_x].cost = 0;//スタート位置のcostを0にする
	node[goal_object_element_count_y][goal_object_element_count_x].flag = true;//スタート位置のフラグをONにする

	bool flag_true;//true すべてのフラグの中で１つ以上trueになっているものがある場合　false　フラグがたっているものがない場合（全てのフラグがOFFになっていたら。）

	//調べる場所の要素数を入れる変数
	int search_location_x;
	int search_location_y;

	//調べる方向のブロック情報
	int check_orientation_block_information;

	//全ての情報のフラグが立っていたら
	do{
		flag_true = false;//初期化(最初は一つたっているが無視)

		//ループ
		for(int map_y = 0; map_y < MAP_Y; map_y++)
		{
			for(int map_x = 0; map_x < MAP_X; map_x++)
			{
				//node情報にフラグがたっているものを探す
				if(node[map_y][map_x].flag == true)
				{
					//4方向調べる
					for(int Direction = 0; Direction < 4; Direction++)
					{
						//調べる場所を入れる
						search_location_x = map_x + direction[Direction][0];
						search_location_y = map_y + direction[Direction][1];

						//調べる方向のブロック情報
						check_orientation_block_information = map[search_location_y][search_location_x];

						//調べる方向に通れる場所があれば
						//調べる方向にボムがありボム判定が無い場合
						//調べる方向に破壊可能ブロック(アニメーション中も)があり破壊可能ブロック判定が無い場合
						if(check_orientation_block_information == 0 ||
							( (bom_hit_test == false && check_orientation_block_information == 4) ||
							  (breakable_block_hit_test == false && check_orientation_block_information == 10 || check_orientation_block_information == 11) ) )
						{
			
							//自身の移動した後のコストが移動先のコストより小さい場合
							if(node[map_y][map_x].cost + 1 < node[search_location_y][search_location_x].cost)
							{
								//戻るときの方向情報
								node[search_location_y][search_location_x].node_x = (-1)*direction[Direction][0];
								node[search_location_y][search_location_x].node_y = (-1)*direction[Direction][1];

								node[search_location_y][search_location_x].flag = true;	//次調べたいのでフラグをONにする
								node[search_location_y][search_location_x].cost = node[map_y][map_x].cost + 1;	//自身の移動した後のコストを入れる

								flag_true = true;//フラブがONになったので
							}
							
						}
					}

					//調べたからフラグをOFFにする
					node[map_y][map_x].flag = false;
				}
			}
		}

	}while(flag_true == true);//全てのフラグの中で一つも立っているものがない場合ぬける


	//for (int i = 0; i < MAP_Y; i++)
	//{
	//	for (int j = 0; j < MAP_X; j++)
	//	{
	//		//方向オブジェクト作成
	//		CObjDirection* obj_direction = new CObjDirection(j * 40, i * 40 ,node[i][j].node_x,node[i][j].node_y);	//ボムオブジェクト作成
	//		Objs::InsertObj(obj_direction, OBJ_BOM, 100);	//ボムオブジェト登録
	//	}
	//}
	return node[start_object_element_count_y][start_object_element_count_x];
}

//関数ランダム
//引数１	int min	:最小数
//引数２	int max	:最大数
//戻り値	最小数から最大数の間でランダムに値を渡す
int GetRandom(int min,int max)
{
	static char s= 0;
	if (s == 0)
	{
		srand((unsigned)time(NULL));
		s = 1;
	}
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

//関数 当たり判定取得用
//引数1 float x			:オブジェクトのX位置
//引数2 float y			:オブジェクトのY位置
//引数3	bool *up		:上下左右判定の上部分に当たっているかどうかを返す
//引数4	bool *down		:上下左右判定の下部分に当たっているかどうかを返す
//引数5	bool *left		:上下左右判定の左部分に当たっているかどうかを返す
//引数6	bool *right		:上下左右判定の右部分に当たっているかどうかを返す
void HitTestInformation(float x,float y,bool *up,bool *down,bool *left,bool *right,bool bom_hit_test,bool breakable_block_hit_test)
{
	//当たり判定初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//マップ情報
	int map[MAP_Y][MAP_X];

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//マップ情報更新
	block->GetMap(map);

	//原点を中央にする
	x += 20;
	y += 20;

	int elements_count_x = ((int)(x + (-block->GetScroll())) / BLOCK_SIZE);//X位置の要素数
	int elements_count_y = ((int) y / BLOCK_SIZE);//Y位置の要素数

	//方向の情報
	int  Direction[4][2]={
		//ｘ、ｙ
		{ 1, 0},//右方向
		{-1, 0},//左方向
		{ 0,-1},//上方向
		{ 0, 1}};//下方向

	//調べる方向のブロック情報を入れる変数
	int check_orientation_block_information;

	//上下左右調べる
	for(int direction = 0; direction < 4; direction++)
	{
		//調べる方向のブロック情報を入れる
		check_orientation_block_information = map[elements_count_y + Direction[direction][1]][elements_count_x + Direction[direction][0]];

		//調べる方向のブロックが通れないところだったら。
		//ボムの判定が無い場合４も通れるところなので処理しない
		//破壊可能ブロックの判定が無い場合10,11も通れるところなので処理しない
		if (check_orientation_block_information == 0 ||
			(bom_hit_test == false && check_orientation_block_information == 4) ||
			(breakable_block_hit_test == false && (check_orientation_block_information == 10 || check_orientation_block_information == 11)))
		{

		}
		else
		{
			//方向別に当たっているか判定
			if(direction == 0)
			{
				*right = true;
			}
			if(direction == 1)
			{
				*left = true;
			}
			if(direction == 2)
			{
				*up = true;
			}
			if(direction == 3)
			{
				*down = true;
			}
		}
	}
}

//関数 移動できる方向にランダムに移動
//引数1	float *vx			:X方向への移動量
//引数2	float *vy			:Y方向への移動量
//引数3 float speed_power	:スピードパワー
//引数4	bool up				:上下左右判定の上部分に当たっているかどうかを返す
//引数5	bool down			:上下左右判定の下部分に当たっているかどうかを返す
//引数6	bool left			:上下左右判定の左部分に当たっているかどうかを返す
//引数7	bool right			:上下左右判定の右部分に当たっているかどうかを返す
void MovableTargetRandomByMove(float *vx,float *vy,float speed_power,bool up,bool down,bool left,bool right)
{
	//ランダムで値を入れる
	int random = GetRandom(1,2);

	//上下に当たり判定があるなら
	if(up == true && down == true)
	{
		//上下はいけないので右か左に行く
		random = 2;
	}
	
	//左右に当たり判定があるなら
	if(right == true && left == true)
	{
		//左右はいけないので上か下に行く
		random = 1;
	}

	//上下
	if(random == 1)
	{
		//ｘ方向へは移動しないので０を代入
		*vx = 0;
		//ランダムで値を入れる
		random = GetRandom(1,2);

		//		上	　&& 上方向に当たり判定が無い場合　｜｜　下方向へ移動できない状態だった場合上に移動	
		if((random == 1 && up == false)|| down == true)
		{
			*vy =-speed_power;
		}
		//下
		else
		{
				
			*vy = speed_power;
		}
	}
	//左右
	else
	{
		//ｙ方向へは移動しないので０を代入
		*vy = 0;
		//ランダムで値を入れる
		random = GetRandom(1,2);
		//		左	　&& 左方向に当たり判定が無い場合｜｜	右の方向へ移動できない状態だった場合左に移動
		if((random == 1 && left == false)|| right == true)
		{
			*vx =-speed_power; 
		}
		//右
		else
		{
			*vx = speed_power;
		}
	}

}
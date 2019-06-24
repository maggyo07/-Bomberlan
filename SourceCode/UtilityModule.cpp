
#include <math.h>
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include <time.h>
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�֐��_�C�N�X�g���@
//�����P	float start_object_x			:�X�^�[�g�n�_X�ʒu
//�����Q	float start_object_y			:�X�^�[�g�n�_Y�ʒu
//�����R	float goal_object_x				:�S�[���n�_X�ʒu
//�����S	float goal_object_y				:�S�[���n�_Y�ʒu
//�����T	float bom_hit_test				:�{���̓����蔻��
//�����U	float breakable_block_hit_test	:�j��\�u���b�N�̓����蔻��
//�߂�l	�X�^�[�g�I�u�W�F�N�g�ɂǂ̕����֍s���΂������̖F�����Ȃ�
Node Dijkstra(float start_object_x,float start_object_y,float goal_object_x,float goal_object_y,bool bom_hit_test,bool breakable_block_hit_test)
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	int map[MAP_Y][MAP_X];//�}�b�v���
	block->GetMap(map);

	//���_�𒆐S�ɂ���
	start_object_x += 20;
	start_object_y += 20;
	goal_object_x += 20;
	goal_object_y += 20;

	//�����̏��
	int  direction[4][2]={
		//���A��
		{ 1, 0},//�E����
		{-1, 0},//������
		{ 0,-1},//�����
		{ 0, 1}};//������
	
	//node���}�b�v�z�񕪍��
	Node node[MAP_Y][MAP_X];

	//�S�Ă�node�̏���������
	for(int map_y = 0; map_y < MAP_Y; map_y++)
	{
		for(int map_x = 0; map_x < MAP_X; map_x++)
		{
			node[map_y][map_x].cost = 99;//������
			node[map_y][map_x].flag = false;
			node[map_y][map_x].node_x = 0;
			node[map_y][map_x].node_y = 0;
		}
	}

	//�S�[���I�u�W�F�N�g�̗v�f��
	int goal_object_element_count_x = ((int)(goal_object_x + (-block->GetScroll())) / BLOCK_SIZE);//�S�[���I�u�W�F�N�g��X�ʒu�̗v�f��
	int goal_object_element_count_y = ((int)goal_object_y / BLOCK_SIZE);//�S�[���I�u�W�F�N�g��Y�ʒu�̗v�f��

	//�X�^�[�g�I�u�W�F�N�g�̗v�f��
	int start_object_element_count_x = ((int)(start_object_x + (-block->GetScroll())) / BLOCK_SIZE);//�X�^�[�g�I�u�W�F�N�g��X�ʒu�̗v�f��
	int start_object_element_count_y = ((int)start_object_y / BLOCK_SIZE);//�X�^�[�g�I�u�W�F�N�g��Y�ʒu�̗v�f��

	node[goal_object_element_count_y][goal_object_element_count_x].cost = 0;//�X�^�[�g�ʒu��cost��0�ɂ���
	node[goal_object_element_count_y][goal_object_element_count_x].flag = true;//�X�^�[�g�ʒu�̃t���O��ON�ɂ���

	bool flag_true;//true ���ׂẴt���O�̒��łP�ȏ�true�ɂȂ��Ă�����̂�����ꍇ�@false�@�t���O�������Ă�����̂��Ȃ��ꍇ�i�S�Ẵt���O��OFF�ɂȂ��Ă�����B�j

	//���ׂ�ꏊ�̗v�f��������ϐ�
	int search_location_x;
	int search_location_y;

	//���ׂ�����̃u���b�N���
	int check_orientation_block_information;

	//�S�Ă̏��̃t���O�������Ă�����
	do{
		flag_true = false;//������(�ŏ��͈�����Ă��邪����)

		//���[�v
		for(int map_y = 0; map_y < MAP_Y; map_y++)
		{
			for(int map_x = 0; map_x < MAP_X; map_x++)
			{
				//node���Ƀt���O�������Ă�����̂�T��
				if(node[map_y][map_x].flag == true)
				{
					//4�������ׂ�
					for(int Direction = 0; Direction < 4; Direction++)
					{
						//���ׂ�ꏊ������
						search_location_x = map_x + direction[Direction][0];
						search_location_y = map_y + direction[Direction][1];

						//���ׂ�����̃u���b�N���
						check_orientation_block_information = map[search_location_y][search_location_x];

						//���ׂ�����ɒʂ��ꏊ�������
						//���ׂ�����Ƀ{��������{�����肪�����ꍇ
						//���ׂ�����ɔj��\�u���b�N(�A�j���[�V��������)������j��\�u���b�N���肪�����ꍇ
						if(check_orientation_block_information == 0 ||
							( (bom_hit_test == false && check_orientation_block_information == 4) ||
							  (breakable_block_hit_test == false && check_orientation_block_information == 10 || check_orientation_block_information == 11) ) )
						{
			
							//���g�̈ړ�������̃R�X�g���ړ���̃R�X�g��菬�����ꍇ
							if(node[map_y][map_x].cost + 1 < node[search_location_y][search_location_x].cost)
							{
								//�߂�Ƃ��̕������
								node[search_location_y][search_location_x].node_x = (-1)*direction[Direction][0];
								node[search_location_y][search_location_x].node_y = (-1)*direction[Direction][1];

								node[search_location_y][search_location_x].flag = true;	//�����ׂ����̂Ńt���O��ON�ɂ���
								node[search_location_y][search_location_x].cost = node[map_y][map_x].cost + 1;	//���g�̈ړ�������̃R�X�g������

								flag_true = true;//�t���u��ON�ɂȂ����̂�
							}
							
						}
					}

					//���ׂ�����t���O��OFF�ɂ���
					node[map_y][map_x].flag = false;
				}
			}
		}

	}while(flag_true == true);//�S�Ẵt���O�̒��ň�������Ă�����̂��Ȃ��ꍇ�ʂ���


	//for (int i = 0; i < MAP_Y; i++)
	//{
	//	for (int j = 0; j < MAP_X; j++)
	//	{
	//		//�����I�u�W�F�N�g�쐬
	//		CObjDirection* obj_direction = new CObjDirection(j * 40, i * 40 ,node[i][j].node_x,node[i][j].node_y);	//�{���I�u�W�F�N�g�쐬
	//		Objs::InsertObj(obj_direction, OBJ_BOM, 100);	//�{���I�u�W�F�g�o�^
	//	}
	//}
	return node[start_object_element_count_y][start_object_element_count_x];
}

//�֐������_��
//�����P	int min	:�ŏ���
//�����Q	int max	:�ő吔
//�߂�l	�ŏ�������ő吔�̊ԂŃ����_���ɒl��n��
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

//�֐� �����蔻��擾�p
//����1 float x			:�I�u�W�F�N�g��X�ʒu
//����2 float y			:�I�u�W�F�N�g��Y�ʒu
//����3	bool *up		:�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//����4	bool *down		:�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//����5	bool *left		:�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
//����6	bool *right		:�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
void HitTestInformation(float x,float y,bool *up,bool *down,bool *left,bool *right,bool bom_hit_test,bool breakable_block_hit_test)
{
	//�����蔻�菉����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//�}�b�v���
	int map[MAP_Y][MAP_X];

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//�}�b�v���X�V
	block->GetMap(map);

	//���_�𒆉��ɂ���
	x += 20;
	y += 20;

	int elements_count_x = ((int)(x + (-block->GetScroll())) / BLOCK_SIZE);//X�ʒu�̗v�f��
	int elements_count_y = ((int) y / BLOCK_SIZE);//Y�ʒu�̗v�f��

	//�����̏��
	int  Direction[4][2]={
		//���A��
		{ 1, 0},//�E����
		{-1, 0},//������
		{ 0,-1},//�����
		{ 0, 1}};//������

	//���ׂ�����̃u���b�N��������ϐ�
	int check_orientation_block_information;

	//�㉺���E���ׂ�
	for(int direction = 0; direction < 4; direction++)
	{
		//���ׂ�����̃u���b�N��������
		check_orientation_block_information = map[elements_count_y + Direction[direction][1]][elements_count_x + Direction[direction][0]];

		//���ׂ�����̃u���b�N���ʂ�Ȃ��Ƃ��낾������B
		//�{���̔��肪�����ꍇ�S���ʂ��Ƃ���Ȃ̂ŏ������Ȃ�
		//�j��\�u���b�N�̔��肪�����ꍇ10,11���ʂ��Ƃ���Ȃ̂ŏ������Ȃ�
		if (check_orientation_block_information == 0 ||
			(bom_hit_test == false && check_orientation_block_information == 4) ||
			(breakable_block_hit_test == false && (check_orientation_block_information == 10 || check_orientation_block_information == 11)))
		{

		}
		else
		{
			//�����ʂɓ������Ă��邩����
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

//�֐� �ړ��ł�������Ƀ����_���Ɉړ�
//����1	float *vx			:X�����ւ̈ړ���
//����2	float *vy			:Y�����ւ̈ړ���
//����3 float speed_power	:�X�s�[�h�p���[
//����4	bool up				:�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//����5	bool down			:�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//����6	bool left			:�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
//����7	bool right			:�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
void MovableTargetRandomByMove(float *vx,float *vy,float speed_power,bool up,bool down,bool left,bool right)
{
	//�����_���Œl������
	int random = GetRandom(1,2);

	//�㉺�ɓ����蔻�肪����Ȃ�
	if(up == true && down == true)
	{
		//�㉺�͂����Ȃ��̂ŉE�����ɍs��
		random = 2;
	}
	
	//���E�ɓ����蔻�肪����Ȃ�
	if(right == true && left == true)
	{
		//���E�͂����Ȃ��̂ŏォ���ɍs��
		random = 1;
	}

	//�㉺
	if(random == 1)
	{
		//�������ւ͈ړ����Ȃ��̂łO����
		*vx = 0;
		//�����_���Œl������
		random = GetRandom(1,2);

		//		��	�@&& ������ɓ����蔻�肪�����ꍇ�@�b�b�@�������ֈړ��ł��Ȃ���Ԃ������ꍇ��Ɉړ�	
		if((random == 1 && up == false)|| down == true)
		{
			*vy =-speed_power;
		}
		//��
		else
		{
				
			*vy = speed_power;
		}
	}
	//���E
	else
	{
		//�������ւ͈ړ����Ȃ��̂łO����
		*vy = 0;
		//�����_���Œl������
		random = GetRandom(1,2);
		//		��	�@&& �������ɓ����蔻�肪�����ꍇ�b�b	�E�̕����ֈړ��ł��Ȃ���Ԃ������ꍇ���Ɉړ�
		if((random == 1 && left == false)|| right == true)
		{
			*vx =-speed_power; 
		}
		//�E
		else
		{
			*vx = speed_power;
		}
	}

}
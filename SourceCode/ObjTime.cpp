//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "Trace.h"
#include "UtilityModule.h"
#include "GameHead.h"
#include "ObjTime.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjTime::CObjTime(int max_time)
{
	m_time = max_time * 60;
}
//�C�j�V�����C�Y
void CObjTime::Init()
{
	//�G�͂܂��o���Ȃ�
	m_out_put_enemy = false;

	m_enemy_time = 0;//�G���ԏ�����
}
//�A�N�V����
void CObjTime::Action()
{
	if(m_out_put_enemy == false)
	{
		m_time--;
	}

	if(m_time < 0)
	{
		m_time = 0;
		//���Ԑ؂�Ȃ̂œG���o��
		m_out_put_enemy = true;
		Audio::Stop(0);//0�ԋȂ��X�g�b�v
		Audio::Start(2);//2�ԋȂ��X�^�[�g
	}

	//�G���o���Ɣ��f�����̂Ŏ��Ԃ����Z���Ă���
	if (m_out_put_enemy == true)
	{
		m_enemy_time++;
	}
	//�G���o���Ƃ��̍��W�擾�ϐ�
	float enemy_x;
	float enemy_y;

	//�ŏ��Ɉ���60*100(100�b)���ƂɓG�o��
	if ((m_enemy_time >= 1 && m_enemy_time % (60 * 100) == 0) || m_enemy_time == 1)
	{
		for (int enemy_num = 0; enemy_num < 1; enemy_num++)
		{
			//�u����ꏊ���烉���_���Ō��߂�
			AllocablePosition(&enemy_x, &enemy_y);

			//�|���^��(�G)�쐬
			CObjPontan* obj_pontan = new CObjPontan(enemy_x, enemy_y);
			Objs::InsertObj(obj_pontan, OBJ_PONTAN, 10);

			//�G���o�������̂�
			((UserData*)Save::GetData())->mEnemyNumber++;
		}

	}

}
//�h���[
void CObjTime::Draw()
{
	//�`��J���[���

	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	wchar_t str[128];

	//�b�̒l�𕶎���	
	swprintf_s(str,L"TIME		%d",(m_time / 60) );//�����𕶎���

	Font::StrDraw(str,10,10,30,c);

}

//�֐��@�}�b�v���̔z�u�\�ꏊ�����߂�
//�����P float* x	:���߂����X�ʒu
//�����Q float* y	:���߂����Y�ʒu
void CObjTime::AllocablePosition(float* x, float* y)
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l�����������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//�}�b�v���
	int map[MAP_Y][MAP_X];
	//�}�b�v���X�V
	block->GetMap(map);

	//��l���̗v�f��
	int hero_element_count_x = ((int)(hero->GetX() + (-block->GetScroll())) / BLOCK_SIZE);
	int hero_element_count_y = ((int)hero->GetY() / BLOCK_SIZE);

	//�u����ꏊ�������邩������ϐ�
	int can_put_location = 0;

	//���ׂẴ}�b�v��������
	//�u����ꏊ�������邩�𐔂���
	for (int map_y = 0; map_y < MAP_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_X; map_x++)
		{
			//��l����X�ʒu�{5���E���������͎�l����X�ʒu-5��荶��
			//��l����Y�ʒu�{5��艺���������͎�l����Y�ʒu-5���㑤
			if (map_x > hero_element_count_x + 5 || map_x < hero_element_count_x - 5 || 
				map_y > hero_element_count_y + 5 || map_y < hero_element_count_y - 5)
			{
				//�}�b�v�̏�̕��͋󔒂Ȃ̂ł��̏ꏊ�ȊO
				if (map_y > 3)
				{
					//�u����ꏊ���ǂ���
					if (map[map_y][map_x] == 0)
					{
						//�u����ꏊ���������̂ŉ��Z
						can_put_location++;
					}
				}
			}
		}
	}
	
	//�u����ꏊ�̒����烉���_���Ō��߂�
	int random = GetRandom(1, can_put_location);

	//���ׂẴ}�b�v��������
	//�u����ꏊ��������̂��킩�����̂�rancom�Ԗڂ̂Ƃ����z�u�ꏊ�Ƃ��Č��߂�
	for (int map_y = 0; map_y < MAP_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_X; map_x++)
		{
			//��l����X�ʒu�{5���E���������͎�l����X�ʒu-5��荶��
			//��l����Y�ʒu�{5��艺���������͎�l����Y�ʒu-5���㑤
			if (map_x > hero_element_count_x + 5 || map_x < hero_element_count_x - 5 ||
				map_y > hero_element_count_y + 5 || map_y < hero_element_count_y - 5)
			{
				//�}�b�v�̏�̕��͋󔒂Ȃ̂ł��̏ꏊ�ȊO
				if (map_y > 3)
				{
					//�u����ꏊ���ǂ���
					if (map[map_y][map_x] == 0)
					{
						if (random == 1)
						{
							*x = map_x * BLOCK_SIZE;
							*y = map_y * BLOCK_SIZE;
							random--;
						}
						else
						{
							random--;
						}
					}
				}
			}
		}
	}
	
		
}
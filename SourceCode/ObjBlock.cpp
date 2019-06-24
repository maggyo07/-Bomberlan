//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjBlock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjBlock::CObjBlock(int map[MAP_Y][MAP_X])
{
	//�}�b�v�f�[�^�R�s�[
	memcpy(m_map,map,sizeof(int) * (MAP_X*MAP_Y));

}
void CObjBlock::GetMap(int map[MAP_Y][MAP_X])
{
	//�}�b�v�f�[�^�R�s�[
	memcpy(map, m_map, sizeof(int) * (MAP_X*MAP_Y));
}
//�}�b�v�ύX�p
void CObjBlock::MapChange(int map[MAP_Y][MAP_X])
{
	//�}�b�v�f�[�^�R�s�[
	memcpy(m_map,map,sizeof(int) * (MAP_X*MAP_Y));
}
//�C�j�V�����C�Y
void CObjBlock::Init()
{
	m_scroll = 0.0f;
	m_magma =192.0f;


	//��l�����K��
	CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);

	//��l���I�u�W�F�N�g�����݂��Ă�����
	if(hero != nullptr)
	{
		m_hero_x = hero->GetX();
		m_hero_y = hero->GetY();
	}
	else
	{
		m_hero_x = 0;
		m_hero_y = 0;
	}
	
}

//BlockDrawMethod�֐�
//�����Pfloat�@��	�F���\�[�X�؂���ʒu��
//�����Qfloat�@��	�F���\�[�X�؂���ʒu��
//�����RRECT_F�� dst�F�`��ʒu
//�����Sfloat�@c[]	�F�J���[���
//�u���b�N��40*40����`��p�B���\�[�X�؂���ʒu�݂̂��A����
//�ݒ�ł���
void CObjBlock::BlockDraw(float x, float y, RECT_F* dst, float c[])
{
	RECT_F src;
	src.m_top	= y;
	src.m_left	= x;
	src.m_right	= src.m_left + IMAAGE_CUT_SIZE;
	src.m_bottom= src.m_top + IMAAGE_CUT_SIZE;
	//�`��
	Draw::Draw(0,&src,dst,c,0.0f);

}

//���ϊ֐�
//����1,2	float ax , ay :A�x�N�g��
//����3,4	float bx , by :B�x�N�g��
//�߂�l�@float�@�F�ˉe
//���e�@A�x�N�g����B�x�N�g���œ��ς��s�����ˉe���߂�
float CObjBlock::Dot(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * bx + ay * by;

	return t;

}
//�O�ϊ֐�
//����1,2	float ax , ay :A�x�N�g��
//����3,4	float bx , by :B�x�N�g��
//�߂�l�@float�@�F�ˉe
//���e�@A�x�N�g����B�x�N�g���ŊO�ς��s�����ˉe���߂�
float CObjBlock::Cross(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * by - ay * bx;

	return t;
}

//���������߂�}�N��
#define SGN(x) 1 - (x <= 0) - (x < 0)

//���Ɛ��Ƃ̌�������
//���� float 1,2	a1x , a1y
//���� float 3,4	a2x , a2y
//���� float 5,6	b1x , b1y
//���� float 7,8	b2x , b2y
//���� float 9,10	out_px,out_py
//�߂�l�@bool	:true��_�L�� false = ��_����
//���e�F������A�EB�x�N�g���̌�_�������Aout_px��out_py�ɕԂ�
bool CObjBlock::LineCrossPoint(
		float a1x,float a1y,float a2x,float a2y,
		float b1x,float b1y,float b2x,float b2y,
		float* out_px,float* out_py
)
{
	//�G���[�R�[�h
	*out_px =-99999.0f;
	*out_py =-99999.0f;

	//A�x�N�g���쐬(a2��a1)
	float ax = a2x - a1x;
	float ay = a2y - a1y;

	//B�x�N�g���쐬(b2��b1)
	float bx = b2x - b1x;
	float by = b2y - b1y;

	//C�x�N�g���쐬(b1��a1)
	float cx = b1x - a1x;
	float cy = b1y - a1y;

	//D�x�N�g���쐬(d2��a1)
	float dx = b2x - a1x;
	float dy = b2y - a1y;

	//A*C�̎ˉe��A*B�̎ˉe�����߂�
	float t1 = Cross(ax,ay,cx,cy);
	float t2 = Cross(ax,ay,dx,dy);

	//�������������ɂȂ��Ă��邩���`�F�b�N
	if(SGN(t1) == SGN(t2))
	{
		return false;	//��_����
	}

	//�ˉe���Βl��
	t1 = abs(t1);
	t2 = abs(t2);

	//��_�����߂�
	float px = bx * (t1 / (t1 + t2)) + b1x;
	float py = by * (t1 / (t1 + t2)) + b1y;

	//AP�x�N�g��(p��a1)
	float apx = px - a1x;
	float apy = py - a1y;

	//BP�x�N�g��(p��a2)
	float bpx = px - a2x;
	float bpy = py - a2y;

	//A�EAP�̎ˉe��A�EBP�̎ˉe�����߂�
	float w1 = Dot(ax,ay,apx,apy);
	float w2 = Dot(ax,ay,bpx,bpy);

	//�����`�F�b�N
	if(SGN(w1) == SGN(w2))
	{
		return false;	//��_���O
	}
	//��_��Ԃ�
	*out_px = px;
	*out_py = py;

	return true;
}

//��l���ƕǂ̌�������֐�
//����1,2
//����3,4
//����5,6
//����7
//��l���̈ʒu+�ړ��x�N�g���Ɗe�u���b�N�̕ӂŌ���������s��
//�ł��߂���_�̈ʒu�Ƌ�����Ԃ�
bool CObjBlock::HeroBlockCrossPoint(
		float x,float y,float vx,float vy,
		float *out_px,float *out_py,float* out_len
	)
{
	bool pb = false;	//��_�m�F�p
	float len = 99999.0f;//��_�Ƃ̋���
	//�u���b�N�̕Ӄx�N�g��
	float edge[4][4]=
	{
		{ 0, 0,64, 0},//��
		{64, 0,64,64},//��
		{64,64, 0,64},//��
		{ 0,64, 0, 0},//��
	};

	//m_map�̑S�v�f�ɃA�N�Z�X
	for(int i = 0; i < 10 ; i++)
	{
		for(int j = 0 ; j < 100 ; j++)
		{
			if(m_map[i][j] != 0 )
			{
				//�u���b�N�̂S�ӂ����_��T��
				for(int k = 0; k < 4 ; k++)
				{
					//��_��T��
					float px,py;
					bool b;
					float l = 0.0f;
					b = LineCrossPoint(x,y,x+vx,y+vy,
						j*64+edge[k][0], i*64+edge[k][1],j*64+edge[k][2],i*64+edge[k][3],
						&px,&py);

					//��_�`�F�b�N
					if(b == true)
					{
						//��_�Ƃ̊Ԋu�����߂�
						l=sqrt((px - x) * (px - x) + (py - y) * (py - y));

						//��������_�̒��ōł��������Z�����̂�T��
						if(len > l)
						{
							len = l;
							*out_px = px;
							*out_py = py;
							pb = true;
						}
					}
				}
			}
		}
	}

	*out_len = len;

	return pb;
}
//BlockHit�֐�
//�����P	float *x		:������s��object��X�ʒu
//�����Q	float *y		:������s��object��Y�ʒu
//�����R	bool scroll_on	:������s��object�̓X�N���[���̉e����^���邩�ǂ���(true=�^����@false=�^���Ȃ�)
//�����S	bool *up		:�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//�����T	bool *down		:�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//�����U	bool *left		:�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
//�����V	bool *right		:�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
//�����W	float *rvx		:���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
//�����X	float *rvy		:�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l��ς��ĕԂ�
//�����P�O	bool bom_hit_test			:�{���ɓ����蔻���t���邩�ǂ���(true = �L��@false = ����)
//�����P�P	bool breakable_block_hit_test	:�j��\�u���b�N�ɓ����蔻���t���邩�ǂ���(true = �L��@false = ����)
//�����P�Q	const float *speed_power	:�X�s�[�h�̃p���[

//������s��object�ƃu���b�N40*40����ŁA�����蔻��Ə㉺���E������s���B
//���̌��ʂ͈����S�`�P�O�ɕԂ�
void CObjBlock::BlockHit(
	float *x,float *y,bool scroll_on,
	bool *up,bool *down,bool *left,bool *right,
	float *vx,float *vy,bool bom_hit_test,bool breakable_block_hit_test,const float *speed_power
	)
{
	//�Ռ���Ԋm�F�p�t���O�̏�����
	*up		=false;
	*down	=false;
	*left	=false;
	*right	=false;

	//��l�����������Ă���
	CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);

	//�����Ă����I�u�W�F�N�g���W����l���̂��̂��ǂ����m�F�p
	bool hero_is_confirmation = false;//true:��l���̂��̂ƒf��  false:��l���̂��̂Ŗ����ƒf��

	//��l���I�u�W�F�N�g�����݂��Ă�����
	if(hero != nullptr)
	{
		//X�ʒu������
		if(*x == hero->GetX())
		{
			//Y�ʒu������
			if(*y == hero->GetY())
			{
				//�����Ă����I�u�W�F�N�g�̍��W����l���̍��W�ƈ�v
				hero_is_confirmation = true;
			}
		}
	}

	//m_mao�̑S�v�f�ɃA�N�Z�X
	for(int i =0 ; i < MAP_Y ; i++)
	{
		for(int j = 0; j < MAP_X ; j++)
		{
			if(m_map[i][j] > 0)
			{
				//�{�����肪�Ȃ��Ă����肵�悤�Ƃ��Ă���ꏊ�Ƀ{�����������珈�������Ȃ�
				if(bom_hit_test == false && m_map[i][j] == 4);
				//�j��\�u���b�N���肪�Ȃ��Ă����肵�悤�Ƃ��Ă���ꏊ�ɔj��\�u���b�N(����݂̂�A�j���[�V������)���������珈�����Ȃ�
				else if(breakable_block_hit_test == false && (m_map[i][j] == 10 || m_map[i][j] == 11));

				else
				{
					//�v�f�ԍ������W�ɕύX
					float bx = j * BLOCK_SIZE;
					float by = i * BLOCK_SIZE;

					//�X�N���[���̉e��
					float scroll = scroll_on ? m_scroll : 0 ;

					//�I�u�W�F�N�g�ƃu���b�N�̂����蔻��
					if((*x + (-scroll)+BLOCK_SIZE > bx) && (*x+(-scroll) < bx+ BLOCK_SIZE) && (*y + BLOCK_SIZE > by) && (*y < by + BLOCK_SIZE))
					{
						//�㉺���E����

						//vector�̍쐬
						float rvx = (*x + (-scroll)) - bx;
						float rvy = *y - by;

						//���������߂�
						float len = sqrt(rvx * rvx + rvy * rvy);

						//�p�x�����߂�
						float r = atan2( rvy , rvx);
						r = r * 180.0f / 3.14f;

						if(r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						if(len < 88.0)
						{
							//�p�x�ŏ㉺���E�𔻒�
							//�E
							if((r < 45 && r >= 0) || r > 315)
							{
								if (!(*vx > 0))//�E�Ɉړ����Ă����画�肵�Ȃ�
								{
									*right = true;//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
									*x = bx + BLOCK_SIZE + (scroll);//�u���b�N�̈ʒu�@+�@�I�u�W�F�N�g�̕�

									//�^�E(�^��)����
									if ((r < 45 && 0 < r))
									{
										//��l���I�u�W�F�N�g��������K��̃{�^�����������ꍇ���������B
										//��l���I�u�W�F�N�g�ł͂Ȃ������炻�̂܂܏���
										if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetVKey('A') == true || Input::GetVKey(VK_LEFT) == true)))
										{
											//��ɉ�������������B�{�����肪���������画��Ȃ��ɂ���B�j��\�u���b�N���肪���������画��Ȃ��ɂ���
											if (m_map[i - 1][j] == 0 || (bom_hit_test == false && m_map[i - 1][j] == 4) ||
												(breakable_block_hit_test == false && m_map[i - 1][j] == 10 || m_map[i - 1][j] == 11))
											{
												//��̏�
												if (r <= 45 && r >= 44)
												{
													//����Y�̈ʒu�̏�̈ʒu�Ɉړ�
													*y = (i - 1) * BLOCK_SIZE;
													*x += -1.0f;
												}
												else
												{
													*vy = -*speed_power;
												}
											}
										}
									}
									//�^�E(�^��)��艺 && ���Ƀu���b�N������������
									else if (r > 315)
									{
										//��l���I�u�W�F�N�g��������K��̃{�^�����������ꍇ���������B
										//��l���I�u�W�F�N�g�ł͂Ȃ������炻�̂܂܏���
										if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetVKey('A') == true || Input::GetVKey(VK_LEFT) == true)))
										{
											//���ɉ�������������B�{�����肪���������画��Ȃ��ɂ���B�j��\�u���b�N���肪���������画��Ȃ��ɂ���
											if (m_map[i + 1][j] == 0 || (bom_hit_test == false && m_map[i + 1][j] == 4) ||
												(breakable_block_hit_test == false && m_map[i + 1][j] == 10 || m_map[i + 1][j] == 11))
											{
												//���̉�
												if (r >= 315 && r <= 316)
												{
													//����Y�̈ʒu�̉��̈ʒu�Ɉړ�
													*y = (i + 1) * BLOCK_SIZE;
													*x += -1.0f;
												}
												else
												{
													*vy = *speed_power;
												}
											}
										}
									}
									//���ɂ���ɂ��u���b�N����������
									else if (m_map[i + 1][j] != 0 && m_map[i - 1][j] != 0)
									{
										*vx = -(*vx) * 0.1f;//-VX*�����W��
									}
								}
							}
							//��
							if(r > 45 && r < 135)
							{
								if (!(*vy < 0))//��Ɉړ����Ă����画�肵�Ȃ�
								{
									*down = true;//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
									*y = by - BLOCK_SIZE;//�u���b�N�̈ʒu�@-�@��l���̕�
									*vy = 0.0f;
									//�^����E
									if (r > 45 && r < 90)
									{
										//�E�ɉ�������������B�{�����肪���������画��Ȃ��ɂ���B�j��\�u���b�N���肪���������画��Ȃ��ɂ���
										if (m_map[i][j + 1] == 0 || (bom_hit_test == false && m_map[i][j + 1] == 4) ||
											(breakable_block_hit_test == false && m_map[i][j + 1] == 10 || m_map[i][j + 1] == 11))
										{
											//�E�̉E
											if (r > 45 && r < 46)
											{
												*x = (j + 1) * BLOCK_SIZE + scroll;
												*y += 1.0f;
											}
											else
											{
												*vx = *speed_power;
											}
										}
									}
									//�^���荶
									else if (r < 135 && r > 90)
									{
										//���ɉ�������������B�{�����肪���������画��Ȃ��ɂ���B�j��\�u���b�N���肪���������画��Ȃ��ɂ���
										if (m_map[i][j - 1] == 0 || (bom_hit_test == false && m_map[i][j - 1] == 4) ||
											(breakable_block_hit_test == false && m_map[i][j - 1] == 10 || m_map[i][j - 1] == 11))
										{
											//���̍�
											if (r < 135 && r > 134)
											{
												*x = (j - 1) * BLOCK_SIZE + scroll;
												*y += 1.0f;
											}
											else
											{
												*vx = -*speed_power;
											}
										}
									}
								}
							}
							//��
							if(r > 135 && r < 225)
							{
								if (!(*vx < 0))//���Ɉړ����Ă����画�肵�Ȃ�
								{
									*left = true;//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
									*x = bx - BLOCK_SIZE + (scroll);//�u���b�N�̈ʒu�@-�@�I�u�W�F�N�g��

									//�^������
									if ((r > 135 && r < 180))
									{
										//��l���I�u�W�F�N�g��������K��̃{�^�����������ꍇ���������B
										//��l���I�u�W�F�N�g�ł͂Ȃ������炻�̂܂܏���
										if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetVKey('D') == true || Input::GetVKey(VK_RIGHT) == true)))
										{
											//��ɉ�������������B�{�����肪���������画��Ȃ��ɂ���B�j��\�u���b�N���肪���������画��Ȃ��ɂ���
											if (m_map[i - 1][j] == 0 || (bom_hit_test == false && m_map[i - 1][j] == 4) ||
												(breakable_block_hit_test == false && m_map[i - 1][j] == 10 || m_map[i - 1][j] == 11))
											{
												//���̍�
												if (r > 135 && r < 136)
												{
													*y = (i - 1) * BLOCK_SIZE;
													*x += 1.0f;
												}
												else
												{
													*vy = -*speed_power;
												}
											}
										}
									}
									//�^����艺
									else if ((r < 225 || r > 180))
									{
										//��l���I�u�W�F�N�g��������K��̃{�^�����������ꍇ���������B
										//��l���I�u�W�F�N�g�ł͂Ȃ������炻�̂܂܏���
										if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetVKey('D') == true || Input::GetVKey(VK_RIGHT) == true)))
										{
											//���ɉ�������������B�{�����肪���������画��Ȃ��ɂ���B�j��\�u���b�N���肪���������画��Ȃ��ɂ���
											if (m_map[i + 1][j] == 0 || (bom_hit_test == false && m_map[i + 1][j] == 4) ||
												(breakable_block_hit_test == false && m_map[i + 1][j] == 10 || m_map[i + 1][j] == 11))
											{
												//�E�̉E
												if (r < 225 && r > 224)
												{
													*y = (i + 1) * BLOCK_SIZE;
													*x += 1.0f;
												}
												else
												{
													*vy = *speed_power;
												}
											}
										}
									}
									//�㉺�Ƀu���b�N����������
									else if (m_map[i + 1][j] != 0 && m_map[i + 1][j] != 0)
									{
										*vx = -(*vx) * 0.1f;//-VX*�����W��
									}
								}
							
							}
							//��
							if(r > 225 && r < 315)
							{
								if (!(*vy > 0))//���Ɉړ����Ă����画�肵�Ȃ�
								{
									*up = true;//��l�����猩�ď�̕������Փ˂��Ă���
									*y = by + BLOCK_SIZE;//�u���b�N�̈ʒu�@+�@��l���̕�
									*vy = 0.0f;
									//�^����荶
									if (r > 225 && r < 275)
									{
										//���ɉ�������������B�{�����肪���������画��Ȃ��ɂ���B�j��\�u���b�N���肪���������画��Ȃ��ɂ���
										if (m_map[i][j - 1] == 0 || (bom_hit_test == false && m_map[i][j - 1] == 4) ||
											(breakable_block_hit_test == false && m_map[i][j - 1] == 10 || m_map[i][j - 1] == 11))
										{
											//���̍�
											if (r > 225 && r < 226)
											{
												*x = (j - 1) * BLOCK_SIZE + scroll;
												*y -= 1.0f;
											}
											else
											{
												*vx = -*speed_power;
											}
										}
									}
									//�^�����E
									else if (r < 315 && r > 275)
									{
										//�E�ɉ�������������B�{�����肪���������画��Ȃ��ɂ���B�j��\�u���b�N���肪���������画��Ȃ��ɂ���
										if (m_map[i][j + 1] == 0 || (bom_hit_test == false && m_map[i][j + 1] == 4) ||
											(breakable_block_hit_test == false && m_map[i][j + 1] == 10 || m_map[i][j + 1] == 11))
										{
											//�E�̉E
											if (r < 315 && r > 314)
											{
												*x = (j + 1) * BLOCK_SIZE + scroll;
												*y -= 1.0f;
											}
											else
											{
												*vx = *speed_power;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
;
}

//�A�N�V����
void CObjBlock::Action()
{
	//��l�����K��
	CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);
	//��l���I�u�W�F�N�g�����݂��Ă�����
	if(hero != nullptr)
	{
		m_hero_x = hero->GetX();
		m_hero_y = hero->GetY();

		//����X�N���[�����C��
		if(m_hero_x < 300)
		{
			//�X�N���[���̒l����ԍ��̏ꍇ�������Ȃ�
			if(m_scroll >= 0);
			else
			{
				hero->SetX(300);			//��l���̓��C���𒴂��Ȃ��悤�ɂ���
				m_scroll-=hero->GetVX();//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
			}
		}
		//�O���X�N���[�����C��
		else if(m_hero_x > 400)
		{
			//�X�N���[���̒l����ԉE�̏ꍇ�������Ȃ�
			if(m_scroll <=-1238);
			else
			{
				hero->SetX(400);
				m_scroll-=hero->GetVX();
			}
		}
	}
	//�G�o�����C��
	//��l���̈ʒu+600��G�o�����C���ɂ���
	float line = m_hero_x + (-m_scroll) + 600;
	
	//�G�o�����C����v�f�ԍ�
	int ex = ((int)line) / BLOCK_SIZE;

	//�G�o�����C���̗������
	for(int i = 0 ; i < MAP_Y ; i++)
	{
		//���C��������T��
		for (ex = ((int)line) / BLOCK_SIZE; ex >= 0; ex--)
		{
			
			//��̒�����20��T��
			if (m_map[i][ex] == 20)
			{
				//�o����(�G)�쐬
				CObjBarom* obj_barom = new CObjBarom(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_barom, OBJ_BAROM, 10);

				m_map[i][ex] = 0;
				
			}
			//��̒�����21��T��
			else if(m_map[i][ex] == 21)
			{
				//�I�j�[��(�G)�쐬
				CObjO_Neal* obj_o_neal = new CObjO_Neal(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_o_neal, OBJ_O_NEAL, 10);

				m_map[i][ex] = 0;
			}
			//��̒�����22��T��
			else if(m_map[i][ex] == 22)
			{
				//�_��(�G)�쐬
				CObjDull* obj_dull = new CObjDull(ex * BLOCK_SIZE, i * BLOCK_SIZE);
				Objs::InsertObj(obj_dull, OBJ_DULL, 10);

				m_map[i][ex] = 0;
			}
			//��̒�����23��T��
			else if(m_map[i][ex] == 23)
			{
				//�~���{�[(�G)�쐬
				CObjMingBo* obj_ming_bo = new CObjMingBo(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_ming_bo, OBJ_MING_BO, 10);

				m_map[i][ex] = 0;
			}
			//��̒�����24��T��
			else if(m_map[i][ex] == 24)
			{
				//�R���h���A(�G)�쐬
				CObjCondoria* obj_condoria = new CObjCondoria(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_condoria, OBJ_CONDORIA, 10);

				m_map[i][ex] = 0;
			}
			//��̒�����25��T��
			else if(m_map[i][ex] == 25)
			{
				//�I�o�s�[(�G)�쐬
				CObjObapy* obj_obapy = new CObjObapy(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_obapy, OBJ_OBAPY, 10);

				m_map[i][ex] = 0;
			}
			//��̒�����26��T��
			else if(m_map[i][ex] == 26)
			{
				//�p�[�X(�G)�쐬
				CObjPerth* obj_perth = new CObjPerth(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_perth, OBJ_PERTH, 10);

				m_map[i][ex] = 0;
			}
			//��̒�����27��T��
			else if(m_map[i][ex] == 27)
			{
				//�|���^��(�G)�쐬
				CObjPontan* obj_pontan = new CObjPontan(ex * BLOCK_SIZE , i * BLOCK_SIZE);
				Objs::InsertObj(obj_pontan, OBJ_PONTAN, 10);

				m_map[i][ex] = 0;
			}
			//��̒�����2��T��
			else if (m_map[i][ex] == 2)
			{
				//�j��\�u���b�N�쐬
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE,false,NOT_ITEM);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);

				//�����蔻�肾������
				m_map[i][ex] = 10;
			}
			//��̒�����R��T��
			else if(m_map[i][ex] == 3)
			{
				//�j��\�u���b�N�쐬(�h�A�t)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE,true,NOT_ITEM);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);

				//�����蔻�肾������
				m_map[i][ex] = 10;
			}
			//��̒�����-2��T��
			else if (m_map[i][ex] == -2)
			{
				//��l���̏����ʒu�܂��͎���

				m_map[i][ex] = 0;
			}
			//��̒�����12��T��
			else if (m_map[i][ex] == 12)
			{
				//�j��\�u���b�N�쐬(�t�@�C�A�[�A�b�v�t)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, FIRE_UP);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//�����蔻�肾������
				m_map[i][ex] = 10;
			}
			//��̒�����13��T��
			else if (m_map[i][ex] == 13)
			{
				//�j��\�u���b�N�쐬(�{���A�b�v�t)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, BOM_UP);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//�����蔻�肾������
				m_map[i][ex] = 10;
			}
			//��̒�����14��T��
			else if (m_map[i][ex] == 14)
			{
				//�j��\�u���b�N�쐬(�����R���t)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, REMOTE_CONTROLLER);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//�����蔻�肾������
				m_map[i][ex] = 10;
			}
			//��̒�����15��T��
			else if (m_map[i][ex] == 15)
			{
				//�j��\�u���b�N�쐬(�X�P�[�g�t)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, SKATE);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//�����蔻�肾������
				m_map[i][ex] = 10;
			}
			//��̒�����16��T��
			else if (m_map[i][ex] == 16)
			{
				//�j��\�u���b�N�쐬(�{�����蔲���t)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, BOM_SLIPPING_THROUGH);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//�����蔻�肾������
				m_map[i][ex] = 10;
			}
			//��̒�����17��T��
			else if (m_map[i][ex] == 17)
			{
				//�j��\�u���b�N�쐬(�j��\�u���b�N���蔲���t)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, DESTRUCTALE_BLOCK_SLIPPING_THROUGH);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//�����蔻�肾������
				m_map[i][ex] = 10;
			}
			//��̒�����18��T��
			else if (m_map[i][ex] == 18)
			{
				//�j��\�u���b�N�쐬(�t�@�C�A�[�}���t)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, FIRE_MAN);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//�����蔻�肾������
				m_map[i][ex] = 10;
			}
			//��̒�����19��T��
			else if (m_map[i][ex] == 19)
			{
				//�j��\�u���b�N�쐬(�p�[�t�F�N�g�}���t)
				CObjDestructableBlock* obj_destructa_block = new CObjDestructableBlock(ex * BLOCK_SIZE, i * BLOCK_SIZE, false, PERFECT_MAN);
				Objs::InsertObj(obj_destructa_block, OBJ_DESTRUCTADLE_BLOCK, 2);
				//�����蔻�肾������
				m_map[i][ex] = 10;
			}
		}
	}

}
//�h���[
void CObjBlock::Draw()
{
	
	//�`��J���[���
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�}�b�v�`�b�v�ɂ��block�ݒu
	for(int i = 0; i < MAP_Y; i++)
	{
		for(int j = 0; j < MAP_X ; j++)
		{
			if(m_map[i][j] != 0)
			{

				//�\���ʒu�̐ݒ�
				dst.m_top	= i * BLOCK_SIZE;
				dst.m_left	= j * BLOCK_SIZE + m_scroll;
				dst.m_right	= dst.m_left+ BLOCK_SIZE;
				dst.m_bottom= dst.m_top + BLOCK_SIZE;

				//map�̂Q�̂Ƃ��̐؂���
				if(m_map[i][j] == 2)
				{
					;
					
				}
				//map�̂P�̂Ƃ��̐؂���
				else if(m_map[i][j] == 1)
				{
					//�j��s�u���b�N
					BlockDraw(433.0f + 40.0f,0.0f,&dst,c);

				}
				
			}
		}
	}
}
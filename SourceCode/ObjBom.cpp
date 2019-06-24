//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjBom.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjBom::CObjBom(float x, float y)
{
	//���A���̈ʒu��40*40�̒���������ɂ���B
	x += 20;
	y += 20;

	//���A���̗v�f�ԍ�
	int x_element_number = ((int)x) / BOM_SIZE;
	int y_element_number = ((int)y) / BOM_SIZE;

	m_y = y_element_number * BOM_SIZE;
	m_x = x_element_number * BOM_SIZE;

}

//�C�j�V�����C�Y
void CObjBom::Init()
{
	m_ani_time = 0;		//�A�j���[�V�����t���[������Ԋu������
	m_ani_frame = 0;	//�`��t���[��������

	m_ani_max_time = 10;	//�A�j���[�V��������Ԋu�ő�l������

	m_ani_frame_change = 3; //�A�j���[�V�����؂�ւ��p������

	m_time = 0;	//���ԏ�����

	//��l�����������Ă���
	CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);

	//��l���I�u�W�F�N�g�����݂��Ă�����
	if(hero != nullptr)
	{
		m_hero_bom_power = hero->GetBomPower();
	}
	else
	{
		m_hero_bom_power = 1;
	}

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this,m_x + (block->GetScroll()),m_y,BOM_SIZE, BOM_SIZE,ELEMENT_RED,OBJ_BOM,1);

	


}
//�A�N�V����
void CObjBom::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	block->GetMap(m_map);//�}�b�v���X�V

	//��l�����������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��l���I�u�W�F�N�g�����݂��Ă�����B
	if(hero != nullptr)
	{
		//��l���̃����R���@�\��ON�̏ꍇ
		if(hero->GetRemoteController() == true)
		{
			//���ԃX�g�b�v
			m_time = 0;
			//�A�j���[�V�������ŏ��ɖ߂�
			m_ani_frame_change = 3;
		}
		else
		{
			m_time++;
		}
	}
	else
	{
		m_time++;
	}
	m_ani_time++;

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + (block->GetScroll()), m_y);

	//��l���I�u�W�F�N�g�ɐڐG���Ă��Ȃ������� && �G�I�u�W�F�N�g�ɐڐG���Ă��Ȃ�������
	if(hit->CheckObjNameHit(OBJ_HERO) == nullptr && hit->CheckElementHit(ELEMENT_ENEMY) == false)
	{

		int x = ((int)m_x) / BOM_SIZE;//X�̗v�f�ԍ�
		int y = ((int)m_y) / BOM_SIZE;//Y�̗v�f�ԍ�
		//�����蔻��p��4����
		m_map[y][x] = 4;

		block->MapChange(m_map);//�}�b�v�̍X�V

	}

	//�����؂�ւ�(�t���[��)�h�~
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame++;
		m_ani_time = 0;
	}

	//�Ō�̃t���[���ɍs������ŏ��̃t���[���ɖ߂�
	if(m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//�A�j���[�V�����؂�ւ�
	if(m_time == 80)
	{
		//���̃A�j���[�V������
		m_ani_frame_change++;
	}
	else if(m_time == 150)
	{
		//���̃A�j���[�V������
		m_ani_frame_change++;
	}

	bool hero_remote_controller;//��l���̃����R�����(true:ON false:OFF)

	//��l���I�u�W�F�N�g�����݂��Ă�����
	if(hero != nullptr)
	{
		//ON
		hero_remote_controller = hero->GetRemoteController();
	}
	else
	{
		//OFF
		hero_remote_controller = false;
	}

	//���ԁ@�b�b�@�����ɓ������Ă����� || (��l���̃����R���@�\��ON�̏ꍇ && Z��������Ă�����)
	if(m_time > 180 || hit->CheckObjNameHit(OBJ_BLAST) != nullptr || (hero_remote_controller == true && Input::GetVKey('Z') == true))
	{
		//�U�O�@*�@�R�@�Ŕ���
		//180
		//��l���I�u�W�F�N�g�����݂��Ă�����
		if(hero != nullptr)
		{
			//�{�������������̂�Hero��bom_num���f�N�������g
			hero->SetBomNum();
		}

		//���̏�̔����I�u�W�F�N�g�쐬
  		CObjBlast* obj_blast = new CObjBlast(m_x , m_y,IN_SITU,1);	//�����I�u�W�F�N�g�쐬
		Objs::InsertObj(obj_blast, OBJ_BLAST, 10);	//�����I�u�W�F�g�o�^

		//�������������Ă���
		CObjBlast* blast = (CObjBlast*) Objs::GetObj(OBJ_BLAST);

		//��l�����������Ă���
		CObjHero* hero = (CObjHero*) Objs::GetObj(OBJ_HERO);

		//��l���I�u�W�F�N�g�����݂��Ă�����
		if(hero != nullptr)
		{
			m_hero_bom_power = hero->GetBomPower();
		}

		//�����쐬
		for(int direction = 0; direction < 4; direction++)
		{
			for(int bom_power = 0; bom_power < m_hero_bom_power; bom_power++)
			{
				//							�E				��				��			 ��   
				int direction_x[4] = {1 + bom_power,-1 - bom_power, 0			 ,0			   };
				int direction_y[4] = {0			   , 0			  ,-1 - bom_power,1 + bom_power};

				//x,y�̗v�f�ԍ�
				int x = ((int)m_x) / BLAST_SIZE + direction_x[direction];
				int y = ((int)m_y) / BLAST_SIZE + direction_y[direction];
				
				block->GetMap(m_map);//�}�b�v���l��

				//�������Ƃ��Ă���ꏊ�Ƀu���b�N
				if (m_map[y][x] == 1 ||
					m_map[y][x] == 10||
					m_map[y][x] == 11
					)
				{
					//�j��\�u���b�N�̔��肾���̂���(10)�̏ꍇ
					if (m_map[y][x] == 10)
					{
						//�j�󂵂��u���b�N�̓����蔻�������
						m_map[y][x] = 11;
						block->MapChange(m_map);//�}�b�v���X�V
					}
					//������~
					break;
				}

				//�u�����Ƃ��Ă���ꏊ�ɔ���������Ώ��������Ȃ�
				else if(m_map[y][x] == -1);

				else
				{
					//�����I�u�W�F�N�g�쐬
					CObjBlast* obj_blast = new CObjBlast(m_x, m_y, direction, bom_power + 1);	//�����I�u�W�F�N�g�쐬
					Objs::InsertObj(obj_blast, OBJ_BLAST, 10);	//�����I�u�W�F�g�o�^
					//�����̐�[
					if (bom_power == m_hero_bom_power - 1)
					{
						//��[�̔������Ƌ�����G
						obj_blast->SetLastBlast(true);
					}
				}
			}
		}
		//��������O�ɓ����蔻�������
		int x = ((int)m_x) / BOM_SIZE;//X�̗v�f�ԍ�
		int y = ((int)m_y) / BOM_SIZE;//Y�̗v�f�ԍ�
		//�����蔻�������
		m_map[y][x] = 0;
		block->MapChange(m_map);//�}�b�v�̍X�V

		Audio::Start(1); //���y�X�^�[�g
		this->SetStatus(false);		//���g�ɏ��Ŗ��߂��o���B
		Hits::DeleteHitBox(this);	//�G�@�����L����HitBox�ɏ��ł���B
	}
	
}
//�h���[
void CObjBom::Draw()
{
	//�`��J���[���
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�����A�j���[�V��������o�^
	int AniData[4] =
	{
		 0 , 1 , 2 , 1
	};

	//�؂���ʒu�̐ݒ�
	src.m_top	= IMAAGE_CUT_SIZE * m_ani_frame_change;
	src.m_left	= IMAAGE_CUT_SIZE * AniData[m_ani_frame];
	src.m_right	= src.m_left + IMAAGE_CUT_SIZE;
	src.m_bottom= IMAAGE_CUT_SIZE + src.m_top;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top	= m_y;
	dst.m_left =  m_x + block->GetScroll();
	dst.m_right = BOM_SIZE + m_x + block->GetScroll();
	dst.m_bottom= BOM_SIZE + m_y;

	//�`��
	Draw::Draw(0,&src,&dst,c,0.0f);

}
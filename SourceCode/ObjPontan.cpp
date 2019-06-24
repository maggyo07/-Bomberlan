//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "Trace.h"

#include "UtilityModule.h"
#include "GameHead.h"
#include "ObjPerth.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjPontan::CObjPontan(float x, float y)
{
	m_x = x;	//�ʒu
	m_y = y;
}
//�C�j�V�����C�Y
void CObjPontan::Init()
{
	m_vx = 0.0f;	//�x�N�g��
	m_vy = 0.0f;

	m_posture = 1.0f; //�E����0.0f ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;	//�Î~�t���[���������ɂ���

	m_speed_power = 3.0f;//�ʏ푬�x

	m_ani_max_time = 2;	//�A�j���[�V�����Ԋu��

	//block�Ƃ̏Ռ���Ԋm�F�p
	m_hit_up	=false;
	m_hit_down	=false;
	m_hit_left	=false;
	m_hit_right	=false;

	m_death_flag = false; //���S�t���O�@true:�����ɐG�ꂽ�Ƃ�	false:�����ɐG��Ă��Ȃ���

	m_death_time = 0;	//���S�t���O����������̎���

	m_bom_hit_test = true;//�{�����茒��

	m_breakable_block_hit_test = false;//�j��\�u���b�N���薳��

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this,m_x,m_y,PONTAN_SIZE, PONTAN_SIZE,ELEMENT_ENEMY,OBJ_PONTAN,1);

	element_number_x = 0;
	element_number_y = 0;

	m_time = 0;
}
//�A�N�V����
void CObjPontan::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l�����������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	m_ani_time++;

	//��l���̈ʒu���
	int hero_x;
	int hero_y;

	//��l���I�u�W�F�N�g�����݂��Ă�����
	if (hero != nullptr)
	{
		//��l���̈ʒu�����擾
		hero_x = hero->GetX();
		hero_y = hero->GetY();
	}
	else
	{
		//��l���̏�񂪂Ƃ�Ȃ��̂łO�ɂ���
		hero_x = 0;
		hero_y = 0;
	}

	//�_�C�N�X�g���@
	m_node = Dijkstra(m_x + block->GetScroll(), m_y, hero_x, hero_y, m_bom_hit_test, m_breakable_block_hit_test);

	//�����ʈړ���
	//X�����̈ړ���
	switch (m_node.node_x)
	{
	case 1:
		m_vx = m_speed_power;
		break;
	case -1:
		m_vx = -m_speed_power;
		break;
	default:
		m_vx = 0;
		break;
	}
	//Y�����̈ړ���
	switch (m_node.node_y)
	{
	case 1:
		m_vy = m_speed_power;
		break;
	case -1:
		m_vy = -m_speed_power;
		break;
	default:
		m_vy = 0;
		break;
	}

	//�ړ����Ȃ��Ƃ����Ȃ��̂�
	if (m_vx == 0 && m_vy == 0)
	{
		m_time++;
		static float vx = 0;
		static float vy = 0;
		//2�u���b�N���i�񂾂�
		if (m_time >= BLOCK_SIZE / m_speed_power * 2)
		{
			//�����蔻��������炤
			HitTestInformation(m_x, m_y, &m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, m_bom_hit_test, m_breakable_block_hit_test);
			//�ړ��ł�������Ƀ����_���ňړ�
			MovableTargetRandomByMove(&m_vx, &m_vy, m_speed_power, m_hit_up, m_hit_down, m_hit_left, m_hit_right);
			vx = m_vx;
			vy = m_vy;
			m_time = 0;
		}
		else
		{
			m_vx = vx;
			m_vy = vy;

		}
		
	}
	else
	{
		m_time = BLOCK_SIZE / m_speed_power * 2;
	}

	//�u���b�N�Ƃ̓����蔻����s
	block->BlockHit(&m_x, &m_y, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		m_bom_hit_test, m_breakable_block_hit_test, &m_speed_power
	);

	//HetBox���
	CHitBox* hit = Hits::GetHitBox(this);

	//���S�t���O��OFF�̏ꍇ
	if(m_death_flag == false)
	{
		m_x += m_vx;
		m_y += m_vy;

		//X�����̈ړ��ʂ��O��菬����������
		if(m_vx < 0)
		{
			//������
			m_posture = 0.0f;
		}
		//X�����̈ړ��ʂ��O���傫��������
		else if(m_vx > 0)
		{
			//�E����
			m_posture = 1.0f;
		}

		//�A�j���[�V�����[�[�[�[�[
		if(m_ani_time > m_ani_max_time)
		{
			m_ani_frame++;
			m_ani_time = 0;
		}

		if(m_ani_frame >= 4)
		{
			m_ani_frame = 0;
		}
		//�|�|�|�|�|�|�|�|�|�|�|�|
		//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_x + block->GetScroll(), m_y);
	}
	//���S�t���O��ON�̏ꍇ
	else
	{
		//���S�t���O��ON�Ȃ̂ŉ��Z
		m_death_time++;
		//HitBox�̈ʒu�̕ύX
		hit->SetPos(-50, 0);//���S�t���O��ON�Ȃ̂ł���Ȃ�

		//���S�t���OON�̂Ƃ��̃A�j���[�V����
		if(m_death_time == 50)
		{
			m_ani_frame++;
		}
		else if(m_death_time == 60)
		{
			m_ani_frame++;
		}
		else if(m_death_time == 70)
		{
			m_ani_frame++;
		}
		//�j��
		else if(m_death_time == 80)
		{
			((UserData*)Save::GetData())->mEnemyNumber--;
			((UserData*)Save::GetData())->mScore += PONTAN_SCORE;

			//�X�R�A�I�u�W�F�N�g�쐬
			CObjScore* obj_score = new CObjScore(PONTAN_SCORE,m_x, m_y);
			Objs::InsertObj(obj_score, OBJ_SCORE, 10);

			this->SetStatus(false);		//���g�ɏ��Ŗ��߂��o���B
			Hits::DeleteHitBox(this);	//�G�@�����L����HitBox�ɏ��ł���B
		}
	}

	//�����ɐڐG���Ă�����
	if (hit->CheckObjNameHit(OBJ_BLAST) != nullptr)
	{
		//���S�t���OON
		m_death_flag = true;
		m_ani_frame = 0;
	}

}
//�h���[
void CObjPontan::Draw()
{
	//�����A����A�j���[�V��������o�^
	int AniData[4];
	//���S�t���O�������Ă��Ȃ�������
	if(m_death_flag == false)
	{
		//���S�t���OOFF�̂Ƃ��̃A�j���[�V�������
		AniData[0] = 0;
		AniData[1] = 1;
		AniData[2] = 2;
		AniData[3] = 1;
	}
	//���S�t���O�������Ă�����
	else
	{
		//���S�t���OON�̂Ƃ��̃A�j���[�V�������
		AniData[0] = 3;
		AniData[1] = 4;
		AniData[2] = 5;
		AniData[3] = 6;
	}

	//�`��J���[���
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top	= ENEMY_CUT_SIZE*7;
	src.m_left	= ENEMY_CUT_SIZE * AniData[m_ani_frame];
	src.m_right	= ENEMY_CUT_SIZE + src.m_left;
	src.m_bottom= src.m_top + ENEMY_CUT_SIZE;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	//�\���ʒu�̐ݒ�
	dst.m_top	= 0.0f + m_y;
	dst.m_left	= (PONTAN_SIZE * m_posture )+ m_x + block->GetScroll();
	dst.m_right	= (PONTAN_SIZE - PONTAN_SIZE * m_posture )+ m_x + block->GetScroll();
	dst.m_bottom= PONTAN_SIZE + m_y;

	//�`��
	Draw::Draw(4,&src,&dst,c,0.0f);

}
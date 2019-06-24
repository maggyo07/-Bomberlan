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
#include "ObjO_Neal.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjO_Neal::CObjO_Neal(float x, float y)
{
	m_x = x;	//�ʒu
	m_y = y;
}
//�C�j�V�����C�Y
void CObjO_Neal::Init()
{
	m_vx = 0.0f;	//�x�N�g��
	m_vy = 0.0f;

	m_posture = 1.0f; //�E����1.0f ������0.0f

	m_ani_time = 0;
	m_ani_frame = 1;	//�Î~�t���[���������ɂ���

	m_speed_power = 2.0f;//�ʏ푬�x

	m_ani_max_time = 7;	//�A�j���[�V�����Ԋu��

	//block�Ƃ̏Ռ���Ԋm�F�p
	m_hit_up	=false;
	m_hit_down	=false;
	m_hit_left	=false;
	m_hit_right	=false;

	m_death_flag = false; //���S�t���O�@true:�����ɐG�ꂽ�Ƃ�	false:�����ɐG��Ă��Ȃ���

	m_death_time = 0;	//���S�t���O����������̎���

	m_bom_hit_test = true;//�{�����茒��

	m_breakable_block_hit_test = true;//�j��\�u���b�N���茒��

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this,m_x,m_y,O_NEAL_SIZE, O_NEAL_SIZE,ELEMENT_ENEMY,OBJ_O_NEAL,1);

	m_time = 0;
}
//�A�N�V����
void CObjO_Neal::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	m_time++;
	m_ani_time++;

	HitTestInformation(m_x,m_y,&m_hit_up,&m_hit_down,&m_hit_left,&m_hit_right,m_bom_hit_test,m_breakable_block_hit_test);
	
	//2�u���b�N���i�񂾂�
	if(m_time >= BLOCK_SIZE / m_speed_power * 2)
	{
		//�ړ��ł�������Ƀ����_���ňړ�
		MovableTargetRandomByMove(&m_vx,&m_vy,m_speed_power,m_hit_up,m_hit_down,m_hit_left,m_hit_right);
		m_time = 0;
	}

	//�u���b�N�Ƃ̓����蔻����s
	block->BlockHit(&m_x, &m_y, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		m_bom_hit_test,m_breakable_block_hit_test,&m_speed_power
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
			((UserData*)Save::GetData())->mScore += O_NEAL_SCORE;

			//�X�R�A�I�u�W�F�N�g�쐬
			CObjScore* obj_score = new CObjScore(O_NEAL_SCORE,m_x, m_y);
			Objs::InsertObj(obj_score, OBJ_SCORE, 10);

			this->SetStatus(false);		//���g�ɏ��Ŗ��߂��o���B
			Hits::DeleteHitBox(this);	//�G�@�����L����HitBox�ɏ��ł���B
		}
	}

	//�����ɐڐG���Ă�����
	if(hit->CheckObjNameHit(OBJ_BLAST) != nullptr)
	{
		//���S�t���OON
		m_death_flag = true;
		m_ani_frame = 0;
	}
}
//�h���[
void CObjO_Neal::Draw()
{
	//�����A����A�j���[�V��������o�^
	int AniData[4];
	//���S�t���O�������Ă��Ȃ�������
	if(m_death_flag == false)
	{
		//���S�t���OOFF�̂Ƃ��̃A�j���[�V�������
		AniData[0] = 1;
		AniData[1] = 0;
		AniData[2] = 2;
		AniData[3] = 0;
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
	src.m_top	= ENEMY_CUT_SIZE*1;
	src.m_left	= ENEMY_CUT_SIZE * AniData[m_ani_frame];
	src.m_right	= ENEMY_CUT_SIZE + src.m_left;
	src.m_bottom= src.m_top + ENEMY_CUT_SIZE;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	//�\���ʒu�̐ݒ�
	dst.m_top	= 0.0f + m_y;
	dst.m_left	= (O_NEAL_SIZE * m_posture )+ m_x + block->GetScroll();
	dst.m_right	= (O_NEAL_SIZE - O_NEAL_SIZE * m_posture )+ m_x + block->GetScroll();
	dst.m_bottom= O_NEAL_SIZE + m_y;

	//�`��
	Draw::Draw(4,&src,&dst,c,0.0f);

}
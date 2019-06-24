//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "Trace.h"
#include "GameHead.h"
#include "ObjGameClear.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;
//�C�j�V�����C�Y
void CObjGameClear::Init()
{
	m_vx = 1.9;
	m_vy = 0;
	m_x = 0;
	m_y = 480.0;
	m_time = 0;
	m_ani_time = 0;	
	m_ani_max_time = 10;	//�A�j���[�V�����Ԋu��
	m_ani_frame = 0;

	m_posture = 0;
	m_stop = false;
}
//�A�N�V����
void CObjGameClear::Action()
{
	m_time++;
	//�����؂�ւ�(�t���[��)�h�~
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame++;
		m_ani_time = 0;
	}

	//�Ō�̃t���[���ɍs������ŏ��̃t���[���ɖ߂�
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//�ړ���~�Ŗ����ꍇ
	if (m_stop == false)
	{
		m_ani_time++;
		m_x += m_vx;
		m_y += m_vy;
	}

	//�E�։�ʊO�ɂ������獶�̉�ʊO�Ɉړ�
	if (m_x > 800)
	{
		m_x = -40.0f;
	}

	//���Ԃ�650�ɂȂ����烍�[�h�����i�[�̎�l���̎p�ɕϐg
	if (m_time == 650)
	{
		m_posture = 1;
	}
	//���Ԃ�1050�ɂȂ����特�y��~�E�ړ���~
	if (m_time == 1050)
	{
		Audio::Stop(0);//0�ԋȂ��~
		m_stop = true;
	}
	//���Ԃ�1150�ɂȂ�����^�C�g����ʂ�
	if (m_time == 1150)
	{
		Scene::SetScene(new CSceneTitle());
	}

	
}
//�h���[
void CObjGameClear::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�w�i-------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0;
	src.m_left = 0;
	src.m_right = 800;
	src.m_bottom = 600;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0;
	dst.m_left = 0;
	dst.m_right = 800;
	dst.m_bottom = 600;

	//�`��
	Draw::Draw(0, &src, &dst, c, 0.0f);
	//----------
	//���ʂ̕���------
	Font::StrDraw(L"CONGRATULATIONS", 200, 20, 50, c);
	Font::StrDraw(L"BOMBER RAN BECOMES RUNNER", 100, 80, 50, c);
	Font::StrDraw(L"SEE YOU AGAIN IN LODE RUNNER", 70, 140, 50, c);

	//------------------

	//��l��---------

	//�\���ʒu�̐ݒ�
	dst.m_top = m_y;
	dst.m_left = m_x + 40.0f;
	dst.m_right = dst.m_left - 40.0f;
	dst.m_bottom = dst.m_top + 40.0f;

	//�����A����A�j���[�V��������o�^
			int AniData[4] =
			{
				1 , 0 , 2 , 0
			};
		//�{���o�[�}���̎�l��
		if (m_posture == 0)
		{
		
			//�؂���ʒu�̐ݒ�
			src.m_top = IMAAGE_CUT_SIZE * 0;
			src.m_left = IMAAGE_CUT_SIZE * AniData[m_ani_frame];
			src.m_right = IMAAGE_CUT_SIZE + AniData[m_ani_frame] * IMAAGE_CUT_SIZE;
			src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;

			//�`��
			Draw::Draw(1, &src, &dst, c, 0.0f);
		}
		//���[�h�����i�[�̎�l��
		else
		{
			//�؂���ʒu�̐ݒ�
			src.m_top = IMAAGE_CUT_SIZE * 0;
			src.m_left = IMAAGE_CUT_SIZE * AniData[m_ani_frame];
			src.m_right = IMAAGE_CUT_SIZE + src.m_left;
			src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;

			//�`��
			Draw::Draw(2, &src, &dst, c, 0.0f);
		}
	//----------
}
//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"
#include "Trace.h"

#include "UtilityModule.h"
#include "GameHead.h"
#include "ObjDoor.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjDoor::CObjDoor(float x, float y)
{
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjDoor::Init()
{
	m_opening_and_closing = false;
	m_door_hit_test_time = 0;
	m_door_hit_test_max_time =150;
	m_hit_blast = false;
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this,m_x,m_y,DOOR_SIZE, DOOR_SIZE,ELEMENT_WHITE,OBJ_DOOR,1);
}
//�A�N�V����
void CObjDoor::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//�G�����S�ɂ��Ȃ��Ȃ�����
	if(((UserData*)Save::GetData())->mEnemyNumber == 0)
	{
		//�h�A�J
		m_opening_and_closing = true;
	}
	//�G���c���Ă�����
	else
	{
		//�h�A��
		m_opening_and_closing = false;
	}

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + block->GetScroll(),m_y);

	//�h�A�̓����蔻�莞�Ԃ��O
	if(m_door_hit_test_time == 0)
	{
		//�����I�u�W�F�N�g�ɓ������Ă�����B
		if(hit->CheckObjNameHit(OBJ_BLAST) != nullptr)
		{
			m_hit_blast = true;
			Audio::Start(4);//4�ԋȂ��X�^�[�g
		}
	}

	//�����ɓ���������
	if(m_hit_blast == true)
	{
		//�h�A����G���o�Ă���܂ł̎��Ԃ����Z
		m_door_hit_test_time++;
	}

	//���Ԑ؂�ɂȂ�����
	if(m_door_hit_test_time > m_door_hit_test_max_time)
	{
		//�P�`�P�O�O�̊ԂŃ����_���ɒl����
		int random = GetRandom(1,100);
		//�G����ʂɏo��
		for(int enemy_num = 0; enemy_num < 4; enemy_num++)
		{
			//�X�O���̊m���Ńo�������o��
			if (random < 90)
			{
				//�o����(�G)�쐬
				CObjBarom* obj_barom = new CObjBarom(m_x, m_y);
				Objs::InsertObj(obj_barom, OBJ_BAROM, 10);
			}
			//�P�O���̊m���Ń|���^�����o��
			else
			{
				//�|���^��(�G)�쐬
				CObjPontan* obj_pontan = new CObjPontan(m_x, m_y);
				Objs::InsertObj(obj_pontan, OBJ_PONTAN, 10);
			}

			//�G�ǉ�
			((UserData*)Save::GetData())->mEnemyNumber++;
		}
		
		m_hit_blast = false;
		m_door_hit_test_time = 0;
	}

	//�h�A���J���Ă�����
	if(m_opening_and_closing == true)
	{
		//��l���ɐG��Ă�����
		if(hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			//�h�A�ɔ����������Ă��Ȃ�������
			if (m_hit_blast == false)
			{
				//�w�肵���X�e�[�W���N���A������Q�[���N���A
				if (((UserData*)Save::GetData())->mStageNumber == MAX_STAGE)
				{
					//�V�[��(�Q�[���N���A)�Ăяo��
					Scene::SetScene(new CSceneGameClear());
				}
				else
				{
					//�X�e�[�W�N���A�����̂Ŏ��̃X�e�[�W��
					((UserData*)Save::GetData())->mStageNumber++;
					//�V�[��(�X�e�[�W�ύX)�Ăяo��
					Scene::SetScene(new CSceneStageChange());
				}
			}
		}
	}

	
}
//�h���[
void CObjDoor::Draw()
{
	//�`��J���[���
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�h�A���J���Ă��Ȃ��Ƃ��̐؂���l
	if (m_opening_and_closing == false)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0;
		src.m_left = 0;
		src.m_right = src.m_left + 40.0f;
		src.m_bottom = 40.0f + src.m_top;
	}
	else 
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0;
		src.m_left = 40.0f;
		src.m_right = src.m_left + 40.0f;
		src.m_bottom = 40.0f + src.m_top;
	}


	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top	= m_y;
	dst.m_left =  m_x + block->GetScroll();
	dst.m_right = BOM_SIZE + m_x + block->GetScroll();
	dst.m_bottom= BOM_SIZE + m_y;

	//�`��
	Draw::Draw(6,&src,&dst,c,0.0f);

}
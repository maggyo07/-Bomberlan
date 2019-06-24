//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "Trace.h"

#include "UtilityModule.h"
#include "GameHead.h"
#include "ObjItem.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjItem::CObjItem(float x, float y,ITEM id)
{
	m_x = x;
	m_y = y;

	//�A�C�e���̎��
	m_item_id = id;
}

//�C�j�V�����C�Y
void CObjItem::Init()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//�I�u�W�F�N�g�̎�ޑ���p
	OBJ_NAME obj_id;

	//�eID���Ƃ̃I�u�W�F�N�g��ޑ��
	if(m_item_id == FIRE_UP)
	{
		obj_id = OBJ_FIRE_UP;
	}
	else if(m_item_id == BOM_UP)
	{
		obj_id = OBJ_BOM_UP;
	}
	else if(m_item_id == REMOTE_CONTROLLER)
	{
		obj_id = OBJ_REMOTE_CONTROLLER;
	}
	else if(m_item_id == SKATE)
	{
		obj_id = OBJ_SKATE;
	}
	else if(m_item_id == BOM_SLIPPING_THROUGH)
	{
		obj_id = OBJ_BOM_SLIPPING_THROUGH;
	}
	else if(m_item_id == DESTRUCTALE_BLOCK_SLIPPING_THROUGH)
	{
		obj_id = OBJ_DESTRUCTALE_BLOCK_SLIPPING_THROUGH;
	}
	else if(m_item_id == FIRE_MAN)
	{
		obj_id = OBJ_FIRE_MAN;
	}
	else if(m_item_id == PERFECT_MAN)
	{
		obj_id = OBJ_PERFECT_MAN;
	}

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this,m_x + (block->GetScroll()),m_y,ITEM_SIZE, ITEM_SIZE,ELEMENT_ITEM,obj_id,1);

	m_ani_time = 0;
	m_ani_frame = 0;
	m_ani_start = false;
}
//�A�N�V����
void CObjItem::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//HitBox���
	CHitBox* hit = Hits::GetHitBox(this);

	//�����I�u�W�F�N�g�ɐڐG���Ă�����
	if(hit->CheckObjNameHit(OBJ_BLAST) != nullptr)
	{
		//�A�j���[�V�����X�^�[�g
		m_ani_start = true;
	}

	//�A�j���[�V�����X�^�[�g�t���O�������Ă�����
	if(m_ani_start == true)
	{
		//�A�j���[�V�����^�C�����Z
		m_ani_time++;
		//HitBox�̈ʒu�̕ύX
		//HitBox����������A�j���[�V�������Ɏ��Ă��܂��̂łǂ����Ɉړ�
		hit->SetPos(-50, 0);
	}
	//�A�j���[�V�����X�^�[�g�t���O�������Ă��Ȃ�������
	else
	{
		//HitBox�̈ʒu�̕ύX
		//�ʏ�̈ʒu��HitBox��z�u
		hit->SetPos(m_x + block->GetScroll(), m_y);
	}

	//�A�j���[�V����----------
	//�A�j���[�V�����^�C�����P�̂Ƃ�(�ŏ��̃A�j���[�V����)
	if(m_ani_time == 1)
	{
		m_ani_frame++;
	}
	//�A�j���[�V�����^�C�����Q�O�ɂȂ�����(�Q��ڂ̃A�j���[�V����)
	else if(m_ani_time == 20)
	{
		m_ani_frame++;
	}
	//�A�j���[�V�����^�C�����R�O�ɂȂ�����(�R��ڂ̃A�j���V����)
	else if(m_ani_time == 30)
	{
		m_ani_frame++;
	}
	//�A�j���[�V�����^�C����50�ɂȂ�����
	else if(m_ani_time == 50)
	{
		//�P�`�P�O�O�̊ԂŃ����_���ɒl������
		int random = GetRandom(1,100);

		//��Q�O���̊m���œG���o�Ă���(�A�C�e����R�₵���̂œV��)
		if(random <= 20)
		{
			//�p�[�X(�G)�쐬
			CObjPerth* obj_perth = new CObjPerth(m_x, m_y);
			Objs::InsertObj(obj_perth, OBJ_PERTH, 10);

			//�G�ǉ�
			((UserData*)Save::GetData())->mEnemyNumber++;
		}

		//�j��
		this->SetStatus(false);		//���g�ɏ��Ŗ��߂��o���B
		Hits::DeleteHitBox(this);	//���g�����L����HitBox�ɏ��ł���B
	}
	
	//------------------------

	//��l���Ɏ��ꂽ��
	if(hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		//�A�C�e���̃X�R�A���Z
		((UserData*)Save::GetData())->mScore += ITEM_SCORE;

		//�X�R�A�I�u�W�F�N�g�쐬
		CObjScore* obj_score = new CObjScore(ITEM_SCORE,m_x, m_y);
		Objs::InsertObj(obj_score, OBJ_SCORE, 10);

		this->SetStatus(false);		//���g�ɏ��Ŗ��߂��o���B
		Hits::DeleteHitBox(this);	//���g�����L����HitBox�ɏ��ł���B
	}
	
}
//�h���[
void CObjItem::Draw()
{
	//�`��J���[���
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top	= ITEM_CUT_SIZE * m_item_id;
	src.m_left	= ITEM_CUT_SIZE * m_ani_frame;
	src.m_right	= src.m_left + ITEM_CUT_SIZE;
	src.m_bottom= ITEM_CUT_SIZE + src.m_top;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top	= m_y;
	dst.m_left =  m_x + block->GetScroll();
	dst.m_right = ITEM_SIZE + m_x + block->GetScroll();
	dst.m_bottom= ITEM_SIZE + m_y;

	//�`��
	Draw::Draw(2,&src,&dst,c,0.0f);

}
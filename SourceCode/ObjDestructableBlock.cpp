//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "UtilityModule.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjDestructableBlock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjDestructableBlock::CObjDestructableBlock(float x, float y,bool door, ITEM id)
{
	m_x = x;	//�ʒu
	m_y = y;
	
	TRACE(L"�R���X�g���N�^\nm_x=%f\nm_y=%f\ndoor=%d\n", m_x, m_y,door);
	m_with_door = door;//�h�A�t���ǂ��� true:�h�A�t	false:�h�A����
	m_item_id = id;	//���̃A�C�e�����o���u���b�N���ǂ���
}
//�C�j�V�����C�Y
void CObjDestructableBlock::Init()
{
	TRACE(L"�A�N�V����\nm_x=%f\nm_y=%f\n",m_x,m_y);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_FIELD, OBJ_DESTRUCTADLE_BLOCK, 1);

	m_hit_erase = false;//�����蔻��������Ȃ�

	m_ani_time = 0;//�A�j���[�V�����t���[������Ԋu
	m_ani_frame = 0;//�`��t���[��
	m_ani_max_time = 10;	//�A�j���[�V��������Ԋu�ő�l

}
//�A�N�V����
void CObjDestructableBlock::Action()
{

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + block->GetScroll(), m_y);

	block->GetMap(m_map);//�}�b�v���K��

	int x = ((int)m_x) / BLOCK_SIZE;
	int y = ((int)m_y) / BLOCK_SIZE;
	
	//���g�̏ꏊ��11��������A�j���[�V�����X�^�[�g
	if (m_map[y][x] == 11)
	{
		m_ani_time++;

	}

	if(m_ani_time >= m_ani_max_time)
	{
		m_ani_time = 0;
		m_ani_frame++;

	}

	if(m_ani_frame >= 4)
	{
		//�A�C�e�����o��u���b�N�ł���΃A�C�e�����o���B
		if(m_item_id != NOT_ITEM)
		{
			
			//���e�A�b�v(�A�C�e��)�I�u�W�F�N�g�쐬
			CObjItem* obj_item = new CObjItem(m_x, m_y,m_item_id);//���e�A�b�v(�A�C�e��)�I�u�W�F�N�g�쐬
			Objs::InsertObj(obj_item, OBJ_BOM_UP, 10);	//���e�A�b�v(�A�C�e��)�I�u�W�F�N�g�o�^
			
		}

		block->GetMap(m_map);//�}�b�v���K��
		m_map[y][x] = 0;	//�����̂Ŏ��g�̃}�b�v���(11)�������B
		block->MapChange(m_map);//�}�b�v���X�V

		//�h�A�t�������ꍇ
		if(m_with_door == true)
		{
			//�h�A�쐬
			CObjDoor* obj_door = new CObjDoor(m_x,m_y);
			Objs::InsertObj(obj_door, OBJ_CONDORIA, 10);
		}
		this->SetStatus(false);		//���g�ɏ��Ŗ��߂��o���B
		Hits::DeleteHitBox(this);	//�G�@�����L����HitBox�ɏ��ł���B
	}

}
//�h���[
void CObjDestructableBlock::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 432.0f - (BLOCK_SIZE * m_ani_frame);
	src.m_right = IMAAGE_CUT_SIZE + src.m_left;
	src.m_bottom = src.m_top + IMAAGE_CUT_SIZE;
	
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�\���ʒu�̐ݒ�
	dst.m_top = m_y;
	dst.m_left = m_x + block->GetScroll();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//�`��
	Draw::Draw(0, &src, &dst, c, 0.0f);

}
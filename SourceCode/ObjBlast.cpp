//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjBlast.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;
//�����P�FX�ʒu
//�����Q�FY�ʒu
//�����R�F����
//�����S�F�{��
CObjBlast::CObjBlast(float x, float y,int direction, int magnification)
{
	//X�ʒu�ύX�p
	int Direction_x[5] = 
	//	�E�A		���A	�@��A���A���̏�
	{BLAST_SIZE * magnification,(-BLAST_SIZE) * magnification, 0,   0,     0};	//X�ʒu

	//Y�ʒu�ύX�p
	int Direction_y[5] =
	//�E�A��		��			��	���̏�
	{  0,  0,(-BLAST_SIZE) * magnification,BLAST_SIZE * magnification,0};//Y�ʒu

	m_x = x + Direction_x[direction];
	m_y = y + Direction_y[direction];
	//������������B
	m_direction = direction;
}

//�C�j�V�����C�Y
void CObjBlast::Init()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	m_last_blast = false;
	
	m_ani_data = 3;//��ԉE�̉摜����X�^�[�g
	m_ani_time = 0;
	m_ani_max_time = 40;//�A�j���[�V�����I�����ԂQ�b(40*3)

	int element_x = ((int)m_x) / BLAST_SIZE;//X�̗v�f�ԍ�
	int element_y = ((int)m_y) / BLAST_SIZE;//Y�̗v�f�ԍ�

	//�}�b�v����-1������B
	block->GetMap(m_map);
	m_map[element_y][element_x] = -1;
	block->MapChange(m_map);

	//�����ʃq�b�g�{�b�N�X
	if(m_direction == UP || m_direction == DOWN)
	{
		//�����c��
		//�����蔻��p��HitBox���쐬
		Hits::SetHitBox(this, m_x + (block->GetScroll()) + RECTANGLE, m_y,BLAST_SIZE - RECTANGLE * 2, BLAST_SIZE,ELEMENT_GREEN,OBJ_BLAST,1);

	}
	else if(m_direction == LEFT || m_direction == RIGHT)
	{
		//��������
		//�����蔻��p��HitBox���쐬
		Hits::SetHitBox(this, m_x + (block->GetScroll()), m_y + RECTANGLE,BLAST_SIZE, BLAST_SIZE - RECTANGLE * 2,ELEMENT_GREEN,OBJ_BLAST,1);

	}
	else
	{
		//����������
		//�����蔻��p��HitBox���쐬
		Hits::SetHitBox(this,m_x + (block->GetScroll()) + RECTANGLE,m_y + RECTANGLE,BLAST_SIZE - RECTANGLE * 2,BLAST_SIZE - RECTANGLE * 2, ELEMENT_GREEN,OBJ_BLAST,1);
	}
	

}

//�A�N�V����
void CObjBlast::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�}�b�v���X�V
	block->GetMap(m_map);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	if(m_direction == UP || m_direction == DOWN)
	{
		hit->SetPos(m_x + (block->GetScroll()) + RECTANGLE , m_y);
	}
	else if(m_direction == LEFT || m_direction == RIGHT)
	{
		hit->SetPos(m_x + (block->GetScroll()) , m_y + RECTANGLE);
	}
	else
	{
		hit->SetPos(m_x + (block->GetScroll()) + RECTANGLE, m_y + RECTANGLE);
	}

	m_ani_time++;
	
	if(m_ani_time == 10 ||
	   m_ani_time == 20 ||
	   m_ani_time == 30)
	{
		m_ani_data--;
	}
	//ani_time���ő�l�𒴂�����
	else if(m_ani_time > m_ani_max_time)
	{

		int element_x = ((int)m_x) / BLAST_SIZE;//X�̗v�f�ԍ�
		int element_y = ((int)m_y) / BLAST_SIZE;//Y�̗v�f�ԍ�

		
		//�����̂Ń}�b�v���̎�����-1�������B
		m_map[element_y][element_x] = 0;
		block->MapChange(m_map);
		

		this->SetStatus(false);		//���g�ɏ��Ŗ��߂��o���B
		Hits::DeleteHitBox(this);	//�G�@�����L����HitBox�ɏ��ł���B
	}
}
//�h���[
void CObjBlast::Draw()
{
	//�`��J���[���
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�Ō�̔����̎��̐؂���ʒu
	if(m_last_blast == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top	= BLAST_CUT_SIZE * 0;
		src.m_left	= BLAST_CUT_SIZE * m_ani_data;
		src.m_right	= src.m_left	+ BLAST_CUT_SIZE;
		src.m_bottom= src.m_top		+ BLAST_CUT_SIZE;
	}
	//���������̏�̂Ƃ��̐؂���ʒu
	else if(m_direction == IN_SITU)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top	= BLAST_CUT_SIZE * 2;
		src.m_left	= BLAST_CUT_SIZE * m_ani_data;
		src.m_right	= src.m_left	+ BLAST_CUT_SIZE;
		src.m_bottom= src.m_top		+ BLAST_CUT_SIZE;
	}
	else
	{
		//�؂���ʒu�̐ݒ�
		src.m_top	= BLAST_CUT_SIZE;
		src.m_left	= BLAST_CUT_SIZE * m_ani_data;
		src.m_right	= src.m_left	+ BLAST_CUT_SIZE;
		src.m_bottom= src.m_top		+ BLAST_CUT_SIZE;
	}
	

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top	= m_y;
	dst.m_left =  m_x + block->GetScroll();
	dst.m_right = BLAST_SIZE + m_x + block->GetScroll();
	dst.m_bottom= BLAST_SIZE + m_y;

	//�����ʂ̕`��
	switch(m_direction)
	{
		//�E
	case RIGHT:
		Draw::Draw(1,&src,&dst,c,270.0f);
		break;
		//��
	case LEFT:
		Draw::Draw(1,&src,&dst,c,90.0f);
		break;
		//��
	case UP:
		Draw::Draw(1,&src,&dst,c,0.0f);
		break;
		//��
	case DOWN:
		Draw::Draw(1,&src,&dst,c,180.0f);
		break;
		//���̏�
	case IN_SITU:
		Draw::Draw(1,&src,&dst,c,0.0f);
		break;
	};
}
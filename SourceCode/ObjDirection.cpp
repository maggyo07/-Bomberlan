//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjDirection.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjDirection::CObjDirection(float x, float y, int directon_x, int directon_y)
{
	m_x = x;
	m_y = y;
	m_directon_x = directon_x;
	m_directon_y = directon_y;
}
//�C�j�V�����C�Y
void CObjDirection::Init()
{
	m_time = 0;
}
//�A�N�V����
void CObjDirection::Action()
{
	if (m_time >= 1)
	{
		this->SetStatus(false);		//���g�ɏ��Ŗ��߂��o���B
	}

	m_time++;

}
//�h���[
void CObjDirection::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 40.0 + (m_directon_y * 40.0);
	src.m_left = 40.0 + (m_directon_x * 40.0);
	src.m_right = src.m_left + 40.0;
	src.m_bottom = 40.0 + src.m_top;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = m_y;
	dst.m_left = m_x + block->GetScroll();
	dst.m_right = 40.0 + m_x + block->GetScroll();
	dst.m_bottom = 40.0 + m_y;

	//�`��
	Draw::Draw(5, &src, &dst, c, 0.0f);
}
//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBackground.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjBackground::Init()
{
}
//�A�N�V����
void CObjBackground::Action()
{
}
//�h���[
void CObjBackground::Draw()
{
	//�`��J���[���@R=RED�@G=Green�@B=Blue�@A��Alpha(���ߏ��)
	float c[4]={1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top	=0.0f;
	src.m_left	=0.0f;
	src.m_right	=512.0f;
	src.m_bottom=500.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top	=0.0f;
	dst.m_left	=0.0f;
	dst.m_right	=800.0f;
	dst.m_bottom=600.0f	;

	//3�Ԃɓo�^�����O���t�B�b�N��src �Edas �Ecno�������ɕ`��
	Draw::Draw(3,&src,&dst,c,0.0f);
}


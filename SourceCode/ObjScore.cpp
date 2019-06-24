//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "ObjScore.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjScore::CObjScore()
{
	//�傫���ق�
	m_big_or_small = true;
}

CObjScore::CObjScore(int score, float x, float y)
{
	//�������ق�
	m_big_or_small = false;

	m_score = score;
	m_x = x;
	m_y = y;
}
//�C�j�V�����C�Y
void CObjScore::Init()
{
	m_time = 0;
}
//�A�N�V����
void CObjScore::Action()
{
	//�������ق���p�̏���
	if (m_big_or_small == false)
	{
		m_time++;

		if (m_time > 100)
		{
			this->SetStatus(false);		//���g�ɏ��Ŗ��߂��o���B
			Hits::DeleteHitBox(this);	//���g�����L����HitBox�ɏ��ł���B
		}
	}
}
//�h���[
void CObjScore::Draw()
{

	

	//�傫���ق���p�̃h���[
	if (m_big_or_small == true)
	{
		//�`��J���[���
		float c[4] = {1.0f,1.0f,1.0f,1.0f};

		wchar_t str[128];

		//�b�̒l�𕶎���
		swprintf_s(str, L"Score:%d", ((UserData*)Save::GetData())->mScore);//�����𕶎���

		Font::StrDraw(str, 300, 50, 30, c);
	}
	//�������ق���p�̃h���[
	else 
	{
		//�u���b�N���������Ă���
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//�`��J���[���
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		wchar_t str[128];

		//�b�̒l�𕶎���
		swprintf_s(str, L"%d", m_score);//�����𕶎���

		Font::StrDraw(str, m_x + block->GetScroll() + 5, m_y + 10, 10, c);
	}

}
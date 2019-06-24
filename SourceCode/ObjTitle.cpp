//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjTitle::Init()
{
	m_key_flag = false;

	m_start_or_continue = true;

}

//�A�N�V����
void CObjTitle::Action()
{
	//�G���^�[�L�[�������ăV�[���@�F�@�Q�[�����C���Ɉړ�����
	if(Input::GetVKey(VK_RETURN)==true)
	{
		if(m_key_flag == true)
		{
			//STARE�ɃJ�[�\���������Ă�����
			if (m_start_or_continue == true)
			{
				Scene::SetScene(new CSceneStageChange());
			}
			//DESCRIPTION�ɃJ�[�\���������Ă�����
			else 
			{
				Scene::SetScene(new CSceneDescription());
			}
		}
	}
	else
	{
		m_key_flag = true;
	}
	//�����������(W)
	if ((Input::GetVKey('W') == true || Input::GetVKey(VK_UP) == true) && m_start_or_continue == false)
	{
		Audio::Start(1); //���y�X�^�[�g
		//START�ɃJ�[�\�������킹��
		m_start_or_continue = true;
	}
	//������������(S)
	if ((Input::GetVKey('S') == true || Input::GetVKey(VK_DOWN) == true) && m_start_or_continue == true)
	{
		Audio::Start(1); //���y�X�^�[�g
		//CONTNUE�ɃJ�[�\�������킹��
		m_start_or_continue = false;
	}
}

//�h���[
void CObjTitle::Draw()
{
	//�`��J���[���@R=RED�@G=Green�@B=Blue�@A��Alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 157.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 150.0f;
	dst.m_right = 256.0f * 2 + dst.m_left;
	dst.m_bottom = 157.0f * 2 + dst.m_top;
	//0�Ԃɓo�^�����O���t�B�b�N��src �Edas �Ecno�������ɕ`��
	Draw::Draw(0, &src, &dst, c, 0.0f);

	Font::StrDraw(L"START", 380, 350, 25, c);
	Font::StrDraw(L"DESCRIPTION", 380, 400, 25, c);
	Font::StrDraw(L"COPYRIGHT   1985   HUDSON   SOFT",220,500,25,c);
	Font::StrDraw(L"ENTER KEY PUSH!", 310, 550, 25, c);
	if (m_start_or_continue == true)
	{
		Font::StrDraw(L"-->",320,350,25,c);
	}
	else
	{
		Font::StrDraw(L"-->", 320, 400, 25, c);
	}
	//TOP�\���[�[�[�[
	wchar_t str[128];

	//TOP�̒l�𕶎���

	swprintf_s(str, L"TOP          %d", ((UserData*)Save::GetData())->mMaxScore);//�����𕶎���

	Font::StrDraw(str, 300, 450, 25, c);
	//�|�|�|�|�|�|�|�|
}
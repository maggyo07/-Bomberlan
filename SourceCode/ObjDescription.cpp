//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"
#include "Trace.h"
#include "GameHead.h"

#include "ObjDescription.h"
#include "ObjBom.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjDescription::Init()
{
}
//�A�N�V����
void CObjDescription::Action()
{	
	if(Input::GetVKey(VK_BACK) == true)
	{
		Scene::SetScene(new CSceneTitle());
	}
}
//�h���[
void CObjDescription::Draw()
{
	//�`��J���[���
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�A�C�e���摜�\���E�A�C�e������
	for(int item = 0; item < 8 ; item++)
	{
		//�A�C�e���摜�\��-----------
		//�؂���ʒu�̐ݒ�
		src.m_top	= ITEM_SIZE * item;
		src.m_left	= 0;
		src.m_right	= src.m_left + ITEM_SIZE;
		src.m_bottom= ITEM_SIZE + src.m_top;

		//�u���b�N���������Ă���
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//�\���ʒu�̐ݒ�
		dst.m_top	= ITEM_SIZE * item;
		dst.m_left =  100;
		dst.m_right = dst.m_left + ITEM_SIZE;
		dst.m_bottom= dst.m_top + ITEM_SIZE;

		//�`��
		Draw::Draw(0,&src,&dst,c,0.0f);
		//----------------------------

		//�A�C�e���̐���-------------
		switch(item)
		{
			case 0:
				Font::StrDraw(L"�t�@�C�A�[�A�b�v�F",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"���Ɣ����͈̔͂��P�}�X����",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"�L����܂�",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 1:

				Font::StrDraw(L"�{���A�b�v�@�@�@�F",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"�P�x�ɃZ�b�g�ł������������B",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 2:

				Font::StrDraw(L"�����R���@�@�@�@�F",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"�ʏ�{���͖�R�b��ɔ������邪",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"�����R��������Z�L�[�Ŕ�������B",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 3:

				Font::StrDraw(L"�X�P�[�g�@�@�@�@�F",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"�X�s�[�h�������㏸���܂��B",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 4:

				Font::StrDraw(L"�{�����蔲���@�@�F",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"�{���̏��ʂ邱�Ƃ��o����B",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 5:

				Font::StrDraw(L"�����K���蔲���@�F",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"�����K�̏��ʂ邱�Ƃ��o����B",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 6:

				Font::StrDraw(L"�t�@�C�A�[�}���@�F",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"�����ɓ������Ă����S���Ȃ��Ȃ�",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;

			case 7:

				Font::StrDraw(L"�p�[�t�F�N�g�}���F",100 + 40,ITEM_SIZE * item,40,c);
				Font::StrDraw(L"��R�O�b�ԉ��y���ς��G�E������",100 + 380,ITEM_SIZE * item,20,c);
				Font::StrDraw(L"�������Ă����S���Ȃ��Ȃ�B",100 + 380,ITEM_SIZE * item + 20,20,c);
				break;
		}
		//---------------------------
	}

	//���̑��̐���--------------
	Font::StrDraw(L"To return, press the BACKSPACE key!",50,320,40,c);

	Font::StrDraw(L"�E���̃Q�[���̓X�e�[�W���̑S�Ă̓G�𔚕�����肭�g���S�ł���",50,360,20,c);
	Font::StrDraw(L"�������̃����K�ɉB��Ă�����ɓ���Ǝ��̃X�e�[�W�֍s��",70,380,20,c);
	Font::StrDraw(L"�X�e�[�W3���N���A����ƃQ�[���N���A�ł��B",70,400,20,c);

	Font::StrDraw(L"�E�����K�͔����Ŕj��ł��܂��B",50,440,20,c);

	Font::StrDraw(L"�E���ɔ����𓖂Ă���A����̎��Ԃ��O�ɂȂ����Ƃ���",50,480,20,c);
	Font::StrDraw(L"0�ɂȂ����Ƃ�����100�b�Ԋu�ŁA�G���o�Ă��܂��B",70,500,20,c);

	Font::StrDraw(L"�E�A�C�e���ɔ����𓖂Ă�ƓG���o�Ă��邱�Ƃ�����܂��B",50,540,20,c);


	//--------------------------
}
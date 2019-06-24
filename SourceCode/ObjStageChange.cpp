//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "ObjStageChange.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjStageChange::Init()
{
	m_time = 0;
}
//�A�N�V����
void CObjStageChange::Action()
{
	m_time ++;


	if(m_time >= 200)
	{
		Scene::SetScene(new CSceneMain());
	}

	//���C���V�[���O�ɃX�y�[�X�������Ǝ�l�����o���u�ԁA�X�y�[�X�L�[��������Ă���Ƃ�������ɂȂ��Ă��܂��ĊJ�n����Ƀ{�����u����Ă��܂��̂ŁB
	if (Input::GetVKey(VK_SPACE));
}
//�h���[
void CObjStageChange::Draw()
{

	//�`��J���[���
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	wchar_t str[128];

	//�b�̒l�𕶎���
	
	swprintf_s(str,L"�X�e�[�W%d",((UserData*)Save::GetData())->mStageNumber);//�����𕶎���
	
	Font::StrDraw(str,300,250,50,c);

}
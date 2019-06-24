//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneTitle.h"
#include "GameHead.h"

//�R���g���X�g
CSceneTitle::CSceneTitle()
{

}
//�f�X�g���X�g
CSceneTitle::~CSceneTitle()
{

}

//�Q�[�����C�����������\�b�h
void CSceneTitle::InitScene()
{
	//���[�h����ƃX�R�A���ς���Ă��܂��̂ł��̑O�ɋL�^
	int score = ((UserData*)Save::GetData())->mScore;

	//���[�h
	Save::Open();//���t�H���_�uUserData�v����f�[�^�擾
	//�ߋ��̃X�R�A��茻�݂̃X�R�A�̂ق���������΍X�V
	if (score > ((UserData*)Save::GetData())->mMaxScore)
	{
		//�X�R�A�X�V�@
		((UserData*)Save::GetData())->mMaxScore = score;
	}
	//�Z�[�u
	Save::Seve();//UserData�̏��𓯃t�H���_�uUserData�v���쐬
	
	//UserData�̏���������------
	((UserData*)Save::GetData())->mScore = 0;
	((UserData*)Save::GetData())->mStageNumber = 1;
	((UserData*)Save::GetData())->mBomUpNum = 0;
	((UserData*)Save::GetData())->mFireUpNum = 0;
	((UserData*)Save::GetData())->mSkateNum = 0;
	((UserData*)Save::GetData())->mBomSlippingThrough = false;
	((UserData*)Save::GetData())->mDestructableBlockSlippingThrough = false;
	((UserData*)Save::GetData())->mFireMan = false;
	((UserData*)Save::GetData())->mRemoteController = false;
	//----------------------------

	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^�i512*512�߸�فj
	Draw::LoadImage(L"Title.png", 0, TEX_SIZE_256);

	//���y����0�Ԃɓǂݍ���
	Audio::LoadAudio(0, L"Title.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(1, L"CursorSelection.wav", SOUND_TYPE::EFFECT);

	//�o�b�N�~���[�W�b�N�X�^�[�g
	float Volume = Audio::VolumeMaster(0.8f);//�}�X�^�[�{�����[����0.8������
	Audio::Start(0); //���y�X�^�[�g

	//�^�C�g���I�u�W�F�N�g�쐬
	CObjTitle* obj= new CObjTitle();	//�^�C�g���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj,OBJ_TITLE,10);	//�^�C�g���I�u�W�F�g�o�^
	

}

//�Q�[�����C�����s�����\�b�h
void CSceneTitle::Scene()
{
	
}
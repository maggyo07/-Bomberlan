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
#include "SceneStageChange.h"
#include "GameHead.h"

//�R���g���X�g
CSceneStageChange::CSceneStageChange()
{

}
//�f�X�g���X�g
CSceneStageChange::~CSceneStageChange()
{

}

//�Q�[�����C�����������\�b�h
void CSceneStageChange::InitScene()
{
	Audio::LoadAudio(0, L"StageChange.wav",EFFECT);
	Audio::Start(0);//0�ԋȂ��X�^�[�g

	//�X�e�[�W�ύX�I�u�W�F�N�g�쐬
	CObjStageChange* obj_stage_change= new CObjStageChange();	//�X�e�[�W�ύX�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj_stage_change,OBJ_STAGE_CHANGE,10);	//�X�e�[�W�ύX�I�u�W�F�g�o�^
}

//�Q�[�����C�����s�����\�b�h
void CSceneStageChange::Scene()
{
	
}
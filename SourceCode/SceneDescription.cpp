//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneDescription.h"
#include "GameHead.h"

//�R���g���X�g
CSceneDescription::CSceneDescription()
{
}
//�f�X�g���X�g
CSceneDescription::~CSceneDescription()
{
}

//�Q�[�����C�����������\�b�h
void CSceneDescription::InitScene()
{
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(320*320�s�N�Z��)
	Draw::LoadImageW(L"item.png",0, TEX_SIZE_320);

	//�Q�[���N���A�I�u�W�F�N�g�쐬
	CObjDescription* obj = new CObjDescription();
	Objs::InsertObj(obj, OBJ_DESCRIPTION, 2);
}

//�Q�[�����C�����s�����\�b�h
void CSceneDescription::Scene()
{
}
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
#include "SceneGameClear.h"
#include "GameHead.h"

//�R���g���X�g
CSceneGameClear::CSceneGameClear()
{
}
//�f�X�g���X�g
CSceneGameClear::~CSceneGameClear()
{

}

//�Q�[�����C�����������\�b�h
void CSceneGameClear::InitScene()
{
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^�i800*800�߸�فj
	Draw::LoadImage(L"GameClearBack.png", 0, TEX_SIZE_800);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^�i512*512�߸�فj
	Draw::LoadImage(L"image.png", 1, TEX_SIZE_512);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^�i120*120�߸�فj
	Draw::LoadImage(L"LoadRunnerHero.png", 2, TEX_SIZE_120);

	//���y����0�Ԃɓǂݍ���
	Audio::LoadAudio(0, L"GameClear.wav", BACK_MUSIC);

	//�o�b�N�~���[�W�b�N�X�^�[�g
	Audio::Start(0); //���y�X�^�[�g

	//�Q�[���N���A�I�u�W�F�N�g�쐬
	CObjGameClear* obj_game_clear = new CObjGameClear();
	Objs::InsertObj(obj_game_clear, OBJ_GAME_CLEAR, 2);
}

//�Q�[�����C�����s�����\�b�h
void CSceneGameClear::Scene()
{
}
#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//MAP_Y�AMAP_X��Block�I�u�W�F�N�g�̂��̗p
#include "ObjBlock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�X�e�[�W�ύX
class CSceneStageChange:public CScene
{
public:
	CSceneStageChange();
	~CSceneStageChange();
	void InitScene();//�X�e�[�W�ύX���������\�b�h
	void Scene();   //�X�e�[�W�ύX�̎��s�����\�b�h
private:
};
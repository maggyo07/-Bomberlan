#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//MAP_Y�AMAP_X��Block�I�u�W�F�N�g�̂��̗p
#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�Q�[�����C��
class CSceneMain :public CScene
{
public:
	CSceneMain();
	~CSceneMain();
	void InitScene();//�Q�[�����C�����������\�b�h
	void Scene();   //�Q�[�����C���̎��s�����\�b�h
private: 
	void WorldDataCreation();
	void MapRandomByValueAssignment(int place_locate, int locate_object, int locate_count);
	int m_map[MAP_Y][MAP_X];
};
#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjTitle:public CObj
{
public:
	CObjTitle(){};
	~CObjTitle(){};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
	bool m_key_flag;	//�L�[�t���O
	bool m_start_or_continue;//���݂̃J�[�\���̈ʒu�@true = start::false = description
};
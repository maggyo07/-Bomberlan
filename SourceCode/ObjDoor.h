#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�w��l�̃X�e�[�W���N���A����ƃQ�[���N���A
#define MAX_STAGE 10

//�I�u�W�F�N�g�F�h�A(��)
class CObjDoor : public CObj
{
public :
	CObjDoor(float x,float y);
	~CObjDoor(){};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

private:
	//�ʒu
	float m_x;
	float m_y;

	//�G�̐�
	int m_enemy_number;

	//�h�A�̊J��	true:�J	false:��
	bool m_opening_and_closing;

	//�h�A�̓����蔻�莞��
	int m_door_hit_test_time;
	//�h�A�̓����蔻�莞�Ԃ̍ő�l
	int m_door_hit_test_max_time;
	//�����I�u�W�F�N�g�ɓ������Ă��邩�ǂ���
	bool m_hit_blast;//true:�������Ă���@false:�������Ă��Ȃ�
};
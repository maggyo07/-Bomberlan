#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�X�R�A
class CObjScore : public CObj
{
public :
	CObjScore();
	CObjScore(int score,float x,float y);
	~CObjScore(){};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

private:
	bool m_big_or_small;//��̂ق��ɑ傫���\������Ă���X�R�A���G��A�C�e���l�����ɂ��炦��X�R�A���@true:�傫���ق�	false�F�������ق�

	//�������\������X�R�A
	int m_score;
	//�������ق��̈ʒu
	float m_x;
	float m_y;

	int m_time;//����
};
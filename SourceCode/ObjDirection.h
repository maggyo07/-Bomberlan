#pragma once
#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F����(�_�C�N�X�g���@�̃m�[�h�����m�F�p)
class CObjDirection : public CObj
{
public:
	CObjDirection(float x,float y,int directon_x, int directon_y);
	~CObjDirection() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	float m_x;
	float m_y;
	int m_directon_x;	//����
	int m_directon_y;
	int m_posture;//�p
	int m_time;
};
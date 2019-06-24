#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define RECTANGLE 5.0//�ǂꂮ�炢�ׂ����邩


enum DIRECTION
	{
		RIGHT,
		LEFT,
		UP,
		DOWN,
		IN_SITU,
	};

//�I�u�W�F�N�g�F����
class CObjBlast : public CObj
{
public :
	CObjBlast(float x, float y,int direction, int magnification);
	~CObjBlast(){};
	void SetLastBlast(bool last_blast){m_last_blast = last_blast;}
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

private:
	float m_x;//�ʒu
	float m_y;
	int m_direction;//����
	bool m_last_blast;//�Ō�̔���
	int m_ani_data;//�����A�j���[�V�����̓���

	int m_ani_time;		//�A�j���[�V�����t���[������Ԋu
	int m_ani_max_time;		//�A�j���[�V�����t���[������Ԋu�ő�l

	int m_map[MAP_Y][MAP_X];

};
#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;



//�I�u�W�F�N�g�F�{��
class CObjBom : public CObj
{
public :
	CObjBom(float x, float y);
	~CObjBom(){};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	float m_x;		//�ʒu
	float m_y;

	int m_ani_time;		//�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;	//�`��t���[��

	int m_time;	//����

	float m_ani_max_time;	//�A�j���[�V��������Ԋu�ő�l

	int m_ani_frame_change; //�A�j���[�V�����؂�ւ��p

	int m_hero_bom_power; //��l���̃{���p���[

	int m_map[MAP_Y][MAP_X];
};
#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;



//�I�u�W�F�N�g�F�I�o�s�[(�G)
class CObjObapy : public CObj
{
public :
	CObjObapy(float x, float y);
	~CObjObapy(){};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

private:
	float m_x;		//�ʒu
	float m_y;
	float m_vx;		//�ړ��x�N�g��
	float m_vy;
	float m_posture;//�p

	int m_ani_time;		//�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;	//�`��t���[��

	float m_speed_power;	//�X�s�[�h�p���[
	float m_ani_max_time;	//�A�j���[�V��������Ԋu�ő�l

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool m_death_flag; //���S�t���O�@true:�����ɐG�ꂽ�Ƃ�	false:�����ɐG��Ă��Ȃ���

	int m_death_time;	//���S�t���O����������̎���

	bool m_bom_hit_test;//�{�������蔻��Btrue:����L��	false:���薳��

	bool m_breakable_block_hit_test;//�j��\�u���b�N�����蔻��Btrue:����L��	false:���薳��

	//����
	int m_time;

	//X�̗v�f�ԍ�
	int element_number_x;
	//Y�̗v�f�ԍ�
	int element_number_y;

	Node m_node;
};
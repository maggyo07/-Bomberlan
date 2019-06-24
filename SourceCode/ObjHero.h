#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define RECTANGLE 5.0//�ǂꂮ�炢�ׂ����邩

//�I�u�W�F�N�g�F��l��
class CObjHero : public CObj
{
public :
	CObjHero() {};
	~CObjHero(){};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	float GetX(){return m_px;}
	float GetY(){return m_py;}
	float GetVY(){return m_vy;}
	float GetVX(){return m_vx;}
	int GetBomPower(){return m_bom_power;}
	bool GetRemoteController(){return m_remote_controller;}

	void SetX(float x){m_px = x;}
	void SetY(float y){m_py = y;}
	void SetVY(float vy){m_vy = vy;}
	void SetVX(float vx){m_vx = vx;}

	void SetBomNum() { m_bom_num--; }

private:
	float m_px;	//�ʒu
	float m_py;
	float m_vx;	//�ړ��x�N�g��
	float m_vy;
	int m_posture;//�p

	int m_ani_time; //�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;//�`��t���[��

	float m_ani_max_time;	//�A�j���[�V��������Ԋu�ő�l

	//block�Ƃ̏Ռ���Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool m_death_flag; //���S�t���O�@true:�G�┚���ɐG�ꂽ�Ƃ�	false:�G�┚���ɐG��Ă��Ȃ���

	int m_death_time;	//���S�t���O����������̎���

	float m_speed_power;//�X�s�[�h�p���[

	int m_bom_num;//�X�e�[�W�ɂ���{���̐�

	int m_bom_max_num;//������ő吔

	int m_bom_power;//�{���̈З�

	bool m_remote_controller;//�����R��ON�EOFF

	bool m_bom_hit_test;//�{�������蔻��Btrue:����L��	false:���薳��

	bool m_breakable_block_hit_test;//�j��\�u���b�N�����蔻��Btrue:����L��	false:���薳��

	bool m_enemy_hit_test;//�G�����蔻��Btrue:����L��	false:���薳��

	bool m_blast_hit_test;//���������蔻��Btrue:����L��	false:���薳��

	bool m_get_fire_man;//�t�@�C�A�[�}������������ǂ�������Btrue:�����	false:����Ă��Ȃ�

	int m_parfect_man_time;//�p�[�t�F�N�g�}�����������̃^�C���B(30�b�ŏI��)

	bool m_get_parfect_man;//�p�[�t�F�N�g�}������������ǂ�������Btrue:�����	false:����Ă��Ȃ�

	void GetItemsInformation(CHitBox* hit);//�A�C�e�����Ƃ���������

	void KeyInput(CHitBox* hit);//�L�[����
};
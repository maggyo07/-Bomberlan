#pragma once
#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�Q�[���N���A
class CObjGameClear : public CObj
{
public:
	CObjGameClear() {};
	~CObjGameClear() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

private:
	float m_x;
	float m_y;

	float m_vx;
	float m_vy;

	int m_time;

	int m_ani_time;
	int m_ani_max_time;
	int m_ani_frame;

	bool m_stop;//�ړ��E�A�j���[�V������~�p	true�F��~	false�F�ʏ�

	int m_posture;

};
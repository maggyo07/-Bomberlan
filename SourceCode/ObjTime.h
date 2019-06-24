#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F����
class CObjTime : public CObj
{
public :
	CObjTime(int max_time);
	~CObjTime(){};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	int GetTime(){return m_time;}

private:
	int m_time;		//����
	bool m_out_put_enemy;//�G���o�����ǂ���	true�F�o��	false:�o���Ȃ�
	int m_enemy_time; //�G���o���Ɣ��f���Ă���̎��Ԍo��

	void AllocablePosition(float* x,float* y);
};
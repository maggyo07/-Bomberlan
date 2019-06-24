#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�A�C�e��
class CObjItem : public CObj
{
public :
	CObjItem(float x,float y,ITEM id);
	~CObjItem(){};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

private:
	float m_x;//�ʒu
	float m_y;

	int m_ani_time;		//�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;	//�`��t���[��

	bool m_ani_start;//�A�j���[�V�����X�^�[�g

	int m_item_id;	//�A�C�e���̎��
};
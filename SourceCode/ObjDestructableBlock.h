#pragma once
#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�j��\�u���b�N
class CObjDestructableBlock : public CObj
{
public:
	
	CObjDestructableBlock(float x, float y,bool door, ITEM id);
	/*CObjDestructableBlock(float x, float y, bool door) { CObjDestructableBlock(x,y,door,NOT_ITEM); }
	CObjDestructableBlock(float x, float y, ITEM id) { CObjDestructableBlock(x, y, false, id); }//�g���ˁ[
	CObjDestructableBlock(float x, float y) { CObjDestructableBlock(x, y, false, NOT_ITEM); }*/
	~CObjDestructableBlock() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	bool GetHitErase() { return m_hit_erase; }//�������ǂ����𔻒�p

private:
	float m_x;//�ʒu
	float m_y;
	bool m_hit_erase;//�����蔻�������

	int m_map[MAP_Y][MAP_X];

	int m_ani_time; //�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;//�`��t���[��

	float m_ani_max_time;	//�A�j���[�V��������Ԋu�ő�l

	bool m_with_door;		//�����B��Ă��邩�ǂ���

	ITEM m_item_id;		//���̃A�C�e�����o���u���b�N���B-1���A�C�e�����o���Ȃ��@
};
#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N
class CObjBlock : public CObj
{
public :
	CObjBlock(int map[MAP_Y][MAP_X]);
	~CObjBlock(){};

	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void SetScroll(float s)	{m_scroll = s;}
	float GetScroll()		{return m_scroll;}

	void GetMap(int map[MAP_Y][MAP_X]);

	//�u���b�N�Ƃ̓����蔻��
	void BlockHit(
	float *x,float *y,bool scroll_on,
	bool *up,bool *down,bool *left,bool *right,
	float *vx,float *vy,bool bom_hit_test,bool breakable_block_hit_test
	,const float *speed_power
	);

	//��l���ƕǂ̌�������
	bool HeroBlockCrossPoint(
		float x,float y,float vx,float vy,
		float *out_px,float *out_py,float* out_len
	);

	//�}�b�v�ύX�p�֐�
	void MapChange(int map[MAP_Y][MAP_X]);

private:
	void BlockDraw(float x, float y, RECT_F* dst, float c[]);
	
	int m_map[MAP_Y][MAP_X]; //�}�b�v���

	float m_scroll;		//���E�X�N���[���p

	float m_magma;		//�}�O�}�̐؂���n�ύX�p

	float m_hero_x;	//��l����X�ʒu
	float m_hero_y;	//��l����Y�ʒu

	float Dot(float ax, float ay, float bx, float by);	//����
	float Cross(float ax, float ay, float bx, float by);//�O��

	//���Ɛ��Ƃ̌�������
	bool CObjBlock::LineCrossPoint(
		float a1x,float a1y,float a2x,float a2y,
		float b1x,float b1y,float b2x,float b2y,
		float* out_px,float* out_py
		);

};
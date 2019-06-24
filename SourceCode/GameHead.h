#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_TITLE,
	OBJ_HERO,
	OBJ_BLOCK,
	OBJ_BACKGROUND,
	OBJ_TIME,
	OBJ_SCORE,
	OBJ_STAGE_CHANGE,
	OBJ_BOM,
	OBJ_BLAST,
	OBJ_DESTRUCTADLE_BLOCK,
	OBJ_MING_BO,
	OBJ_OBAPY,
	OBJ_DOOR,
	OBJ_GAME_CLEAR,
	OBJ_DESCRIPTION,
	
	//�A�C�e���I�u�W�F�N�g
	OBJ_FIRE_UP,
	OBJ_BOM_UP,
	OBJ_REMOTE_CONTROLLER,
	OBJ_SKATE,
	OBJ_BOM_SLIPPING_THROUGH,
	OBJ_DESTRUCTALE_BLOCK_SLIPPING_THROUGH,
	OBJ_FIRE_MAN,
	OBJ_PERFECT_MAN,
	//--------------------

	//�G�I�u�W�F�N�g
	OBJ_BAROM,
	OBJ_O_NEAL,
	OBJ_DULL,
	OBJ_CONDORIA,
	OBJ_PERTH,
	OBJ_PONTAN,
	//--------------------


};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	//�Z�[�u�����[�h�̓V�[���^�C�g��

	int mSeveData;	//�T���v���Z�[�u�f�[�^�@((UserData*)Save::GetData())->

	int mEnemyNumber;//�G�̐�		�F�������̓V�[�����C��

	int mScore;		//�X�R�A		�F�������̓V�[���^�C�g��
	int mMaxScore;	//�ߋ��ő�X�R�A�F�������̓V�[���^�C�g��

	int mStageNumber;//�X�e�[�W�ԍ�	�F�������̓V�[���^�C�g��

	int mFireUpNum;							//�t�@�C�A�A�b�v�����Ƃ������̏��			�F�������̓V�[���^�C�g��
	int mBomUpNum;							//�{���A�b�v������������̏��				�F�������̓V�[���^�C�g��
	int mSkateNum;							//�X�P�[�g�����Ƃ������̏��					�F�������̓V�[���^�C�g��
	bool mRemoteController;					//�����R������������ǂ����̏��				�F�������̓V�[���^�C�g��
	bool mFireMan;							//�t�@�C�A�[�}�����Ƃ������ǂ����̏��			�F�������̓V�[���^�C�g��
	bool mBomSlippingThrough;				//�{�����蔲�����Ƃ������ǂ����̏��			�F�������̓V�[���^�C�g��
	bool mDestructableBlockSlippingThrough;	//�j��\�u���b�N���蔲�����Ƃ������ǂ����̏��F�������̓V�[���^�C�g��
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--

//�m�[�h(�_�C�N�X�g���@�Ɏg��)
typedef struct Node
{
	int node_x;//�ړ�����ׂ�����X

	int node_y;//�ړ�����ׂ�����Y

	int cost;//�ړ��ɂ�����R�X�g

	bool flag;//���ׂ邩���ׂȂ����B
};

//�A�C�e���̎�ށ@��
enum ITEM
{
	NOT_ITEM=-1,
	FIRE_UP,
	BOM_UP,
	REMOTE_CONTROLLER,
	SKATE,
	BOM_SLIPPING_THROUGH,
	DESTRUCTALE_BLOCK_SLIPPING_THROUGH,
	FIRE_MAN,
	PERFECT_MAN,
};

//------------------------------------------------

//�Q�[�����Ŏg�p����}�N��------------------------
#define BLOCK_SIZE 40.0f
#define HERO_SIZE 40.0f
#define BOM_SIZE 40.0f
#define BLAST_SIZE 40.0f
#define DOOR_SIZE 40.0f

//�G�T�C�Y�[�[�[�[�[�[
#define BAROM_SIZE 40.0f
#define O_NEAL_SIZE 40.0f
#define DULL_SIZE 40.0f
#define MING_BO_SIZE 40.0f
#define OBAPY_SIZE 40.0f
#define CONDORIA_SIZE 40.0f
#define PERTH_SIZE 40.0f
#define PONTAN_SIZE 40.0f
//�|�|�|�|�|�|�|�|�|�|
//�A�C�e���T�C�Y�[�[�[
#define ITEM_SIZE 40.0f
//�|�|�|�|�|�|�|�|�|�|

//�؂���T�C�Y�[�[�[
#define BLAST_CUT_SIZE 32.0f
#define ENEMY_CUT_SIZE 40.0f
#define IMAAGE_CUT_SIZE 40.0f
#define ITEM_CUT_SIZE 40.0f
//�|�|�|�|�|�|�|�|�|�|

//�X�R�A�n�[�[�[�[�[�[

//�G�̃X�R�A
#define	BAROM_SCORE		100
#define	O_NEAL_SCORE	200
#define	DULL_SCORE		400
#define	MING_BO_SCORE	800
#define	OBAPY_SCORE		2000
#define	CONDORIA_SCORE	1000
#define PERTH_SCORE		4000
#define PONTAN_SCORE	8000
//�A�C�e���̃X�R�A
//�|�|�|�|�|�|�|�|�|�|
#define ITEM_SCORE		1000
//�[�[�[�[�[�[�[�[�[�[
#define MAP_X 51
#define MAP_Y 15
#define SKATE_SPEED_POWER 0.2f	//�X�P�[�g�������̑����X�s�[�h��
//------------------------------------------------

//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "ObjTitle.h"
#include "ObjHero.h"
#include "ObjBlock.h"
#include "ObjBom.h"
#include "ObjBlast.h"
#include "ObjDestructableBlock.h"
#include "ObjBackground.h"
#include "ObjTime.h"
#include "ObjDull.h"
#include "ObjDoor.h"
#include "ObjScore.h"
#include "ObjStageChange.h"
#include "ObjGameClear.h"
#include "ObjDescription.h"

#include "ObjBarom.h"
#include "ObjO_Neal.h"
#include "ObjDull.h"
#include "ObjMingBo.h"
#include "ObjObapy.h"
#include "ObjCondoria.h"
#include "ObjPerth.h"
#include "ObjPontan.h"

#include "ObjItem.h"

#include "ObjDirection.h"
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_-----------------------
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneStageChange.h"
#include "SceneGameClear.h"
#include "SceneDescription.h"
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START CSceneTitle
//#define SET_GAME_START CSceneGameClear
//-----------------------------------------------
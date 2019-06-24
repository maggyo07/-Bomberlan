//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"
#include "Trace.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "GameHead.h"
#include "UtilityModule.h"
#include <time.h>
//�R���g���X�g
CSceneMain::CSceneMain()
{
}
//�f�X�g���X�g
CSceneMain::~CSceneMain()
{

}

//�Q�[�����C�����������\�b�h
void CSceneMain::InitScene()
{
	//�G�̐�������
	((UserData*)Save::GetData())->mEnemyNumber = 0;

	//���[���h�f�[�^�쐬
	CSceneMain::WorldDataCreation();

	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^�i512*512�߸�فj
	Draw::LoadImage(L"image.png", 0, TEX_SIZE_512);

	//�O���O���t�B�b�N�t�@�C����ǂݍ��݂P�Ԃɓo�^(128*128�s�N�Z��)
	Draw::LoadImageW(L"blast.png",1, TEX_SIZE_128);

	//�O���O���t�B�b�N�t�@�C����ǂݍ��݂Q�Ԃɓo�^(320*320�s�N�Z��)
	Draw::LoadImageW(L"item.png",2, TEX_SIZE_320);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���3�Ԃɓo�^(800*800�s�N�Z��)
	Draw::LoadImageW(L"Background_03.png",3, TEX_SIZE_800);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���4�Ԃɓo�^(320*320�s�N�Z��)
	Draw::LoadImageW(L"enemy.png",4, TEX_SIZE_320);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���5�Ԃɓo�^(128*128�s�N�Z��)
	Draw::LoadImageW(L"direction.png", 5, TEX_SIZE_128);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���6�Ԃɓo�^(80*80�s�N�Z��)
	Draw::LoadImageW(L"door.png", 6, TEX_SIZE_80);

	//���y����ǂݍ���
	Audio::LoadAudio(0, L"main.wav", BACK_MUSIC);
	Audio::LoadAudio(1, L"BomBursting.wav", EFFECT);
	Audio::LoadAudio(2, L"mainTimeOver.wav", BACK_MUSIC);
	Audio::LoadAudio(3, L"ItemsObtain.wav", EFFECT);
	Audio::LoadAudio(4, L"DoorBlastHit.wav", EFFECT);
	Audio::LoadAudio(5, L"InvincibleState.wav", BACK_MUSIC);
	Audio::LoadAudio(6, L"DeadMoment.wav", EFFECT);
	Audio::LoadAudio(7, L"DeadAfter.wav", EFFECT);
	//�o�b�N�~���[�W�b�N�X�^�[�g
	Audio::Start(0); //���y�X�^�[�g

	//�u���b�N�I�u�W�F�N�g�쐬
	CObjBlock* obj_block = new CObjBlock(m_map);
	Objs::InsertObj(obj_block, OBJ_BLOCK, 9);

	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj_hero = new CObjHero();	//��l���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj_hero, OBJ_HERO, 10);	//��l���I�u�W�F�g�o�^

	//�o�b�N�O���t�B�b�N�I�u�W�F�N�g�쐬
	CObjBackground* obj_background = new CObjBackground();
	Objs::InsertObj(obj_background, OBJ_BACKGROUND, 1);

	//���ԃI�u�W�F�N�g�쐬
	CObjTime* obj_time = new CObjTime(200);
	Objs::InsertObj(obj_time, OBJ_TIME, 2);

	//�X�R�A�I�u�W�F�N�g�쐬
	CObjScore* obj_score = new CObjScore();
	Objs::InsertObj(obj_score, OBJ_SCORE, 2);
}

//�Q�[�����C�����s�����\�b�h
void CSceneMain::Scene()
{
}
//�֐��@���[���h�f�[�^�쐬
void CSceneMain::WorldDataCreation()
{
	//�O���f�[�^�̓ǂݍ���(�X�e�[�W���)
	unique_ptr<wchar_t> p;//�X�e�[�W���|�C���^�[
	int size;			  //�X�e�[�W���̑傫��

	p = Save::ExternalDataOpen(L"Debug.csv", &size);//�O���f�[�^�ǂݍ��݁F�f�o�b�N�p

	int count = 1;

	for (int map_y = 0; map_y < MAP_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_X; map_x++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			m_map[map_y][map_x] = w;
				count += 2;
		}
	}

	//��l���̏����ʒu�܂��͂��̎��ӂ�-2������
	//(���ꂪ�Ȃ���΃V�[�����C����MapRandomByValueAssignment�֐��ŋ󔒂��w��ꏊ�ƂȂ����ꍇ��l���̏����ʒu�ɐݒu����Ă��܂��̂�-2�������Ă���)
	m_map[5][1] = -2;//��l���̏����ʒu
	m_map[6][1] = -2;//��l���̏����ʒu�̉�
	m_map[5][2] = -2;//��l���̏����ʒu�̉E

	//�����_���Œl������p
	int random;

	//�󔒂̒�����j��\�u���b�N�������_���Ŕz�u
	random = GetRandom(70, 90);
	MapRandomByValueAssignment(0, 2, random);

	//�j��\�u���b�N�̒�����h�A�t���j��\�u���b�N�������_���Ō��߂�
	MapRandomByValueAssignment(2, 3, 1);

	//�󔒃u���b�N�̒�����G�������_���Ŕz�u����O��
	//��l���̋߂��ɓG�������獢��̂Ŏ�l���̏����ʒu�̎���5�܂�����-2������
	//�����̏����͔j��\�u���b�N�ݒu��ɂ���
	for (int map_y = 5; map_y <= 5 + 5; map_y++)
	{
		for (int map_x = 1; map_x <= 1 + 5; map_x++)
		{
			if (m_map[map_y][map_x] == 0)
			{
				m_map[map_y][map_x] = -2;
			}
		}
	}

	//�X�e�[�W���Ƃ̏���
	//�A�C�e���u���b�N�ƓG�̔z�u�����߂�
	switch (((UserData*)Save::GetData())->mStageNumber)
	{
	case 1:
		//�j��\�u���b�N�̒�����t�@�C�A�[�A�b�v(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(3, 5);
		MapRandomByValueAssignment(2, 12, random);

		//�󔒃u���b�N�̒�����o����(�G�j�������_���Ŕz�u����
		random = GetRandom(4, 6);
		MapRandomByValueAssignment(0, 20, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 2:
		//�j��\�u���b�N�̒�����t�@�C�A�[�A�b�v(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 12, random);
		//�j��\�u���b�N�̒�����{���A�b�v(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(2, 3);
		MapRandomByValueAssignment(2, 13, random);

		//�󔒃u���b�N�̒�����o����(�G�j�������_���Ŕz�u����
		random = GetRandom(5, 8);
		MapRandomByValueAssignment(0, 20, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 3:
		//�j��\�u���b�N�̒�����t�@�C�A�[�A�b�v(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(0, 1);
		MapRandomByValueAssignment(2, 12, random);
		//�j��\�u���b�N�̒�����{���A�b�v(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 13, random);

		//�󔒃u���b�N�̒�����o����(�G�j�������_���Ŕz�u����
		random = GetRandom(5, 8);
		MapRandomByValueAssignment(0, 20, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//�󔒃u���b�N�̒�����_��(�G�j�������_���Ŕz�u����
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(0, 22, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 4:
		//�j��\�u���b�N�̒�����{���A�b�v(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(2, 3);
		MapRandomByValueAssignment(2, 13, random);
		//�j��\�u���b�N�̒�����X�P�[�g(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(2, 4);
		MapRandomByValueAssignment(2, 15, random);

		//�󔒃u���b�N�̒�����o����(�G�j�������_���Ŕz�u����
		random = GetRandom(5, 7);
		MapRandomByValueAssignment(0, 20, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//�󔒃u���b�N�̒�����_��(�G�j�������_���Ŕz�u����
		random = GetRandom(2, 5);
		MapRandomByValueAssignment(0, 22, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 5:
		//�j��\�u���b�N�̒�����{�����蔲��(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 16, random);
		//�j��\�u���b�N�̒�����j��\�u���b�N���蔲��(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 17, random);

		//�󔒃u���b�N�̒�����_��(�G�j�������_���Ŕz�u����
		random = GetRandom(3, 5);
		MapRandomByValueAssignment(0, 22, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//�󔒃u���b�N�̒�����~���{�[(�G�j�������_���Ŕz�u����
		random = GetRandom(2, 5);
		MapRandomByValueAssignment(0, 23, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 6:
		//�j��\�u���b�N�̒�����t�@�C�A�[�A�b�v(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 12, random);
		//�j��\�u���b�N�̒����烊���R��(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		MapRandomByValueAssignment(2, 14, 1);

		//�󔒃u���b�N�̒�����~���{�[(�G�j�������_���Ŕz�u����
		random = GetRandom(3, 7);
		MapRandomByValueAssignment(0, 23, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//�󔒃u���b�N�̒�����R���h���A(�G�j�������_���Ŕz�u����
		random = GetRandom(2, 5);
		MapRandomByValueAssignment(0, 24, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 7:
		//�j��\�u���b�N�̒�����t�@�C�A�[�}��(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		MapRandomByValueAssignment(2, 18, 1);
		//�j��\�u���b�N�̒�����p�[�t�F�N�g�}��(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		MapRandomByValueAssignment(2, 19, 1);

		//�󔒃u���b�N�̒�����R���h���A(�G�j�������_���Ŕz�u����
		random = GetRandom(3, 7);
		MapRandomByValueAssignment(0, 24, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//�󔒃u���b�N�̒�����p�[�X(�G�j�������_���Ŕz�u����
		random = GetRandom(2, 3);
		MapRandomByValueAssignment(0, 26, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 8:
		//�j��\�u���b�N�̒�����{�����蔲��(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		MapRandomByValueAssignment(2, 16, 1);
		//�j��\�u���b�N�̒�����j��\�u���b�N���蔲��(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		MapRandomByValueAssignment(2, 17, 1);

		//�󔒃u���b�N�̒�����p�[�X(�G�j�������_���Ŕz�u����
		random = GetRandom(2, 3);
		MapRandomByValueAssignment(0, 26, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//�󔒃u���b�N�̒�����I�o�s�[(�G�j�������_���Ŕz�u����
		random = GetRandom(3, 4);
		MapRandomByValueAssignment(0, 25, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 9:
		//�j��\�u���b�N�̒�����t�@�C�A�[�A�b�v(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 12, random);

		//�󔒃u���b�N�̒�����I�o�s�[(�G�j�������_���Ŕz�u����
		random = GetRandom(4, 6);
		MapRandomByValueAssignment(0, 25, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		//�󔒃u���b�N�̒�����I�j�[��(�G�j�������_���Ŕz�u����
		random = GetRandom(3, 4);
		MapRandomByValueAssignment(0, 21, random);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += random;
		break;

	case 10:
		//�j��\�u���b�N�̒�����{���A�b�v(�A�C�e��)���o��u���b�N�����_���Ō��߂�
		random = GetRandom(1, 2);
		MapRandomByValueAssignment(2, 13, random);

		//�󔒃u���b�N�̒�����o����(�G�j�������_���Ŕz�u����
		MapRandomByValueAssignment(0, 20, 2);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//�󔒃u���b�N�̒�����I�j�[��(�G�j�������_���Ŕz�u����
		MapRandomByValueAssignment(0, 21, 2);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//�󔒃u���b�N�̒�����_��(�G�j�������_���Ŕz�u����
		MapRandomByValueAssignment(0, 22, 2);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//�󔒃u���b�N�̒�����~���{�[(�G�j�������_���Ŕz�u����
		MapRandomByValueAssignment(0, 23, 2);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//�󔒃u���b�N�̒�����R���h���A(�G�j�������_���Ŕz�u����
		MapRandomByValueAssignment(0, 24, 2);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//�󔒃u���b�N�̒�����I�o�s�[(�G�j�������_���Ŕz�u����
		MapRandomByValueAssignment(0, 25, 2);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//�󔒃u���b�N�̒�����p�[�X(�G�j�������_���Ŕz�u����
		MapRandomByValueAssignment(0, 26, 2);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += 2;
		//�󔒃u���b�N�̒�����|���^��(�G�j�������_���Ŕz�u����
		MapRandomByValueAssignment(0, 27, 1);
		//�G��z�u���������Z
		((UserData*)Save::GetData())->mEnemyNumber += 1;
		break;

	}
}

//�֐��@�}�b�v�Ƀ����_���Ŏw��ꏊ�Ɏw�蕨���w�肵�����������
//�����P	int place_locate	:�w��ꏊ(�w�蕨������ꏊ)
//�����Q	int locate_object	:�w�蕨(�w�肵���ꏊ�Ƀ����_���Ŏw�蕨���w�萔���)
//�����R	int locate_count	:�w�萔(�w�蕨��������邩)
void CSceneMain::MapRandomByValueAssignment(int place_locate, int locate_object, int locate_count)
{
	//�ݒu�ꏊ�̐�
	int place_locate_count = 0;

	//�}�b�v�̒�����w�肳�ꂽ�I�u�W�F�N�g�̐��𐔂���
	for(int y = 5;y < MAP_Y; y++)
	{
		for(int x = 0; x < MAP_X; x++)
		{
			//�ݒu�ꏊ���Ɖ��Z
			if(m_map[y][x] == place_locate)
			{
				place_locate_count++;
			}
		}
	}

	//�����_���Őݒu����ꏊ�����߂Ă��̒l������
	int random_place_locate[100] = {0};
	int a;
	//�ݒu�ꏊ�����w�萔(����)������������
	if (locate_count > place_locate_count)
	{
		//�ݒu�ꏊ�̐�������
		a = place_locate_count;
	}
	else
	{
		a = locate_count;
	}
	//�ݒu���鐔����
	for(int i = 0; i < a; i++)
	{
		//�ݒu�\�ꏊ�������_���Ō��߂�
		int random_place_locate_count = GetRandom(1, place_locate_count);

		//��x���߂��l�łȂ����𒲂ׂ�
		for(int j = 0; j < 100; j++)
		{
			//��x���߂��l�������烋�[�v�𔲂���
			if(random_place_locate_count == random_place_locate[j])
			{
				i--;
				break;
			}

			//���߂Ă̒l���Ƒ��
			if (j == 99)
			{
				random_place_locate[i] = random_place_locate_count;
			}
		}
	}

	//�ݒu�ꏊ�̐���������
	place_locate_count = 0;

	
	for(int map_y = 5; map_y < MAP_Y; map_y++)
	{
		for(int map_x = 0; map_x < MAP_X; map_x++)
		{
			//�ݒu����I�u�W�F�N�g�ł����
			if(m_map[map_y][map_x] == place_locate)
			{
				//���Z
				place_locate_count++;

				for(int i = 0; i < 100 ; i++)
				{
					//�������l��������
					if(place_locate_count == random_place_locate[i])
					{
						//���̏ꏊ�ɐݒu����I�u�W�F�N�g����
						m_map[map_y][map_x] = locate_object;
					}
				}
			}
		}
	}
}
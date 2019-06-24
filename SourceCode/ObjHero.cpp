//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"
#include "Trace.h"

#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = 40.0f;	//�����ʒu
	m_py = BLOCK_SIZE * 5;

	m_vx = 0.0f;	//�x�N�g��
	m_vy = 0.0f;

	m_posture = 0; //�E����0 ������1 ���2�@������3

	m_ani_time = 0;
	m_ani_frame = 0;	//�Î~�t���[���������ɂ���

	m_ani_max_time = 4;	//�A�j���[�V�����Ԋu��

	m_speed_power = 0.5f + (SKATE_SPEED_POWER * ((UserData*)Save::GetData()) ->mSkateNum);//�X�s�[�h�p���[������

	//block�Ƃ̏Ռ���Ԋm�F�p
	m_hit_up	=false;
	m_hit_down	=false;
	m_hit_left	=false;
	m_hit_right	=false;
	 
	m_death_flag = false;//���S�t���O������
	m_death_time = 0;	//���S�t���O���ԏ�����

	m_remote_controller = ((UserData*)Save::GetData()) ->mRemoteController;//�����R���@�\

	m_bom_power = 1 + ((UserData*)Save::GetData()) ->mFireUpNum;//�{���̈З͏�����

	m_bom_num = 0;	//�X�e�[�W���ɂ���{���̐�
	m_bom_max_num = 1 +((UserData*)Save::GetData()) ->mBomUpNum;//�X�e�[�W���ɂ�����ő吔

	//�{�����蔲�����Ƃ��Ă�����
	if (((UserData*)Save::GetData())->mBomSlippingThrough == true)
	{
		m_bom_hit_test = false;//�{�������蔻�薳��
	}
	else
	{
		m_bom_hit_test = true;//�{�������蔻�肠��
	}

	//�j��\�u���b�N���蔲�����Ƃ���������
	if (((UserData*)Save::GetData())->mDestructableBlockSlippingThrough == true)
	{
		m_breakable_block_hit_test = false;//�j��\�u���b�N�����蔻�薳��
	}
	else
	{
		m_breakable_block_hit_test = true;//�j��\�u���b�N�����蔻�肠��
	}

	if (((UserData*)Save::GetData())->mFireMan == true)
	{
		m_blast_hit_test = false;//���������蔻�薳��
	}
	else
	{
		m_blast_hit_test = true;//���������蔻�肠��
	}

	m_enemy_hit_test = true;//�G���茒��

	m_get_fire_man = ((UserData*)Save::GetData())->mFireMan;	//�t�@�C�A�[�}�����Ƃ����ǂ���

	m_parfect_man_time = 0;

	m_get_parfect_man = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px + RECTANGLE, m_py + RECTANGLE, HERO_SIZE - RECTANGLE * 2, HERO_SIZE - RECTANGLE * 2, ELEMENT_PLAYER, OBJ_HERO, 1);


}
//�A�N�V����
void CObjHero::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + RECTANGLE, m_py + RECTANGLE);

	//���S�t���O�������Ă��Ȃ�������
	if (m_death_flag == false)
	{
		//�L�[����
		KeyInput(hit);

		//�����؂�ւ�(�t���[��)�h�~
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame++;
			m_ani_time = 0;
		}

		//�Ō�̃t���[���ɍs������ŏ��̃t���[���ɖ߂�
		if(m_ani_frame == 4)
		{
			m_ani_frame = 0;
		}

		//���C
		m_vx += -(m_vx * 0.198);
		m_vy += -(m_vy * 0.198);

		//�u���b�N����
		block->BlockHit(&m_px,&m_py,true,
			&m_hit_up,&m_hit_down,&m_hit_left,&m_hit_right,&m_vx,&m_vy,
			m_bom_hit_test,m_breakable_block_hit_test,&m_speed_power
			);
	
		//�ʒu�̍X�V
		m_py += m_vy;
		m_px += m_vx;

	}
	//���S�t���O�������Ă�����
	else
	{
		m_death_time++;

		//���S���Ă���̎��ԒP�ʂ̃t���[���؂�ւ�
		//�P��ڂ̃t���[���؂�ւ�
		if(m_death_time == 20)
		{
			Audio::Start(7); //7�ԋȂ��X�^�[�g
			m_ani_frame++;
		}
		//�Q��ڂ̃t���[���؂�ւ�
		if (m_death_time == 60)
		{
			m_ani_frame++;
		}
		//3��ڂ̃t���[���؂�ւ�
		if (m_death_time == 100)
		{
			m_ani_frame++;
		}

		//�{���ɏ���
		if (m_death_time == 140)
		{
			this->SetStatus(false);		//���g�ɏ��Ŗ��߂��o���B
			Hits::DeleteHitBox(this);	//���g�����L����HitBox�ɏ��ł���B

			//�X�e�[�W�P�����蒼��
			((UserData*)Save::GetData())->mStageNumber = 1;

			//�V�[��(�X�e�[�W�ύX)�Ăяo��
			//Scene::SetScene(new CSceneStageChange());
			//��񎀂񂾂�I��
			Scene::SetScene(new CSceneTitle());
		}

	}
	

	//�����I�u�W�F�N�g�ɐڐG���Ă����� && �������肪��������
	if(hit->CheckObjNameHit(OBJ_BLAST) != nullptr && m_blast_hit_test == true)
	{
		//���łɎ��S�t���O�������Ă����珈�����Ȃ�
		if (m_death_flag != true)
		{
			Audio::Start(6); //6�ԋȂ��X�^�[�g

			//�ǂ��炪����Ă��邩�킩��Ȃ��̂łQ�X�g�b�v
			Audio::Stop(0);	//0�ԋȂ��X�g�b�v
			Audio::Stop(2);//2�ԋȂ��X�g�b�v

			m_death_flag = true;//�����ɐG�ꂽ�I
			m_ani_frame = 0;//�t���[�������O�ɂ���
		}
	}

	//ENEMENT_ENEMY�����I�u�W�F�N�g�ɐڐG���Ă����� && �G���肪��������
	if(hit->CheckElementHit(ELEMENT_ENEMY) == true && m_enemy_hit_test == true)
	{
		//���łɎ��S�t���O�������Ă����珈�����Ȃ�
		if (m_death_flag != true)
		{
			Audio::Start(6); //6�ԋȂ��X�^�[�g

			//�ǂ��炪����Ă��邩�킩��Ȃ��̂łQ�X�g�b�v
			Audio::Stop(0);	//0�ԋȂ��X�g�b�v
			Audio::Stop(2);//2�ԋȂ��X�g�b�v
			m_death_flag = true; //�G�ɐG�ꂽ�I
			m_ani_frame = 0;//�t���[�������O�ɂ���
		}
	}

	//�p�[�t�F�N�g�}��������Ă�����
	if(m_get_parfect_man == true)
	{
		//�p�[�t�F�N�g�}���^�C�����Z
		m_parfect_man_time++;
		//�ǂ��炪����Ă��邩�킩��Ȃ��̂łǂ�������y���X�g�b�v������
		Audio::Stop(0);//0�ԋȂ��X�g�b�v
		Audio::Stop(2);//2�ԋȂ��X�g�b�v

		//�p�[�t�F�N�g�}���^�C����30�b(�t���[����*30)�ȏゾ������
		//�p�[�t�F�N�g��ԏI��
		if(m_parfect_man_time >= 60*30)
		{
			Audio::Stop(5);//5�ԋȂ��X�g�b�v

			//Time�I�u�W�F�N�g���������Ă���
			CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);

			//���Ԃ��O�̂Ƃ�
			if (time->GetTime() <= 0)
			{
				Audio::Start(2);//2�ԋȂ��X�^�[�g
			}
			else
			{
				Audio::Start(0);//0�ԋȂ��X�^�[�g
			}

			//�p�[�t�F�N�g�}���t���O����
			m_get_parfect_man = false;
			//�p�[�t�F�N�g�}���^�C��������
			m_parfect_man_time = 0;
			//�G�̓����蔻�蕜��
			m_enemy_hit_test = true;

			//�t�@�C�A�[�}��������Ă��Ȃ�������
			if(m_get_fire_man == false)
			{

				m_blast_hit_test = true;
			}

		}
	}

	//�A�C�e�����Ƃ���������
	GetItemsInformation(hit);

}
//�h���[
void CObjHero::Draw()
{
	

	//�`��J���[���
	float c[4] = {1.0f,1.0f,1.0f,1.0f};

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu
	//���S�t���O�������Ă��Ȃ�������
	if (m_death_flag == false)
	{
		//�����A����A�j���[�V��������o�^
		int AniData[4] =
		{
			 1 , 0 , 2 , 0
		};
		//�E����0 ������1 �����2�@������3
		//�������p�̐؂���ʒu
		if (m_posture == 2)
		{
			//�؂���ʒu�̐ݒ�
			src.m_top = IMAAGE_CUT_SIZE * 1;
			src.m_left = IMAAGE_CUT_SIZE * AniData[m_ani_frame];
			src.m_right = IMAAGE_CUT_SIZE + AniData[m_ani_frame] * 40.0f;
			src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;
		}
		//��������p�̐؂���ʒu
		else if (m_posture == 3)
		{
			//�؂���ʒu�̐ݒ�
			src.m_top = IMAAGE_CUT_SIZE * 2;
			src.m_left = IMAAGE_CUT_SIZE * AniData[m_ani_frame];
			src.m_right = IMAAGE_CUT_SIZE + AniData[m_ani_frame] * 40.0f;
			src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;
		}
		//�E�E��������p�̐؂���ʒu
		else
		{
			//�؂���ʒu�̐ݒ�
			src.m_top = IMAAGE_CUT_SIZE * 0;
			src.m_left = IMAAGE_CUT_SIZE * AniData[m_ani_frame];
			src.m_right = IMAAGE_CUT_SIZE + AniData[m_ani_frame] * 40.0f;
			src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;
		}


		//�E����0 ������1 �����2�@������3
		//��E��������p�\���ʒu
		if (m_posture == 2 || m_posture == 3)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = 0.0f + m_py;
			dst.m_left = (HERO_SIZE * 0) + m_px;
			dst.m_right = (HERO_SIZE - HERO_SIZE * 0) + m_px;
			dst.m_bottom = HERO_SIZE + m_py;

		}
		//�E�E��������p�̕\���ʒu
		else
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = 0.0f + m_py;
			dst.m_left = (HERO_SIZE * m_posture) + m_px;
			dst.m_right = (HERO_SIZE - HERO_SIZE * m_posture) + m_px;
			dst.m_bottom = HERO_SIZE + m_py;

		}


		//�`��
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	//���S�t���O�������Ă�����
	else
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = IMAAGE_CUT_SIZE;
		src.m_left = IMAAGE_CUT_SIZE * 3 + IMAAGE_CUT_SIZE * m_ani_frame;
		src.m_right = src.m_left + IMAAGE_CUT_SIZE;
		src.m_bottom = IMAAGE_CUT_SIZE + src.m_top;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = (HERO_SIZE * 0) + m_px;
		dst.m_right = (HERO_SIZE - HERO_SIZE * 0) + m_px;
		dst.m_bottom = HERO_SIZE + m_py;

		//�`��
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}

}

//�֐��@�A�C�e�����Ƃ������ǂ����̔���
//�����P�@CHitBox* hit�@�Fhittobox�̏��
void CObjHero::GetItemsInformation(CHitBox* hit)
{
		//�t�@�C�A�[�A�b�v�����ƃ{���̉ἨA�b�v
		if(hit->CheckObjNameHit(OBJ_FIRE_UP) != nullptr)
		{
			Audio::Start(3);//3�ԋȂ��X�^�[�g
			//�t�@�C�A�[�A�b�v��15�܂�
			if(m_bom_power <15)
			{
				m_bom_power++; 
				((UserData*)Save::GetData())->mFireUpNum++;
			}
		}
		//���e�A�b�v�����ƃ{���̒u����ő吔���A�b�v
		if(hit->CheckObjNameHit(OBJ_BOM_UP) != nullptr)
		{
			Audio::Start(3);//3�ԋȂ��X�^�[�g
			//���e�A�b�v��10�܂�
			if(m_bom_max_num < 10)
			{
				m_bom_max_num++;
				((UserData*)Save::GetData())->mBomUpNum++;
			}
		}
		//�����R�������ƃ����R���@�\ON
		if(hit->CheckObjNameHit(OBJ_REMOTE_CONTROLLER) != nullptr)
		{
			Audio::Start(3);//3�ԋȂ��X�^�[�g
			m_remote_controller = true;
			((UserData*)Save::GetData())->mRemoteController = true;
		}
		//�X�P�[�g�����ƃX�s�[�h�p���[�A�b�v
		if(hit->CheckObjNameHit(OBJ_SKATE) != nullptr)
		{
			Audio::Start(3);//3�ԋȂ��X�^�[�g
			m_speed_power+= SKATE_SPEED_POWER;
			((UserData*)Save::GetData())->mSkateNum++;
		}
		//���e���蔲�������Ɣ��e�̔��薳��
		if(hit->CheckObjNameHit(OBJ_BOM_SLIPPING_THROUGH) != nullptr)
		{
			Audio::Start(3);//3�ԋȂ��X�^�[�g
			m_bom_hit_test = false;
			((UserData*)Save::GetData())->mBomSlippingThrough = true;
		}
		//�j��\�u���b�N���蔲�������Ɣj��\�u���b�N�̔��薳��
		if(hit->CheckObjNameHit(OBJ_DESTRUCTALE_BLOCK_SLIPPING_THROUGH) != nullptr)
		{
			Audio::Start(3);//3�ԋȂ��X�^�[�g
			m_breakable_block_hit_test = false;
			((UserData*)Save::GetData())->mDestructableBlockSlippingThrough = true;
		}
		//�t�@�C�A�[�}�������Ɣ����̔��薳��
		if(hit->CheckObjNameHit(OBJ_FIRE_MAN) != nullptr)
		{
			Audio::Start(3);//3�ԋȂ��X�^�[�g
			m_get_fire_man = true;
			m_blast_hit_test = false;
			((UserData*)Save::GetData())->mFireMan = true;
		}
		//�p�[�t�F�N�g�}�������Ɣ����E�G�̔��薳��
		if(hit->CheckObjNameHit(OBJ_PERFECT_MAN) != nullptr)
		{
			Audio::Start(3);//3�ԋȂ��X�^�[�g

			Audio::Start(5);//5�ԋȂ��X�^�[�g

			m_get_parfect_man = true;
			m_enemy_hit_test = false;
			m_blast_hit_test = false;
		}

}

//�֐��@�L�[����
//�����P�@CHitBox* hit�@:�q�b�g�{�b�N�X�̏��@�X�y�[�X�L�[����(�{���ݒu)�̍ۂɂ̂ݎg��
void CObjHero::KeyInput(CHitBox* hit)
{
	//�u���b�N���������Ă���
	//�{���ݒu�̍ۂɎg��
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�L�[�̓��͕���
	if (Input::GetVKey('D') == true || Input::GetVKey(VK_RIGHT) == true)
	{
		m_vx += m_speed_power;
		m_ani_time++;
		m_posture = 1; //�E����0 ������1 ���2�@������3
	}
	else if (Input::GetVKey('A') == true || Input::GetVKey(VK_LEFT) == true)
	{
		m_vx -= m_speed_power;
		m_ani_time++;
		m_posture = 0; //�E����0 ������1 ���2�@������3
	}
	else if (Input::GetVKey('W') == true || Input::GetVKey(VK_UP) == true)
	{
		m_vy -= m_speed_power;
		m_ani_time++;
		m_posture = 2; //�E����0 ������1 �����2�@������3
	}
	else if (Input::GetVKey('S') == true || Input::GetVKey(VK_DOWN) == true)
	{
		m_vy += m_speed_power;
		m_ani_time++;
		m_posture = 3; //�E����0 ������1 �����2�@������3
	}
	//�L�[���͂������ꍇ�͐Î~�t���[���ɂ���
	else
	{
		m_ani_frame = 1;
		m_ani_time = 0;
	}

	//�X�y�[���L�[����
	if (Input::GetVKey(VK_SPACE))
	{
		//�{���̍ő吔�𒴂��Ă��Ȃ�������
		if (m_bom_num < m_bom_max_num)
		{
			//�{���I�u�W�F�N�g�ɐڐG���Ă��Ȃ�������
			if (hit->CheckObjNameHit(OBJ_BOM) == nullptr)
			{
				//�����I�u�W�F�N�g�ɐڐG�����Ă��Ȃ�������
				if (hit->CheckObjNameHit(OBJ_BLAST) == nullptr)
				{
					//�j��\�I�u�W�F�N�g�ɐڐG���Ă��Ȃ�������
					if (hit->CheckObjNameHit(OBJ_DESTRUCTADLE_BLOCK) == nullptr)
					{
						//�h�A�I�u�W�F�N�g�ɐڐG���Ă��Ȃ�������
						if (hit->CheckObjNameHit(OBJ_DOOR) == nullptr)
						{
							m_bom_num++;
							//�{���I�u�W�F�N�g�쐬
							CObjBom* obj_bom = new CObjBom(m_px - block->GetScroll(), m_py);	//�{���I�u�W�F�N�g�쐬
							Objs::InsertObj(obj_bom, OBJ_BOM, 10);	//�{���I�u�W�F�g�o�^
							
						}
					}
				}
			}
		}
	}

}
#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_sceneName = SCENE_NAME_LOADDING_SCENE;

	scene::init();

	_loading = new loading;
	_loading->init();

	this->totalLoding();

	return S_OK;
}

void loadingScene::update()
{
	scene::update();
	_loading->update();


	//�ε��� ������ ü����
	if (_loading->loadingDone())
	{
		gameNode::init(true, true);

		SCENEMANAGER->changeScene("startScene");
	}


}

void loadingScene::release()
{
	scene::release();
	SAFE_DELETE(_loading);
}

void loadingScene::render()
{
	scene::render();
	_loading->render();
}

void loadingScene::totalLoding()
{
	//----------------------------------------------------------------------------------------------
	//�÷��̾� �ε��Դϴ�

	//�÷��̾� idle(��,��,��,��)
	_loading->loadImage("player_up_idle", "PLAYER_UP_IDLE.bmp", 50 * 3, 50 * 3, true, RGB(255, 0, 255));//
	_loading->loadImage("player_down_idle", "PLAYER_DOWN_IDLE.bmp", 50 * 3, 50 * 3, true, RGB(255, 0, 255));//
	_loading->loadImage("player_left_idle", "PLAYER_LEFT_IDLE.bmp", 50 * 3, 50 * 3, true, RGB(255, 0, 255));//
	_loading->loadImage("player_right_idle", "PLAYER_RIGHT_IDLE.bmp", 50 * 3, 50 * 3, true, RGB(255, 0, 255));//

	//�÷��̾� ����(��,��,��,��)
	_loading->loadFrameImage("player_up", "images/player/PLAYER_UP_MOVE.bmp", 450 * 3, 50 * 3, 9, 1, true, RGB(255, 0, 255)); //
	_loading->loadFrameImage("player_down", "images/player/PLAYER_DOWN_MOVE.bmp", 450 * 3, 50 * 3, 9, 1, true, RGB(255, 0, 255));//
	_loading->loadFrameImage("player_left", "images/player/PLAYER_LEFT_MOVE.bmp", 350 * 3, 50 * 3, 7, 1, true, RGB(255, 0, 255));//
	_loading->loadFrameImage("player_right", "images/player/PLAYER_RIGHT_MOVE.bmp", 350 * 3, 50 * 3, 7, 1, true, RGB(255, 0, 255));//

	//�÷��̾� ����(��,��,��,��)
	_loading->loadFrameImage("player_up_attack", "images/player/PLAYER_UP_ATTACK.bmp", 250 * 3, 50 * 3, 5, 1, true, RGB(255, 0, 255));//
	_loading->loadFrameImage("player_down_attack", "images/player/PLAYER_DOWN_ATTACK.bmp", 300 * 3, 50 * 3, 6, 1, true, RGB(255, 0, 255)); //
	_loading->loadFrameImage("player_left_attack", "images/player/PLAYER_LEFT_ATTACK.bmp", 250 * 3, 50 * 3, 5, 1, true, RGB(255, 0, 255));//
	_loading->loadFrameImage("player_right_attack", "images/player/PLAYER_RIGHT_ATTACK.bmp", 250 * 3, 50 * 3, 5, 1, true, RGB(255, 0, 255));//

	//�÷��̾� Ȱ(��,��,��,��)
	_loading->loadFrameImage("player_up_bow", "images/player/PLAYER_UP_BOW.bmp", 150 * 3, 50 * 3, 3, 1, true, RGB(255, 0, 255)); //
	_loading->loadFrameImage("player_down_bow", "images/player/PLAYER_DOWN_BOW.bmp", 150 * 3, 50 * 3, 3, 1, true, RGB(255, 0, 255)); //
	_loading->loadFrameImage("player_left_bow", "images/player/PLAYER_LEFT_BOW.bmp", 150 * 3, 50 * 3, 3, 1, true, RGB(255, 0, 255)); //
	_loading->loadFrameImage("player_right_bow", "images/player/PLAYER_RIGHT_BOW.bmp", 150 * 3, 50 * 3, 3, 1, true, RGB(255, 0, 255)); //
	//�÷��̾� ȭ��(��,��,��,��)
	_loading->loadFrameImage("player_up_arrow", "images/player/UP_Arrow.bmp", 5 * 3, 15 * 3, 2, 1, true, RGB(255, 0, 255)); //
	_loading->loadFrameImage("player_down_arrow", "images/player/Down_Arrow.bmp", 5 * 3, 15 * 3, 2, 1, true, RGB(255, 0, 255)); //
	_loading->loadFrameImage("player_left_arrow", "images/player/Left_Arrow.bmp", 15 * 3, 5 * 3, 2, 1, true, RGB(255, 0, 255));//
	_loading->loadFrameImage("player_right_arrow", "images/player/Right_Arrow.bmp", 15 * 3, 5 * 3, 2, 1, true, RGB(255, 0, 255));// 20
	//�÷��̾� �θ޶�(��,��,��,��)
	_loading->loadFrameImage("player_up_boomerang", "images/player/PLAYER_UP_Boomerang.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(255, 0, 255));//
	_loading->loadFrameImage("player_down_boomerang", "images/player/PLAYER_DOWN_Boomerang.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(255, 0, 255));//
	_loading->loadFrameImage("player_left_boomerang", "images/player/PLAYER_LEFT_Boomerang.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(255, 0, 255));//
	_loading->loadFrameImage("player_right_boomerang", "images/player/PLAYER_RIGHT_Boomerang.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(255, 0, 255));//

	//�÷��̾� �θ޶�
	_loading->loadFrameImage("player_throw_boomerang", "images/player/Boomerang.bmp", 40 * 3, 10 * 3, 4, 1, true, RGB(255, 0, 255)); //

	//�÷��̾� ��ź
	_loading->loadFrameImage("player_boom", "images/player/Boom.bmp", 104 * 3, 19 * 3, 8, 1, true, RGB(255, 192, 255));//

	//�÷��̾� ����
	_loading->loadFrameImage("player_dead", "images/player/Player_Dead.bmp", 150 * 3, 50 * 3, 3, 1, true, RGB(0, 84, 84));//
	_loading->loadFrameImage("player_rotate", "images/player/Player_Rotate.bmp", 200 * 3, 50 * 3, 4, 1, true, RGB(0, 84, 84));//


	//���� IDLE (����»��ٸ�)
	_loading->loadFrameImage("player_up_idle_swim", "images/player/PLAYER_UP_IDLE_SWIM.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_down_idle_swim", "images/player/PLAYER_DOWN_IDLE_SWIM.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_left_idle_swim", "images/player/PLAYER_LEFT_IDLE_SWIM.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_right_idle_swim", "images/player/PLAYER_RIGHT_IDLE_SWIM.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(0, 64, 64));//

	//���� MOVE (����»� �ٸ�)
	_loading->loadFrameImage("player_up_move_swim", "images/player/PLAYER_UP_MOVE_SWIM.bmp", 300 * 3, 50 * 3, 6, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_down_move_swim", "images/player/PLAYER_DOWN_MOVE_SWIM.bmp", 300 * 3, 50 * 3, 6, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_left_move_swim", "images/player/PLAYER_LEFT_MOVE_SWIM.bmp", 300 * 3, 50 * 3, 6, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_right_move_swim", "images/player/PLAYER_RIGHT_MOVE_SWIM.bmp", 300 * 3, 50 * 3, 6, 1, true, RGB(0, 64, 64));//

	//������Ʈ LIFT (����»��ٸ�)
	_loading->loadFrameImage("player_up_lift", "images/player/PLAYER_UP_LIFT.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_down_lift", "images/player/PLAYER_DOWN_LIFT.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_left_lift", "images/player/PLAYER_LEFT_LIFT.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_right_lift", "images/player/PLAYER_RIGHT_LIFT.bmp", 100 * 3, 50 * 3, 2, 1, true, RGB(0, 64, 64));//

	//������Ʈ LIFTING (����»� �ٸ�)
	_loading->loadFrameImage("player_up_move_lift", "images/player/PLAYER_UP_MOVE_LIFT.bmp", 200 * 3, 50 * 3, 4, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_down_move_lift", "images/player/PLAYER_DOWN_MOVE_LIFT.bmp", 200 * 3, 50 * 3, 4, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_left_move_lift", "images/player/PLAYER_LEFT_MOVE_LIFT.bmp", 150 * 3, 50 * 3, 3, 1, true, RGB(0, 64, 64));//
	_loading->loadFrameImage("player_right_move_lift", "images/player/PLAYER_RIGHT_MOVE_LIFT.bmp", 150 * 3, 50 * 3, 3, 1, true, RGB(0, 64, 64));//




	//----------------------------------------------------------------------------------------------
	//���� �ε��Դϴ�
	_loading->loadImage("maptool_img", "images/maptool/maptool_img.bmp", 1200, 800, true, RGB(255, 0, 255));
	_loading->loadImage("selectSampleRect", "images/maptool/sampleSelect.bmp", 24, 24, true, RGB(0, 0, 0));
	_loading->loadFrameImage("maptool_tilebutton", "images/maptool/maptool_tilebutton.bmp", 200, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_objbutton", "images/maptool/maptool_objbutton.bmp", 200, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_obj2button", "images/maptool/maptool_obj2button.bmp", 200, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_eraserbutton", "images/maptool/maptool_eraserbutton.bmp", 200, 50, 2, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("maptool_sizebutton", "images/maptool/maptool_sizebutton.bmp", 200, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_savebutton", "images/maptool/maptool_savebutton.bmp", 200, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_loadbutton", "images/maptool/maptool_loadbutton.bmp", 200, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_firstfloorbutton", "images/maptool/maptool_firstfloorbutton.bmp", 200, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_secondfloorbutton", "images/maptool/maptool_secondfloorbutton.bmp", 200, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_rightbutton", "images/maptool/maptool_rightbutton.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_leftbutton", "images/maptool/maptool_leftbutton.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("maptool_tile1", "images/maptool/maptool_tile1.bmp", 120 * TOTALSIZE, 16 * TOTALSIZE, 15, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_tile2", "images/maptool/maptool_tile2.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_overworldtile1", "images/maptool/maptool_overworldtile1.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_overworldtile2", "images/maptool/maptool_overworldtile2.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));

	_loading->loadFrameImage("maptool_obj", "images/maptool/maptool_obj.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_dungeonobj1", "images/maptool/maptool_dungeonobj1.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_shop", "images/maptool/maptool_shop.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_house", "images/maptool/maptool_house.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_overworldblock1", "images/maptool/maptool_overworldblock1.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_overworldblock2", "images/maptool/maptool_overworldblock2.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_overworldblock3", "images/maptool/maptool_overworldblock3.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_houseexterior", "images/maptool/maptool_houseexterior.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255)); _loading->loadFrameImage("maptool_overworldblock3", "images/maptool/maptool_overworldblock3.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_overworldblock4", "images/maptool/maptool_overworldblock4.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_dungeonobj2", "images/maptool/maptool_dungeonobj2.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptool_dungeonobj3", "images/maptool/maptool_dungeonobj3.bmp", 160 * TOTALSIZE, 80 * TOTALSIZE, 20, 10, true, RGB(255, 0, 255));

	_loading->loadImage("maptool_grass", "images/maptool/maptool_grass.bmp", 16 * TOTALSIZE, 16 * TOTALSIZE, true, RGB(255, 0, 255));
	_loading->loadImage("maptool_smallrock", "images/maptool/maptool_smallrock.bmp", 16 * TOTALSIZE, 16 * TOTALSIZE, true, RGB(255, 0, 255));
	_loading->loadImage("maptool_ladder", "images/maptool/maptool_ladder.bmp", 32 * TOTALSIZE, 32 * TOTALSIZE, true, RGB(255, 0, 255));
	_loading->loadImage("maptool_bigtreasurebox", "images/maptool/maptool_bigtreasurebox.bmp", 32 * TOTALSIZE, 24 * TOTALSIZE, true, RGB(255, 0, 255));
	_loading->loadImage("maptool_nullbigtreasurebox", "images/maptool/maptool_nullbigtreasurebox.bmp", 32 * TOTALSIZE, 24 * TOTALSIZE, true, RGB(255, 0, 255));
	_loading->loadImage("maptool_treasurebox", "images/maptool/maptool_treasurebox.bmp", 16 * TOTALSIZE, 16 * TOTALSIZE, true, RGB(255, 0, 255));
	_loading->loadImage("maptool_nulltreasurebox", "images/maptool/maptool_nulltreasurebox.bmp", 16 * TOTALSIZE, 16 * TOTALSIZE, true, RGB(255, 0, 255));
	_loading->loadImage("maptool_jar", "images/maptool/maptool_jar.bmp", 16 * TOTALSIZE, 16 * TOTALSIZE, true, RGB(255, 0, 255));
	_loading->loadImage("maptool_opendoor", "images/maptool/maptool_opendoor.bmp", 32 * TOTALSIZE, 24 * TOTALSIZE, true, RGB(255, 0, 255));
	_loading->loadImage("maptool_lockeddoor", "images/maptool/maptool_lockeddoor.bmp", 32 * TOTALSIZE, 24 * TOTALSIZE, true, RGB(255, 0, 255));
	_loading->loadImage("maptool_ladderreverse", "images/maptool/maptool_ladder_reverse.bmp", 32 * TOTALSIZE, 32 * TOTALSIZE, true, RGB(255, 0, 255));


	//----------------------------------------------------------------------------------------------
	//�� �ε��Դϴ�
	_loading->loadImage("townMap", "images/map.bmp", MAPENDVIEWX, MAPENDVIEWY, true, RGB(255, 0, 255));



	//----------------------------------------------------------------------------------------------
	//UI�ε� �Դϴ�
	_loading->loadImage("Ű����", "images/keyEx3.bmp", 600, 300, false, RGB(255, 0, 255));

	_loading->loadImage("���UI", "images/itemImages/interface.bmp", WINSIZEX - 100, 150, true, RGB(255, 0, 255));
	_loading->loadImage("ȰUI", "images/itemImages/bow.bmp", 57, 57, false, RGB(0, 0, 0));
	_loading->loadImage("�θ޶�UI", "images/itemImages/boomerang.bmp", 57, 57, false, RGB(0, 0, 0));
	_loading->loadImage("��źUI", "images/itemImages/bomb.bmp", 57, 57, false, RGB(0, 0, 0));
	_loading->loadImage("ü��UI", "images/itemImages/hpMax.bmp", 57, 57, false, RGB(0, 0, 0));

	_loading->loadImage("ȭ���Ȱ", "images/itemImages/bowAndArrow.bmp", 180, 120, true, RGB(0, 0, 0));
	_loading->loadImage("�θ޶�����", "images/itemImages/boomerangInfo.bmp", 180, 120, true, RGB(0, 0, 0));
	_loading->loadImage("��ź����", "images/itemImages/bombInfo.bmp", 180, 120, true, RGB(0, 0, 0));
	_loading->loadImage("��������", "images/itemImages/lifeInfo.bmp", 180, 120, true, RGB(0, 0, 0));

	_loading->loadImage("����", "images/itemImages/shop.bmp", 710, 600, true, RGB(255, 0, 255));

	_loading->loadImage("�κ��丮", "images/itemImages/inven.bmp", 230, 360, true, RGB(255, 0, 255));
	//�κ� �����ۼ���
	_loading->loadFrameImage("����", "images/itemImages/select.bmp", 180, 90, 2, 1, true, RGB(0, 4, 0));

	_loading->loadImage("ü��1", "images/itemImages/hp1.bmp", 21, 21, true, RGB(255, 0, 255));
	_loading->loadImage("ü��2", "images/itemImages/hp2.bmp", 21, 21, true, RGB(255, 0, 255));
	_loading->loadImage("ü��3", "images/itemImages/hp3.bmp", 21, 21, true, RGB(255, 0, 255));

	_loading->loadFrameImage("����", "images/itemImages/number.bmp", 210, 21, 10, 1, true, RGB(255, 0, 255));
	//----------------------------------------------------------------------------------------------
	//���� �ε��Դϴ�


	//----------------------------------------------------------------------------------------------
	//��ǳ�� �ε��Դϴ�
	_loading->loadFrameImage("�������帻ǳ��", "images/itemImages/shopEnter.bmp", 3 * (WINSIZEX - 180), 180, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������ǳ��", "images/startScene/ending.bmp", 3 * (WINSIZEX - 180), 180, 3, 1, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//����ȭ�� �ε��Դϴ�
	_loading->loadImage("����ȭ��", "images/itemImages/soundScene.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����off", "images/itemImages/soundOff.bmp", 132, 116, false, RGB(255, 0, 255));
	_loading->loadImage("����on", "images/itemImages/soundOn.bmp", 132, 116, false, RGB(255, 0, 255));
	_loading->loadImage("�� ���ǰ�����", "images/itemImages/progressBarFront.bmp", 300, 6, false, RGB(255, 0, 255));
	_loading->loadImage("�� ���ǰ�����", "images/itemImages/progressBarBack.bmp", 300, 6, false, RGB(255, 0, 255));
	_loading->loadImage("��������", "images/itemImages/volume.bmp", 42, 42, false, RGB(255, 0, 255));
	_loading->loadImage("�������", "images/itemImages/backSoundText.bmp", 254, 28, false, RGB(255, 0, 255));
	_loading->loadImage("ȿ������", "images/itemImages/effectSoundText.bmp", 254, 28, false, RGB(255, 0, 255));
	_loading->loadImage("back", "images/itemImages/back.bmp", 94, 34, false, RGB(255, 0, 255));


	//----------------------------------------------------------------------------------------------
	//���� �ε��Դϴ�

	//---------------------------------------------------------------------------------------------
	//��������Ʈ �ε��Դϴ�
	//�ͽ��÷��� ��������Ʈ
	_loading->loadFrameImage("player_boom_explosion", "images/player/BoomExplosion.bmp", 315 * 3, 46 * 3, 7, 1, true, RGB(255, 192, 255));//
	_loading->loadFrameImage("destory_sprite", "images/maptool/maptool_destorysprite.bmp", 240 * 3, 28 * 3, 8, 1, true, RGB(255, 128, 255));//
	_loading->loadFrameImage("destory_grass_sprite", "images/maptool/maptool_grass_destorysprite.bmp", 232 * 3, 43 * 3, 8, 1, true, RGB(255, 128, 255));//
	_loading->loadFrameImage("enemy_death", "images/enemy/enemy_death.bmp", 182 * 3, 32 * 3, 7, 1, true, RGB(255, 0, 255));//


	//----------------------------------------------------------------------------------------------
	//������ �ε��Դϴ�

	_loading->loadImage("Ȱ", "images/itemImages/bow.bmp", 48, 48, true, RGB(0, 4, 0));
	_loading->loadImage("�θ޶�", "images/itemImages/boomerang.bmp", 48, 48, true, RGB(0, 0, 0));
	_loading->loadImage("��ź10��", "images/itemImages/bomb10.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("ü��MAX", "images/itemImages/hpMax.bmp", 48, 48, true, RGB(0, 4, 0));
	_loading->loadImage("��ź", "images/itemImages/bomb.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��", "images/itemImages/money.bmp", 54, 36, 3, 1, true, RGB(255, 0, 255));
	_loading->loadImage("ȭ��10��", "images/itemImages/arrow10.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("ü�¾�����", "images/itemImages/hpItem.bmp", 27, 24, true, RGB(255, 0, 255));
	_loading->loadImage("�ִ�ü��", "images/itemImages/hpMaxUp.bmp", 52, 45, true, RGB(255, 0, 255));
	_loading->loadImage("����Ҵ�Ʈ", "images/itemImages/greenPendent.bmp", 48, 48, true, RGB(0, 0, 0));
	_loading->loadImage("�������Ҵ�Ʈ", "images/itemImages/redPendent.bmp", 48, 48, true, RGB(0, 0, 0));
	_loading->loadImage("�Ķ����Ҵ�Ʈ", "images/itemImages/bluePendent.bmp", 48, 48, true, RGB(0, 0, 0));
	_loading->loadImage("����", "images/itemImages/key.bmp", 28, 32, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//NPC �ε��Դϴ�

	_loading->loadFrameImage("��������", "images/itemImages/shopNpc.bmp", 84, 66, 2, 1, true, RGB(255, 0, 255));



	//----------------------------------------------------------------------------------------------
	//����ȭ�� �ε��Դϴ�

	_loading->loadFrameImage("���ÿ���", "images/startScene/angel.bmp", 68, 34, 2, 1, true, RGB(255, 0, 255));
	_loading->loadImage("���۹�ư", "images/startScene/start2.bmp", 164, 34, true, RGB(255, 0, 255));
	_loading->loadImage("������ư", "images/startScene/maptool.bmp", 230, 34, true, RGB(255, 0, 255));
	_loading->loadImage("�Ҹ���ư", "images/startScene/sound.bmp", 164, 34, true, RGB(255, 0, 255));
	_loading->loadImage("��������", "images/startScene/black.bmp", 164, 34, true, RGB(255, 0, 255));
	_loading->loadImage("��������1", "images/startScene/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loading->loadImage("����ȭ��1", "images/startScene/intro_1.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��2", "images/startScene/intro_2.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��3", "images/startScene/intro_3.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��4", "images/startScene/intro_4.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��5", "images/startScene/intro_5.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��6", "images/startScene/intro_6.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��7", "images/startScene/intro_7.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��8", "images/startScene/intro_8.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��9", "images/startScene/intro_9.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��10", "images/startScene/intro_10.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��11", "images/startScene/intro_11.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��12", "images/startScene/intro_12.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��13", "images/startScene/intro_13.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��14", "images/startScene/intro_14.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��15", "images/startScene/intro_15.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��16", "images/startScene/intro_16.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��17", "images/startScene/intro_17.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��18", "images/startScene/intro_18.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��19", "images/startScene/intro_19.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��20", "images/startScene/intro_20.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��21", "images/startScene/intro_21.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��22", "images/startScene/intro_22.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��23", "images/startScene/intro_23.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��24", "images/startScene/intro_24.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��25", "images/startScene/intro_25.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��26", "images/startScene/intro_26.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��27", "images/startScene/intro_27.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��28", "images/startScene/intro_28.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��29", "images/startScene/intro_29.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��30", "images/startScene/intro_30.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��31", "images/startScene/intro_31.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��32", "images/startScene/intro_32.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��33", "images/startScene/intro_33.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��34", "images/startScene/intro_34.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��35", "images/startScene/intro_35.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��36", "images/startScene/intro_36.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��37", "images/startScene/intro_37.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��38", "images/startScene/intro_38.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��39", "images/startScene/intro_39.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��40", "images/startScene/intro_40.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��41", "images/startScene/intro_41.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��42", "images/startScene/intro_42.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��43", "images/startScene/intro_43.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��44", "images/startScene/intro_44.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��45", "images/startScene/intro_45.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��46", "images/startScene/intro_46.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��47", "images/startScene/intro_47.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��48", "images/startScene/intro_48.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��49", "images/startScene/intro_49.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��50", "images/startScene/intro_50.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��51", "images/startScene/intro_51.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��52", "images/startScene/intro_52.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��53", "images/startScene/intro_53.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��54", "images/startScene/intro_54.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��55", "images/startScene/intro_55.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��56", "images/startScene/intro_56.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��57", "images/startScene/intro_57.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��58", "images/startScene/intro_58.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��59", "images/startScene/intro_59.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��60", "images/startScene/intro_60.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��61", "images/startScene/intro_61.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��62", "images/startScene/intro_62.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��63", "images/startScene/intro_63.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��64", "images/startScene/intro_64.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��65", "images/startScene/intro_65.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��66", "images/startScene/intro_66.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��67", "images/startScene/intro_67.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��68", "images/startScene/intro_68.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��69", "images/startScene/intro_69.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��70", "images/startScene/intro_70.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��71", "images/startScene/intro_71.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��72", "images/startScene/intro_72.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��73", "images/startScene/intro_73.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��74", "images/startScene/intro_74.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��75", "images/startScene/intro_75.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��76", "images/startScene/intro_76.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��77", "images/startScene/intro_77.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��78", "images/startScene/intro_78.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��79", "images/startScene/intro_79.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��80", "images/startScene/intro_80.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��81", "images/startScene/intro_81.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��82", "images/startScene/intro_82.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��83", "images/startScene/intro_83.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��84", "images/startScene/intro_84.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��85", "images/startScene/intro_85.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��86", "images/startScene/intro_86.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��87", "images/startScene/intro_87.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��88", "images/startScene/intro_88.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��89", "images/startScene/intro_89.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��90", "images/startScene/intro_90.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��91", "images/startScene/intro_91.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��92", "images/startScene/intro_92.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��93", "images/startScene/intro_93.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��94", "images/startScene/intro_94.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��95", "images/startScene/intro_95.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��96", "images/startScene/intro_96.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��97", "images/startScene/intro_97.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��98", "images/startScene/intro_98.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��99", "images/startScene/intro_99.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��100", "images/startScene/intro_100.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��101", "images/startScene/intro_101.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��102", "images/startScene/intro_102.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��103", "images/startScene/intro_103.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��104", "images/startScene/intro_104.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��105", "images/startScene/intro_105.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��106", "images/startScene/intro_106.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��107", "images/startScene/intro_107.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��108", "images/startScene/intro_108.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��109", "images/startScene/intro_109.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��110", "images/startScene/intro_110.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��111", "images/startScene/intro_111.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��112", "images/startScene/intro_112.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��113", "images/startScene/intro_113.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��114", "images/startScene/intro_114.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��115", "images/startScene/intro_115.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��116", "images/startScene/intro_116.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��117", "images/startScene/intro_117.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��118", "images/startScene/intro_118.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��119", "images/startScene/intro_119.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��120", "images/startScene/intro_120.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��121", "images/startScene/intro_121.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��122", "images/startScene/intro_122.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��123", "images/startScene/intro_123.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��124", "images/startScene/intro_124.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��125", "images/startScene/intro_125.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��126", "images/startScene/intro_126.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("����ȭ��127", "images/startScene/intro_127.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));

	//��Ÿ �̹��� �ε��Դϴ�
}

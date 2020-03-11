#include "stdafx.h"
#include "mapToolScene.h"


mapToolScene::mapToolScene()
{
}


mapToolScene::~mapToolScene()
{
	release();
}

HRESULT mapToolScene::init()
{
	_sceneName = SCENE_NAME_MAPTOOL_SCENE;

	scene::init();

	//������ ������ ����
	RECT rc;
	rc = RectMake(0, 0, MAPTOOL_WINSIZEX, MAPTOOL_WINSIZEY);
	AdjustWindowRect(&rc, WINSTYLE, false);
	//�� RECT ������ ������ ������ ����
	SetWindowPos(m_hWnd, NULL, 0, 0, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
	IMAGEMANAGER->setImageReSize("backbuffer", MAPTOOL_WINSIZEX, MAPTOOL_WINSIZEY);

	//�� backbuffer����
	_mapBackBuffer = IMAGEMANAGER->addImage("mapbackBuffer", TILEX * MAPTOOL_TILESIZE, TILEY * MAPTOOL_TILESIZE);

	_img = IMAGEMANAGER->findImage("maptool_img");

	//Ÿ�ϸʰ� ���ø� �ʱ�ȭ
	_nowImg = IMAGEMANAGER->findImage(*_tileSampleImageNameVector.begin());

	_firstFloorTileMap.initTileMap(TILEX, TILEY, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, _nowImg);
	_secondFloorTileMap.initTileMap(TILEX, TILEY, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, NULL);

	_currentMapX = TILEX;
	_currentMapY = TILEY;

	_currentMapXPos = TILEX * MAPTOOL_TILESIZE;
	_currentMapYPos = TILEY * MAPTOOL_TILESIZE;

	//ī�޶���ġ�� �̴ϸ� ī�޶���� �ʱ�ȭ
	_nowFloor = 1;

	_nowCarmeraX = 0;
	_nowCarmeraY = 0;

	IMAGEMANAGER->addImage("����ī�޶�", "images/maptool/ī�޶�.bmp", 300 * MAPTOOL_VIEWSIZEX / _currentMapXPos, 300 * MAPTOOL_VIEWSIZEY / _currentMapYPos, true, RGB(0, 0, 0));

	//���� �� ����
	drawBackTileMap(0, _nowFloor);

	//������ ���� �� ����
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{

			_sampleTiles[i * SAMPLETILEX + j]._frameX = j;
			_sampleTiles[i * SAMPLETILEX + j]._frameY = i;
			_sampleTiles[i * SAMPLETILEX + j]._img = _nowImg;

			//��ǥ���� ����
			SetRect(&_sampleTiles[i* SAMPLETILEX + j]._rcTile, MAPTOOL_SIDEBAR_STARTX + j * MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTY + i * MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTX + j * MAPTOOL_TILESIZE + MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTY + i * MAPTOOL_TILESIZE + MAPTOOL_TILESIZE);
		}

	}

	//���õ� ���ø� ���� �ʱ�ȭ
	tagCurrentTile currenTileTemp;

	_selectTileX = 1;
	_selectTileY = 1;
	_currentTileVector.clear();

	currenTileTemp._x = _sampleTiles[0]._frameX;
	currenTileTemp._y = _sampleTiles[0]._frameY;
	currenTileTemp._img = _sampleTiles[0]._img;

	_currentTileVector.push_back(currenTileTemp);

	//���õ� ��Ʈũ��� �簢�� �׷��ֱ�
	IMAGEMANAGER->deleteImage("selectSampleRect");
	IMAGEMANAGER->addImage("selectSampleRect", "images/maptool/sampleSelect.bmp", _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE, true, RGB(0, 0, 0));
	_nowSelectSampleTileRect = RectMake(MAPTOOL_SIDEBAR_STARTX, 0, MAPTOOL_SIDEBAR_STARTX+_selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE);

	//_nowSelectSampleTileRect = RectMake(MAPTOOL_SIDEBAR_STARTX, 0, _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE);

	//���콺 ��ǥ �ʱ�ȭ
	_startMousePointX = 0;
	_startMousePointY = 0;

	//�̴ϸ� ���� �ʱ�ȭ
	_isMinimapView = true;

	//��ư, �ؽ�Ʈ ����Ʈ �ʱ�ȭ
	buttonAdd("maptool_tilebutton", MAPTOOL_BUTTONKIND_TERRAINDRAW, MAPTOOL_SIDEBAR_STARTX + 20, 300, 100, 50, true);
	buttonAdd("maptool_objbutton", MAPTOOL_BUTTONKIND_OBJDRAW, MAPTOOL_SIDEBAR_STARTX + 130, 300, 100, 50, true);
	buttonAdd("maptool_obj2button", MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW, MAPTOOL_SIDEBAR_STARTX + 240, 300, 100, 50, true);
	buttonAdd("maptool_eraserbutton", MAPTOOL_BUTTONKIND_ERASER, MAPTOOL_SIDEBAR_STARTX + 350, 300, 100, 50, true);

	buttonAdd("maptool_sizebutton", MAPTOOL_BUTTONKIND_RESIZE, MAPTOOL_SIDEBAR_STARTX + 350, 670, 100, 50, true);
	buttonAdd("maptool_savebutton", MAPTOOL_BUTTONKIND_SAVE, MAPTOOL_SIDEBAR_STARTX + 350, 450, 100, 50, true);
	buttonAdd("maptool_loadbutton", MAPTOOL_BUTTONKIND_LOAD, MAPTOOL_SIDEBAR_STARTX + 350, 550, 100, 50, true);
	buttonAdd("maptool_firstfloorbutton", MAPTOOL_BUTTONKIND_FIRSTFLOOR, 150, 580, 100, 50, true);
	buttonAdd("maptool_secondfloorbutton", MAPTOOL_BUTTONKIND_SECONDFLOOR, 350, 580, 100, 50, true);
	buttonAdd("maptool_leftbutton", MAPTOOL_BUTTONKIND_LEFTBUTTON, MAPTOOL_SIDEBAR_STARTX + 180, 260, 24, 24, true);
	buttonAdd("maptool_rightbutton", MAPTOOL_BUTTONKIND_RIGHTBUTTON, MAPTOOL_SIDEBAR_STARTX + 280, 260, 24, 24, true);

	hEdit1 = CreateWindow("edit", "", WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, MAPTOOL_SIDEBAR_STARTX + 30, 700, 100, 30, m_hWnd, (HMENU)1, m_hInstance, NULL);
	hEdit2 = CreateWindow("edit", "", WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, MAPTOOL_SIDEBAR_STARTX + 180, 700, 100, 30, m_hWnd, (HMENU)2, m_hInstance, NULL);
	hEdit3 = CreateWindow("edit", "", WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE | WS_BORDER, MAPTOOL_SIDEBAR_STARTX + 330, 400, 150, 30, m_hWnd, (HMENU)3, m_hInstance, NULL);

	_ctrSelect = MAPTOOL_BUTTONKIND_TERRAINDRAW;

	_sound.soundOff();
	_sound.soundPlay("����â");

	return S_OK;
}

void mapToolScene::release()
{
	RECT rc;
	rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	AdjustWindowRect(&rc, WINSTYLE, false);
	//�� RECT ������ ������ ������ ����
	SetWindowPos(m_hWnd, NULL, 0, 0, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
	IMAGEMANAGER->setImageReSize("backbuffer", WINSIZEX, WINSIZEY);

	IMAGEMANAGER->deleteImage("mapbackbuffer");
	IMAGEMANAGER->deleteImage("����ī�޶�");

	DestroyWindow(hEdit1);
	DestroyWindow(hEdit2);
	DestroyWindow(hEdit3);

	_firstFloorTileMap.release();
	_secondFloorTileMap.release();

	scene::release();

}

void mapToolScene::update()
{
	//�̹��� ��ư�� ���콺 ��ġ ���� �Ǵ�
	for (int i = 0; i < imageButtonVector.size(); i++)
	{
		imageButtonPoint(&imageButtonVector[i]);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_startMousePointX = m_ptMouse.x;
		_startMousePointY = m_ptMouse.y;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		setMap();
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		//��ư Ŭ�� ����
		selectButton();

		//������ ���� ���� ��������.
		if (_ctrSelect != MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW)
		{
			for (int i = 0; i < SAMPLETILEY; i++)
			{
				for (int j = 0; j < SAMPLETILEX; j++)
				{
					_sampleTiles[i * SAMPLETILEX + j]._frameX = j;
					_sampleTiles[i * SAMPLETILEX + j]._frameY = i;
					_sampleTiles[i * SAMPLETILEX + j]._img = _nowImg;

					//��ǥ���� ����
					SetRect(&_sampleTiles[i* SAMPLETILEX + j]._rcTile, MAPTOOL_SIDEBAR_STARTX + j * MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTY + i * MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTX + j * MAPTOOL_TILESIZE + MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTY + i * MAPTOOL_TILESIZE + MAPTOOL_TILESIZE);
				}
			}

			//Ŭ���� �ح����� ������ ��ǥ�� ��Ʈ�� �����
			//��ǥ�ȿ� ���õ��� ���Ϳ� �־� �׸� �� �ְ� �Ѵ�
			RECT sampleRect, currentSampleRect, rectTemp;
			tagCurrentTile currenTileTemp;
			int maxCurrentX = 0;

			sampleRect = RectMake(MAPTOOL_SIDEBAR_STARTX, 0, 480, 240);

			//���ø� �ȿ����� �۵�
			if (PtInRect(&sampleRect, m_ptMouse))
			{
				//���õ� ���� �ʱ�ȭ
				_currentTileVector.clear();

				currentSampleRect = RectMake(_startMousePointX, _startMousePointY, m_ptMouse.x - _startMousePointX, m_ptMouse.y - _startMousePointY);

				if (currentSampleRect.right - currentSampleRect.left == 0)
				{
					currentSampleRect.right += 1;
				}
				if (currentSampleRect.bottom - currentSampleRect.top == 0)
				{
					currentSampleRect.bottom += 1;
				}

				//Ÿ�ϼ� ����
				_selectTileX = 0;
				_selectTileY = 0;
				maxCurrentX = 0;

				for (int i = 0; i < SAMPLETILEY; i++)
				{
					if (maxCurrentX <= _selectTileX)
					{
						maxCurrentX = _selectTileX;
					}

					_selectTileX = 0;

					for (int j = 0; j < SAMPLETILEX; j++)
					{
						if (IntersectRect(&rectTemp, &_sampleTiles[i*SAMPLETILEX + j]._rcTile, &currentSampleRect))
						{
							currenTileTemp._x = _sampleTiles[i*SAMPLETILEX + j]._frameX;
							currenTileTemp._y = _sampleTiles[i*SAMPLETILEX + j]._frameY;
							currenTileTemp._img = _sampleTiles[i*SAMPLETILEX + j]._img;

							_currentTileVector.push_back(currenTileTemp);
							if (_selectTileX == 0)
							{
								_selectTileY++;
							}
							_selectTileX++;
						}
					}
				}
				_selectTileX = maxCurrentX;

				//�Ѱ��� ���Ϳ� �������� ������(������)
				if (_selectTileX == 0)
				{
					_selectTileX = 1;
				}
				if (_selectTileY == 0)
				{
					_selectTileY = 1;
				}
				if (_currentTileVector.size() <= 0)
				{
					for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
					{
						if (PtInRect(&_sampleTiles[i]._rcTile, m_ptMouse))
						{

							currenTileTemp._x = _sampleTiles[i]._frameX;
							currenTileTemp._y = _sampleTiles[i]._frameY;
							currenTileTemp._img = _sampleTiles[i]._img;

							_currentTileVector.push_back(currenTileTemp);
							break;
						}
					}
				}

				//���õ� ��Ʈũ��� �簢�� �׷��ֱ�
				IMAGEMANAGER->deleteImage("selectSampleRect");
				IMAGEMANAGER->addImage("selectSampleRect", "images/maptool/sampleSelect.bmp", _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE, true, RGB(0, 0, 0));

				//�Ѱ��� ���
				if (_currentTileVector.size() == 1)
				{
					_nowSelectSampleTileRect = RectMake(MAPTOOL_SIDEBAR_STARTX + ((m_ptMouse.x - MAPTOOL_SIDEBAR_STARTX) / MAPTOOL_TILESIZE) * MAPTOOL_TILESIZE, ((m_ptMouse.y) / MAPTOOL_TILESIZE) * MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTX + _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE);
				}
				else
				{
					_nowSelectSampleTileRect = RectMake(MAPTOOL_SIDEBAR_STARTX + ((_startMousePointX - MAPTOOL_SIDEBAR_STARTX) / MAPTOOL_TILESIZE) * MAPTOOL_TILESIZE, ((_startMousePointY) / MAPTOOL_TILESIZE) * MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTX + _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE);
				}
			}
		}
		else
		{
			//���õ� ��Ʈũ��� �簢�� �׷��ֱ�
			IMAGEMANAGER->deleteImage("selectSampleRect");
			IMAGEMANAGER->addImage("selectSampleRect", "images/maptool/sampleSelect.bmp", _nowImg->getWidth(), _nowImg->getHeight(), true, RGB(0, 0, 0));

			setNowInteractionObject(_nowImgNum);
		}

	}//oncekeydown/left end

	//�ʻ���� ���� ���� ������ ī�޶� ������ Ÿ�ϸ� �並 �̵���Ų��.
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_nowCarmeraX + MAPTOOL_VIEWSIZEX < _currentMapXPos)
		{
			_nowCarmeraX += 10;
		}
		else
		{
			if (_currentMapXPos < MAPTOOL_VIEWSIZEX)
			{
				_nowCarmeraX = 0;
			}
			else
			{
				_nowCarmeraX = _currentMapXPos - MAPTOOL_VIEWSIZEX;
			}
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_nowCarmeraX > 0)
		{
			_nowCarmeraX -= 10;
		}
		else
		{
			_nowCarmeraX = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_nowCarmeraY + MAPTOOL_VIEWSIZEY < _currentMapYPos)
		{
			_nowCarmeraY += 10;
		}
		else
		{
			if (_currentMapYPos < MAPTOOL_VIEWSIZEY)
			{
				_nowCarmeraY = 0;
			}
			else
			{
				_nowCarmeraY = _currentMapYPos - MAPTOOL_VIEWSIZEY;
			}
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_nowCarmeraY > 0)
		{
			_nowCarmeraY -= 10;
		}
		else
		{
			_nowCarmeraY = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_isMinimapView = !_isMinimapView;
	}

}

void mapToolScene::render()
{
	//����̹����� �׷��ش�
	_img->render(getMemDC(), 0, 0);

	//��ư�� �׷��ش�
	for (int i = 0; i < imageButtonVector.size(); i++)
	{
		imageButtonRender(imageButtonVector[i]);
	}

	drawBackTileMap(1, _nowFloor);

	//�� ����ۿ� �ִ� ������ �׷��ش�	(�� ��ũ��� �߶�)										     ����				���� ũ��
	//IMAGEMANAGER->render("mapbackBuffer", getMemDC(), 0, 0, _nowCarmeraX, _nowCarmeraY, MAPTOOL_VIEWSIZEX, MAPTOOL_VIEWSIZEY);

	if (_currentMapXPos < MAPTOOL_VIEWSIZEX && _currentMapYPos < MAPTOOL_VIEWSIZEY)
	{
		IMAGEMANAGER->render("mapbackBuffer", getMemDC(), 0, 0, _nowCarmeraX, _nowCarmeraY, _currentMapXPos, _currentMapYPos);
	}
	else if (_currentMapXPos < MAPTOOL_VIEWSIZEX)
	{
		IMAGEMANAGER->render("mapbackBuffer", getMemDC(), 0, 0, _nowCarmeraX, _nowCarmeraY, _currentMapXPos, MAPTOOL_VIEWSIZEY);
	}
	else if (_currentMapYPos < MAPTOOL_VIEWSIZEY)
	{
		IMAGEMANAGER->render("mapbackBuffer", getMemDC(), 0, 0, _nowCarmeraX, _nowCarmeraY, MAPTOOL_VIEWSIZEX, _currentMapYPos);
	}
	else
	{
		IMAGEMANAGER->render("mapbackBuffer", getMemDC(), 0, 0, _nowCarmeraX, _nowCarmeraY, MAPTOOL_VIEWSIZEX, MAPTOOL_VIEWSIZEY);
	}

	if (_ctrSelect != MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW)
	{
		//���ø�
		for (int i = 0; i < SAMPLETILEY; i++)
		{
			for (int j = 0; j < SAMPLETILEX; j++)
			{
				_sampleTiles[i * SAMPLETILEX + j]._img->frameRender(getMemDC(), _sampleTiles[i * SAMPLETILEX + j]._rcTile.left, _sampleTiles[i * SAMPLETILEX + j]._rcTile.top, _sampleTiles[i * SAMPLETILEX + j]._frameX, _sampleTiles[i * SAMPLETILEX + j]._frameY);
			}
		}

		IMAGEMANAGER->render("selectSampleRect", getMemDC(), _nowSelectSampleTileRect.left, _nowSelectSampleTileRect.top);

		/*
		IMAGEMANAGER->minimapRender("selectSampleRect",getMemDC(), _nowSelectSampleTileRect.left, _nowSelectSampleTileRect.top, _nowSelectSampleTileRect.right-_nowSelectSampleTileRect.left, _nowSelectSampleTileRect.bottom-_nowSelectSampleTileRect.top,
			IMAGEMANAGER->findImage("selectSampleRect")->getMemDC(),0,0,24,24);
			*/
		
	}
	else
	{
		_nowImg->render(getMemDC(), MAPTOOL_SIDEBAR_STARTX, 0);

		IMAGEMANAGER->render("selectSampleRect", getMemDC(), MAPTOOL_SIDEBAR_STARTX, 0);

		/*
		IMAGEMANAGER->minimapRender("selectSampleRect",getMemDC(), _nowSelectSampleTileRect.left, _nowSelectSampleTileRect.top, _nowSelectSampleTileRect.right-_nowSelectSampleTileRect.left, _nowSelectSampleTileRect.bottom-_nowSelectSampleTileRect.top,
			IMAGEMANAGER->findImage("selectSampleRect")->getMemDC(),0,0,24,24);
			*/
	}


	//�̴ϸ�(���� 300x300����)
	if (_isMinimapView)
	{
		_mapBackBuffer->minimapRender(getMemDC(), MAPTOOL_SIDEBAR_STARTX, 390, 300, 300, getMapBackBufferDc(), 0, 0, _currentMapXPos, _currentMapYPos);
	}

	//ī�޶�
	if (_currentMapXPos < 600 && _currentMapYPos < 600)
	{
		IMAGEMANAGER->render("����ī�޶�", getMemDC(), MAPTOOL_SIDEBAR_STARTX, 390);
	}
	else if (_currentMapXPos < 600)
	{
		IMAGEMANAGER->render("����ī�޶�", getMemDC(), MAPTOOL_SIDEBAR_STARTX, 390 + _nowCarmeraY / (_currentMapYPos / 300));
	}
	else if (_currentMapYPos < 600)
	{
		IMAGEMANAGER->render("����ī�޶�", getMemDC(), MAPTOOL_SIDEBAR_STARTX + _nowCarmeraX / (_currentMapXPos / 300), 390);
	}
	else
	{
		IMAGEMANAGER->render("����ī�޶�", getMemDC(), MAPTOOL_SIDEBAR_STARTX + _nowCarmeraX / (_currentMapXPos / 300), 390 + _nowCarmeraY / (_currentMapYPos / 300));
	}
}

void mapToolScene::setMap()
{
	//
	//ȭ�� Ŭ���� ���� �信 ���õ� ���� �׸��� �Լ�
	//

	int mapX = 0, mapY = 0;																//��ü�� ��ǥ�Ǵ�, �����ϴ� ����
	RECT viewToolMapRect = RectMake(0, 0, MAPTOOL_VIEWSIZEX, MAPTOOL_VIEWSIZEY);		//���� ����Ʈ�� ��Ʈ�� ������ �ִ� ����

	vector<vector<tagTile>> tileMapVectorTemp;
	vector<tagInteractionObject> interactionObjectVectorTemp;
	if (_nowFloor == 1)
	{
		tileMapVectorTemp = _firstFloorTileMap.getTileMap();
		interactionObjectVectorTemp = _firstFloorTileMap.getInteractionObject();
	}
	else if (_nowFloor == 2)
	{
		tileMapVectorTemp = _secondFloorTileMap.getTileMap();
		interactionObjectVectorTemp = _secondFloorTileMap.getInteractionObject();
	}

	//����Ÿ��

	if (PtInRect(&viewToolMapRect, m_ptMouse))
	{
		int num = 0;		//Ÿ�Ϻ��͸� ������ ���� ����

		mapX = (m_ptMouse.x + _nowCarmeraX) / MAPTOOL_TILESIZE;
		mapY = (m_ptMouse.y + _nowCarmeraY) / MAPTOOL_TILESIZE;

		if (mapX >= _currentMapX)
		{
			return;
		}

		if (mapY >= _currentMapY)
		{
			return;
		}

		if (_nowFloor == 1)
		{
			if (_ctrSelect == MAPTOOL_BUTTONKIND_TERRAINDRAW)
			{
				for (int y = 0; y < _selectTileY; y++)
				{
					if (mapY + y >= _currentMapY)
					{
						break;
					}
					//���õ� ũ���� Ÿ���� �׷��ش�
					for (int x = 0; x < _selectTileX; x++)
					{
						if (mapX + x >= _currentMapX)
						{
							break;
						}

						_firstFloorTileMap.setTerrainFrameX(mapX + x, mapY + y, _currentTileVector[num]._x);
						_firstFloorTileMap.setTerrainFrameY(mapX + x, mapY + y, _currentTileVector[num]._y);

						_firstFloorTileMap.setMapTerrainImage(mapX + x, mapY + y, _currentTileVector[num]._img);
						_firstFloorTileMap.setTerrainImageNum(mapX + x, mapY + y, _nowImgNum);
						_firstFloorTileMap.setMapTerrain(mapX + x, mapY + y, terrainSelect(_currentTileVector[num]._x, _currentTileVector[num]._y));
						num++;
					}
				}
			}
			else if (_ctrSelect == MAPTOOL_BUTTONKIND_OBJDRAW)
			{
				for (int y = 0; y < _selectTileY; y++)
				{
					if (mapY + y >= _currentMapY)
					{
						break;
					}
					//���õ� ũ���� Ÿ���� �׷��ش�
					for (int x = 0; x < _selectTileX; x++)
					{
						if (mapX + x >= _currentMapX)
						{
							break;
						}
						_firstFloorTileMap.setObjFrameX(mapX + x, mapY + y, _currentTileVector[num]._x);
						_firstFloorTileMap.setObjFrameY(mapX + x, mapY + y, _currentTileVector[num]._y);

						_firstFloorTileMap.setMapObjImage(mapX + x, mapY + y, _currentTileVector[num]._img);
						_firstFloorTileMap.setObjImageNum(mapX + x, mapY + y, _nowImgNum);
						_firstFloorTileMap.setMapObj(mapX + x, mapY + y, objSelect(_currentTileVector[num]._x, _currentTileVector[num]._y));
						num++;
					}
				}
			}
			else if (_ctrSelect == MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW)
			{
				//��ȣ�ۿ� ������Ʈ�� Ÿ�ϸ��� �ƴ� ���� �������� ���� ó���� �����̱� ������ �ٸ������� �߰��Ѵ�
				//��üũ�Ⱑ �ϳ��� ������Ʈ�� �����Ǿ��ϱ� ����

				RECT rectTemp, currentRectTemp = RectMake(mapX*MAPTOOL_TILESIZE, mapY*MAPTOOL_TILESIZE, _currentInteractionObject.widthPos*MAPTOOL_TILESIZE, _currentInteractionObject.heightPos*MAPTOOL_TILESIZE);

				for (int i = 0; i <= interactionObjectVectorTemp.size(); i++)
				{
					if (i == interactionObjectVectorTemp.size())
					{
						_firstFloorTileMap.addInteractionObject(mapX, mapY, _currentInteractionObject.widthPos, _currentInteractionObject.heightPos, currentRectTemp, _currentInteractionObject.obj, _nowImg, _nowImgNum);
						break;
					}
					//������Ʈ���� ��ġ�� ���� x
					if (IntersectRect(&rectTemp, &currentRectTemp, &interactionObjectVectorTemp[i]._rc))
					{
						break;
					}
				}

			}

			else if (_ctrSelect == MAPTOOL_BUTTONKIND_ERASER)
			{
				POINT mouse = m_ptMouse;
				_firstFloorTileMap.setObjFrameX(mapX, mapY, 0);
				_firstFloorTileMap.setObjFrameY(mapX, mapY, 0);

				_firstFloorTileMap.setMapObjImage(mapX, mapY, nullptr);
				_firstFloorTileMap.setMapObj(mapX, mapY, OBJ_NONE);

				for (int i = 0; i < interactionObjectVectorTemp.size(); i++)
				{
					if (PtInRect(&interactionObjectVectorTemp[i]._rc, POINT{ mouse.x + _nowCarmeraX,mouse.y + _nowCarmeraY }))
					{
						_firstFloorTileMap.deleteInteractionObject(i);
						break;
					}
				}
			}
		}
		else if (_nowFloor == 2)
		{
			if (_ctrSelect == MAPTOOL_BUTTONKIND_TERRAINDRAW)
			{
				for (int y = 0; y < _selectTileY; y++)
				{
					if (mapY + y >= _currentMapY)
					{
						break;
					}
					//���õ� ũ���� Ÿ���� �׷��ش�
					for (int x = 0; x < _selectTileX; x++)
					{
						if (mapX + x >= _currentMapX)
						{
							break;
						}
						_secondFloorTileMap.setTerrainFrameX(mapX + x, mapY + y, _currentTileVector[num]._x);
						_secondFloorTileMap.setTerrainFrameY(mapX + x, mapY + y, _currentTileVector[num]._y);

						_secondFloorTileMap.setMapTerrainImage(mapX + x, mapY + y, _currentTileVector[num]._img);
						_secondFloorTileMap.setTerrainImageNum(mapX + x, mapY + y, _nowImgNum);
						_secondFloorTileMap.setMapTerrain(mapX + x, mapY + y, terrainSelect(_currentTileVector[num]._x, _currentTileVector[num]._y));
						num++;
					}
				}
			}
			else if (_ctrSelect == MAPTOOL_BUTTONKIND_OBJDRAW)
			{
				for (int y = 0; y < _selectTileY; y++)
				{
					if (mapY + y >= _currentMapY)
					{
						break;
					}
					//���õ� ũ���� Ÿ���� �׷��ش�
					for (int x = 0; x < _selectTileX; x++)
					{
						if (mapX + x >= _currentMapX)
						{
							break;
						}
						_secondFloorTileMap.setObjFrameX(mapX + x, mapY + y, _currentTileVector[num]._x);
						_secondFloorTileMap.setObjFrameY(mapX + x, mapY + y, _currentTileVector[num]._y);

						_secondFloorTileMap.setMapObjImage(mapX + x, mapY + y, _currentTileVector[num]._img);
						_secondFloorTileMap.setObjImageNum(mapX + x, mapY + y, _nowImgNum);
						_secondFloorTileMap.setMapObj(mapX + x, mapY + y, objSelect(_currentTileVector[num]._x, _currentTileVector[num]._y));
						num++;
					}
				}
			}
			else if (_ctrSelect == MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW)
			{
				//��ȣ�ۿ� ������Ʈ�� Ÿ�ϸ��� �ƴ� ���� �������� ���� ó���� �����̱� ������ �ٸ������� �߰��Ѵ�
				//��üũ�Ⱑ �ϳ��� ������Ʈ�� �����Ǿ��ϱ� ����

				RECT rectTemp, currentRectTemp = RectMake(mapX*MAPTOOL_TILESIZE, mapY*MAPTOOL_TILESIZE, _currentInteractionObject.widthPos*MAPTOOL_TILESIZE, _currentInteractionObject.heightPos*MAPTOOL_TILESIZE);

				for (int i = 0; i <= interactionObjectVectorTemp.size(); i++)
				{
					if (i == interactionObjectVectorTemp.size())
					{
						_secondFloorTileMap.addInteractionObject(mapX, mapY, _currentInteractionObject.widthPos, _currentInteractionObject.heightPos, currentRectTemp, _currentInteractionObject.obj, _nowImg, _nowImgNum);
						break;
					}
					//������Ʈ���� ��ġ�� ���� x
					if (IntersectRect(&rectTemp, &currentRectTemp, &interactionObjectVectorTemp[i]._rc))
					{
						break;
					}
				}
			}
			else if (_ctrSelect == MAPTOOL_BUTTONKIND_ERASER)
			{
				POINT mouse = m_ptMouse;

				_secondFloorTileMap.setObjFrameX(mapX, mapY, 0);
				_secondFloorTileMap.setObjFrameY(mapX, mapY, 0);

				_secondFloorTileMap.setMapObjImage(mapX, mapY, nullptr);
				_secondFloorTileMap.setMapObj(mapX, mapY, OBJ_NONE);

				for (int i = 0; i < interactionObjectVectorTemp.size(); i++)
				{
					if (PtInRect(&interactionObjectVectorTemp[i]._rc, POINT{ mouse.x + _nowCarmeraX,mouse.y + _nowCarmeraY }))
					{
						_secondFloorTileMap.deleteInteractionObject(i);
						break;
					}
				}
			}
		}

		InvalidateRect(m_hWnd, NULL, false);
	}
}

void mapToolScene::save()
{
	char str[1000];							//���ڿ��� ����, �о�� ����
	char editTemp[256] = { 0 };				//hEdit1�ڵ鿡 ���ڸ� �Է��ϱ� ���ؼ� ���۸� �����Ѵ�. 

	vector<vector<tagTile>> tileMapVectorTemp;
	vector<tagInteractionObject> interactionObjectVectorTemp;

	tileMapVectorTemp = _firstFloorTileMap.getTileMap();
	interactionObjectVectorTemp = _firstFloorTileMap.getInteractionObject();

	GetWindowText							//������ ĵ�Ǹ��� �����ϴ� �Լ��̴�,
	(hEdit3,								//��Ʈ���� �ڵ�
		editTemp,							//ĸ���� ���� ���� ����
		128);								//������ ũ��

	file = CreateFile(editTemp, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ZeroMemory(str, sizeof(str));
	sprintf_s(str, "x : %d, y : %d\r\n", _currentMapX, _currentMapY);
	WriteFile(file, str, strlen(str), &write, NULL);

	for (int i = 0; i < _currentMapY; i++)
	{
		for (int j = 0; j < _currentMapX; j++)
		{
			ZeroMemory(str, sizeof(str));
			sprintf_s(str, "%d ,%d, %d, %d, %d, %d, %d, %d\r\n",
				tileMapVectorTemp[i][j].terrainImageNum,
				tileMapVectorTemp[i][j].terrainFrameX,
				tileMapVectorTemp[i][j].terrainFrameY,
				tileMapVectorTemp[i][j].terrain,
				tileMapVectorTemp[i][j].objImageNum,
				tileMapVectorTemp[i][j].objFrameX,
				tileMapVectorTemp[i][j].objFrameY,
				tileMapVectorTemp[i][j].obj);

			WriteFile(file, str, strlen(str), &write, NULL);
		}
	}

	ZeroMemory(str, sizeof(str));
	sprintf_s(str, "interaction_obj_num : %d\r\n", interactionObjectVectorTemp.size());
	WriteFile(file, str, strlen(str), &write, NULL);

	for (int i = 0; i < interactionObjectVectorTemp.size(); i++)
	{
		ZeroMemory(str, sizeof(str));

		sprintf_s(str, "%d ,%d, %d, %d, %d, %d\r\n",
			interactionObjectVectorTemp[i].xPos,
			interactionObjectVectorTemp[i].yPos,
			interactionObjectVectorTemp[i].widthPos,
			interactionObjectVectorTemp[i].heightPos,
			interactionObjectVectorTemp[i].obj,
			interactionObjectVectorTemp[i].imageNum);

		WriteFile(file, str, strlen(str), &write, NULL);
	}


	//2�� ���̺�
	tileMapVectorTemp = _secondFloorTileMap.getTileMap();
	interactionObjectVectorTemp = _secondFloorTileMap.getInteractionObject();

	ZeroMemory(str, sizeof(str));
	sprintf_s(str, "x : %d, y : %d\r\n", _currentMapX, _currentMapY);
	WriteFile(file, str, strlen(str), &write, NULL);

	for (int i = 0; i < _currentMapY; i++)
	{
		for (int j = 0; j < _currentMapX; j++)
		{
			ZeroMemory(str, sizeof(str));
			sprintf_s(str, "%d ,%d, %d, %d, %d, %d, %d, %d\r\n",
				tileMapVectorTemp[i][j].terrainImageNum,
				tileMapVectorTemp[i][j].terrainFrameX,
				tileMapVectorTemp[i][j].terrainFrameY,
				tileMapVectorTemp[i][j].terrain,
				tileMapVectorTemp[i][j].objImageNum,
				tileMapVectorTemp[i][j].objFrameX,
				tileMapVectorTemp[i][j].objFrameY,
				tileMapVectorTemp[i][j].obj);

			WriteFile(file, str, strlen(str), &write, NULL);
		}
	}

	ZeroMemory(str, sizeof(str));
	sprintf_s(str, "interaction_obj_num : %d\r\n", interactionObjectVectorTemp.size());
	WriteFile(file, str, strlen(str), &write, NULL);

	for (int i = 0; i < interactionObjectVectorTemp.size(); i++)
	{
		ZeroMemory(str, sizeof(str));

		sprintf_s(str, "%d ,%d, %d, %d, %d, %d\r\n",
			interactionObjectVectorTemp[i].xPos,
			interactionObjectVectorTemp[i].yPos,
			interactionObjectVectorTemp[i].widthPos,
			interactionObjectVectorTemp[i].heightPos,
			interactionObjectVectorTemp[i].obj,
			interactionObjectVectorTemp[i].imageNum);

		WriteFile(file, str, strlen(str), &write, NULL);
	}

	CloseHandle(file);
}

void mapToolScene::load()
{
	char str[1000];
	char editTemp[256] = { 0 };				//hEdit1�ڵ鿡 ���ڸ� �Է��ϱ� ���ؼ� ���۸� �����Ѵ�. 

	GetWindowText							//������ ĵ�Ǹ��� �����ϴ� �Լ��̴�,
	(hEdit3,								//��Ʈ���� �ڵ�
		editTemp,							//ĸ���� ���� ���� ����
		128);								//������ ũ��

	// 1���ε�
	ifstream inFile(editTemp);

	//Ÿ�ϸ�
	tileMap *tileMapTemp;
	tileMapTemp = new tileMap();
	vector<vector<tagTile>> tileMapVectorTemp;

	//������Ʈ
	vector<tagInteractionObject> interactionObjectVectorTemp;
	tagInteractionObject interactionObject_Temp;
	int vectorNum;


	ZeroMemory(str, sizeof(str));
	inFile.getline(str, 1000);
	sscanf_s(str, "x : %d, y : %d\r\n", &_currentMapX, &_currentMapY);

	reMapSize(true);

	tileMapTemp->initTileMap(_currentMapX, _currentMapY, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, NULL);
	tileMapVectorTemp = tileMapTemp->getTileMap();

	for (int i = 0; i < _currentMapY; i++)
	{
		for (int j = 0; j < _currentMapX; j++)
		{
			ZeroMemory(str, sizeof(str));
			inFile.getline(str, 1000);

			sscanf_s(str, "%d ,%d, %d, %d, %d, %d, %d, %d\r\n",
				&tileMapVectorTemp[i][j].terrainImageNum,
				&tileMapVectorTemp[i][j].terrainFrameX,
				&tileMapVectorTemp[i][j].terrainFrameY,
				&tileMapVectorTemp[i][j].terrain,
				&tileMapVectorTemp[i][j].objImageNum,
				&tileMapVectorTemp[i][j].objFrameX,
				&tileMapVectorTemp[i][j].objFrameY,
				&tileMapVectorTemp[i][j].obj);

			tileMapVectorTemp[i][j].terrainImg = IMAGEMANAGER->findImage(*(_tileSampleImageNameVector.begin() + tileMapVectorTemp[i][j].terrainImageNum));
			tileMapVectorTemp[i][j].objImg = IMAGEMANAGER->findImage(*(_objSampleImageNameVector.begin() + tileMapVectorTemp[i][j].objImageNum));
		}
	}
	_firstFloorTileMap.setTileMap(tileMapVectorTemp);

	ZeroMemory(str, sizeof(str));
	inFile.getline(str, 1000);
	sscanf_s(str, "interaction_obj_num : %d\r\n", &vectorNum);

	for (int i = 0; i < vectorNum; i++)
	{
		ZeroMemory(str, sizeof(str));
		inFile.getline(str, 1000);

		sscanf_s(str, "%d ,%d, %d, %d, %d, %d\r\n",
			&interactionObject_Temp.xPos,
			&interactionObject_Temp.yPos,
			&interactionObject_Temp.widthPos,
			&interactionObject_Temp.heightPos,
			&interactionObject_Temp.obj,
			&interactionObject_Temp.imageNum);

		interactionObject_Temp._rc = RectMake(interactionObject_Temp.xPos*MAPTOOL_TILESIZE, interactionObject_Temp.yPos*MAPTOOL_TILESIZE, interactionObject_Temp.widthPos*MAPTOOL_TILESIZE, interactionObject_Temp.heightPos*MAPTOOL_TILESIZE);
		interactionObject_Temp._img = IMAGEMANAGER->findImage(*(_interactionObjectSampleImageNameVector.begin() + interactionObject_Temp.imageNum));

		interactionObjectVectorTemp.push_back(interactionObject_Temp);
	}
	_firstFloorTileMap.setInteractionObject(interactionObjectVectorTemp);


	tileMapTemp->initTileMap(_currentMapX, _currentMapY, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, NULL);
	tileMapVectorTemp = tileMapTemp->getTileMap();
	interactionObjectVectorTemp.clear();

	//2�� �ε�
	ZeroMemory(str, sizeof(str));
	inFile.getline(str, 1000);
	sscanf_s(str, "x : %d, y : %d\r\n", &_currentMapX, &_currentMapY);

	for (int i = 0; i < _currentMapY; i++)
	{
		for (int j = 0; j < _currentMapX; j++)
		{
			ZeroMemory(str, sizeof(str));
			inFile.getline(str, 1000);

			sscanf_s(str, "%d ,%d, %d, %d, %d, %d, %d, %d\r\n",
				&tileMapVectorTemp[i][j].terrainImageNum,
				&tileMapVectorTemp[i][j].terrainFrameX,
				&tileMapVectorTemp[i][j].terrainFrameY,
				&tileMapVectorTemp[i][j].terrain,
				&tileMapVectorTemp[i][j].objImageNum,
				&tileMapVectorTemp[i][j].objFrameX,
				&tileMapVectorTemp[i][j].objFrameY,
				&tileMapVectorTemp[i][j].obj);

			tileMapVectorTemp[i][j].terrainImg = IMAGEMANAGER->findImage(*(_tileSampleImageNameVector.begin() + tileMapVectorTemp[i][j].terrainImageNum));
			tileMapVectorTemp[i][j].objImg = IMAGEMANAGER->findImage(*(_objSampleImageNameVector.begin() + tileMapVectorTemp[i][j].objImageNum));
		}
	}
	_secondFloorTileMap.setTileMap(tileMapVectorTemp);

	ZeroMemory(str, sizeof(str));
	inFile.getline(str, 1000);
	sscanf_s(str, "interaction_obj_num : %d\r\n", &vectorNum);

	for (int i = 0; i < vectorNum; i++)
	{
		ZeroMemory(str, sizeof(str));
		inFile.getline(str, 1000);

		sscanf_s(str, "%d ,%d, %d, %d, %d, %d\r\n",
			&interactionObject_Temp.xPos,
			&interactionObject_Temp.yPos,
			&interactionObject_Temp.widthPos,
			&interactionObject_Temp.heightPos,
			&interactionObject_Temp.obj,
			&interactionObject_Temp.imageNum);

		interactionObject_Temp._rc = RectMake(interactionObject_Temp.xPos*MAPTOOL_TILESIZE, interactionObject_Temp.yPos*MAPTOOL_TILESIZE, interactionObject_Temp.widthPos*MAPTOOL_TILESIZE, interactionObject_Temp.heightPos*MAPTOOL_TILESIZE);
		interactionObject_Temp._img = IMAGEMANAGER->findImage(*(_interactionObjectSampleImageNameVector.begin() + interactionObject_Temp.imageNum));

		interactionObjectVectorTemp.push_back(interactionObject_Temp);
	}
	_secondFloorTileMap.setInteractionObject(interactionObjectVectorTemp);

	_nowFloor = 1;
	drawBackTileMap(0, _nowFloor);

	delete(tileMapTemp);
}

TERRAIN mapToolScene::terrainSelect(int frameX, int frameY)
{
	if (_nowImgNum == 0)
	{
		return TR_GRASS;
	}
	//�ø�Ʈ
	else if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}
	//��ٴ�
	else if (frameX == 2 && frameY == 0)
	{
		return TR_DESERT;
	}
	//�ܵ�
	else if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}
	//��
	else if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}
	return TR_GRASS;
}

OBJECT mapToolScene::objSelect(int frameX, int frameY)
{
	if (_nowImgNum == 2)
	{
		if ((frameX == 11 && frameY == 5) || (frameX == 11 && frameY == 6) || (frameX == 12 && frameY == 5) || (frameX == 12 && frameY == 6))
		{
			return OBJ_DOOR;
		}
	}

	if (_nowImgNum == 3)
	{
		if ( (frameX == 8 && frameY == 1) || (frameX == 8 && frameY == 2) || (frameX == 9 && frameY == 1) || (frameX == 9 && frameY == 2)
			|| (frameX == 8 && frameY == 3) || (frameX == 8 && frameY == 4) || (frameX == 9 && frameY == 3) || (frameX == 9 && frameY == 4)
			|| (frameX == 11 && frameY == 1) || (frameX == 11 && frameY == 2) || (frameX == 12 && frameY == 1) || (frameX == 12 && frameY == 2)
			|| (frameX == 12 && frameY == 5) || (frameX == 12 && frameY == 6) || (frameX == 13 && frameY == 5) || (frameX == 13 && frameY == 6) )
		{
			return OBJ_DOOR;
		}
	}
	if (_nowImgNum == 7)
	{
		if ((frameX == 5 && frameY == 8) || (frameX == 5 && frameY == 9) || (frameX == 6 && frameY == 8) || (frameX == 6 && frameY == 9))
		{
			return OBJ_DOOR;
		}
	}
	if (_nowImgNum == 9)
	{
		if ((frameX == 9 && frameY == 7) || (frameX == 9 && frameY == 8) || (frameX == 10 && frameY == 7) || (frameX == 10 && frameY == 8))
		{
			return OBJ_DOOR;
		}
	}
	if (_nowImgNum == 10)
	{
		if ((frameX == 15 && frameY == 0) || (frameX == 15 && frameY == 1) || (frameX == 16 && frameY == 0) || (frameX == 16 && frameY == 1)
			|| (frameX == 15 && frameY == 4) || (frameX == 15 && frameY == 5) || (frameX == 16 && frameY == 4) || (frameX == 16 && frameY == 5)
			||(frameX == 4 && frameY == 7) || (frameX == 4 && frameY == 8) || (frameX ==5  && frameY == 7) || (frameX == 5 && frameY == 8)
			|| (frameX == 8 && frameY == 7) || (frameX == 8 && frameY == 8) || (frameX == 9 && frameY == 7) || (frameX == 9 && frameY == 8))
		{
			return OBJ_DOOR;
		}
	}


	return OBJ_BLOCK;
}

void mapToolScene::buttonAdd(string imageName, MAPTOOL_BUTTONKIND buttonKind, int x, int y, int width, int height, bool isFrame)
{
	imageButton buttonTemp;
	buttonTemp._img = IMAGEMANAGER->findImage(imageName);
	buttonTemp._kind = buttonKind;
	buttonTemp._rc = RectMake(x, y, width, height);
	buttonTemp._isFrame = isFrame;
	buttonTemp._ischeck = false;
	buttonTemp._currentX = 0;

	imageButtonVector.push_back(buttonTemp);
}

void mapToolScene::selectButton()
{
	tagCurrentTile currenTileTemp;

	for (int i = 0; i < imageButtonVector.size(); i++)
	{
		if (PtInRect(&imageButtonVector[i]._rc, m_ptMouse))
		{
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_RESIZE)
			{
				reMapSize(false);
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_TERRAINDRAW)
			{
				//Ÿ�Ϸ� �����̹��� ����
				_ctrSelect = MAPTOOL_BUTTONKIND_TERRAINDRAW;
				_nowImg = IMAGEMANAGER->findImage(*_tileSampleImageNameVector.begin());
				_nowImgNum = 0;
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_OBJDRAW)
			{
				//������Ʈ�� �����̹��� ����
				_ctrSelect = MAPTOOL_BUTTONKIND_OBJDRAW;
				_nowImg = IMAGEMANAGER->findImage(*_objSampleImageNameVector.begin());
				_nowImgNum = 0;
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW)
			{
				//��ȣ�ۿ� ������Ʈ�� �����̹��� ����
				_ctrSelect = MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW;
				_nowImgNum = 0;
				setNowInteractionObject(_nowImgNum);
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_ERASER)
			{
				_ctrSelect = MAPTOOL_BUTTONKIND_ERASER;
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_SAVE)
			{
				save();
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_LOAD)
			{
				load();
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_FIRSTFLOOR)
			{
				_nowFloor = 1;
				drawBackTileMap(0, 1);
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_SECONDFLOOR)
			{
				_nowFloor = 2;
				drawBackTileMap(0, 2);
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_LEFTBUTTON)
			{
				moveNowSampleImage(true);
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_RIGHTBUTTON)
			{
				moveNowSampleImage(false);
			}

			//���õ� ���ø� ���� �ʱ�ȭ(��ư �ٲ�� �ʱⰪ���� �ʱ�ȭ)
			_selectTileX = 1;
			_selectTileY = 1;
			_currentTileVector.clear();

			currenTileTemp._x = _sampleTiles[0]._frameX;
			currenTileTemp._y = _sampleTiles[0]._frameY;
			currenTileTemp._img = _sampleTiles[0]._img;

			_currentTileVector.push_back(currenTileTemp);

			//���õ� ��Ʈũ��� �簢�� �׷��ֱ�
			IMAGEMANAGER->deleteImage("selectSampleRect");
			IMAGEMANAGER->addImage("selectSampleRect", "images/maptool/sampleSelect.bmp", _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE, true, RGB(0, 0, 0));
			_nowSelectSampleTileRect = RectMake(MAPTOOL_SIDEBAR_STARTX, 0, MAPTOOL_SIDEBAR_STARTX + _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE);

			break;
		}
	}
}

void mapToolScene::reMapSize(bool isLoad)
{
	char editTemp[6] = { 0 };				//hEdit1�ڵ鿡 ���ڸ� �Է��ϱ� ���ؼ� ���۸� �����Ѵ�. 
	int xTilePos = 0, yTilePos = 0;			//���ڿ��� ���� ���������� ���� ����

	if (!isLoad)
	{
		GetWindowText							//������ ĵ�Ǹ��� �����ϴ� �Լ��̴�,
		(hEdit1,								//��Ʈ���� �ڵ�
			editTemp,							//ĸ���� ���� ���� ����
			128);								//������ ũ��

		xTilePos = atoi(editTemp);				//���ڿ��� ���� ���·� ��ȯ�Ͽ� num1���� �Ͽ���

		if (xTilePos > 500)
		{
			xTilePos = 500;
		}

		GetWindowText
		(
			hEdit2,
			editTemp,
			128);

		yTilePos = atoi(editTemp);
		if (yTilePos > 500)
		{
			yTilePos = 500;
		}

		_currentMapX = xTilePos;
		_currentMapY = yTilePos;
	}
	IMAGEMANAGER->deleteImage("mapbackBuffer");
	IMAGEMANAGER->deleteImage("����ī�޶�");

	//�� backbuffer����
	_mapBackBuffer = IMAGEMANAGER->addImage("mapbackBuffer", _currentMapX * MAPTOOL_TILESIZE, _currentMapY * MAPTOOL_TILESIZE);

	_currentMapXPos = _currentMapX * MAPTOOL_TILESIZE;
	_currentMapYPos = _currentMapY * MAPTOOL_TILESIZE;

	//�̴ϸ� ī�޶� �缱��
	if (_currentMapXPos < 600 && _currentMapYPos < 600)
	{
		IMAGEMANAGER->addImage("����ī�޶�", "images/maptool/ī�޶�.bmp", 300, 300, true, RGB(0, 0, 0));
	}
	else if (_currentMapXPos < 600)
	{
		IMAGEMANAGER->addImage("����ī�޶�", "images/maptool/ī�޶�.bmp", 300, 300 * MAPTOOL_VIEWSIZEY / _currentMapYPos, true, RGB(0, 0, 0));
	}
	else if (_currentMapYPos < 600)
	{
		IMAGEMANAGER->addImage("����ī�޶�", "images/maptool/ī�޶�.bmp", 300 * MAPTOOL_VIEWSIZEX / _currentMapXPos, 300, true, RGB(0, 0, 0));
	}
	else
	{
		IMAGEMANAGER->addImage("����ī�޶�", "images/maptool/ī�޶�.bmp", 300 * MAPTOOL_VIEWSIZEX / _currentMapXPos, 300 * MAPTOOL_VIEWSIZEY / _currentMapYPos, true, RGB(0, 0, 0));
	}

	//Ÿ�ϸ�
	_firstFloorTileMap.initTileMap(_currentMapX, _currentMapY, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, IMAGEMANAGER->findImage(*_tileSampleImageNameVector.begin()));
	_secondFloorTileMap.initTileMap(_currentMapX, _currentMapY, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, NULL);

	_nowCarmeraX = 0;
	_nowCarmeraY = 0;

	//�ٲ� Ÿ�ϸ��� �ѹ� �׷��ش�
	_nowFloor = 1;
	drawBackTileMap(0, _nowFloor);
}

void mapToolScene::drawBackTileMap(int set, int floor)
{

	//�� �Լ��� ���� ����۰� �ƴ� �ٸ� ��(���)�� �׷��ִ� �Լ��̴�
	//�� �� �Ϻκ��� ���ͼ� ȭ�鿡 ���, �̴ϸ��� �׷��ְ� �ȴ�
	//set = ��ü��, ����� ����/ floor = �׷��ִ� �� ����
	vector<vector<tagTile>> tileMapVectorTemp;
	vector<tagInteractionObject> interactionObjectVectorTemp;

	if (floor == 1)
	{
		tileMapVectorTemp = _firstFloorTileMap.getTileMap();
		interactionObjectVectorTemp = _firstFloorTileMap.getInteractionObject();
	}
	else if (floor == 2)
	{
		tileMapVectorTemp = _secondFloorTileMap.getTileMap();
		interactionObjectVectorTemp = _secondFloorTileMap.getInteractionObject();
	}
	if (set == 0)
	{
		//��ü���� ��ʿ� �׷��ش�
		for (int i = 0; i < _currentMapY; i++)
		{
			for (int j = 0; j < _currentMapX; j++)
			{
				if (tileMapVectorTemp[i][j].terrain == TR_NONE)continue;

				tileMapVectorTemp[i][j].terrainImg->frameRender(getMapBackBufferDc(), tileMapVectorTemp[i][j].rc.left, tileMapVectorTemp[i][j].rc.top, tileMapVectorTemp[i][j].terrainFrameX, tileMapVectorTemp[i][j].terrainFrameY);

				if (tileMapVectorTemp[i][j].obj == OBJ_NONE)continue;

				tileMapVectorTemp[i][j].objImg->frameRender(getMapBackBufferDc(), tileMapVectorTemp[i][j].rc.left, tileMapVectorTemp[i][j].rc.top, tileMapVectorTemp[i][j].objFrameX, tileMapVectorTemp[i][j].objFrameY);
			}
		}

		for (int i = 0; i < interactionObjectVectorTemp.size(); i++)
		{
			interactionObjectVectorTemp[i]._img->render(getMapBackBufferDc(), interactionObjectVectorTemp[i].xPos*MAPTOOL_TILESIZE, interactionObjectVectorTemp[i].yPos*MAPTOOL_TILESIZE);
		}
	}
	if (set == 1)
	{
		//�� �κ��� ���̴� ȭ�鸸 ��ʿ� �ٽ� �׷��ִ� �Լ��̴�.
		//���� �� ����ۿ� �׷��ش�
		for (int i = _nowCarmeraY / MAPTOOL_TILESIZE; i < _currentMapY; i++)
		{
			//ȭ�鿡 ������ Ÿ�ϸ� �׷��ֱ� ����
			if ((_nowCarmeraY + MAPTOOL_VIEWSIZEY) / MAPTOOL_TILESIZE <= i)
				break;

			for (int j = _nowCarmeraX / MAPTOOL_TILESIZE; j < _currentMapX; j++)
			{

				//ȭ�鿡 ������ Ÿ�ϸ� �׷��ֱ� ����
				if ((_nowCarmeraX + MAPTOOL_VIEWSIZEX) / MAPTOOL_TILESIZE <= j)
					break;

				if (tileMapVectorTemp[i][j].terrain == TR_NONE)continue;

				tileMapVectorTemp[i][j].terrainImg->frameRender(getMapBackBufferDc(), tileMapVectorTemp[i][j].rc.left, tileMapVectorTemp[i][j].rc.top, tileMapVectorTemp[i][j].terrainFrameX, tileMapVectorTemp[i][j].terrainFrameY);

				if (tileMapVectorTemp[i][j].obj == OBJ_NONE)continue;

				tileMapVectorTemp[i][j].objImg->frameRender(getMapBackBufferDc(), tileMapVectorTemp[i][j].rc.left, tileMapVectorTemp[i][j].rc.top, tileMapVectorTemp[i][j].objFrameX, tileMapVectorTemp[i][j].objFrameY);
			}
		}
		for (int i = 0; i < interactionObjectVectorTemp.size(); i++)
		{

			if (interactionObjectVectorTemp[i].xPos*MAPTOOL_TILESIZE + interactionObjectVectorTemp[i].widthPos*MAPTOOL_TILESIZE< _nowCarmeraX || interactionObjectVectorTemp[i].xPos*MAPTOOL_TILESIZE>_nowCarmeraX + MAPTOOL_VIEWSIZEX)
			{
				continue;
			}
			else if (interactionObjectVectorTemp[i].yPos*MAPTOOL_TILESIZE + interactionObjectVectorTemp[i].heightPos*MAPTOOL_TILESIZE< _nowCarmeraY || interactionObjectVectorTemp[i].yPos*MAPTOOL_TILESIZE>_nowCarmeraY + MAPTOOL_VIEWSIZEY)
			{
				continue;
			}

			interactionObjectVectorTemp[i]._img->render(getMapBackBufferDc(), interactionObjectVectorTemp[i].xPos*MAPTOOL_TILESIZE, interactionObjectVectorTemp[i].yPos*MAPTOOL_TILESIZE);
		}
	}
}

void mapToolScene::moveNowSampleImage(bool isleft)
{
	if (isleft)
	{
		_nowImgNum--;

		if (_ctrSelect == MAPTOOL_BUTTONKIND_TERRAINDRAW)
		{
			if (_nowImgNum < 0)
			{
				_nowImgNum = _tileSampleImageNameVector.size() - 1;
			}
			_nowImg = IMAGEMANAGER->findImage(*(_tileSampleImageNameVector.begin() + _nowImgNum));
		}
		else if (_ctrSelect == MAPTOOL_BUTTONKIND_OBJDRAW)
		{
			if (_nowImgNum < 0)
			{
				_nowImgNum = _objSampleImageNameVector.size() - 1;
			}
			_nowImg = IMAGEMANAGER->findImage(*(_objSampleImageNameVector.begin() + _nowImgNum));
		}
		else if (_ctrSelect == MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW)
		{
			if (_nowImgNum < 0)
			{
				_nowImgNum = _interactionObjectSampleImageNameVector.size() - 1;
			}
			setNowInteractionObject(_nowImgNum);
		}
	}
	else
	{
		_nowImgNum++;

		if (_ctrSelect == MAPTOOL_BUTTONKIND_TERRAINDRAW)
		{
			if (_nowImgNum >= _tileSampleImageNameVector.size())
			{
				_nowImgNum = 0;
			}
			_nowImg = IMAGEMANAGER->findImage(*(_tileSampleImageNameVector.begin() + _nowImgNum));
		}
		else if (_ctrSelect == MAPTOOL_BUTTONKIND_OBJDRAW)
		{
			if (_nowImgNum >= _objSampleImageNameVector.size())
			{
				_nowImgNum = 0;
			}
			_nowImg = IMAGEMANAGER->findImage(*(_objSampleImageNameVector.begin() + _nowImgNum));
		}
		else if (_ctrSelect == MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW)
		{
			if (_nowImgNum >= _interactionObjectSampleImageNameVector.size())
			{
				_nowImgNum = 0;
			}
			setNowInteractionObject(_nowImgNum);
		}
	}
}


void mapToolScene::setNowInteractionObject(int num)
{
	_nowImg = IMAGEMANAGER->findImage(*(_interactionObjectSampleImageNameVector.begin() + num));

	_currentInteractionObject.widthPos = _nowImg->getWidth() / 24;
	_currentInteractionObject.heightPos = _nowImg->getHeight() / 24;

	if (num == 0)
	{
		_currentInteractionObject.obj = INTERACTIONOBJ_GRASS;
	}
	else if (num == 1)
	{
		_currentInteractionObject.obj = INTERACTIONOBJ_SMALLROCK;
	}
	else if (num == 2)
	{
		_currentInteractionObject.obj = INTERACTIONOBJ_LADDER;
	}
	else if (num == 3)
	{
		_currentInteractionObject.obj = INTERACTIONOBJ_TREASUREBOX;
	}
	else if (num == 4)
	{
		_currentInteractionObject.obj = INTERACTIONOBJ_BIGTREASUREBOX;
	}
	else if (num == 5)
	{
		_currentInteractionObject.obj = INTERACTIONOBJ_JAR;
	}
	else if (num == 6)
	{
		_currentInteractionObject.obj = INTERACTIONOBJ_OPENDOOR;
	}
	else if (num == 7)
	{
		_currentInteractionObject.obj = INTERACTIONOBJ_ROCKEDDOOR;
	}
	else if (num == 8)
	{
		_currentInteractionObject.obj = INTERACTIONOBJ_LADDER;
	}
}


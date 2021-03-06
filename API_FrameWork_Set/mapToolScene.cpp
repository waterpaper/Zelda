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

	//윈도우 사이즈 조절
	RECT rc;
	rc = RectMake(0, 0, MAPTOOL_WINSIZEX, MAPTOOL_WINSIZEY);
	AdjustWindowRect(&rc, WINSTYLE, false);
	//위 RECT 정보로 윈도우 사이즈 셋팅
	SetWindowPos(m_hWnd, NULL, 0, 0, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
	IMAGEMANAGER->setImageReSize("backbuffer", MAPTOOL_WINSIZEX, MAPTOOL_WINSIZEY);

	//맵 backbuffer선언
	_mapBackBuffer = IMAGEMANAGER->addImage("mapbackBuffer", TILEX * MAPTOOL_TILESIZE, TILEY * MAPTOOL_TILESIZE);

	_img = IMAGEMANAGER->findImage("maptool_img");

	//타일맵과 샘플맵 초기화
	_nowImg = IMAGEMANAGER->findImage(*_tileSampleImageNameVector.begin());

	_firstFloorTileMap.initTileMap(TILEX, TILEY, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, _nowImg);
	_secondFloorTileMap.initTileMap(TILEX, TILEY, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, NULL);

	_currentMapX = TILEX;
	_currentMapY = TILEY;

	_currentMapXPos = TILEX * MAPTOOL_TILESIZE;
	_currentMapYPos = TILEY * MAPTOOL_TILESIZE;

	//카메라위치와 미니맵 카메라사진 초기화
	_nowFloor = 1;

	_nowCarmeraX = 0;
	_nowCarmeraY = 0;

	IMAGEMANAGER->addImage("맵툴카메라", "images/maptool/카메라.bmp", 300 * MAPTOOL_VIEWSIZEX / _currentMapXPos, 300 * MAPTOOL_VIEWSIZEY / _currentMapYPos, true, RGB(0, 0, 0));

	//왼쪽 맵 셋팅
	drawBackTileMap(0, _nowFloor);

	//오른쪽 샘플 맵 셋팅
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{

			_sampleTiles[i * SAMPLETILEX + j]._frameX = j;
			_sampleTiles[i * SAMPLETILEX + j]._frameY = i;
			_sampleTiles[i * SAMPLETILEX + j]._img = _nowImg;

			//좌표값을 설정
			SetRect(&_sampleTiles[i* SAMPLETILEX + j]._rcTile, MAPTOOL_SIDEBAR_STARTX + j * MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTY + i * MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTX + j * MAPTOOL_TILESIZE + MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTY + i * MAPTOOL_TILESIZE + MAPTOOL_TILESIZE);
		}

	}

	//선택된 샘플맵 백터 초기화
	tagCurrentTile currenTileTemp;

	_selectTileX = 1;
	_selectTileY = 1;
	_currentTileVector.clear();

	currenTileTemp._x = _sampleTiles[0]._frameX;
	currenTileTemp._y = _sampleTiles[0]._frameY;
	currenTileTemp._img = _sampleTiles[0]._img;

	_currentTileVector.push_back(currenTileTemp);

	//선택된 렉트크기로 사각형 그려주기
	IMAGEMANAGER->deleteImage("selectSampleRect");
	IMAGEMANAGER->addImage("selectSampleRect", "images/maptool/sampleSelect.bmp", _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE, true, RGB(0, 0, 0));
	_nowSelectSampleTileRect = RectMake(MAPTOOL_SIDEBAR_STARTX, 0, MAPTOOL_SIDEBAR_STARTX+_selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE);

	//_nowSelectSampleTileRect = RectMake(MAPTOOL_SIDEBAR_STARTX, 0, _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE);

	//마우스 좌표 초기화
	_startMousePointX = 0;
	_startMousePointY = 0;

	//미니맵 여부 초기화
	_isMinimapView = true;

	//버튼, 텍스트 에디트 초기화
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
	_sound.soundPlay("선택창");

	return S_OK;
}

void mapToolScene::release()
{
	RECT rc;
	rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	AdjustWindowRect(&rc, WINSTYLE, false);
	//위 RECT 정보로 윈도우 사이즈 셋팅
	SetWindowPos(m_hWnd, NULL, 0, 0, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
	IMAGEMANAGER->setImageReSize("backbuffer", WINSIZEX, WINSIZEY);

	IMAGEMANAGER->deleteImage("mapbackbuffer");
	IMAGEMANAGER->deleteImage("맵툴카메라");

	DestroyWindow(hEdit1);
	DestroyWindow(hEdit2);
	DestroyWindow(hEdit3);

	_firstFloorTileMap.release();
	_secondFloorTileMap.release();

	scene::release();

}

void mapToolScene::update()
{
	//이미지 버튼에 마우스 위치 여부 판단
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
		//버튼 클릭 감지
		selectButton();

		//오른쪽 샘플 맵을 셋팅하자.
		if (_ctrSelect != MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW)
		{
			for (int i = 0; i < SAMPLETILEY; i++)
			{
				for (int j = 0; j < SAMPLETILEX; j++)
				{
					_sampleTiles[i * SAMPLETILEX + j]._frameX = j;
					_sampleTiles[i * SAMPLETILEX + j]._frameY = i;
					_sampleTiles[i * SAMPLETILEX + j]._img = _nowImg;

					//좌표값을 설정
					SetRect(&_sampleTiles[i* SAMPLETILEX + j]._rcTile, MAPTOOL_SIDEBAR_STARTX + j * MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTY + i * MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTX + j * MAPTOOL_TILESIZE + MAPTOOL_TILESIZE, MAPTOOL_SIDEBAR_STARTY + i * MAPTOOL_TILESIZE + MAPTOOL_TILESIZE);
				}
			}

			//클릭을 멈췃을때 까지의 좌표를 렉트를 만든다
			//좌표안에 샘플들을 벡터에 넣어 그릴 수 있게 한다
			RECT sampleRect, currentSampleRect, rectTemp;
			tagCurrentTile currenTileTemp;
			int maxCurrentX = 0;

			sampleRect = RectMake(MAPTOOL_SIDEBAR_STARTX, 0, 480, 240);

			//샘플맵 안에서만 작동
			if (PtInRect(&sampleRect, m_ptMouse))
			{
				//선택된 벡터 초기화
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

				//타일수 세기
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

				//한개도 벡터에 존재하지 않을시(역방향)
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

				//선택된 렉트크기로 사각형 그려주기
				IMAGEMANAGER->deleteImage("selectSampleRect");
				IMAGEMANAGER->addImage("selectSampleRect", "images/maptool/sampleSelect.bmp", _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE, true, RGB(0, 0, 0));

				//한개일 경우
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
			//선택된 렉트크기로 사각형 그려주기
			IMAGEMANAGER->deleteImage("selectSampleRect");
			IMAGEMANAGER->addImage("selectSampleRect", "images/maptool/sampleSelect.bmp", _nowImg->getWidth(), _nowImg->getHeight(), true, RGB(0, 0, 0));

			setNowInteractionObject(_nowImgNum);
		}

	}//oncekeydown/left end

	//맵사이즈를 벗어 나지 않을때 카메라를 조정해 타일맵 뷰를 이동시킨다.
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
	//배경이미지를 그려준다
	_img->render(getMemDC(), 0, 0);

	//버튼을 그려준다
	for (int i = 0; i < imageButtonVector.size(); i++)
	{
		imageButtonRender(imageButtonVector[i]);
	}

	drawBackTileMap(1, _nowFloor);

	//맵 백버퍼에 있는 정보를 그려준다	(맵 뷰크기로 잘라서)										     가로				세로 크기
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
		//샘플맵
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


	//미니맵(현재 300x300범위)
	if (_isMinimapView)
	{
		_mapBackBuffer->minimapRender(getMemDC(), MAPTOOL_SIDEBAR_STARTX, 390, 300, 300, getMapBackBufferDc(), 0, 0, _currentMapXPos, _currentMapYPos);
	}

	//카메라
	if (_currentMapXPos < 600 && _currentMapYPos < 600)
	{
		IMAGEMANAGER->render("맵툴카메라", getMemDC(), MAPTOOL_SIDEBAR_STARTX, 390);
	}
	else if (_currentMapXPos < 600)
	{
		IMAGEMANAGER->render("맵툴카메라", getMemDC(), MAPTOOL_SIDEBAR_STARTX, 390 + _nowCarmeraY / (_currentMapYPos / 300));
	}
	else if (_currentMapYPos < 600)
	{
		IMAGEMANAGER->render("맵툴카메라", getMemDC(), MAPTOOL_SIDEBAR_STARTX + _nowCarmeraX / (_currentMapXPos / 300), 390);
	}
	else
	{
		IMAGEMANAGER->render("맵툴카메라", getMemDC(), MAPTOOL_SIDEBAR_STARTX + _nowCarmeraX / (_currentMapXPos / 300), 390 + _nowCarmeraY / (_currentMapYPos / 300));
	}
}

void mapToolScene::setMap()
{
	//
	//화면 클릭시 왼쪽 뷰에 선택된 맵을 그리는 함수
	//

	int mapX = 0, mapY = 0;																//전체맵 좌표판단, 저장하는 변수
	RECT viewToolMapRect = RectMake(0, 0, MAPTOOL_VIEWSIZEX, MAPTOOL_VIEWSIZEY);		//맵툴 뷰파트의 렉트를 가지고 있는 변수

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

	//왼쪽타일

	if (PtInRect(&viewToolMapRect, m_ptMouse))
	{
		int num = 0;		//타일벡터를 돌리기 위한 변수

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
					//선택된 크기의 타일을 그려준다
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
					//선택된 크기의 타일을 그려준다
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
				//상호작용 오브젝트는 타일맵이 아닌 따른 형식으로 저장 처리될 예정이기 때문에 다른식으로 추가한다
				//전체크기가 하나의 오브젝트로 유지되야하기 때문

				RECT rectTemp, currentRectTemp = RectMake(mapX*MAPTOOL_TILESIZE, mapY*MAPTOOL_TILESIZE, _currentInteractionObject.widthPos*MAPTOOL_TILESIZE, _currentInteractionObject.heightPos*MAPTOOL_TILESIZE);

				for (int i = 0; i <= interactionObjectVectorTemp.size(); i++)
				{
					if (i == interactionObjectVectorTemp.size())
					{
						_firstFloorTileMap.addInteractionObject(mapX, mapY, _currentInteractionObject.widthPos, _currentInteractionObject.heightPos, currentRectTemp, _currentInteractionObject.obj, _nowImg, _nowImgNum);
						break;
					}
					//오브젝트끼리 겹치면 생성 x
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
					//선택된 크기의 타일을 그려준다
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
					//선택된 크기의 타일을 그려준다
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
				//상호작용 오브젝트는 타일맵이 아닌 따른 형식으로 저장 처리될 예정이기 때문에 다른식으로 추가한다
				//전체크기가 하나의 오브젝트로 유지되야하기 때문

				RECT rectTemp, currentRectTemp = RectMake(mapX*MAPTOOL_TILESIZE, mapY*MAPTOOL_TILESIZE, _currentInteractionObject.widthPos*MAPTOOL_TILESIZE, _currentInteractionObject.heightPos*MAPTOOL_TILESIZE);

				for (int i = 0; i <= interactionObjectVectorTemp.size(); i++)
				{
					if (i == interactionObjectVectorTemp.size())
					{
						_secondFloorTileMap.addInteractionObject(mapX, mapY, _currentInteractionObject.widthPos, _currentInteractionObject.heightPos, currentRectTemp, _currentInteractionObject.obj, _nowImg, _nowImgNum);
						break;
					}
					//오브젝트끼리 겹치면 생성 x
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
	char str[1000];							//문자열을 저장, 읽어올 변수
	char editTemp[256] = { 0 };				//hEdit1핸들에 문자를 입력하기 위해서 버퍼를 지정한다. 

	vector<vector<tagTile>> tileMapVectorTemp;
	vector<tagInteractionObject> interactionObjectVectorTemp;

	tileMapVectorTemp = _firstFloorTileMap.getTileMap();
	interactionObjectVectorTemp = _firstFloorTileMap.getInteractionObject();

	GetWindowText							//윈도우 캔션명을 조사하는 함수이다,
	(hEdit3,								//컨트롤의 핸들
		editTemp,							//캡션을 리턴 받을 버퍼
		128);								//버퍼의 크기

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


	//2층 세이브
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
	char editTemp[256] = { 0 };				//hEdit1핸들에 문자를 입력하기 위해서 버퍼를 지정한다. 

	GetWindowText							//윈도우 캔션명을 조사하는 함수이다,
	(hEdit3,								//컨트롤의 핸들
		editTemp,							//캡션을 리턴 받을 버퍼
		128);								//버퍼의 크기

	// 1층로드
	ifstream inFile(editTemp);

	//타일맵
	tileMap *tileMapTemp;
	tileMapTemp = new tileMap();
	vector<vector<tagTile>> tileMapVectorTemp;

	//오브젝트
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

	//2층 로드
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
	//시멘트
	else if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}
	//흙바닥
	else if (frameX == 2 && frameY == 0)
	{
		return TR_DESERT;
	}
	//잔디
	else if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}
	//물
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
				//타일로 샘플이미지 변경
				_ctrSelect = MAPTOOL_BUTTONKIND_TERRAINDRAW;
				_nowImg = IMAGEMANAGER->findImage(*_tileSampleImageNameVector.begin());
				_nowImgNum = 0;
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_OBJDRAW)
			{
				//오브젝트로 샘플이미지 변경
				_ctrSelect = MAPTOOL_BUTTONKIND_OBJDRAW;
				_nowImg = IMAGEMANAGER->findImage(*_objSampleImageNameVector.begin());
				_nowImgNum = 0;
			}
			if (imageButtonVector[i]._kind == MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW)
			{
				//상호작용 오브젝트로 샘플이미지 변경
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

			//선택된 샘플맵 벡터 초기화(버튼 바뀔시 초기값으로 초기화)
			_selectTileX = 1;
			_selectTileY = 1;
			_currentTileVector.clear();

			currenTileTemp._x = _sampleTiles[0]._frameX;
			currenTileTemp._y = _sampleTiles[0]._frameY;
			currenTileTemp._img = _sampleTiles[0]._img;

			_currentTileVector.push_back(currenTileTemp);

			//선택된 렉트크기로 사각형 그려주기
			IMAGEMANAGER->deleteImage("selectSampleRect");
			IMAGEMANAGER->addImage("selectSampleRect", "images/maptool/sampleSelect.bmp", _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE, true, RGB(0, 0, 0));
			_nowSelectSampleTileRect = RectMake(MAPTOOL_SIDEBAR_STARTX, 0, MAPTOOL_SIDEBAR_STARTX + _selectTileX * MAPTOOL_TILESIZE, _selectTileY * MAPTOOL_TILESIZE);

			break;
		}
	}
}

void mapToolScene::reMapSize(bool isLoad)
{
	char editTemp[6] = { 0 };				//hEdit1핸들에 문자를 입력하기 위해서 버퍼를 지정한다. 
	int xTilePos = 0, yTilePos = 0;			//문자열을 받을 정수형태의 변수 선언

	if (!isLoad)
	{
		GetWindowText							//윈도우 캔션명을 조사하는 함수이다,
		(hEdit1,								//컨트롤의 핸들
			editTemp,							//캡션을 리턴 받을 버퍼
			128);								//버퍼의 크기

		xTilePos = atoi(editTemp);				//문자열을 정수 형태로 전환하여 num1저장 하였다

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
	IMAGEMANAGER->deleteImage("맵툴카메라");

	//맵 backbuffer선언
	_mapBackBuffer = IMAGEMANAGER->addImage("mapbackBuffer", _currentMapX * MAPTOOL_TILESIZE, _currentMapY * MAPTOOL_TILESIZE);

	_currentMapXPos = _currentMapX * MAPTOOL_TILESIZE;
	_currentMapYPos = _currentMapY * MAPTOOL_TILESIZE;

	//미니맵 카메라 재선언
	if (_currentMapXPos < 600 && _currentMapYPos < 600)
	{
		IMAGEMANAGER->addImage("맵툴카메라", "images/maptool/카메라.bmp", 300, 300, true, RGB(0, 0, 0));
	}
	else if (_currentMapXPos < 600)
	{
		IMAGEMANAGER->addImage("맵툴카메라", "images/maptool/카메라.bmp", 300, 300 * MAPTOOL_VIEWSIZEY / _currentMapYPos, true, RGB(0, 0, 0));
	}
	else if (_currentMapYPos < 600)
	{
		IMAGEMANAGER->addImage("맵툴카메라", "images/maptool/카메라.bmp", 300 * MAPTOOL_VIEWSIZEX / _currentMapXPos, 300, true, RGB(0, 0, 0));
	}
	else
	{
		IMAGEMANAGER->addImage("맵툴카메라", "images/maptool/카메라.bmp", 300 * MAPTOOL_VIEWSIZEX / _currentMapXPos, 300 * MAPTOOL_VIEWSIZEY / _currentMapYPos, true, RGB(0, 0, 0));
	}

	//타일맵
	_firstFloorTileMap.initTileMap(_currentMapX, _currentMapY, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, IMAGEMANAGER->findImage(*_tileSampleImageNameVector.begin()));
	_secondFloorTileMap.initTileMap(_currentMapX, _currentMapY, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, NULL);

	_nowCarmeraX = 0;
	_nowCarmeraY = 0;

	//바뀐 타일맵을 한번 그려준다
	_nowFloor = 1;
	drawBackTileMap(0, _nowFloor);
}

void mapToolScene::drawBackTileMap(int set, int floor)
{

	//이 함수는 맵을 백버퍼가 아닌 다른 곳(백맵)에 그려주는 함수이다
	//이 중 일부분을 때와서 화면에 출력, 미니맵을 그려주게 된다
	//set = 전체맵, 현재맵 유무/ floor = 그려주는 층 구분
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
		//전체맵을 백맵에 그려준다
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
		//이 부분은 보이는 화면만 백맵에 다시 그려주는 함수이다.
		//맵을 맵 백버퍼에 그려준다
		for (int i = _nowCarmeraY / MAPTOOL_TILESIZE; i < _currentMapY; i++)
		{
			//화면에 나오는 타일만 그려주기 위함
			if ((_nowCarmeraY + MAPTOOL_VIEWSIZEY) / MAPTOOL_TILESIZE <= i)
				break;

			for (int j = _nowCarmeraX / MAPTOOL_TILESIZE; j < _currentMapX; j++)
			{

				//화면에 나오는 타일만 그려주기 위함
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


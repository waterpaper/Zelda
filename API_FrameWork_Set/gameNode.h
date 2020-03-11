#pragma once
#include"stdafx.h"
#include"image.h"
#include"tileMap.h"
//����� �̹����� ����ƽ���� ����

class gameNode
{
private:
	HDC _hdc;
	static image* _backBuffer;
	bool _managerInit;

public:
	gameNode();
	~gameNode();

	bool _isRectRend;
	bool _start;

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit, bool imageLoad);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual tileMap getTileMap() { return tileMap{}; };
	virtual void setNowFloor(int floor) { return; };
	virtual int getNowFloor() { return 0; };
	virtual void reDrawPosition(bool isPlayer, int floor, int positionX, int positionY, int width, int height, int cameraX, int cameraY) { return; };

	//����� ������
	image* getBackBuffer() { return _backBuffer; }

	//�߰�(�޸� DC)
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	//�߰� HDC���
	HDC getHDC() { return _hdc; }

	virtual LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
#pragma once
#pragma warning(disable:4996)
#include "scene.h"
#include "loading.h"

class loadingScene:public scene
{
	/*
	�ε�ȭ���� ���� ���Դϴ�
	�ε� �̹����� �Ʒ� loading Ŭ������ ���ǵǾ� �ֽ��ϴ�
	�ε��� �Ϸ��� �̹����� �Ʒ� total loading �Լ��� �߰��մϴ�
	*/
private:
	loading *_loading;

public:
	loadingScene();
	~loadingScene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	void totalLoding();
};


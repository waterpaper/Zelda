#pragma once
#include "scene.h"

class soundScene : public scene
{
private:

	image* _soundEffectBarFront;	//ȿ������ �� �̹���
	image* _soundEffectBarBack;		//ȿ������ �� �̹���

	image* _soundBackgruondBarFront;	//������� �� �̹���
	image* _soundBackgruondBarBack;		//������� �� �̹���

	image* _volume;

	image* _backGround;

	image* _backText;
	image* _effectText;

	RECT backVolumeRc;
	RECT effectVolumeRc;
	RECT backRc;
	POINT _backVolumeXY;
	POINT _effectVolumeXY;

	RECT backVolumeOff;
	RECT effectVolumeOff;

	bool backVolume;
	bool effectVolume;
public:
	soundScene();
	~soundScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void volumeControl();
};



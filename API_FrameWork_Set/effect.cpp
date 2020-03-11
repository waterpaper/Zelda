#include "stdafx.h"
#include "effect.h"

effect::effect()
	:_effectImage(nullptr)
	, _effectAni(nullptr)
	, _isRunnig(NULL)
	, _x(0)
	, _y(0)
{
}

effect::~effect()
{
}

HRESULT effect::init(image * effectImage, int frameW, int frameH, int FPS, float elapsedTime)
{
	//����Ʈ �̹����� ������ �ٷ� ����
	if (!effectImage) return E_FAIL;

	_effectImage = effectImage;
	_elapsedTime = elapsedTime;
	_isRunnig = false;

	//����Ʈ �ִϸ��̼� ������ ���� ����!
	if (!_effectAni) _effectAni = new animation;
	//�ִϸ��̼� ���� �ʱ�ȭ
	_effectAni->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAni->setDefPlayFrame();
	_effectAni->setFPS(FPS);

	return S_OK;
}

void effect::release(void)
{
	SAFE_DELETE(_effectAni);
}

void effect::update(void)
{
	if (_isRunnig)
	{
		_effectAni->frameUpdate(_elapsedTime);
	}

	//����Ʈ �ִϸ��̼��� ���ᰡ �Ǹ� �����ڤ�
	if (!_effectAni->isPlay()) stopEffect();
}

void effect::render(HDC hdc)
{
	if (_isRunnig)
	{
		_effectImage->aniRender(hdc, _x, _y, _effectAni);
	}
}

void effect::startEffect(int x, int y)
{
	//��ġ ��ǥ�� ���� ��ǥ�� �����
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunnig = true;
	_effectAni->start();

}

void effect::stopEffect()
{
	_isRunnig = false;
}

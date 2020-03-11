#pragma once
#include "gameNode.h"

class effect : public gameNode
{
private:
	image * _effectImage;	//����Ʈ �̹���
	animation* _effectAni;	//����Ʈ �ִϸ��̼�

	int _x, _y;				//����Ʈ ��Ʈ�� ��ǥ
	float _elapsedTime;		//����Ʈ ����ð�(�ӵ�)
	bool _isRunnig;			//����Ʈ ���
		
public:
	effect();
	~effect();

	//����Ʈ �ʱ�ȭ(����Ʈ �̹���, ����Ʈ �������� ���α���, ���α���, FPS(1), ����Ʈ �ӵ�)
	HRESULT init(image* effectImage, int frameW, int frameH, int FPS, float elapsedTime);
	void release(void);
	void update(void);
	void render(HDC hdc);

	//���� ���ϴ� ��ǥ�� ����Ʈ��Ʈ����
	void startEffect(int x, int y);
	//����Ʈ ���߱�
	void stopEffect();
	//����Ʈ ��������� ���°� ��������
	bool getIsRunning() { return _isRunnig; }



};

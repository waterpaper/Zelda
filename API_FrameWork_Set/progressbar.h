#pragma once
#include"gameNode.h"

class progressBar : public gameNode
{
private:

	RECT _rcProgress;	//ü�¹� ��Ʈ
	int _x, _y;			//��ǥ
	int _width;			//ü�¹� ���α���(�̰ɷ� ������)

	image* _progressBarFront;	//ü�¹� �� �̹���
	image* _progressBarBack;	//ü�¹� �� �̹���
public:
	progressBar();
	~progressBar();

	//ü�¹� �ʱ�ȭ(���̹���, ���̹���, x, y, ���α���, ���α���)
	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render();

	int getWidth() { return _width; };

	//���α׷����� ������ ����
	void setGauge(float currentGauge, float maxGauge);

	//���α׷����� ��ġ
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	//ü�¹� ��Ʈ
	RECT getRect() { return _rcProgress; }
};


#pragma once
#include"singletonBase.h"
//����Ʈ Ŭ���� ���漱��
class effect;
class effectManager : public singletonBase<effectManager>
{
private:

	//����Ʈ Ŭ������ ���� �༮
	typedef vector<effect*> vEffect;
	typedef vector<effect*>::iterator viEffect;
	//����Ʈ Ŭ������ ����� �ִ� ���͸� ���� �༮
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;
	//��� ����Ʈ�� ������ �༮
	typedef vector<mEffect> vTotalEffect;
	typedef vector<mEffect>::iterator viTotalEffect;

	//���� ��� ����Ʈ�� ����� �ִ� �༮
	vTotalEffect m_vTotalEffect;

public:
	effectManager();
	~effectManager();


	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	//����Ʈ �߰�(Ű��, �̹��� �̸�, �̹��� ����, ����, �������� ����, ����, FPS, ����Ʈ �ӵ�, ���۰���)
	void addEffect(string effectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer);

	//����Ʈ �÷���(����Ʈ Ű��, ����Ʈ ��Ʈ�� ��ǥ)
	void play(string effectKey, int x, int y);

};
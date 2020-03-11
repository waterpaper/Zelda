#pragma once
#include"singletonBase.h"

class animationManager : public singletonBase<animationManager>
{
private:
	typedef map<string, animation*> arrAnimation;
	typedef map<string, animation*>::iterator iterArrAnimation;

	arrAnimation _animation;
public:
	animationManager();
	~animationManager();


	HRESULT init();
	void release();
	void update();
	void render();

	//ó������ ������
	void addDefAnimation(string animationKeyName, char* imageKeyName, int fps, bool reverse = false, bool loop = false);
	//�迭�� ��Ƽ�
	void addAnimation(string animationKeyName, char* imageKeyName, int* playArr, int arrLen, int fps, bool loop = false);
	//���� ���ؼ�
	void addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse = false, bool loop = false);

	//�÷���
	void start(string animationKeyName);
	//����
	void stop(string animationKeyName);
	//�Ͻ�����
	void pause(string animationKeyName);
	//�ٽ� ���
	void resume(string animationKeyName);

	//�ִϸ��̼� ã��
	animation* findAnimation(string animationKeyName);

	//�ִϸ��̼� ã�� ����
	void deleteALL();
};

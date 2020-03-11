#pragma once
#include"singletonBase.h"
#include<bitset>

using namespace std;

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyUP;
	bitset<KEYMAX> _keyDown;

public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();

	//Ű�� �ѹ��� ����
	bool isOnceKeyDown(int key);
	//�����ٰ� �Է������
	bool isOnceKeyUp(int key);
	//��� ����
	bool isStayKeyDown(int key);
	//���
	bool isToggleKey(int key);
};
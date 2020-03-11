#pragma once
#include "singletonBase.h"

/*
	INI������ ������ �����ų� �о�ö� Ȥ�� �ʱ������� �о�ö� ���̴� ���� ����
*/
struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class iniData : public singletonBase <iniData>
{
private:
	typedef vector<tagIniData> arrIniData;

	typedef vector<arrIniData> arrIniDatas;

private:
	arrIniDatas _vIniData;

public:
	iniData();
	~iniData();

	HRESULT init();

	//������ �߰��ϱ�(����,Ű,����)
	void addData(char* section, char* key, char* value);
	//���̺� -> �����̸��� �־ �ڵ� ����
	void iniSave(char* fileName);

	//���ڰ� �ε�
	char* loadDataString(char* fileName, char* section, char* key);
	//������ �ε�
	int loadDataIntrger(char* fileName, char* section, char* key);
};


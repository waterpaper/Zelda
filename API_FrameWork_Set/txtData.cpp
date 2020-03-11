#include "stdafx.h"
#include "txtData.h"
txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::init()
{
	return S_OK;
}

//����¥�� �����͸� ��ƵѰ�(��� �����͸� ���� ������ ©�� �����Ѵ�.)
void txtData::txtSave(char * saveFileName, vector<string> vStr)
{
	HANDLE file;
	char str[128];
	DWORD write;

	strncpy_s(str, 128, vectorArrayCombine(vStr), 128);

	file = CreateFile
	(saveFileName,				//������ ���� �Ǵ� �� ��ġ�� �����̸�
		GENERIC_WRITE,			//�����̳� ��ġ�� ����ų� ���� ����� ����
		0,						//���� ���� ��� �Է�
		NULL,					//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
		CREATE_ALWAYS,			//�����̳� ��ġ�� ���� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL,	//�����̳� ��ġ�� ���� ���� �� Ư��
		NULL);					//������� ������ ���� �� Ư�� �� Ȯ�� Ư���� ���� ������ ������ �ִ� �༮

	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);

}

//���� ����� ������(����¥���� �����͸� ��ǥ ������ �� ����)
char * txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		//strncat_s : ���ڿ��� �κй��ڿ��� ���Ѵ٤�.
		strncat_s(str, 128, vArray[i].c_str(), 128);

		if ((i + 1) < vArray.size())
		{
			strcat_s(str, ",");								//��ǥ������ ������
		}
	}

	return str;
}

vector<string> txtData::txtLoad(char * loadFileName)
{
	HANDLE file;
	char str[128];
	DWORD read;

	file = CreateFile
	(loadFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, str, 128, &read, NULL);
	CloseHandle(file);

	return charArraySeperation(str);
}

vector<string> txtData::charArraySeperation(char charArray[])
{
	vector<string> vArray;
	char* separator = ",";
	char* token;
	char* context;				//����, strtok_s�� ����° ���ڷ� �п��� ���ڿ��� ���� �ּҰ��� ����Ų��

	token = strtok_s(charArray, separator,&context);
	vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &context)))
	{
		vArray.push_back(token);
	}
	return vArray;
}

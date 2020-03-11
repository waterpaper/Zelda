#include "stdafx.h"
#include "iniData.h"

iniData::iniData()
{
}


iniData::~iniData()
{
}

HRESULT iniData::init()
{
	return S_OK;
}

void iniData::addData(char * section, char * key, char * value)
{
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	//ini������ ����ü ���Ϳ� ���
	arrIniData vIniData;
	vIniData.push_back(iniData);

	//��� �����ʹ� _vIniData�� ����ü�� ���� ���͸� ���
	_vIniData.push_back(vIniData);

}

void iniData::iniSave(char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\save/%s.ini", fileName);

	//GetCurrentDirectory :  ���� ���α׷��� �۾� ��θ� ������ ���
	GetCurrentDirectory(356, str);
	strcat_s(str, dir);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];


		//���Ͽ� ������ ����. ���࿡ �ش� ���ǰ� Ű���� ������ �ڵ����� �����Ѵ�.
		WritePrivateProfileString
		(
			vData[0].section,	//������
			vData[0].key,		//�������
			vData[0].value,		//������ҿ� �ۼ��� ����
			str);				//ini���ϰ��
		vData.clear();
	}
	_vIniData.clear();
}

char * iniData::loadDataString(char * fileName, char * section, char * key)
{

	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\save/%s.ini", fileName);

	GetCurrentDirectory(356, str);
	strcat_s(str, dir);

	char data[64] = { NULL };
	GetPrivateProfileString(
		section,//������
		key,	//Ű��
		"",		//�����̸��̳� Ű�̸��� ã�� ���ϸ� ����Ʈ�� ����� ��Ʈ��
		data,	//Ű������ ����Ű�� ���� ������ ����
		64,		//Ű���� ������ ���� ������
		str);	//���

	return data;
}

int iniData::loadDataIntrger(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\save/%s.ini", fileName);

	//
	GetCurrentDirectory(256, str);
	strcat_s(str, dir);
	//INI���Ϸκ��� �б�     //����	 Ű   ����Ʈ  ���ϸ�
	return GetPrivateProfileInt(section, key, 0, str);
}

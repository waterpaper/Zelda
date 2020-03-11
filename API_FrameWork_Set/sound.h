#pragma once

//fmode
#include "inc/fmod.h"
#pragma  comment( lib, "fmodL64_vc.lib" )

//ä�ι��ۿ� ���� ����
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 100
#define EFFEXTRACHANNELBUFFER 5
#define EFFSOUNDBUFFER 100

//���۰� �۾Ƽ� ������ ������ �ؼ��ϱ� ����
#define TOTALSOUNDBUFFER EXTRACHANNELBUFFER+SOUNDBUFFER
#define TOTALEFFSOUNDBUFFER EFFEXTRACHANNELBUFFER+EFFSOUNDBUFFER

/*
fmod
���带 �÷����ϱ� ���� �����ִ� ���̺귯��
�����ϰ� ��밡���ϰ� �����ϴ� Ȯ���ڰ� ���Ƽ� ���� �����
*/

//===============================================
//FOMD ��������
//===============================================
static FMOD_SYSTEM *g_pSystem;				//fmod�� �ý���
static FMOD_SOUND **g_pSound;				//����Ŭ����
static FMOD_CHANNEL **g_pChannel;			//ä�� Ŭ����

static FMOD_SYSTEM *effg_pSystem;
static FMOD_SOUND **effg_pSound;
static FMOD_CHANNEL **effg_pChannel;

class sound
{
private:
	typedef map<string, FMOD_SOUND**> arrSounds;
	typedef map<string, FMOD_SOUND**>::iterator arrSoundIter;

	arrSounds m_totalBgmSounds; //�ʿ� ��� ��� ���� ���
	arrSounds m_totalEffSounds; //�ʿ� ��� ȿ���� ���� ���

	float _bgmVolume;
	float _effVolume;

public:
	sound();
	~sound();

	void init();
	void update();
	void release();
	
	//��� ���� �߰�
	void addBgmSound(string keyName, string soundName, bool loop);
	//���� �÷���
	void soundPlay(string keyName);
	//����
	void soundOff();
	//���� ����
	void soundOff(string keyName);
	//�Ͻ�����
	void pause(string keyName);
	//�ٽ����
	void resume(string keyName);
	//�÷��� ������
	bool isPlaySound(string keyName);
	//�Ͻ����� ������
	bool isPauseSound(string keyName);

	//ȿ���� �߰�
	void addEffSound(string keyName, string soundName, bool loop);
	//ȿ���� �� ����
	void effSoundOff();
	//ȿ���� ���� ����
	void effSoundOff(string keyName);
	//ȿ���� ���
	void effSoundPlay(string keyName);
	//�Ͻ�����
	void effPause(string keyName);
	//�ٽ����
	void effResume(string keyName);
	//�÷��� ������
	bool effIsPlaySound(string keyName);
	//�Ͻ����� ������
	bool effIsPauseSound(string keyName);

	void addSound();

	float getBgmVolume() { return _bgmVolume; };
	float getEffVolume() { return _effVolume; };
	void setBgmVolume(float bgmVolume) { _bgmVolume = bgmVolume; };
	void setEffVolume(float effVolume) { _effVolume = effVolume; };
};
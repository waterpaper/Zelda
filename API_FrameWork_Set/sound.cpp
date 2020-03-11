#include"stdafx.h"
#include "sound.h"

sound::sound()
{
}


sound::~sound()
{
}

void sound::init()
{
	//FMOD��� �ʱ�ȭ
	FMOD_System_Create(&g_pSystem);
	FMOD_System_Init(g_pSystem, TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	FMOD_System_Create(&effg_pSystem);
	FMOD_System_Init(effg_pSystem, TOTALEFFSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//���� ä�� �Ҵ�
	g_pSound = new FMOD_SOUND *[TOTALSOUNDBUFFER];
	g_pChannel = new FMOD_CHANNEL *[TOTALSOUNDBUFFER];
	effg_pSound = new FMOD_SOUND *[TOTALEFFSOUNDBUFFER];
	effg_pChannel = new FMOD_CHANNEL *[TOTALEFFSOUNDBUFFER];

	memset(g_pSound, 0, sizeof(FMOD_SOUND*)*(TOTALSOUNDBUFFER));
	memset(g_pChannel, 0, sizeof(FMOD_CHANNEL*)*(TOTALSOUNDBUFFER));
	memset(effg_pSound, 0, sizeof(FMOD_SOUND*)*(TOTALEFFSOUNDBUFFER));
	memset(effg_pChannel, 0, sizeof(FMOD_CHANNEL*)*(TOTALEFFSOUNDBUFFER));

	//���� �ʱ�ȭ
	_bgmVolume = 0.8f;
	_effVolume = 1.0f;

	addSound();
}

void sound::update()
{
	FMOD_System_Update(g_pSystem);
	FMOD_System_Update(effg_pSystem);
}

void sound::release()
{
	soundOff();
	FMOD_Sound_Release(*g_pSound);
	FMOD_Channel_Stop(*g_pChannel);
	FMOD_System_Release(g_pSystem);
	FMOD_System_Close(g_pSystem);
	
	effSoundOff();
	FMOD_Sound_Release(*effg_pSound);
	FMOD_Channel_Stop(*effg_pChannel);
	FMOD_System_Release(effg_pSystem);
	FMOD_System_Close(effg_pSystem);
	
	/*
	fmod���� 3d���� ������ 
	3d���� �Ÿ��� ���� ����
	set3DminMaxDistance
	*/
}

void sound::addBgmSound(string keyName, string soundName, bool loop = FALSE)
{	
	if (loop)
	{
		FMOD_System_CreateStream(g_pSystem, soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &g_pSound[m_totalBgmSounds.size()]);
	}
	else
	{
		FMOD_System_CreateStream(g_pSystem, soundName.c_str(), FMOD_DEFAULT, nullptr, &g_pSound[m_totalBgmSounds.size()]);
	}

	m_totalBgmSounds.insert(make_pair(keyName, &g_pSound[m_totalBgmSounds.size()]));
}

void sound::soundPlay(string keyName)
{
	if (!_isSound) return;

	int count = 0;
	arrSoundIter iter = m_totalBgmSounds.begin();
	//ä�ο��� �÷��� �ؾ��ϴ� ī��Ʈ ������.
	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//����� ���
			FMOD_System_PlaySound(g_pSystem, *iter->second, 0, 0, &g_pChannel[count]);
			FMOD_Channel_SetVolume(g_pChannel[count], _bgmVolume);
		}
	}
	//m_totalBgmSounds.insert(make_pair(keyName, &g_pSound[m_totalBgmSounds.size()]));
}

void sound::soundOff()
{
	int count = 0;
	arrSoundIter iter = m_totalBgmSounds.begin();
	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		FMOD_Channel_Stop(g_pChannel[count]);
	}
}

void sound::soundOff(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalBgmSounds.begin();
	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_Stop(g_pChannel[count]);
		}
	}
}

void sound::pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalBgmSounds.begin();

	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_SetPaused(g_pChannel[count],true);
		}
	}
}

void sound::resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalBgmSounds.begin();

	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_SetPaused(g_pChannel[count], false);
		}
	}
}

bool sound::isPlaySound(string keyName)
{
	int count = 0;
	FMOD_BOOL isPlay;
	arrSoundIter iter = m_totalBgmSounds.begin();

	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_IsPlaying(g_pChannel[count], &isPlay);
		}
	}

	return isPlay;
}

bool sound::isPauseSound(string keyName)
{
	int count = 0;
	FMOD_BOOL isPause;

	arrSoundIter iter = m_totalBgmSounds.begin();

	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_GetPaused(g_pChannel[count], &isPause);
		}
	}

	return isPause;
}

void sound::addEffSound(string keyName, string soundName, bool loop)
{
	if (loop)
	{
		FMOD_System_CreateStream(effg_pSystem, soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &effg_pSound[m_totalEffSounds.size()]);
	}
	else
	{
		FMOD_System_CreateStream(effg_pSystem, soundName.c_str(), FMOD_DEFAULT, nullptr, &effg_pSound[m_totalEffSounds.size()]);
	}

	m_totalEffSounds.insert(make_pair(keyName, &effg_pSound[m_totalEffSounds.size()]));
}

void sound::effSoundOff()
{
	int count = 0;
	arrSoundIter iter = m_totalEffSounds.begin();
	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		FMOD_Channel_Stop(effg_pChannel[count]);
	}
}

void sound::effSoundOff(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalEffSounds.begin();
	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_Stop(effg_pChannel[count]);
		}
	}
}

void sound::effSoundPlay(string keyName)
{
	if (!_isSound) return;

	int count = 0;
	arrSoundIter iter = m_totalEffSounds.begin();
	//ä�ο��� �÷��� �ؾ��ϴ� ī��Ʈ ������.
	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//����� ���
			FMOD_System_PlaySound(effg_pSystem, *iter->second, 0, 0, &effg_pChannel[count]);
			FMOD_Channel_SetVolume(effg_pChannel[count], _effVolume);
		}
	}
}

void sound::effPause(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalEffSounds.begin();

	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_SetPaused(effg_pChannel[count], true);
		}
	}
}

void sound::effResume(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalEffSounds.begin();

	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_SetPaused(effg_pChannel[count], false);
		}
	}
}

bool sound::effIsPlaySound(string keyName)
{
	int count = 0;
	FMOD_BOOL isPlay;
	arrSoundIter iter = m_totalEffSounds.begin();

	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_IsPlaying(effg_pChannel[count], &isPlay);
		}
	}

	return isPlay;
}

bool sound::effIsPauseSound(string keyName)
{
	int count = 0;
	FMOD_BOOL isPause;

	arrSoundIter iter = m_totalEffSounds.begin();

	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_GetPaused(effg_pChannel[count], &isPause);
		}
	}

	return isPause;
}

void sound::addSound()
{
	addBgmSound("Ÿ��Ʋ", "sound/title.mp3", false);
	addBgmSound("����â", "sound/select.mp3", true);
	addBgmSound("��������", "sound/overworld.mp3", true);
	addBgmSound("����", "sound/dungeon.mp3", true);
	addBgmSound("����", "sound/boss_bgm.mp3", true);
	addBgmSound("��","sound/home.mp3",true);
	addBgmSound("����", "sound/ending.mp3", true);


	addEffSound("��","sound/sword.wav",false);
	addEffSound("ȭ��", "sound/arrow.wav", false);
	addEffSound("��ź", "sound/bomb.wav", false);
	addEffSound("�θ޶�", "sound/boomerang.wav", false);
	addEffSound("���", "sound/lift.wav", false);
	addEffSound("����", "sound/link_dies.wav", false);
	addEffSound("ü�¾���", "sound/low_hp.wav", true);
	addEffSound("����", "sound/break.wav", false);
	addEffSound("Ǯ����", "sound/grass_destroyed.wav", false);
	addEffSound("��Ʈ", "sound/heart.wav", false);
	addEffSound("��Ʈ����", "sound/heart_piece.wav", false);
	addEffSound("������", "sound/throw.wav", false);
	addEffSound("�޴�����", "sound/menu_open.wav", false);
	addEffSound("�޴��ݱ�", "sound/menu_close.wav", false);
	addEffSound("������Ʈ", "sound/boss_hit.wav", false);
	addEffSound("��������", "sound/boss_dies.wav", false);
	addEffSound("����", "sound/click.wav", false);

}


#pragma once
class animation
{
private:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;		//������ �÷��� ���

	int _frameNum;						//������ ����
	_vFrameList _frameList;				//������ ��ġ���
	_vPlayList _playList;				//�÷��� ���

	int _frameWidth;					//������ ����ũ��					
	int _frameHeight;					//������ ����ũ��
	bool _loop;


	float _frameUpdateSec;				//������ ������Ʈ 
	float _elapsedSec;					//������ ����ð�
	DWORD _nowPlayIndex;				//���� �÷��� �ε���
	bool _play;							//�÷��� ����


public:
	animation();
	~animation();

	//�ʱ�ȭ(�̹��� ��ü���� ũ��, ����ũ��, �������� ����, ���� ũ��)
	HRESULT init(int totalW, int totalH, int frameW, int frameH);

	//ó������ ������ �ִϸ��̼� ����
	void setDefPlayFrame(bool reverse = false, bool loop = false);
	//�迭�� ����� �ִ� �͸�
	void setPlayFrame(int* playArr, int arrLen, bool loop = false);

	//���۰� �������� ���ؼ�
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	//�ʴ� ����Ƚ��
	void setFPS(int framePerSec);

	//������ ������Ʈ Ÿ��
	void frameUpdate(float elapsedTime);

	void start();//����
	void stop();//����
	void pause();//�Ͻ�����
	void resume();//�ٽ�

	inline bool isPlay() { return _play; }
	
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }

	//�߰� �� �Լ�
	int getFrameIndex() { return _nowPlayIndex; }
	void setFrameIndex(int nowPlayIndex) { _nowPlayIndex = nowPlayIndex; }

	int getFrameNum() { return _frameNum; }
	void setFrameNum(int frameNum) { _frameNum = frameNum; }
};


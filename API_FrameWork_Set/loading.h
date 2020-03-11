#pragma once
#include"gameNode.h"
#include"progressBar.h"

//�ε� �������� ����
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,	//�� ��Ʈ��	�̹���
	LOAD_KIND_IMAGE_1,	//�Ϲ� �̹���
	LOAD_KIND_IMAGE_2,	//�Ϲ��̹���(��ġ��ǥ����)
	LOAD_KIND_FRAMEIMAGE_0,	//������
	LOAD_KIND_FRAMEIMAGE_1,	//�÷���(��ġ ��ǥ ����)
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};
//�̹��� ���ҽ� ����ü
struct tagImageResource
{
	string keyName;			//Ű��
	const char* fileName;	//�����̸�
	int x, y;				//��ġ��ǥ
	int width, height;		//���μ��� ũ��
	int frameX, frameY;		//������ xy
	bool trans;				//��� ���ٲ���
	COLORREF transColor;
};

class loadItem
{
private:

	LOAD_KIND _kind;
	tagImageResource _imageResource;

public:
	loadItem() {}
	~loadItem() {}

	//Ű ������ �� ��Ʈ�� �ʱ�ȭ
	HRESULT initForImage(string keyName, int width, int height);

	//Ű������ �̹��� ���� �ʱ�ȭ
	HRESULT initForImage(string keyname, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//Ű������ ������ �̹��� ���� �ʱ�ȭ
	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//�ε� ������ ����
	LOAD_KIND getLoadingKind() { return _kind; }

	//�̹��� ���ҽ�
	tagImageResource getImageResource() { return _imageResource; }
};

class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;

	arrLoadItem _vLoadItem;
	//�ε�ȭ�鿡�� ����� �̹��� �� �ε���
	image* _background;
	//�ε�ȭ�鿡�� ���
	progressBar* _loadingBar;
	//�ε��� ������
	int _currentGauge;

	int count;
	int index;
	image* _loading;

public:
	loading();
	~loading();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadImage(string keyName, int width, int height);

	void loadImage(string keyName, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//�ε��Ϸ�(�ε� �Ϸ��� ������)
	BOOL loadingDone();

	//�ε� ������ ��������
	vector<loadItem*>getLoadItem() { return _vLoadItem; }

	void loadingAni();
};
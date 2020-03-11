#include"stdafx.h"
#include"mainGame.h"

//---------------------------------------
//�� ���� stdafx�� �����ߴ� ���������� �����մϴ�

//�ν��Ͻ�->�޸𸮻� �Ҵ�Ǿ� �������� ���α׷�
//OS Ȯ���ϱ� ���� ��
HINSTANCE m_hInstance;

//������ �ڵ�(���������δ� 32��Ʈ or 64��Ʈ�� ������)
//��� ���� -> ��󳢸� �����ϱ� ����, ���ڿ����� ������ �ӵ��� ������ ����

//---------------------------------------
//�������� ����
HWND m_hWnd;
POINT m_ptMouse = { 0,0 };

player _player;
sound _sound;
bool _isDebug;
bool _isSound;

//---------------------------------------

mainGame mg;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

/*
WndProc�� �����쿡�� �̷�� ���� ����, �޽����� ó��
*/

//������ �����Լ�
//hInstance : �ν��Ͻ� �ڵ�
//hPrevInstance : ������ ����� �ν��Ͻ� �ڵ�(������ ������� ����)
//lpszCmdParam : ��������� �Էµ� ���α׷� �μ�
//nCmdShow : ���α׷��� ���۵� ����(�ּ�ȭ,����ũ�� ���)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//�ν��ͽ��� m_hInstance(��������) ����ش�
	//���α׷� ��ü�� ��üȭ�� �ּ�, ���α׷� ��ü�� �ڵ�
	m_hInstance = hInstance;

	//�������� ����
	//1. ������â ���� �� ȭ�鿡 ����
	//2. �޼��� ����

	//WNDCLASS : ������ â�� ������ �����ϱ� ���� ����ü
	//������â ����ü ���� �� �ʱ�ȭ
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	//������ Ŭ�������� ����ϰ��� �ϴ� ������ �޸𸮾��� ����Ʈ ������ ����
	wndClass.cbWndExtra = 0;	//cbClsExtra �����ϵ� ���� �����쿡�� ����ϰ��� �ϴ� ������ �޸𸮾��� ����
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ �۾������� ĥ�� ��� �귯�ø� ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//Ŭ���� Ŀ���� ����
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//Ÿ��Ʋ���� �»�ܿ� ������ �����ܰ� �����찡 �ּ�ȭ �Ǿ����� ������ �������� ����
	wndClass.hInstance = hInstance;	//������ Ŭ������ ����� �������α׷��� �ν��Ͻ� �ڵ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;	//�޼����� ó���ϴ� �Լ��� ����(������ ���ν���)
	wndClass.lpszClassName = WINNAME;	//����ϰ��� �ϴ� ������ Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;			//Ŭ�����κ��� ������� �����찡 ����� �޴��� ����
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//������ Ŭ������ ��Ÿ���� ����

												//������ Ŭ���� ���
												//����� ������ Ŭ������ Ư���� �����ϴ� WNDCLASS ����ü�� ������ ����
	RegisterClass(&wndClass);

	//������ â ����
	m_hWnd = CreateWindow(
		WINNAME,		//������ Ŭ������ �̸�
		WINNAME,		//������ Ÿ��Ʋ�� �̸�
		WS_OVERLAPPEDWINDOW,//������ ��Ÿ��
		0,				//������ ȭ���� x��ǥ
		0,				//������ ȭ���� y��ǥ
		WINSIZEX,				//������ ȭ���� ����ũ��
		WINSIZEY,				//������ ȭ���� ����ũ��
		NULL,				//�θ�������
		(HMENU)NULL,		//�޴��ڵ�
		hInstance,			//�ν��Ͻ� ����
		NULL);				//������� ����

							//ȭ�鿡 ������ �����ֱ�


	//ȭ�� �۾� ������ ���� ���
	setWindowSize(0, 0, WINSIZEX, WINSIZEY);
	ShowWindow(m_hWnd, nCmdShow);

	//���ΰ��� Ŭ������ �ʱ�ȭ�� �����ϸ� ����
	if (FAILED(mg.init()))
	{
		return 0;
	}

	//MSG : �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü
	MSG message;

	//TranslateMessage : Ű���� �Է¸޼����� ó�� ���
	//WM_CHAR �޼����� �߻���Ų��.

	//DispatchMessage : ������ ���ν����� ���޵� �޼����� ���� ������� �������ش�.

	//GetMessage : ������
	/*�޽��� ����
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);//Ű���� �ԷµǴ� ���� �޽��� ó��
		DispatchMessage(&message);//������ ������� �޽����� �������ִ� ����
	}
	//�޽��� ������ �� ���Ҵٸ� ����
	*/

	/*
		getMessage�� PeekMessage �� �Լ� ��� winMain���� �޼���ť�� ����
		�޼����� �����ϴ� �Լ�.
		getMessage�Լ��� �޼���ť�� �޼����� ������ �׳� �״�� ��ȯ���� ��ȯ����
		�ʰ� �״�� �����·� �ִٰ� �޼����� ����� �ش� �޼����� �����ϰ� ��ȯ
		������ 1�� ������.
		���� �޼����� ������ �׻� 1�� �����ϴ� ���� �ƴϰ� WM_QUIT �޼����� �߻�
		������� 0�� �����Ѵ�.


		�׿� ���� PeekMessage�Լ���  getMessage�� �ٸ���
		�������Ӹ��� �Լ��� ����Ǹ� �޼��� ť�� �˻��ϰ� �׻� ��ȯ������ 1�� ��ȯ�Ѵ�.
		�� ��� ���°� ����.
		�� �����Ӹ��� �Լ��� ����ǰ� �޼��� ť�� �˻��ϰ� �޼����� �ֵ� ���� �׻� 1��
		��ȯ�Ѵٴ� ��.
	*/

	//���ӿ� ����
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{	//�ʴ� 60���������� ������Ʈ �ض�
			TIMEMANAGER->update(60.0f);
			mg.update();
			mg.render();
		}
	}

	mg.release();
	return message.wParam;

}

//������ ���ν��� : �޼����� �ü���� ���� ������ �ü���� ȣ�����ش�.
//hWnd : ��� �����쿡�� �߻��� �޼������� ����
//iMessage : �޼��� ���� ��ȣ
//wParam : unsigned int ���콺 ��ư�� ����, Ű���� ����Ű�� ���¸� �����Ѵ�.
//lParam : unsigned long ���콺 Ŭ�� ��ǥ�� ����
//CALLBACK �Լ��� � �̺�Ʈ�� �߻� ���� �� ������ �˷��޶�� �ϴ� ��!(�� ȣ�� �Ǵ� ���̶�� ������)
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return mg.MainProc(hWnd, iMessage, wParam, lParam);

}

//=================================================================
//	## ������ ũ�� ���� ## (Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�)
//=================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect(&rc, WINSTYLE, false);

	//�� RECT ������ ������ ������ ����
	SetWindowPos(m_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}

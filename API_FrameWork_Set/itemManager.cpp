#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	_item = new item;
	_item->init();

	return S_OK;
}

void itemManager::release()
{
	if (_item != nullptr)
	{
		_item->release();
	}
}

void itemManager::update()
{
	_item->update();
}

void itemManager::render(HDC hdc)
{
	_item->render(hdc);
}


void itemManager::dropRandItem(int x, int y)
{
	tagItem _item1;
	ZeroMemory(&_item1, sizeof(tagItem));

	int dropRand = RND->getInt(4);
	switch (dropRand)
	{
	case MONEY:
		_item1.itemImage = IMAGEMANAGER->findImage("��");
		_item1.itemKind = MONEY;
		_item1.itemRc1 = RectMakeCenter(x, y, 18, 36);
		_item1.itemPosition = PointMake(_item1.itemRc1.left + (_item1.itemRc1.right - _item1.itemRc1.left) / 2, _item1.itemRc1.top + (_item1.itemRc1.bottom - _item1.itemRc1.top) / 2);
		_item1.destination = PointMake(x, y - 20);
		_item1.itemUp = true;

		_item->addItem(_item1);
		break;
	case ARROW10:
		_item1.itemImage = IMAGEMANAGER->findImage("ȭ��10��");
		_item1.itemKind = ARROW10;
		_item1.itemRc1 = RectMakeCenter(x, y, 48, 48);
		_item1.itemPosition = PointMake(_item1.itemRc1.left + (_item1.itemRc1.right - _item1.itemRc1.left) / 2, _item1.itemRc1.top + (_item1.itemRc1.bottom - _item1.itemRc1.top) / 2);
		_item1.destination = PointMake(x, y - 20);
		_item1.itemUp = true;

		_item->addItem(_item1);
		break;
	case LIFE:
		_item1.itemImage = IMAGEMANAGER->findImage("ü�¾�����");
		_item1.itemKind = LIFE;
		_item1.itemRc1 = RectMakeCenter(x, y, 27, 24);
		_item1.itemPosition = PointMake(_item1.itemRc1.left + (_item1.itemRc1.right - _item1.itemRc1.left) / 2, _item1.itemRc1.top + (_item1.itemRc1.bottom - _item1.itemRc1.top) / 2);
		_item1.destination = PointMake(x, y - 20);
		_item1.itemUp = true;

		_item->addItem(_item1);
		break;
	default:
		break;
	}

}

//hp������ Ȯ���� ����

void itemManager::dropHpItem(int x, int y, int dropPercentage)
{
	tagItem _item1;
	ZeroMemory(&_item1, sizeof(tagItem));

	int a = RND->getInt(99);

	if (a <= dropPercentage - 1)
	{
		_item1.itemImage = IMAGEMANAGER->findImage("ü�¾�����");
		_item1.itemKind = LIFE;
		_item1.itemRc1 = RectMakeCenter(x, y, 27, 24);
		_item1.itemPosition = PointMake(_item1.itemRc1.left + (_item1.itemRc1.right - _item1.itemRc1.left) / 2, _item1.itemRc1.top + (_item1.itemRc1.bottom - _item1.itemRc1.top) / 2);
		_item1.destination = PointMake(x, y - 20);
		_item1.itemUp = true;

		_item->addItem(_item1);
	}

}

//�ִ� ü�� ���� ������ ����
void itemManager::dropMaxHp(int x, int y)
{
	tagItem _item1;
	ZeroMemory(&_item1, sizeof(tagItem));

	_item1.itemImage = IMAGEMANAGER->findImage("�ִ�ü��");
	_item1.itemKind = HPMAXUP;
	_item1.itemRc1 = RectMakeCenter(x, y, 52, 45);
	_item1.itemPosition = PointMake(_item1.itemRc1.left + (_item1.itemRc1.right - _item1.itemRc1.left) / 2, _item1.itemRc1.top + (_item1.itemRc1.bottom - _item1.itemRc1.top) / 2);
	_item1.destination = PointMake(x, y - 20);
	_item1.itemUp = true;

	_item->addItem(_item1);

}

//�ִ� ü�� ���� ������ ����
void itemManager::dropKey(int x, int y)
{
	tagItem _item1;
	ZeroMemory(&_item1, sizeof(tagItem));

	_item1.itemImage = IMAGEMANAGER->findImage("����");
	_item1.itemKind = KEY;
	_item1.itemRc1 = RectMakeCenter(x, y, 24, 30);
	_item1.itemPosition = PointMake(_item1.itemRc1.left + (_item1.itemRc1.right - _item1.itemRc1.left) / 2, _item1.itemRc1.top + (_item1.itemRc1.bottom - _item1.itemRc1.top) / 2);
	_item1.destination = PointMake(x, y - 20);
	_item1.itemUp = true;

	_item->addItem(_item1);

}

//�� Ȯ���� ����
void itemManager::dropMoneyItem(int x, int y, int dropPercentage)
{
	tagItem _item1;
	ZeroMemory(&_item1, sizeof(tagItem));

	int a = RND->getInt(99);

	if (a <= dropPercentage - 1)
	{
		_item1.itemImage = IMAGEMANAGER->findImage("��");
		_item1.itemKind = MONEY;
		_item1.itemRc1 = RectMakeCenter(x, y, 18, 36);
		_item1.itemPosition = PointMake(_item1.itemRc1.left + (_item1.itemRc1.right - _item1.itemRc1.left) / 2, _item1.itemRc1.top + (_item1.itemRc1.bottom - _item1.itemRc1.top) / 2);
		_item1.destination = PointMake(x, y - 20);
		_item1.itemUp = true;

		_item->addItem(_item1);
	}
}

//���ϴ� �Ҵ�Ʈ ���
void itemManager::dropPendent(int x, int y, ITEM pendentColor)
{
	tagItem _item1;
	ZeroMemory(&_item1, sizeof(tagItem));

	if (pendentColor == GREENPENDENT)
	{
		_item1.itemImage = IMAGEMANAGER->findImage("����Ҵ�Ʈ");
		_item1.itemKind = GREENPENDENT;
		_item1.itemRc1 = RectMakeCenter(x, y, 18, 36);
		_item1.itemPosition = PointMake(_item1.itemRc1.left + (_item1.itemRc1.right - _item1.itemRc1.left) / 2, _item1.itemRc1.top + (_item1.itemRc1.bottom - _item1.itemRc1.top) / 2);
		_item1.destination = PointMake(x, y - 20);
		_item1.itemUp = true;

		_item->addItem(_item1);
	}
	if (pendentColor == REDPENDENT)
	{
		_item1.itemImage = IMAGEMANAGER->findImage("�������Ҵ�Ʈ");
		_item1.itemKind = REDPENDENT;
		_item1.itemRc1 = RectMakeCenter(x, y, 18, 36);
		_item1.itemPosition = PointMake(_item1.itemRc1.left + (_item1.itemRc1.right - _item1.itemRc1.left) / 2, _item1.itemRc1.top + (_item1.itemRc1.bottom - _item1.itemRc1.top) / 2);
		_item1.destination = PointMake(x, y - 20);
		_item1.itemUp = true;

		_item->addItem(_item1);
	}
	if (pendentColor == BLUEPENDENT)
	{
		_item1.itemImage = IMAGEMANAGER->findImage("�Ķ����Ҵ�Ʈ");
		_item1.itemKind = BLUEPENDENT;
		_item1.itemRc1 = RectMakeCenter(x, y, 18, 36);
		_item1.itemPosition = PointMake(_item1.itemRc1.left + (_item1.itemRc1.right - _item1.itemRc1.left) / 2, _item1.itemRc1.top + (_item1.itemRc1.bottom - _item1.itemRc1.top) / 2);
		_item1.destination = PointMake(x, y - 20);
		_item1.itemUp = true;

		_item->addItem(_item1);
	}
}

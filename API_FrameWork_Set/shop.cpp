#include "stdafx.h"
#include "shop.h"


shop::shop()
{
}


shop::~shop()
{
}

HRESULT shop::init()
{
	tagShopItem sItem;
	ZeroMemory(&sItem, sizeof(tagShopItem));

	sItem.itemImage = IMAGEMANAGER->findImage("Ȱ");
	sItem.itemKind = BOW;
	sItem.price = 30;
	sItem.num = 0;
	_vSItem.push_back(sItem);

	sItem.itemImage = IMAGEMANAGER->findImage("�θ޶�");
	sItem.itemKind = BOOMERANG;
	sItem.price = 50;
	sItem.num = 1;
	_vSItem.push_back(sItem);

	sItem.itemImage = IMAGEMANAGER->findImage("��ź10��");
	sItem.itemKind = BOMB;
	sItem.price = 40;
	sItem.num = 2;
	_vSItem.push_back(sItem);

	sItem.itemImage = IMAGEMANAGER->findImage("ü��MAX");
	sItem.itemKind = HPMAX;
	sItem.price = 20;
	sItem.num = 3;
	_vSItem.push_back(sItem);

	sItem.itemImage = IMAGEMANAGER->findImage("ȭ��10��");
	sItem.itemKind = SHOPARROW10;
	sItem.price = 20;
	sItem.num = 4;
	_vSItem.push_back(sItem);

	randomSetting();


	npc = RectMakeCenter(WINSIZEX / 2, 310, 42, 66);
	shopNpc = IMAGEMANAGER->findImage("��������");
	_index = 0;
	_count = 0;
	return S_OK;
}

void shop::release()
{
	vector<tagShopItem>::iterator eIter = _vSItem.begin();
	for (eIter; eIter != _vSItem.end();)
	{
		//SAFE_DELETE((eIter));
		eIter = _vSItem.erase(eIter);
	}

}

void shop::update()
{
	buyItem();
	collision();

	_count++;
	shopNpc->setFrameY(0);
	if (_count % 12 == 0)
	{
		_index++;
		if (_index > shopNpc->getMaxFrameX())
		{
			_index = 0;
		}
		shopNpc->setFrameX(_index);
	}
}

void shop::render(HDC hdc)
{
	string numberTemp;
	image *numberImageTemp;
	int frameNumXTemp;
	numberImageTemp = IMAGEMANAGER->findImage("����");

	for (_viSItem = _vSItem.begin(); _viSItem != _vSItem.end(); ++_viSItem)
	{
		//���õ� �����۸� �׸���
		if (_viSItem->num == setItem || _viSItem->num == setItem1 || _viSItem->num == setItem2)
		{
			//����������
			_viSItem->itemImage->render(hdc, _viSItem->itemRc1.left, _viSItem->itemRc1.top);

			//���������� ����ǥ
			char str[128];
			numberTemp = to_string(_viSItem->price);
			for (int i = numberTemp.size() - 1; i >= 0; i--)
			{
				frameNumXTemp = numberTemp[i] - '0';
				numberImageTemp->frameRender(hdc, _viSItem->itemRc1.left + 21 * i, _viSItem->itemRc1.bottom + 10, frameNumXTemp, 0);
			}
		}
		if (_isDebug)
		{
			//Rectangle(hdc, _viSItem->itemRc2.left, _viSItem->itemRc2.top, _viSItem->itemRc2.right, _viSItem->itemRc2.bottom);
			Rectangle(hdc, _viSItem->itemRc1.left, _viSItem->itemRc1.top, _viSItem->itemRc1.right, _viSItem->itemRc1.bottom);
		}
	}

	IMAGEMANAGER->frameRender("��������", hdc, npc.left, npc.top, shopNpc->getFrameX(), shopNpc->getFrameY());
}

void shop::buyItem()
{
	//���������� ����
	for (_viSItem = _vSItem.begin(); _viSItem != _vSItem.end(); )
	{
		RECT temp;   //�÷��̾� ������ �浹											�������� �����۰��ݺ��� ����					sŰ������ ����
		if (IntersectRect(&temp, &_player.getRect(), &_viSItem->itemRc2) && (INVENTORYMANAGER->getMoney() >= _viSItem->price) && KEYMANAGER->isOnceKeyDown('S'))
		{
			INVENTORYMANAGER->setMoney(INVENTORYMANAGER->getMoney() - _viSItem->price);
			//��ź��������
			if (_viSItem->itemKind == BOMB)
			{
				INVENTORYMANAGER->setBomb(INVENTORYMANAGER->getBomb() + 10);
			}
			//ȭ�찹������
			if (_viSItem->itemKind == SHOPARROW10)
			{
				INVENTORYMANAGER->setArrow(INVENTORYMANAGER->getArrow() + 10);
			}
			if (_viSItem->itemKind != SHOPARROW10)
			{
				INVENTORYMANAGER->setIsItem(_viSItem->itemKind, true);
			}
			_viSItem = _vSItem.erase(_viSItem);
			//INVENTORYMANAGER->addItem(Initem1);
		}
		else
		{
			++_viSItem;
		}
	}
}

//���� ������ �÷��̾� �浹
void shop::collision()
{
	POINT _playerPoint = { _player.getPositionX() + 25, _player.getPositionY() + 30 };

	for (_viSItem = _vSItem.begin(); _viSItem != _vSItem.end(); ++_viSItem)
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (PtInRect(&_viSItem->itemRc1, POINT{ _playerPoint.x - (_player.getRect().right - _player.getRect().left) / 2 + 1, _playerPoint.y + (_player.getRect().bottom - _player.getRect().top) / 2 })
				|| (PtInRect(&_viSItem->itemRc1, POINT{ _playerPoint.x + (_player.getRect().right - _player.getRect().left) / 2 - 12, _playerPoint.y + (_player.getRect().bottom - _player.getRect().top) / 2 })))
			{
				_player.setPositionY(_viSItem->itemRc1.top - (_player.getRect().bottom - _player.getRect().top) / 2 - 30);
				_player.setRect(RectMakeCenter(_player.getPositionX() + 25, _player.getPositionY() + 30, (_player.getRect().right - _player.getRect().left), (_player.getRect().bottom - _player.getRect().top)));
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (PtInRect(&_viSItem->itemRc1, POINT{ _playerPoint.x - (_player.getRect().right - _player.getRect().left) / 2,_playerPoint.y - (_player.getRect().bottom - _player.getRect().top) / 2 + 1 })
				|| (PtInRect(&_viSItem->itemRc1, POINT{ _playerPoint.x - (_player.getRect().right - _player.getRect().left) / 2, _playerPoint.y + (_player.getRect().bottom - _player.getRect().top) / 2 - 15 }))
				|| (PtInRect(&_viSItem->itemRc1, POINT{ _playerPoint.x - (_player.getRect().right - _player.getRect().left) / 2, _playerPoint.y })))
			{
				_player.setPositionX(_viSItem->itemRc1.right + (_player.getRect().right - _player.getRect().left) / 2 - 25);
				_player.setRect(RectMakeCenter(_player.getPositionX() + 25, _player.getPositionY() + 30, (_player.getRect().right - _player.getRect().left), (_player.getRect().bottom - _player.getRect().top)));
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (PtInRect(&_viSItem->itemRc1, POINT{ _playerPoint.x + (_player.getRect().right - _player.getRect().left) / 2,_playerPoint.y - (_player.getRect().bottom - _player.getRect().top) / 2 + 1 })
				|| (PtInRect(&_viSItem->itemRc1, POINT{ _playerPoint.x + (_player.getRect().right - _player.getRect().left) / 2, _playerPoint.y + (_player.getRect().bottom - _player.getRect().top) / 2 - 15 }))
				|| (PtInRect(&_viSItem->itemRc1, POINT{ _playerPoint.x + (_player.getRect().right - _player.getRect().left) / 2, _playerPoint.y })))
			{
				_player.setPositionX(_viSItem->itemRc1.left - (_player.getRect().right - _player.getRect().left) / 2 - 25);
				_player.setRect(RectMakeCenter(_player.getPositionX() + 25, _player.getPositionY() + 30, (_player.getRect().right - _player.getRect().left), (_player.getRect().bottom - _player.getRect().top)));
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (PtInRect(&_viSItem->itemRc1, POINT{ _playerPoint.x - (_player.getRect().right - _player.getRect().left) / 2 + 1, _playerPoint.y - (_player.getRect().bottom - _player.getRect().top) / 2 })
				|| (PtInRect(&_viSItem->itemRc1, POINT{ _playerPoint.x + (_player.getRect().right - _player.getRect().left) / 2 - 12, _playerPoint.y - (_player.getRect().bottom - _player.getRect().top) / 2 })))
			{
				_player.setPositionY(_viSItem->itemRc1.bottom + (_player.getRect().bottom - _player.getRect().top) / 2 - 30);
				_player.setRect(RectMakeCenter(_player.getPositionX() + 25, _player.getPositionY() + 30, (_player.getRect().right - _player.getRect().left), (_player.getRect().bottom - _player.getRect().top)));
			}
		}
	}

}

void shop::randomSetting()
{
	//ù��° ����������
	setItem = RND->getInt(SHOPITEMCOUNT - 1);
	for (_viSItem = _vSItem.begin(); _viSItem != _vSItem.end(); ++_viSItem)
	{
		if (_viSItem->num == setItem)
		{
			_viSItem->itemRc1 = RectMakeCenter(230, 440, 47, 47);
			_viSItem->itemRc2 = RectMakeCenter(230, 440, 87, 87);
		}
	}

	//�ι�° ����������
	setItem1 = RND->getInt(SHOPITEMCOUNT - 1);
	for (_viSItem = _vSItem.begin(); _viSItem != _vSItem.end(); ++_viSItem)
	{
		while (1)
		{
			//�Ȱ��� ��ȣ�� ���ý� �ٽõ�����
			if (setItem1 == setItem)
			{
				setItem1 = RND->getInt(3);
			}
			else
			{
				break;
			}
		}
		if (_viSItem->num == setItem1)
		{
			_viSItem->itemRc1 = RectMakeCenter(380, 440, 47, 47);
			_viSItem->itemRc2 = RectMakeCenter(380, 440, 87, 87);
		}
	}
	//����° ����������
	setItem2 = RND->getInt(SHOPITEMCOUNT - 1);
	for (_viSItem = _vSItem.begin(); _viSItem != _vSItem.end(); ++_viSItem)
	{
		while (1)
		{
			//�Ȱ��� ��ȣ�� ���ý� �ٽõ�����
			if (setItem2 == setItem || setItem2 == setItem1)
			{
				setItem2 = RND->getInt(3);
			}
			else
			{
				break;
			}
		}
		if (_viSItem->num == setItem2)
		{
			_viSItem->itemRc1 = RectMakeCenter(530, 440, 47, 47);
			_viSItem->itemRc2 = RectMakeCenter(530, 440, 87, 87);
		}
	}

}

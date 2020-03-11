#include "stdafx.h"
#include "inventoryManager.h"


inventoryManager::inventoryManager()
{
}


inventoryManager::~inventoryManager()
{
}

HRESULT inventoryManager::init()
{
	_shop = RectMake(30, -610, 453, 360);
	_inven = RectMake(510, -610, 230, 360);

	_inventory = new inventory();
	_inventory->init(_shop);

	_selectRc = RectMake(_inventory->getInvenRc(0, 0).left - 22, _inventory->getInvenRc(0, 0).top - 23, 80, 80);

	_count = 0;
	_index = 0;

	_invenX = 0;
	_invenY = 0;

	_money = 100;
	_bomb = 0;
	_arrow = 0;
	_key = 0;

	_invenUp = false;	//�κ��� ����
	_invenDown = false; //�κ� ������
	
	greenPendent = false;
	redPendent = false;
	bluePendent = false;

	_selectImage = IMAGEMANAGER->findImage("����");
	_greenPendent = IMAGEMANAGER->findImage("����Ҵ�Ʈ");

	_nowItem = ITEMNULL;

	return S_OK;
}

void inventoryManager::update()
{
	_selectX = _selectRc.left + (_selectRc.right - _selectRc.left) / 2;
	_selectY = _selectRc.top + (_selectRc.bottom - _selectRc.top) / 2;

	_inventory->update();

	int i = _invenX;
	int count = 0, maxcount = _inventory->getInItem().size();
	if (!_isInventory&&KEYMANAGER->isOnceKeyDown('R'))
	{
		_sound.effSoundPlay("�޴�����");
		//�κ�â Ű�����
		_isInventory = !_isInventory;
	}

	if (_isInventory)
	{
		if (greenPendent == true)
		{
		}
		if (KEYMANAGER->isOnceKeyDown('R'))
		{
			_sound.effSoundPlay("�޴��ݱ�");
			_invenUp = true;
			_invenDown = false;
		}
		if (_invenUp)
		{
			if (_shop.top > -610)
			{
				_shop.top -= INVENSPEED;
				_shop.bottom -= INVENSPEED;

				_inven.top -= INVENSPEED;
				_inven.bottom -= INVENSPEED;
			}
			if (_shop.top <= -610)
			{
				_shop.top = -610;
				_shop.bottom = _shop.top + 360;
				_isInventory = false;
				_invenUp = false;
			}
		}

		else
		{
			if (_shop.top <= 50)
			{
				_shop.top += INVENSPEED;
				_shop.bottom += INVENSPEED;

				_inven.top += INVENSPEED;
				_inven.bottom += INVENSPEED;
			}
			if (_shop.top > 50)
			{
				_shop.top = 50;
				_shop.bottom = _shop.top + 360;

				_inven.top = 50;
				_inven.bottom = _inven.top + 360;

				_invenDown = true;

			}
		}
		if (_invenDown&&KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			moveSelect();
		}

		_count++;
		_selectImage->setFrameY(0);
		if (_count % 18 == 0)
		{
			_count = 0;
			_index++;
			if (_index > _selectImage->getMaxFrameX())
			{
				_index = 0;
			}
			_selectImage->setFrameX(_index);
		}
	}
	//�κ�ĭ�� �κ�â�� �Բ� �����̱�
	_inventory->getInvenRc(_shop);
}

void inventoryManager::release()
{
	_inventory->release();
	greenPendent = false;
	redPendent = false;
	bluePendent = false;
	_arrow = 0;
	_bomb = 0;
	_money = 100;
	_key = 0;
	_nowItem = ITEMNULL;

}

void inventoryManager::render(HDC hdc)
{
	if (_isInventory)
	{
		IMAGEMANAGER->render("����", hdc, _shop.left, _shop.top);
		IMAGEMANAGER->render("�κ��丮", hdc, _inven.left, _inven.top);
		if (_invenDown)
		{
			if (_inventory->getIsItem(BOW) || _inventory->getIsItem(BOOMERANG) || _inventory->getIsItem(BOMB) || _inventory->getIsItem(HPMAX))
			{
				IMAGEMANAGER->frameRender("����", hdc, _selectRc.left, _selectRc.top, _selectImage->getFrameX(), _selectImage->getFrameY());
			}
		}
		if (_nowItem == BOW)
		{
			IMAGEMANAGER->render("ȭ���Ȱ", hdc, _inven.left + 22, _inven.top + 12);
		}
		if (_nowItem == BOOMERANG)
		{
			IMAGEMANAGER->render("�θ޶�����", hdc, _inven.left + 32, _inven.top + 12);
		}
		if (_nowItem == BOMB)
		{
			IMAGEMANAGER->render("��ź����", hdc, _inven.left + 22, _inven.top + 12);
		}
		if (_nowItem == HPMAX)
		{
			IMAGEMANAGER->render("��������", hdc, _inven.left + 22, _inven.top + 12);
		}
		if (greenPendent)
		{
			IMAGEMANAGER->render("����Ҵ�Ʈ", hdc, _inven.left + 34, _inven.bottom - 84);
		}
		if (redPendent)
		{
			IMAGEMANAGER->render("�������Ҵ�Ʈ", hdc, _inven.left + 88, _inven.bottom - 156);
		}
		if (bluePendent)
		{
			IMAGEMANAGER->render("�Ķ����Ҵ�Ʈ", hdc, _inven.left + 148, _inven.bottom - 84);
		}
		_inventory->render(hdc);
	}
}

void inventoryManager::addItem(int itemkind)
{
	_inventory->addItem((SHOPITEM)itemkind);
}

void inventoryManager::addItem(tagInvenItem item)
{
	_inventory->addItem(item);
}

void inventoryManager::moveSelect()
{
	_invenX++;

	int count = 0, maxcount = _inventory->getInItem().size();

	while (1)
	{
		int i = _invenX + _invenY * 5;

		if (_invenX > 4)
		{
			_invenX = 0;
			_invenY++;
			if (_invenY > 3)
			{
				_invenY = 0;
			}
		}
		if (count == maxcount)
		{
			break;
		}
		if (i >= maxcount)
		{
			i = 0;
			_invenX = 0;
			_invenY = 0;
		}

		if (_inventory->getIsItem((SHOPITEM)i))
		{
			_selectRc = RectMake(_inventory->getInvenRc(_invenX, _invenY).left - 22, _inventory->getInvenRc(_invenX, _invenY).top - 23, 80, 80);
			_nowItem = (SHOPITEM)i;
			break;
		}
		else
		{
			count++;
			_invenX++;
			//i++;
		}
	}
}
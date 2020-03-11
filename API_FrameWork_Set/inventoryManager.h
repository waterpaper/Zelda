#pragma once
#include"singletonBase.h"
#include"inventory.h"

#define INVENSPEED 20

class inventoryManager : public singletonBase<inventoryManager>
{
private:

	//�κ� ����������
	image* _bowInfo;
	image* _boomerangInfo;
	image* _bombInfo;
	image* _LifeInfo;

	image* _greenPendent;

	//�κ�âui
	image* _shopPage;
	image* _invenPage;
	//�����̹���
	image* _selectImage;
	//animation* _selectAni;
	//�κ�â ����
	RECT _shop;
	RECT _inven;

	//���û���
	RECT _selectRc;

	int _money;
	int _bomb;
	int _arrow;
	int _key;

	bool _isInventory;
	bool _invenUp;
	bool _invenDown;

	bool greenPendent;
	bool redPendent;
	bool bluePendent;

	int _count;
	int _index;

	int _invenX;
	int _invenY;

	inventory* _inventory;

	int _xIndex;
	int _yIndex;

	int _selectX, _selectY;

	SHOPITEM _nowItem;				//���� ���������� ���� ����

public:
	inventoryManager();
	~inventoryManager();

	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);

	void addItem(int itemkind);
	void addItem(tagInvenItem item);

	RECT getShopRc(int x, int y) { return _inventory->getInvenRc(y, x); };

	bool getIsItem(SHOPITEM item) { return _inventory->getIsItem(item); };
	void setIsItem(SHOPITEM item, bool set) { _inventory->setIsItem(item, set); };
	//�κ�â�� �ִ�.
	bool getIsInventory() { return _isInventory; };


	//��
	int getMoney() { return _money; };
	void setMoney(int money) { _money = money; };
	//��ź ����
	int getBomb() { return _bomb; };
	void setBomb(int bomb) { _bomb = bomb; };
	//ȭ�� ����
	int getArrow() { return _arrow; };
	void setArrow(int arrow) { _arrow = arrow; };
	//���� ��������
	int getKey() { return _key; };
	void setKey(int key) { _key = key; };


	RECT getInven() { return _inven; };

	//�κ������� ���ÿ�����
	void moveSelect();

	//��������� ������
	SHOPITEM getNowItem() { return _nowItem; };
	void setNowItem(SHOPITEM nowItem) { _nowItem= nowItem; };

	//�κ������� ���� ��ǥ
	POINT getSlectPosition() { return POINT{ _selectX,_selectY }; };
	int getSlectPositionX() { return _selectX; };
	int getSlectPositionY() { return _selectY; };

	void setSlectPosition(int x, int y) { _selectX = x, _selectY = y; };
	void setSlectPositionX(int x) { _selectX = x; };
	void setSlectPositionY(int y) { _selectY = y; };

	bool getGreenPendent() { return greenPendent; };
	void setGreenPendent(bool __greenPendent) { greenPendent = __greenPendent; };

	bool getRedPendent() { return redPendent; };
	void setRedPendent(bool __redPendent) { redPendent = __redPendent; };

	bool getBluePendent() { return bluePendent; };
	void setBluePendent(bool __bluePendent) { bluePendent = __bluePendent; };
};


#pragma once
#include "singletonBase.h"
#include "playerInteractionObject.h"
#include "agahnim_bolt.h"
#include "agahnim_bubble.h"
#include "agahnim_smallbubble.h"

class equipment;
class equipmentManager : public singletonBase<equipmentManager>
{
private:
	typedef vector<equipment*> vEquipment;
	vEquipment _equipVector;

	int _startTime;
	bool _isBoom; // ���߿��� üũ

	bool _isInteractionObject;		//��ȣ�ۿ� ������Ʈ�� ������ �ִ��� ����
	bool _isFireInteractionObject;		//��ȣ�ۿ� ������Ʈ�� �߻��ϴ��� ����


public:
	void addEquipment(equipment* equipment) { _equipVector.push_back(equipment); }
	vEquipment getEquipmentVector() { return _equipVector; }
public:
	virtual HRESULT init();
	virtual void render(HDC hdc);
	virtual void release();
	virtual void update();
	void FireEquipment(EQUIPMENT_KIND kind, POINT position, float angle, float speed, bool isPlayer);
	equipmentManager();
	virtual ~equipmentManager();


	bool getIsBoom() { return _isBoom; }
	bool getIsInteractionObject() { return _isInteractionObject; };
	bool getIsFireInteractionObject() {return _isFireInteractionObject;};
	void setIsInteractionObject(bool isInteractionObject) { _isInteractionObject = isInteractionObject; };
	void setIsFireInteractionObject(bool isFireInteractionObject) { _isFireInteractionObject = isFireInteractionObject; };
	void setIsInteractionObject(bool isInteractionObject, POINT position, INTERACTIONOBJECT obj);
	void setIsFireInteractionObject(bool isFireInteractionObject, float angle);

	void isActiveOff();
};


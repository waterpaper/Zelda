#pragma once

//����(EX ������ ���带 ���� �ϰų� �̵��� �� ���� ���� ���)
enum TERRAIN
{
	TR_NONE, TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//������Ʈ(EX �������ʿ� ��ġ, �÷��̾��� �̵��� �����ϴ� ����)
enum OBJECT
{
	OBJ_NONE,
	OBJ_BLOCK,
	OBJ_DOOR,
	OBJ_BLOCKS,
	OBJ_END
};
//��ȣ�ۿ� ������Ʈ(Ÿ���� ũ��ʹ� �ٸ��� �÷��̾�� ��ȣ�ۿ��ϰ� �����̴� ��ü)
enum INTERACTIONOBJECT
{
	INTERACTIONOBJ_NONE,
	INTERACTIONOBJ_GRASS,
	INTERACTIONOBJ_SMALLROCK,
	INTERACTIONOBJ_LADDER,
	INTERACTIONOBJ_BIGTREASUREBOX,
	INTERACTIONOBJ_TREASUREBOX,
	INTERACTIONOBJ_JAR,
	INTERACTIONOBJ_ROCKEDDOOR,
	INTERACTIONOBJ_OPENDOOR,
	INTERACTIONOBJ_END
};
//��ġ ��ǥ
enum POS
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

//Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	image *terrainImg, *objImg;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;

	int terrainImageNum;
	int objImageNum;
};

struct tagInteractionObject
{
	INTERACTIONOBJECT obj;
	image *_img;
	RECT _rc;

	//�ʿ����� Ÿ�� ��ǥ��
	int xPos;
	int yPos;

	//�⺻������ ������ �ִ� Ÿ��ũ��
	int widthPos;
	int heightPos;

	int imageNum;
};

class tileMap
{
	/*
	1���� Ÿ�ϸ�(���� ������Ʈ ����)�� ���� Ŭ�����Դϴ�
	���Ϳ� �� �������� �����͸� �����ϰ� ����մϴ�
	*/
private:
	int _mapSizeX;
	int _mapSizeY;

	vector<vector<tagTile>> _map;
	vector<tagInteractionObject> _interactionObject;

public:
	tileMap();
	~tileMap();

	virtual HRESULT init();
	virtual HRESULT init(int sizeX, int sizeY);
	virtual HRESULT initTileMap(int sizeX, int sizeY,int tileSizeX, int tileSizeY, image* setImg);

	virtual void update();
	virtual void render();
	virtual void release ();

	vector<vector<tagTile>> getTileMap() { return _map; };
	void setTileMap(vector<vector<tagTile>> tilemap) {_map=tilemap; };

	vector<tagInteractionObject> getInteractionObject() { return _interactionObject; };
	void setInteractionObject(vector<tagInteractionObject> interactionObject) { _interactionObject = interactionObject; };


	//�� ������ get, set
	int getMapSizeX() { return _mapSizeX; };
	int getMapSizeY() { return _mapSizeY; };

	void setMapSizeX(int sizeX) { _mapSizeX = sizeX; };
	void setMapSizeY(int sizeY) { _mapSizeY = sizeY; };


	//�� ����ü get,set
	int getMapTerrain(int x, int y) { return _map[y][x].terrain; };
	int getMapObj(int x, int y);
	image* getMapTerrainImage(int x, int y) { return _map[y][x].terrainImg; };
	image* getMapObjImage(int x, int y) { return _map[y][x].objImg; };
	int getTerrainImageNum(int x, int y) { return _map[y][x].terrainImageNum; };
	int getObjImageNum(int x, int y) { return _map[y][x].objImageNum; };
	
	void setMapTerrain(int x, int y, TERRAIN terrain) { _map[y][x].terrain= terrain; };
	void setMapObj(int x, int y, OBJECT object) { _map[y][x].obj= object; };
	void setTerrainFrameX(int x, int y, int frameX) { _map[y][x].terrainFrameX = frameX; };
	void setTerrainFrameY(int x, int y, int frameY) { _map[y][x].terrainFrameY = frameY; };
	void setObjFrameX(int x, int y, int frameX) { _map[y][x].objFrameX = frameX; };
	void setObjFrameY(int x, int y, int frameY) { _map[y][x].objFrameY = frameY; };
	void setMapTerrainImage(int x, int y, image* terrainImage) { _map[y][x].terrainImg = terrainImage; };
	void setMapObjImage(int x, int y, image* objImage) { _map[y][x].objImg = objImage; };
	void setTerrainImageNum(int x, int y, int num) { _map[y][x].terrainImageNum = num; };
	void setObjImageNum(int x, int y, int num) { _map[y][x].objImageNum = num; };

	void addInteractionObject(int x, int y, int widthXPos, int heightYPos, RECT rc,INTERACTIONOBJECT obj, image* img, int imageNum);
	void deleteInteractionObject(int num);
};


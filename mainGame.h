#pragma once
#include"gameNode.h"
#define NUM 31
#define OBS 5
#define COIN 32
#define JELLY 32
struct tagRect
{
	RECT rc;
	bool touch=false;
	float comSpeed = 10.0f;
};

class mainGame : public gameNode
{
private:
	image * _bgImage;
	image * _run;
	image * _floor;
	image * _under1;
	image * _under2;
	image * _up1;
	image * _up2;
	image * _underFork;
	image * _coin;
	image * _jelly;
	image * _pinkJelly;
	image * _hpBar;
	image * _magnet;
	image * _booster;
	image * _boosterCookie;
	RECT player;
	RECT magnet;
	RECT booster;
	RECT hpBar;
	RECT blackBar;
	tagRect floor[NUM];
	RECT rcTemp;
	tagRect obstacle[OBS];
	tagRect coin[COIN];
	//tagRect pinkJelly[JELLY];
	tagRect jelly[JELLY];
	int index;	//������ �ε���
	int count;	//������ ���� ī��Ʈ
	int count1;	//������ ���� ī��Ʈ
	int count2;	//������ ���� ī��Ʈ
	int count3;	//������ ���� ī��Ʈ
	int boosterCount=0;	
	
	//�� 0 ����1 1 ����2 2 �����̵� 3 Ÿ�ӿ��� 4 ��� 5
	int status;
	int statusCount=0;
	bool run=true; //��
	bool drop = true;
	bool can2Jump=false; //1��������?
	bool can1Jump=false; //2��������?
	bool isBooster=false; //�ν���

	int jumpCount = 0;
	int gravity = 10;
	
	
	int obsNum = 0;
	float hp = 10000.0f;
	bool isDebug;
	//bool booster = false;
	//int boostCount = 0;
	float speed = 0.0f;
	
	int score = 0;
	char str[128];
	//������ ����
	int _loopX;
	int _loopY;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(HDC hdc);//�׸��°�

};


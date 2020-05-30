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
	int index;	//프레임 인덱스
	int count;	//프레임 돌릴 카운트
	int count1;	//프레임 돌릴 카운트
	int count2;	//프레임 돌릴 카운트
	int count3;	//프레임 돌릴 카운트
	int boosterCount=0;	
	
	//런 0 점프1 1 점프2 2 슬라이드 3 타임오버 4 드랍 5
	int status;
	int statusCount=0;
	bool run=true; //런
	bool drop = true;
	bool can2Jump=false; //1점프가능?
	bool can1Jump=false; //2점프가능?
	bool isBooster=false; //부스터

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
	//루프용 변수
	int _loopX;
	int _loopY;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(HDC hdc);//그리는곳

};


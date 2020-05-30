#include "stdafx.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init();
	status = 0;
	drop = false;
	_bgImage = new image;
	_bgImage->init("images/backGround.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("배경화면", "images/backGound.bmp", WINSIZEX * 6, WINSIZEY, true, RGB(255, 0, 255));
	for (int i = 0; i < NUM; i++) {
		floor[i].rc = RectMakeCenter(100 * i, 750, 100, 150);
	}
	for (int i = 0; i < OBS; i++)
	{
		switch (i)
		{
		case 0:obstacle[i].rc = RectMake(1200, 540, 40, 140); break;
		case 1:obstacle[i].rc = RectMake(1250, 540, 40, 140); break;
		case 2:obstacle[i].rc = RectMake(2400, 0, 50, 550); break;
		case 3:obstacle[i].rc = RectMake(2450, 0, 50, 550); break;
		case 4:obstacle[i].rc = RectMake(3600, 380, 100, 300); break;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++) {
			coin[8*i+j].rc = RectMake(1600 + (65 * j), 200 + (i * 65), 50, 50);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++) {
			jelly[8 * i + j].rc = RectMake(2800 + (65 * j), 200 + (i * 65), 50, 50);
		}
	}

	player = RectMake(250, 500, 100, 150);
	hpBar = RectMake(110, 60, 400, 50);
	blackBar = RectMake(612, 88, 0, 55);
	magnet = RectMake(150, 350, 90, 90);
	booster = RectMake(650, 350, 90, 90);
	_run = new image;
	_run->init("images/cookie1.bmp", (player.right-player.left)*10, (player.bottom-player.top)*10, 4, 6, true, RGB(170, 0, 0));
	
	_floor = new image;
	_floor->init("images/floor.bmp", 0, 700, floor[0].rc.right-floor[0].rc.left, floor[0].rc.bottom-floor[0].rc.top, 1, 1, true, RGB(170, 0, 0));
	//
	_under1 = new image;
	_under1->init("images/under1.bmp", obstacle[0].rc.left, obstacle[0].rc.top, obstacle[0].rc.right-obstacle[0].rc.left, obstacle[0].rc.bottom-obstacle[0].rc.top, 1, 1, true, RGB(170, 0, 0));
	//
	_under2 = new image;
	_under2->init("images/under2.bmp", obstacle[1].rc.left, obstacle[1].rc.top, obstacle[1].rc.right - obstacle[1].rc.left, obstacle[1].rc.bottom - obstacle[1].rc.top, 1, 1, true, RGB(170, 0, 0));
	
	_up1 = new image;
	_up1->init("images/up1.bmp", obstacle[2].rc.left, obstacle[2].rc.top, obstacle[2].rc.right - obstacle[2].rc.left, obstacle[2].rc.bottom - obstacle[2].rc.top, 1, 1, true, RGB(170, 0, 0));

	_up2 = new image;
	_up2->init("images/up2.bmp", obstacle[3].rc.left, obstacle[3].rc.top, obstacle[3].rc.right - obstacle[3].rc.left, obstacle[3].rc.bottom - obstacle[3].rc.top, 1, 1, true, RGB(170, 0, 0));
	
	_underFork = new image;
	_underFork->init("images/underFork.bmp", obstacle[4].rc.left, obstacle[4].rc.top, obstacle[4].rc.right - obstacle[4].rc.left, obstacle[4].rc.bottom - obstacle[4].rc.top, 1, 1, true, RGB(170, 0, 0));

	_coin = new image;
	_coin->init("images/coin.bmp", coin[0].rc.left, coin[0].rc.top, 700, coin[0].rc.bottom - coin[0].rc.top, 6, 1, true, RGB(170, 0, 0));

	_jelly = new image;
	_jelly->init("images/jelly.bmp", jelly[0].rc.left, jelly[0].rc.top, jelly[0].rc.right-jelly[0].rc.left, jelly[0].rc.bottom - jelly[0].rc.top, 1, 1, true, RGB(170, 0, 0));

	_pinkJelly = new image;
	_pinkJelly->init("images/pinkJelly.bmp", jelly[1].rc.left, jelly[1].rc.top, jelly[1].rc.right - jelly[1].rc.left, jelly[1].rc.bottom - jelly[1].rc.top, 1, 1, true, RGB(170, 0, 0));


	_hpBar = new image;
	_hpBar->init("images/hp.bmp", hpBar.left, hpBar.top,hpBar.right, hpBar.bottom,  1, 1, true, RGB(170, 0, 0));

	_magnet = new image;
	_magnet->init("images/magnet.bmp", (magnet.right - magnet.left)*4, (magnet.bottom - magnet.top), 4, 1, true, RGB(170, 0, 0));

	_booster = new image;
	_booster->init("images/booster.bmp", (booster.right - booster.left) * 4, (booster.bottom - booster.top), 4, 1, true, RGB(170, 0, 0));

	_boosterCookie = new image;
	_boosterCookie->init("images/boosterCookie.bmp", 200, 350, 1, 1, true, RGB(170, 0, 0));

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_run);
	SAFE_DELETE(_floor);
	SAFE_DELETE(_under1);
	SAFE_DELETE(_under2);
	SAFE_DELETE(_up1);
	SAFE_DELETE(_up2);
	SAFE_DELETE(_underFork);
	SAFE_DELETE(_coin);
	SAFE_DELETE(_jelly);
	SAFE_DELETE(_pinkJelly);
	SAFE_DELETE(_hpBar);
	SAFE_DELETE(_magnet);
	SAFE_DELETE(_booster);
	SAFE_DELETE(_boosterCookie);
}

void mainGame::update()
{
	gameNode::update();
	//랜덤함수
	//rndNum = RND->getInt(480);
	//downNum = RND->getFromIntTo(15, 10);
	

	
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		drop = true;
		if(can2Jump){
			
		}
		else if (status==1||can1Jump)
		{
			status = 2;
			can2Jump = true;
			drop = false;
			jumpCount = 30;
		}
		else if(!can1Jump){
			drop = false;
			status = 1;
			can1Jump = true;
			jumpCount = 30;
		}
	}
	//슬라이딩
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		status = 3;
		player = RectMakeH(player.left, player.bottom, 100, 100);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		status = 0;
		player = RectMake(player.left, player.top-50, 100, 150);
	}
	
	
	if (status==1) {
		player.top -= 20;
		player.bottom -= 20;
		jumpCount--;
	}
	if (status == 2) {
		player.top -= 22;
		player.bottom -= 22;
		jumpCount--;
	}
	if (jumpCount == 0&&drop&&status!=3)
	{
		status=0;
	}
	for (int i = 0; i < NUM; i++) {
		if (player.bottom >= floor[i].rc.top&&player.left<floor[i].rc.right&&player.right>floor[i].rc.left) {

			drop = false;
			can2Jump = false;
			can1Jump = false;
			
			break;
		}
		else {
			drop = true;
			
		}

	}
	
	if (drop) {
		player.top += gravity;
		player.bottom += gravity;
		
	}
	

	//디버그 키
	if (KEYMANAGER->isOnceKeyDown(VK_F11))
	{
		isDebug = !isDebug;
	}
	//배경화면 이동
	_loopX = _loopX + speed / 8;
	//바닥 이동
	for (int i = 0; i < NUM; i++)
	{
		floor[i].rc.left -= speed / 4;
		floor[i].rc.right -= speed / 4;
		if (floor[i].rc.right < 0)
		{
			floor[i].rc = RectMake(3000, 678, 100, 150);
		}
	}

	speed = speed + 0.5f;
	
	switch (status) {
	case 0: 
		count++;
		_run->setFrameY(0);

		if (count % 15 == 0)
		{
			count = 0;
			index++;

			if (index > 3)
			{
				index = 0;
			}
			_run->setFrameX(index);
		}
		
		break;
	case 1:
		count++;
		_run->setFrameY(1);

		if (count % 20 == 0)
		{
			count = 0;
			index++;

			if (index > 3)
			{
				index = 0;
			}
			_run->setFrameX(index);
		}
		break;
	case 2:
		count++;
		_run->setFrameY(2);

		if (count % 14 == 0)
		{
			count = 0;
			index++;
			
			if (index > 3)
			{
			index = 0;
			}
			_run->setFrameX(index);
		}
		break;
	case 3:
		count++;
		_run->setFrameY(3);

		if (count % 8 == 0)
		{
			count = 0;
			index++;

			if (index > 3)
			{
				index = 0;
			}
			_run->setFrameX(index);
		}
		
		break;
	case 4:
		count++;
		_run->setFrameY(4);

		if (count % 20 == 0)
		{
			count = 0;
			index++;

			if (index > 3)
			{
				index = 0;
			}
			_run->setFrameX(index);
		}
		break;
	case 5:
		count++;
		_run->setFrameY(0);

		if (count % 20 == 0)
		{
			count = 0;
			index++;

			if (index > 3)
			{
				index = 0;
			}
			_run->setFrameX(index);
		}
		break;
	case 6:
		count++;
		_run->setFrameY(5);

		if (count % 12 == 0)
		{
			count = 0;
			index++;

			if (index > 3)
			{
				index = 0;
			}
			_run->setFrameX(index);
		}
		break;
	}
	
	if (speed >= 50) {
		speed = 50;
	}
	//속도 0이하 제한
	else if (speed <= 0||status==4)
	{
		speed = 0;
	}
	//obstacle 설정
	if (statusCount == 0) {
		status = 0;
		statusCount = 0;
	}
	statusCount--;
	for (int i = 0; i < OBS; i++) {
		//충돌시
		
		if (IntersectRect(&rcTemp, &player, &obstacle[i].rc)&&!obstacle[i].touch&&!isBooster)
		{
			status = 6;
			statusCount=10;
			speed = speed - 10.0f;
			
			obstacle[i].touch = true;
			blackBar.left -= 20;
			
			if (speed < 0.0f)
			{
				speed = 0.0f;
			}
		}
		if (status != 4) {
			obstacle[i].rc.left = obstacle[i].rc.left - obstacle[i].comSpeed;
			obstacle[i].rc.right = obstacle[i].rc.right - obstacle[i].comSpeed;
		}
		if (obstacle[i].comSpeed >= 10.0f) {
			obstacle[i].comSpeed = 10.0f;
		}
		obstacle[i].comSpeed += 0.2f;
	}
	for (int i = 0; i < COIN; i++) {
		//충돌시
		count1++;
		_coin->setFrameY(0);

		if (count1 % 6 == 0)
		{
			count1 = 0;
			index++;

			if (index > 5)
			{
				index = 0;
			}
			_coin->setFrameX(index);
		}
		if (IntersectRect(&rcTemp, &player, &coin[i].rc))
		{
			score+=100;
			coin[i].touch = true;
		}
		if (status != 4) {
			coin[i].rc.left = coin[i].rc.left - coin[i].comSpeed;
			coin[i].rc.right = coin[i].rc.right - coin[i].comSpeed;
		}
		if (coin[i].comSpeed >= 10.0f) {
			coin[i].comSpeed = 10.0f;
		}
		coin[i].comSpeed += 0.2f;
	}
	//자석
	for (int i = 0; i < JELLY; i++) {
		if (getDistance((magnet.right + magnet.left) / 2,
			(magnet.bottom + magnet.top) / 2,
			(jelly[i].rc.right + jelly[i].rc.left) / 2,
			(jelly[i].rc.bottom + jelly[i].rc.top) / 2) < 400
			&& (magnet.right + magnet.left) / 2 +150>= (jelly[i].rc.right + jelly[i].rc.left) / 2) {
			
			if ((magnet.bottom + magnet.top) / 2 <= (jelly[i].rc.bottom + jelly[i].rc.top) / 2)
			{
				jelly[i].rc.bottom -= 10;
				jelly[i].rc.top -= 10;
			}
			if ((magnet.bottom + magnet.top) / 2 >= (jelly[i].rc.bottom + jelly[i].rc.top) / 2)
			{
				jelly[i].rc.bottom += 10;
				jelly[i].rc.top += 10;
			}
		}
		//if (getDistance((magnet.right + magnet.left) / 2,
		//	(magnet.bottom + magnet.top) / 2,
		//	(jelly[i].rc.right + jelly[i].rc.left) / 2,
		//	(jelly[i].rc.bottom + jelly[i].rc.top) / 2) < 400
		//	&& (magnet.right + magnet.left) / 2 + 150 >= (jelly[i].rc.right + jelly[i].rc.left) / 2) {
		//
		//
		//	//magnet.left += 10;
		//	//magnet.right += 10;
		//
		//	if ((magnet.bottom + magnet.top) / 2 <= (jelly[i].rc.bottom + jelly[i].rc.top) / 2)
		//	{
		//		jelly[i].rc.bottom -= 10;
		//		jelly[i].rc.top -= 10;
		//	}
		//	if ((magnet.bottom + magnet.top) / 2 >= (jelly[i].rc.bottom + jelly[i].rc.top) / 2)
		//	{
		//		jelly[i].rc.bottom += 10;
		//		jelly[i].rc.top += 10;
		//	}
		//}
		if (IntersectRect(&rcTemp, &player, &jelly[i].rc)|| IntersectRect(&rcTemp, &magnet, &jelly[i].rc))
		{
			score += 100;
			jelly[i].touch = true;
		}
		if (status != 4) {
			jelly[i].rc.left = jelly[i].rc.left - jelly[i].comSpeed;
			jelly[i].rc.right = jelly[i].rc.right - jelly[i].comSpeed;
		}
		if (jelly[i].comSpeed >= 10.0f) {
			jelly[i].comSpeed = 10.0f;
		}
		jelly[i].comSpeed += 0.2f;
	}
	//화면 넘어갈시
	for (int i = 0; i < OBS; i++)
	{
		
		if (obstacle[i].rc.right < 0)
		{
			obstacle[i].touch = false;
			switch (i) {
			case 0: obstacle[i].rc = RectMake(5000, obstacle[i].rc.top, 50, obstacle[i].rc.bottom - obstacle[i].rc.top);
			case 1: obstacle[i].rc = RectMake(5000, obstacle[i].rc.top, 50, obstacle[i].rc.bottom - obstacle[i].rc.top);
			case 2: obstacle[i].rc = RectMake(5000, obstacle[i].rc.top, 50, obstacle[i].rc.bottom - obstacle[i].rc.top);
			case 3: obstacle[i].rc = RectMake(5000, obstacle[i].rc.top, 50, obstacle[i].rc.bottom - obstacle[i].rc.top);
			case 4: obstacle[i].rc = RectMake(5000, obstacle[i].rc.top, 70, obstacle[i].rc.bottom - obstacle[i].rc.top);
			}
		}
	}
	for (int i = 0; i < COIN; i++)
	{
		if (coin[i].rc.right < 0)
		{
			coin[i].touch = false;
			
			coin[i].rc = RectMake(5000, coin[i].rc.top, 50, 50);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++) {
			if (jelly[8*i+j].rc.right < 0)
			{
				jelly[8 * i + j].touch = false;

				jelly[8 * i + j].rc = RectMake(5000 + (10 * j), 200 + (i * 65), 50, 50);
			}
		}
	}
	count2++;
	_magnet->setFrameY(0);

	if (count2 % 5 == 0)
	{
		count2 = 0;
		index++;

		if (index > 5)
		{
			index = 0;
		}
		_magnet->setFrameX(index);
	}
	if (IntersectRect(&rcTemp, &player, &booster))
	{
		isBooster = true;
		boosterCount = 100;
	}
	if (status != 4) {
		booster.left = booster.left - 10;
		booster.right = booster.right - 10;
	}
	
	count3++;
	_booster->setFrameY(0);

	if (count3 % 5 == 0)
	{
		count3 = 0;
		index++;

		if (index > 5)
		{
			index = 0;
		}
		_booster->setFrameX(index);
	}
	//체력
	//blackBar.left -= 0.0001f;
	if (blackBar.left <= hpBar.left+63)
	{
		status = 4;
		blackBar.left = hpBar.left + 63;
	}
	

	boosterCount--;

	score += speed;
	if (isBooster) {
		for (int i = 0; i < NUM;i++) {
			floor[i].comSpeed = 50;
		}
		for (int i = 0; i < OBS; i++) {
			obstacle[i].comSpeed = 50;
		}
		for (int i = 0; i < COIN; i++) {
			coin[i].comSpeed = 50;
		}
		for (int i = 0; i < JELLY; i++) {
			jelly[i].comSpeed = 50;
		}

	}
	
	if (boosterCount <= 0)
	{
		boosterCount = 0;
		isBooster = false;
		for (int i = 0; i < NUM; i++) {
			floor[i].comSpeed = 10;
		}
		for (int i = 0; i < OBS; i++) {
			obstacle[i].comSpeed = 10;
		}
		for (int i = 0; i < COIN; i++) {
			coin[i].comSpeed = 10;
		}
		for (int i = 0; i < JELLY; i++) {
			jelly[i].comSpeed = 10;
		}
	}
}

void mainGame::render(HDC hdc)
{
	//백버퍼에 뿌리자.
	HDC memDC = this->getBackBuffer()->getMemDC();
	//흰색 비트맵
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================
	//배경
	_bgImage->loopRender(memDC, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX, _loopY);
	//쿠키
	if (isBooster) {
		_boosterCookie->render(memDC, player.left - 100, player.top - 100);
	}
	_run->frameRender(memDC, player.left - 70, player.top - 100);
	_magnet->frameRender(memDC, magnet.left, magnet.top);
	_booster->frameRender(memDC, booster.left, booster.top);
	
	//바닥
	for (int i = 0; i < NUM; i++)
	{
		_floor->render(memDC, floor[i].rc.left - 10, floor[i].rc.top);
	}
	//방해물
	for (int i = 0; i < OBS; i++)
	{
		obsNum = i % 5;
		switch (obsNum)
		{
		case 0:_under1->render(memDC, obstacle[i].rc.left, obstacle[i].rc.top); break;
		case 1:_under2->render(memDC, obstacle[i].rc.left, obstacle[i].rc.top); break;
		case 2:_up1->render(memDC, obstacle[i].rc.left, obstacle[i].rc.top); break;
		case 3:_up2->render(memDC, obstacle[i].rc.left, obstacle[i].rc.top); break;
		case 4:_underFork->render(memDC, obstacle[i].rc.left, obstacle[i].rc.top); break;
		}
	}
	//코인
	for (int i = 0; i < COIN; i++)
	{
		if (coin[i].touch == false) {
			_coin->frameRender(memDC, coin[i].rc.left - 40, coin[i].rc.top, _coin->getFrameX(), _coin->getFrameY());
		}
	}
	//젤리
	for (int i = 0; i < JELLY; i++)
	{
		if (jelly[i].touch == false) {
			switch (i % 2) {
			case 0:_jelly->render(memDC, jelly[i].rc.left - 40, jelly[i].rc.top); break;
			case 1:_pinkJelly->render(memDC, jelly[i].rc.left - 40, jelly[i].rc.top); break;
			}
		}
	}
	//hp바
	_hpBar->render(memDC, hpBar.left, hpBar.top);
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	Rectangle(memDC, blackBar.left, blackBar.top, blackBar.right, blackBar.bottom);
	FillRect(memDC, &blackBar, brush);
	DeleteObject(brush);
	//게임 종료
	if (status == 4)
	{
		wsprintf(str, "GAME OVER");
		TextOut(memDC, 500, 500, str, strlen(str));

	}
	
	wsprintf(str, "점수: %d", score);
	TextOut(memDC, 800, 10, str, strlen(str));
	////점수 출력
	wsprintf(str, "상태: %d", boosterCount);
	TextOut(memDC, 800, 30, str, strlen(str));
	//디버그 if문
	if (isDebug)
	{
		
		Rectangle(memDC, player.left, player.top, player.right, player.bottom);
		
		Rectangle(memDC, magnet.left, magnet.top, magnet.right, magnet.bottom);
		Rectangle(memDC, booster.left, booster.top, booster.right, booster.bottom);
		for (int i = 0; i < NUM; i++)
		{
			Rectangle(memDC, floor[i].rc.left, floor[i].rc.top, floor[i].rc.right, floor[i].rc.bottom);
		}
		for (int i = 0; i < OBS; i++)
		{
			Rectangle(memDC, obstacle[i].rc.left, obstacle[i].rc.top, obstacle[i].rc.right, obstacle[i].rc.bottom);
		}
		for (int i = 0; i < COIN; i++)
		{
			Rectangle(memDC, coin[i].rc.left, coin[i].rc.top, coin[i].rc.right, coin[i].rc.bottom);
		}
		for (int i = 0; i < JELLY; i++)
		{
			Rectangle(memDC, jelly[i].rc.left, jelly[i].rc.top, jelly[i].rc.right, jelly[i].rc.bottom);
		}
	}
	//=================================================
	//백버퍼의 내용을 HDC에 그린다.(건드리지말것.)
	this->getBackBuffer()->render(hdc, 0, 0);
}

	

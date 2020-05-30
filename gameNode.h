#pragma once
#include"image.h"
class gameNode
{
	/*
		더블버퍼링 :  현재까지의 화면은 도형을
		직접 hdc에 뿌리는 방식임.
		도형이나 비트맵이 커지면 부하가 커진다.
		즉, 이말은 깜박거리는 현상이 발생된다.
		메모리 내에서 출력(화면에 보이지 않는 출력)이 더 빠르다는 점을 이용하여
		메모리에 모든 출력할 내용을 뿌린다음에 hdc로 옮기는 방법이 더블버퍼이다.

	*/

private:

	image * _backBuffer;		//백버퍼
	void setBackBuffer();		//백버퍼 셋팅

public:
	gameNode();
	~gameNode();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	//백버퍼 가져오기
	image* getBackBuffer() { return _backBuffer; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};


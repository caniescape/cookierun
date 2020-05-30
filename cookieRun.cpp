#include"stdafx.h"
#include"mainGame.h"
//인스턴스 :  메모리상에 할당되어 실행중인 프로그램
//OS를 확인하기 위한 값.
HINSTANCE m_hInstance;
HWND m_hWnd;
POINT m_ptMouse = { 0,0 };
//윈도우 핸들
//대상끼리 구분하기 위해 사용한다.

//메인게임
mainGame mg;

//윈도우 클래스 이름
LPTSTR m_lpszClass = TEXT("경일 프로그래밍 18기");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height);

//hInstance : 인스턴스 핸들
//hPrevInstance :  이전에 실행된 인스턴스 핸들
//lpszCmdParam : 명령으로 입력된 프로그램 인수
//nCmdShow :  프로그램이 시작될 형태
//윈메인의 역할
//1.윈도우창 세팅후 화면에 띄우고
//2.메세지 루프
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	//윈도우 API는 크게 winMain, WndProc두개의 함수로 이루어져 있다.
	//윈도우 프로시져는 윈도우에서 이루어지는 동작을 이야기한다. 즉 메세지를 처리한다.

	m_hInstance = hInstance;

	//WNDCLASS  :  윈도우 창의 정보를 저장하기 위한 구조체.
	//윈도우창 구조체 선언후 초기화
	WNDCLASS wndClass;

	//윈도우 클래스에서 사용하고자하는 여분의 메모리양을 바이트 단위로 지정
	wndClass.cbClsExtra = 0;
	//cbClsExtra 이랑 유사하나 개별 윈도우에서 사용하고자 하는 여분의 메모리양을 지정
	wndClass.cbWndExtra = 0;
	//윈도우 작업영역에 칠할 배경 브러시
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//커서지정
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//타이틀바의 좌상단에 보여줄 아이콘과 윈도우가 최소화 되었을때 보여줄 아이콘을 지정
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	//윈도우 클래스를 등록한 응용프로그램의 인스턴스 핸들
	wndClass.hInstance = hInstance;
	//메세지를 처리하는 함수를 지정(윈도우 프로시져)
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	//등록하고자ㅏ 하는 윈도우 클래스 이름
	wndClass.lpszClassName = m_lpszClass;
	//클래스로 부터 만들어진 윈도구 사용할 메뉴를 지정
	wndClass.lpszMenuName = NULL;
	//윈도우 클래스의 스타일을 지정
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//윈도우 클래스 등록
	//등록할 윈도우 클래스의 특성을 지정하는 WNDCLASS구조체 전달
	RegisterClass(&wndClass);

	m_hWnd = CreateWindow(
		WINNAME,			//클래스이름
		WINNAME,			//윈도우타이틀 이름
		WS_OVERLAPPEDWINDOW,	//윈도우 스타일
		WINSTARTX,					//윈도우 화면 X
		WINSTARTY,					//윈도우 화면 y
		WINSIZEX,					//가로크기
		WINSIZEY,					//세로크기
		NULL,					//부모윈도우
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스지정
		NULL);

	//화면 작업사이즈 영역계산
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//화면에 윈도우 보여주자
	ShowWindow(m_hWnd, nCmdShow);

	//메인게임 초기화 실패하면 종료
	if (FAILED(mg.init()))
	{
		return 0;
	}
	//MSG : 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체
	MSG message;


	//게임용 루프
	/*while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{

			if (message.message == WM_QUIT)break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{

		}
	}*/

	//TranslateMessage :  키보드 입력메세지 처리를 담당
	//DispatchMessage : 윈도우 프로시져에 전달된 메세지를 실제 윈도우에 전달
	//getMessage : 대기상태
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//메시지 루프를 다돌면 해제하자.
	mg.release();
	return message.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	return mg.MainProc(hWnd, iMessage, wParam, lParam);

}
//=======================================================
//윈도우 크기조정(클라이언트 영역의 사이즈를 정확히 잡아준다)
//=======================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect(&rc, WINSTYLE, false);

	//위 RECT정보로 윈도우 사이즈를 셋팅하자.

	SetWindowPos(m_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}
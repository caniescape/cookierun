#include "stdafx.h"
#include "image.h"
//알파블렌드를 사용하기 위해서
#pragma comment(lib,"msimg32.lib")
//멤버 이니셜라이즈 초기화
//객체 생성과 동시에 초기화
image::image() : _imageInfo(NULL),
_fileName(NULL),
_isTrans(false),
_transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	//이미지 정보가 들어있다면 해제해라
	if (_imageInfo != NULL)release();
	//DC가져오기(현재 윈도우에 대한 화면 DC를 임시로 가져온다.)
	//CreateCompatibleDC : 비트맵을 출력하기 위해 메모리 DC를 만들어준다.
	//CreateCompatibleBitmap : 원본DC와 호환되는 비트맵을 생성해준다.
	//SelectObject : 기본의 비트맵 핸들을 반환하고, 새로운 비트맵을 메모리 DC가ㅏ
	//선택하고 메모리 DC에 비트맵이 그려진다. 화면DC가 아니므로 모니터에 출력X
	HDC hdc = GetDC(m_hWnd);

	//이미지 정보 생성
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;//블렌딩 연산자

	//알파 블렌드를 사용하기위한 이미지 초기화

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//투명키 셋팅
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//리소스를 얻어오는데 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	//DC해제
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;
	if (_imageInfo != NULL)release();

	HDC hdc = GetDC(m_hWnd);


	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName,
		IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;//블렌딩 연산자

									 //알파 블렌드를 사용하기위한 이미지 초기화

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;



	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소를 얻어오는데 실패했다면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	//해제
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;
	if (_imageInfo != NULL)release();

	HDC hdc = GetDC(m_hWnd);


	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName,
		IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;


	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;//블렌딩 연산자

									 //알파 블렌드를 사용하기위한 이미지 초기화

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;


	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;


	//리소를 얻어오는데 실패했다면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	//해제
	ReleaseDC(m_hWnd, hdc);
	return S_OK;
}

HRESULT image::init(const char * fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;
	if (_imageInfo != NULL)release();

	HDC hdc = GetDC(m_hWnd);


	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName,
		IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);

	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;


	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;//블렌딩 연산자

									 //알파 블렌드를 사용하기위한 이미지 초기화

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;


	//리소를 얻어오는데 실패했다면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	//해제
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

void image::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}
}

void image::render(HDC hdc)
{
	if (_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,							//복사될 장소의 DC
			0,								//복사될 좌표의 시작점 X
			0,								//복사될 좌표의 시작점 Y
			_imageInfo->width,				//복사될 이미지 가로크기
			_imageInfo->height,				//복사될 이미지 세로크기
			_imageInfo->hMemDC,				//복사될 대상 DC
			0,								//복사시작 지점 X
			0,								//복사시작 지점 Y
			_imageInfo->width,				//복사영역 가로크기
			_imageInfo->height,				//복사영역 세로크기
			_transColor);					//복사할때 제외할 색상
	}
	else
	{
		//SRCCOPY  : 복사해주는 함수 가로 세로를 재정의해사 복사
		//DC간의 영역끼리 고속복사해주는 녀석
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,							//복사될 장소의 DC
			destX,								//복사될 DC영역에 뿌려줄 X좌표
			destY,								//복사될 DC영역에 뿌려줄 Y좌표
			_imageInfo->width,				//복사될 이미지 가로크기
			_imageInfo->height,				//복사될 이미지 세로크기
			_imageInfo->hMemDC,				//복사될 대상 DC
			0,								//복사시작 지점 X
			0,								//복사시작 지점 Y
			_imageInfo->width,				//복사영역 가로크기
			_imageInfo->height,				//복사영역 세로크기
			_transColor);					//복사할때 제외할 색상
	}
	else
	{
		//SRCCOPY  : 복사해주는 함수 가로 세로를 재정의해사 복사
		//DC간의 영역끼리 고속복사해주는 녀석
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
//뿌릴곳 x,y			//뿌려올곳 x,y
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX,
			sourY,
			sourWidth,
			sourHeight,
			_transColor);
	}
	else
	{
		//SRCCOPY  : 복사해주는 함수 가로 세로를 재정의해사 복사
		//DC간의 영역끼리 고속복사해주는 녀석
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		//SRCCOPY  : 복사해주는 함수 가로 세로를 재정의해사 복사
		//DC간의 영역끼리 고속복사해주는 녀석
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;


	if (_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		//SRCCOPY  : 복사해주는 함수 가로 세로를 재정의해사 복사
		//DC간의 영역끼리 고속복사해주는 녀석
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}

}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//보정하기
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는(복사되어오는 이미지 영역)
	RECT rcSour;

	int sourWidth;
	int sourHeight;
	//그려지는 DC영역
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//영역의 높이 계산하자.
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//영역이 그리는 화명을 넘어갔다면(화면 밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀의 값을 올려줌 
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프 영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//영역계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//화면밖으로 넘어 갔다면
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 양만큼 라이트 값을 왼쪽으로..
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;
			//그리자
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//보정하기
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는(복사되어오는 이미지 영역)
	RECT rcSour;

	int sourWidth;
	int sourHeight;
	//그려지는 DC영역
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//영역의 높이 계산하자.
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//영역이 그리는 화명을 넘어갔다면(화면 밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀의 값을 올려줌 
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프 영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//영역계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//화면밖으로 넘어 갔다면
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 양만큼 라이트 값을 왼쪽으로..
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;
			//그리자
			alphaRender(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top, alpha);
		}
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{

		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}

}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

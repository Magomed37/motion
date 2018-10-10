// fdfgkjhj.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"

const wchar_t windowClass[] = L"win32app";
const wchar_t windowTitle[] = L"Win32API - Пример окна";
int x, y = 0, x_2, y_2, x_1, y_1, n = 1,k=1, n_1 = 0, n_2=1, n_3=0;

long __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;	
	POINT pt[4] = { {x_1, y_1}, {100 + x_1,200 + y_1}, {400 + x_1,5 + y_1} , { 900 + x_1,100 + y_1 } };

	RECT r;
	GetClientRect(hWnd, &r);
	HPEN pen, pen_1, old_pen;
	HBRUSH brush, old_brush;
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_RBUTTONDOWN:
	if(LOWORD(lParam)<=r.right/3){
		x_2 = LOWORD(lParam);
		y_2 = HIWORD(lParam);
			
		
		InvalidateRect(hWnd, NULL, false);
		n_1 = 1;
	}
		break;
	case WM_TIMER:
		if (wParam == 33) {

			y += n;
			if (y == 550) {
			n = -1;
		}
			if (y == 0) {
			n = 1;
		}
		}
		
		if(wParam == 34) {
			x_2 += k;
		}
		InvalidateRect(hWnd, NULL, true);
		
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//TextOut(hdc, 0, 0, L"ПКИМС рулит!", 12);
		pen = CreatePen(PS_SOLID, 5, RGB(148, 0, 211));
		old_pen = (HPEN)SelectObject(hdc, pen);
		brush = CreateSolidBrush(RGB(0, 128, 0));
		old_brush = (HBRUSH)SelectObject(hdc, brush);
		//Polygon(hdc, pt, 5);
		x = r.right-250;
		Rectangle(hdc, x, y, 250 + x, 150 + y);

		if (n_1 == 1 ) {
			Rectangle(hdc, x_2, y_2, 250 + x_2, 150 + y_2);
		}
		// Polygon(hdc, pt,4);
		//Ellipse(hdc, 100+y_1, 100+x_1, 400 + y_1, 400 + x_1);
		SelectObject(hdc, old_brush);
		DeleteObject(brush);

		// Rectangle(hdc, 50, 50, 250, 150);
		//SelectObject(hdc, old_pen);
		DeleteObject(pen);

		/* Ellipse(hdc, 100, 100, 400, 400);
		 MoveToEx(hdc, 99, 400, NULL);
		 LineTo(hdc,900, 900);
		 LineTo(hdc, 200, 99);
		 Polygon(hdc, pt, 5);
		 SetPixel(hdc, 340, 888, RGB(456, 100, 45));*/ 

		if((x<x_2 && x_2<(x+250)&& y_2>=y && y_2<(y+150))  
			|| ((x<x_2 && x_2<(x+250)) && (y_2+150)>=y && y_2<(y)) 
			|| (((x+250)>(x_2+250) && (x_2+250)>(x)) && (y_2+150)>=y && y_2<(y))
			|| (((x+250)>(x_2+250) && (x_2+250)>(x)) && y_2>=y && y_2<(y+150))
			&& n_1==1){
            n_2++;

             WCHAR  hah[100];
             wsprintf(hah,TEXT("%d"),x);
             TextOut(hdc, 10, 30,hah,lstrlen(hah));
			 wsprintf(hah,TEXT("%d"),y);
             TextOut(hdc, 50, 30,hah,lstrlen(hah));
			 wsprintf(hah,TEXT("%d"),x_2);
             TextOut(hdc, 100, 30,hah,lstrlen(hah));
			 wsprintf(hah,TEXT("%d"),y_2);
			 TextOut(hdc, 150, 30,hah,lstrlen(hah));
	           k=0;
			   n=0;
			   if(n_2==2){
				// PostMessage(hWnd, WM_CLOSE, 0, 0);
			 if (MessageBox(hWnd, L"ПЕРЕСЕК!!!", L"Внимание сообщение", MB_YESNO | MB_ICONQUESTION) == IDNO) {
            n_2=1;
				return 0;
			 }
		else {
            return DefWindowProc(hWnd, message, wParam, lParam);
		} 
			 }
		}
			
		break;
	 case WM_CLOSE:
		if (MessageBox(hWnd, L"Выйти из программы?", L"Внимание сообщение", MB_YESNO | MB_ICONQUESTION) == IDNO) {
	
			return 0;
		}
		else {
            return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
		
	return 0;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = windowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, L"CanТt register window class!", L"Win32 API Test", NULL);
		return 1;
	}

	HWND hWnd = CreateWindow(windowClass, windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

	if (!hWnd) {
		MessageBox(NULL, L"CanТt create window!", L"Win32 API Test", NULL);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	SetTimer(hWnd, 33, 10, NULL);
	SetTimer(hWnd, 34, 10, NULL);
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	KillTimer(hWnd, 33);
	KillTimer(hWnd, 34);

	return msg.wParam;
}
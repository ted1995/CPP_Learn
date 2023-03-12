#include <Windows.h>

// ����Ҫ����ǰ������  
LRESULT CALLBACK WindowProc(
	_In_  HWND hwnd,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
);

int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
)
{

	// ��ƴ�����  
	WNDCLASS wc = { sizeof(WNDCLASS) };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = L"cls_Name";
	wc.hInstance = hInstance;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	// ע�ᴰ����  
	RegisterClass(&wc);

	// ��������
	HWND hwnd = CreateWindow(
		L"cls_Name"   ,   //������Ҫ�͸ղ�ע���һ��  
		L"�ҵ�Ӧ�ó���",          //���ڱ�������  
		WS_OVERLAPPEDWINDOW,        //���������ʽ  
		38,             //��������ڸ�����X����  
		20,             //��������ڸ�����Y����  
		480,                //���ڵĿ��  
		250,                //���ڵĸ߶�  
		NULL,               //û�и����ڣ�ΪNULL  
		NULL,               //û�в˵���ΪNULL  
		hInstance,          //��ǰӦ�ó����ʵ�����  
		NULL);              //û�и������ݣ�ΪNULL  
	if (hwnd == NULL)                //��鴰���Ƿ񴴽��ɹ�  
		return 0;

	// ��ʾ����  
	ShowWindow(hwnd, SW_SHOW);

	// ���´���  
	UpdateWindow(hwnd);

	// ��Ϣѭ��  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

// ��WinMain��ʵ��  
LRESULT CALLBACK WindowProc(
	_In_  HWND hwnd,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	
	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

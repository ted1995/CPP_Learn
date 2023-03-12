#include<windows.h>


LRESULT CALLBACK winCallBack(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hInstance1, LPSTR lpCmdLine, int nShowMode)
{
	WNDCLASSEX windowClass;
	windowClass.cbClsExtra = 0;
	windowClass.cbSize = sizeof(WNDCLASS);
	windowClass.cbClsExtra = 0;
	windowClass.hbrBackground = NULL;
	windowClass.hCursor = NULL;
	windowClass.hIcon = NULL;
	windowClass.hIconSm = NULL;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = winCallBack;
	windowClass.lpszClassName = L"c3window";
	windowClass.lpszMenuName = NULL;
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	//注册结构体
	RegisterClassEx(&windowClass);

	//创建窗口
	HWND hWnd = CreateWindow(L"c3window", L"c3窗口", WS_OVERLAPPEDWINDOW, 200, 200, 600, 400, NULL, NULL, hInstance, NULL);
	if (NULL == hWnd)
	{
		return 0;
	}

	//显示窗口
	ShowWindow(hWnd, nShowMode);

	//更新窗口
	UpdateWindow(hWnd);

	//消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK winCallBack(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	//分类处理
	switch (msgID)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;

	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}
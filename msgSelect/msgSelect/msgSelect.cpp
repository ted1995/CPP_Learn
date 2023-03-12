
#include<iostream>
using namespace std;
#define FD_SETSIZE 128
#include<WinSock2.h>
#include <ws2tcpip.h> 
#pragma comment(lib,"Ws2_32.lib")
using namespace std;

//自定义一个自己的消息宏
#define UM_ASYNC WM_USER+1


int y = 0;

//回调函数声明
LRESULT CALLBACK winCallBack(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam);




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstance1, LPSTR lpCmdLine, int nShowMode)
{
	WNDCLASS windowClass = { sizeof(WNDCLASS) };
	windowClass.cbClsExtra = 0;
	windowClass.cbClsExtra = 0;
	windowClass.hbrBackground = NULL;
	windowClass.hCursor = NULL;
	windowClass.hIcon = NULL;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = winCallBack;
	windowClass.lpszClassName = L"c3window";
	windowClass.lpszMenuName = NULL;
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	//注册结构体
	RegisterClass(&windowClass);

	//创建窗口
	HWND hWnd = CreateWindow(L"c3window", L"c3窗口", WS_OVERLAPPEDWINDOW, 200, 200, 600, 400, NULL, NULL, hInstance, NULL);
	if (NULL == hWnd)
	{
		return 0;
	}

	//显示窗口
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//更新窗口
	UpdateWindow(hWnd);


	//网络初始化
	//打开网络库，进行网络编程
	WORD wdVersion = MAKEWORD(2, 2);
	WSADATA wdSockMsg;
	int nRes = WSAStartup(wdVersion, &wdSockMsg);
	if (nRes != 0)
	{
		//打开失败
		cout << "网络库打开失败" << endl;
	}

	//校验版本
	//高字节是副版本，低字节是主版本
	if (HIBYTE(wdSockMsg.wVersion) != 2 && LOBYTE(wdSockMsg.wVersion) != 2)
	{
		//版本不对，关闭网络库，结束
		WSACleanup();
		return 0;
	}

	//创建服务端的socket
	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketServer == INVALID_SOCKET)
	{
		//socket创建失败
		cout << "socket创建失败" << endl;
	}

	

	//给socket绑定服务端的端口与ip地址
	sockaddr_in server_sockin;
	server_sockin.sin_family = AF_INET;
	server_sockin.sin_port = htons(12345);
	server_sockin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int reBindNum = bind(socketServer, (sockaddr*)&server_sockin, sizeof(server_sockin));
	if (SOCKET_ERROR == reBindNum)
	{
		cout << "绑定失败" << endl;
	}

	//开始监听服务端有没有接收到信息，
	int reLisNum = listen(socketServer, SOMAXCONN);
	if (reLisNum == SOCKET_ERROR)
	{
		cout << "监听失败" << endl;
	}
	else
	{
		cout << "开始监听" << endl;
	}


	//异步选择模型，将socket指定一个消息编号和信号，然后投递到指定窗口的操作系统的消息队列中，操作系统会自动检测这些消息有没有发出信号
	//如果发出了信号，那么就调用回调函数处理这个消息对应的socket的动作。

	//将服务端socket投递到窗口中,并指定消息编号
	int wNum = WSAAsyncSelect(socketServer, hWnd, UM_ASYNC, FD_ACCEPT);
	if (wNum == SOCKET_ERROR)
	{
		cout << "投递出错" << endl;
	}


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
	HDC hdc = GetDC(hWnd);
	//分类处理
	switch (msgID)
	{
		case WM_CREATE:
			//类似于初始化，只执行一次
			break;
		case UM_ASYNC:
		{
			//MessageBox(NULL, L"有信号了", L"提示",MB_YESNO);
			//获取socket
			SOCKET socket = (SOCKET)wParam;
			//获取消息
			//没有错误码
			if (HIWORD(lParam) != 0)
			{
				break;
			}
			switch (LOWORD(lParam))
			{
				case FD_ACCEPT:
				{
					//在窗口输出文本
					TextOut(hdc, 0, y, L"accept", 6);
					y += 15;
					//接收客户端socket
					SOCKET clientSocket = accept(socket, NULL, NULL);
					if (INVALID_SOCKET == clientSocket)
					{
						cout << "客户端socket创建出错" << endl;
					}
					//将客户端socket投递到系统的消息队列中
					if (SOCKET_ERROR == WSAAsyncSelect(clientSocket, hWnd, UM_ASYNC, FD_READ | FD_WRITE | FD_CLOSE))
					{
						cout << "socket投递失败" << endl;
						closesocket(clientSocket);
					}
					break;
				}

				case FD_READ:
				{
					//FD_READ信号，客户端socket发送数据，服务端需要接收，调用recv函数
					char buf[1500] = { 0 };
					recv(socket, buf, 1499, 0);
					TextOut(hdc, 0, y, L"read", 5);
					y += 15;
					break;
				}

				case FD_WRITE:
				{
					//FD_WRITE信号，客户端socket接受数据，只执行一次
					send(socket, "write", strlen("write"), 0);
					break;
				}

				case FD_CLOSE:
				{
					//FD_CLOSE信号，客户端断开连接
					//不再监管这个socket上的消息
					WSAAsyncSelect(socket, hWnd, 0, 0);
					break;
				}
			}
			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
	}

	ReleaseDC(hWnd, hdc);
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}
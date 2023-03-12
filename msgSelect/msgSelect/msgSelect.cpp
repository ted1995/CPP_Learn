
#include<iostream>
using namespace std;
#define FD_SETSIZE 128
#include<WinSock2.h>
#include <ws2tcpip.h> 
#pragma comment(lib,"Ws2_32.lib")
using namespace std;

//�Զ���һ���Լ�����Ϣ��
#define UM_ASYNC WM_USER+1


int y = 0;

//�ص���������
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

	//ע��ṹ��
	RegisterClass(&windowClass);

	//��������
	HWND hWnd = CreateWindow(L"c3window", L"c3����", WS_OVERLAPPEDWINDOW, 200, 200, 600, 400, NULL, NULL, hInstance, NULL);
	if (NULL == hWnd)
	{
		return 0;
	}

	//��ʾ����
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//���´���
	UpdateWindow(hWnd);


	//�����ʼ��
	//������⣬����������
	WORD wdVersion = MAKEWORD(2, 2);
	WSADATA wdSockMsg;
	int nRes = WSAStartup(wdVersion, &wdSockMsg);
	if (nRes != 0)
	{
		//��ʧ��
		cout << "������ʧ��" << endl;
	}

	//У��汾
	//���ֽ��Ǹ��汾�����ֽ������汾
	if (HIBYTE(wdSockMsg.wVersion) != 2 && LOBYTE(wdSockMsg.wVersion) != 2)
	{
		//�汾���ԣ��ر�����⣬����
		WSACleanup();
		return 0;
	}

	//��������˵�socket
	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketServer == INVALID_SOCKET)
	{
		//socket����ʧ��
		cout << "socket����ʧ��" << endl;
	}

	

	//��socket�󶨷���˵Ķ˿���ip��ַ
	sockaddr_in server_sockin;
	server_sockin.sin_family = AF_INET;
	server_sockin.sin_port = htons(12345);
	server_sockin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int reBindNum = bind(socketServer, (sockaddr*)&server_sockin, sizeof(server_sockin));
	if (SOCKET_ERROR == reBindNum)
	{
		cout << "��ʧ��" << endl;
	}

	//��ʼ�����������û�н��յ���Ϣ��
	int reLisNum = listen(socketServer, SOMAXCONN);
	if (reLisNum == SOCKET_ERROR)
	{
		cout << "����ʧ��" << endl;
	}
	else
	{
		cout << "��ʼ����" << endl;
	}


	//�첽ѡ��ģ�ͣ���socketָ��һ����Ϣ��ź��źţ�Ȼ��Ͷ�ݵ�ָ�����ڵĲ���ϵͳ����Ϣ�����У�����ϵͳ���Զ������Щ��Ϣ��û�з����ź�
	//����������źţ���ô�͵��ûص��������������Ϣ��Ӧ��socket�Ķ�����

	//�������socketͶ�ݵ�������,��ָ����Ϣ���
	int wNum = WSAAsyncSelect(socketServer, hWnd, UM_ASYNC, FD_ACCEPT);
	if (wNum == SOCKET_ERROR)
	{
		cout << "Ͷ�ݳ���" << endl;
	}


	//��Ϣѭ��
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
	//���ദ��
	switch (msgID)
	{
		case WM_CREATE:
			//�����ڳ�ʼ����ִֻ��һ��
			break;
		case UM_ASYNC:
		{
			//MessageBox(NULL, L"���ź���", L"��ʾ",MB_YESNO);
			//��ȡsocket
			SOCKET socket = (SOCKET)wParam;
			//��ȡ��Ϣ
			//û�д�����
			if (HIWORD(lParam) != 0)
			{
				break;
			}
			switch (LOWORD(lParam))
			{
				case FD_ACCEPT:
				{
					//�ڴ�������ı�
					TextOut(hdc, 0, y, L"accept", 6);
					y += 15;
					//���տͻ���socket
					SOCKET clientSocket = accept(socket, NULL, NULL);
					if (INVALID_SOCKET == clientSocket)
					{
						cout << "�ͻ���socket��������" << endl;
					}
					//���ͻ���socketͶ�ݵ�ϵͳ����Ϣ������
					if (SOCKET_ERROR == WSAAsyncSelect(clientSocket, hWnd, UM_ASYNC, FD_READ | FD_WRITE | FD_CLOSE))
					{
						cout << "socketͶ��ʧ��" << endl;
						closesocket(clientSocket);
					}
					break;
				}

				case FD_READ:
				{
					//FD_READ�źţ��ͻ���socket�������ݣ��������Ҫ���գ�����recv����
					char buf[1500] = { 0 };
					recv(socket, buf, 1499, 0);
					TextOut(hdc, 0, y, L"read", 5);
					y += 15;
					break;
				}

				case FD_WRITE:
				{
					//FD_WRITE�źţ��ͻ���socket�������ݣ�ִֻ��һ��
					send(socket, "write", strlen("write"), 0);
					break;
				}

				case FD_CLOSE:
				{
					//FD_CLOSE�źţ��ͻ��˶Ͽ�����
					//���ټ�����socket�ϵ���Ϣ
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
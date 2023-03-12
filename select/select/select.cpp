#include<iostream>
using namespace std;
#define FD_SETSIZE 128
#include<WinSock2.h>
#include <ws2tcpip.h> 
#pragma comment(lib,"Ws2_32.lib")

//定义一个结构体存储socket
fd_set allSockets;

BOOL WINAPI fun(DWORD dwCtrlType)
{
	switch (dwCtrlType)
	{
		//单击控制台的X，会调用这个回调函数，关闭socket和网络库
	case CTRL_CLOSE_EVENT:
		for (int i = 0; allSockets.fd_count; i++)
		{
			closesocket(allSockets.fd_array[i]);
		}
		WSACleanup();
	}
	return TRUE;
}

int main()
{

	//使用控制台，在关闭窗口后，关闭已经打开的socket
	SetConsoleCtrlHandler(fun, TRUE);
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

	//select模型：将所有的socket都放到一个结构体中，遍历这个结构体，找出所有的有响应的socket，反馈出来进行处理。

	//SELECT，遍历socket数组，找出有响应的socket，分别进行处理

	//初始化结构体
	FD_ZERO(&allSockets);
	//将服务器socket放进去
	FD_SET(socketServer, &allSockets);
	//等待时间3s
	timeval st;
	st.tv_sec = 3;
	st.tv_usec = 0;

	while (1)
	{
		fd_set tempSockets = allSockets;
		int selRes = select(0, &tempSockets, NULL, NULL, &st);
		//没有响应的socket
		if (selRes == 0)
		{
			continue;
		}
		//有响应的socket
		else if (selRes > 0)
		{
			for (u_int i = 0; i < tempSockets.fd_count; i++)
			{
				//服务端socket响应用accept
				if (tempSockets.fd_array[i] == socketServer)
				{
					SOCKET socketClient = accept(socketServer, NULL, NULL);
					if (socketClient == SOCKET_ERROR)
					{
						cout << "客户端socket创建失败" << endl;
						continue;
					}
					//与客户端建立链接
					//将客户端soscket加入socket数组中
					FD_SET(socketClient, &allSockets);
					//可以向客户端发送消息了
					cout << "创建连接成功" << endl;
				}
				//客户端socket响应用recv
				else
				{
					char rbuf[1500] = { 0 };
					int nRec = recv(tempSockets.fd_array[i], rbuf, 1500, 0);
					//客户端断开链接
					if (nRec == 0)
					{
						//将客户端从总的socket数组中删除
						SOCKET tempSocket = tempSockets.fd_array[i];
						FD_CLR(tempSockets.fd_array[i], &allSockets);
						closesocket(tempSocket);
						cout << "客户端正常断开连接" << endl;
					}
					//接收到客户端消息
					else if (nRec > 0)
					{
						cout << rbuf << endl;
					}
					//出错
					else
					{
						cout << "sfdsdf" << endl;
						cout << "客户端强制关闭，断开连接" << endl;
						SOCKET tempSocket1 = tempSockets.fd_array[i];
						FD_CLR(tempSockets.fd_array[i], &allSockets);
						closesocket(tempSocket1);
					}
				}
			}
		}
	}
	return 0;
}

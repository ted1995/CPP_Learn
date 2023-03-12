#include<iostream>
using namespace std;
#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")


int main()
{
	//打开网络库
	WORD wd_version = MAKEWORD(2, 2);
	WSADATA wdsockmsg;
	int nRes = WSAStartup(wd_version, &wdsockmsg);
	if (nRes != 0)
	{
		cout << "网络库打开失败" << endl;
	}
	else
	{
		cout << "网络库打开成功" << endl;
	}

	//校验版本
	if (HIBYTE(wdsockmsg.wVersion) != 2 && LOBYTE(wdsockmsg.wVersion) != 2)
	{
		cout << "版本不对" << endl;
	}

	//创建服务端socket
	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketServer == INVALID_SOCKET)
	{
		cout << "socket创建失败" << endl;
	}
	else
	{
		cout << "创建socket成功" << endl;
	}

	//连接服务器
	sockaddr_in sockin_server;
	sockin_server.sin_family = AF_INET;
	sockin_server.sin_addr.S_un.S_addr = inet_addr("192.168.174.135");
	sockin_server.sin_port = htons(22);
	int con_res = connect(socketServer, (sockaddr*)&sockin_server, sizeof(sockin_server));
	if (con_res == SOCKET_ERROR)
	{
		cout << "连接失败" << endl;
	}
	else
	{
		cout << "连接成功" << endl;
	}


	char buf[1500] = { 0 };
	int recv_num = recv(socketServer, buf, 1499, 0);
	cout << buf << endl;

	while (1)
	{
		//收发数据

		

		char sbuf[1500] = { 0 };
		cout << "请输入要发送的数据:" << endl;
		cin >> sbuf;
		if (sbuf[0] == '0')
		{
			break;
		}
		send(socketServer, sbuf, strlen(sbuf), 0);
		

	}
	closesocket(socketServer);
	WSACleanup();
	system("pause");
	return 0;
}

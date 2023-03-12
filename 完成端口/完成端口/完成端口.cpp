

#include<iostream>
using namespace std;
#include<WinSock2.h>
#include <ws2tcpip.h> 
#include<Mswsock.h>
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Mswsock.lib")
#define MAX_COUNT 1024


//定义socket数组
SOCKET allSocket[MAX_COUNT];
//定义重叠io数组
OVERLAPPED allLap[MAX_COUNT];
//定义计数器
int ocount;
//接收缓冲区
char str[1024] = { 0 };

int postSend(int ocount);
int postRecv(int ocount);
DWORD WINAPI ThreadProc(LPVOID lpParameter);
int postAccept();

int postRecv(int ocount)
{
	WSABUF wsabuf;
	wsabuf.buf = str;
	wsabuf.len = 1024;
	DWORD recvLen;
	DWORD dflag = 0;
	//投递客户端的Recv
	int recvNum = WSARecv(allSocket[ocount], &wsabuf, 1, &recvLen, &dflag, &allLap[ocount], NULL);
	if (recvNum == 0)
	{
		//投递recv立即成功
		cout << "投递recv立即成功" << endl;
		cout << wsabuf.buf << endl;
		//清空缓冲区，用于下一次接收
		memset(str, 0, 1024);
		//继续下次投递
		postRecv(ocount);
		return 0;
	}
	else
	{
		int a = WSAGetLastError();
		if (a == ERROR_IO_PENDING)
		{
			cout << "投递recv成功，但延迟处理" << endl;
			return 0;
		}
		else
		{
			cout << "投递recv出错" << endl;
			return 0;
		}

	}

}


int postSend(int ocount)
{
	WSABUF wsabuf;
	wsabuf.buf = (CHAR*)"您已成功连接服务器";
	wsabuf.len = 1024;
	DWORD sendLen;
	DWORD dflag = 0;
	//投递客户端的Recv
	int recvNum = WSASend(allSocket[ocount], &wsabuf, 1, &sendLen, dflag, &allLap[ocount], NULL);
	if (recvNum == 0)
	{
		//投递recv立即成功
		cout << "投递send立即成功" << endl;
		return 0;
	}
	else
	{
		int a = WSAGetLastError();
		if (a == ERROR_IO_PENDING)
		{
			cout << "投递send成功，但延迟处理" << endl;
			return 0;
		}
		else
		{
			cout << "投递send出错" << endl;
			return 0;
		}
	}
}


//投递服务器的socket，异步接收链接请求
int postAccept()
{
	char str1[1];
	DWORD dwRecvcount;
	//创建一个socket，用来存储客户端的信息
	allSocket[ocount] = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	//创建一个新的事件
	allLap[ocount].hEvent = WSACreateEvent();
	//绑定socket和客户端的信息，形成一个客户端的socket,同时可以接受客户端发送的第一条数据，并投递AcceptEx给系统
	bool ANum = AcceptEx(allSocket[0], allSocket[ocount], str1, 0, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &dwRecvcount, &allLap[0]);
	if (ANum == true)
	{
		cout << "投递成功，连接立即完成了" << endl;
		//对刚刚连接的客户端socket投递recv
		postRecv(ocount);
		//根据情况投递send
		//数组下标前进一格，用于下次存储
		ocount++;
		//立即完成，则递归的调用这个函数，重复的投递AcceptEx
		postAccept();
	}
	else
	{
		int a = WSAGetLastError();
		if (a == ERROR_IO_PENDING)
		{
			//所谓延时执行就是当时没有客户端连接，单开一个线程进行等待连接
			cout << "投递成功，连接延时执行" << endl;
		}
		else
		{
			cout << "投递AcceptEx出错了" << endl;
		}

	}
	return 0;
}


//线程执行函数
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	HANDLE port = (HANDLE)lpParameter;
	//传递的字节数
	DWORD numberOfBytes;
	//下标
	ULONG_PTR index;
	LPOVERLAPPED overLapped;
	//获取完成端口的状态，当有重叠任务完成时，在多个调用该函数的线程中挑选一个线程返回，并返回相应的结构用于Accept，Recv，Send等操作。
	while (1)
	{
		BOOL bNum = GetQueuedCompletionStatus(port, &numberOfBytes, &index, &overLapped, INFINITE);
		if (bNum == false)
		{
			cout << "获取完成端口状态出错" << endl;
		}

		//处理accept
		if (index == 0)
		{
			//接收到一个客户端连接请求，重叠结构中生成了客户端的socket，将其绑定到完成端口
			HANDLE cport1 = CreateIoCompletionPort((HANDLE)allSocket[ocount], port, ocount, 0);
			if (cport1 != port)
			{
				cout << "客户端socket绑定完成端口失败" << endl;
				closesocket(allSocket[ocount]);
			}

			//投递新客户端的recv
			//postRecv(ocount);
			ocount++;
			//投递新的socket等待连接
			postAccept();
		}
		else
		{
			if (numberOfBytes == 0)
			{
				cout << "客户端下线" << endl;
				closesocket(allSocket[index]);
				WSACloseEvent(allLap[index].hEvent);
				//socket在绑定完成端口时已经指定了其绑定的下标，因此不能再交换socket的位置，只能将其置空
				allSocket[index] = 0;
				allLap[index].hEvent = NULL;
			}
			else
			{

				cout << "接收到数据：" << str << endl;
				memset(str, 0, 1024);
				postRecv(index);
			}
		}
	}
	return 0;
}





int main()
{

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


	//创建一个用于异步操作的服务端socket
	SOCKET serverSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (serverSocket == SOCKET_ERROR)
	{
		cout << "服务端socket创建失败" << endl;
		closesocket(serverSocket);
	}


	//给socket绑定服务端的端口与ip地址
	sockaddr_in server_sockin;
	server_sockin.sin_family = AF_INET;
	server_sockin.sin_port = htons(12345);
	server_sockin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int reBindNum = bind(serverSocket, (sockaddr*)&server_sockin, sizeof(server_sockin));
	if (SOCKET_ERROR == reBindNum)
	{
		cout << "绑定失败" << endl;
	}

	//创建服务端socket和重叠结构事件数组
	allSocket[ocount] = serverSocket;
	allLap[ocount].hEvent = WSACreateEvent();
	ocount++;

	//创建完成端口
	HANDLE cport = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (cport == 0)
	{
		cout << "完成端口创建失败" << endl;
	}


	//绑定socket和完成端口
	HANDLE cport1 = CreateIoCompletionPort(HANDLE(serverSocket), cport, 0, 0);
	if (cport1 != cport)
	{
		cout << "完成端口绑定失败" << endl;
		CloseHandle(cport);
	}


	//监听
	int lNum = listen(serverSocket, SOMAXCONN);
	if (lNum == SOCKET_ERROR)
	{
		int a = WSAGetLastError();
		cout << "监听失败:" << a << endl;
		closesocket(serverSocket);
	}
	else
	{
		cout << "开始监听" << endl;
	}



	//投递
	postAccept();

	//先获得cpu的核数
	SYSTEM_INFO systemprocesscount;
	GetSystemInfo(&systemprocesscount);
	int processcount = systemprocesscount.dwNumberOfProcessors;

	//用malloc创建数组存储线程
	HANDLE *pThread = (HANDLE*)malloc(sizeof(HANDLE)*processcount);
	//创建线程,返回的是线程句柄
	for (int i = 0; i < processcount; i++)
	{
		pThread[i] = CreateThread(NULL, 0, ThreadProc, cport, 0, NULL);
		if (pThread[i] == NULL)
		{
			cout << "线程创建失败" << endl;
		}

	}

	//主线程阻塞在这里，以保证子线程的运行
	while (1)
	{
		Sleep(1000);
	}

	return 0;
}







#include<iostream>
using namespace std;
#define FD_SETSIZE 128
#include<WinSock2.h>
#include <ws2tcpip.h> 
#pragma comment(lib,"Ws2_32.lib")



//定义事件选择数组
class fd_se_set
{
public:
	//计算socket的数量，并实现增加或者删除的功能
	unsigned int count = 0;
	//默认最大的处理数量是64
	SOCKET sockAll[64];
	WSAEVENT eventAll[64];

};


BOOL WINAPI fun(DWORD dwCtrlType)
{
	switch (dwCtrlType)
	{
		//单击控制台的X，会调用这个回调函数，关闭socket和网络库
	case CTRL_CLOSE_EVENT:
		break;
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



	//事件选择模型：创建一个事件，给事件绑定上一个socket与操作码，并投递给操作系统，哪一个事件发出信号，就处理哪一个事件
	//其中我们会定义一个结构体存储事件数组和socket数组，并且下标一一对应，表示同一组的事件和socket

	//事件数组对象初始化
	fd_se_set seSet = { 0,{0},{0} };
	cout << "初始化成功" << endl;
	//创建事件
	WSAEVENT eventServer = WSACreateEvent();
	if (WSA_INVALID_EVENT == eventServer)
	{
		//
		cout << "创建事件失败" << endl;
	}
	else
	{
		cout << "服务端事件创建成功" << endl;
	}
	//绑定服务端socket，并将事件投递给系统
	//第一个参数是socket，第二个参数是事件，第三个是绑定的操作
	int aNum = WSAEventSelect(socketServer, eventServer, FD_ACCEPT);
	if (aNum == SOCKET_ERROR)
	{
		cout << "事件与服务端socket绑定失败" << endl;
	}
	else
	{
		cout << "服务端事件与socket绑定成功并投递" << endl;
	}

	//将事件放进事件数组中
	seSet.eventAll[seSet.count] = eventServer;
	seSet.sockAll[seSet.count] = socketServer;
	seSet.count++;

	//拿出有信号的事件
	while (1)
	{
		
		////第一个参数是事件的个数,第二个参数是事件列表，第三个参数是事件等待方式，返回值是下标,第四个参数是信号检查方式，
		//DWORD nRes = WSAWaitForMultipleEvents(seSet.count, seSet.eventAll, false, WSA_INFINITE, false);
		//if (WSA_WAIT_FAILED == nRes)
		//{
		//	cout << "取出事件出错" << endl;
		//	continue;
		//}
		//if (WSA_WAIT_TIMEOUT == nRes)
		//{
		//	cout << "取出事件超时" << endl;
		//	continue;
		//}

		////取出事件的下标
		//DWORD nIndex = nRes - WSA_WAIT_EVENT_0;

		////得到下标对应的具体操作
		//WSANETWORKEVENTS netWorkEvent;
		//if (SOCKET_ERROR == WSAEnumNetworkEvents(seSet.sockAll[nIndex], seSet.eventAll[nIndex], &netWorkEvent))
		//{
		//	cout << "得到事件出错" << endl;
		//	continue;
		//}


		////进行位与运算，得真，则说明是FD_ACCEPT信号
		//if (netWorkEvent.lNetworkEvents&FD_ACCEPT)
		//{
		//	//判断FD_ACCEPT没有错误码，则正常连接，否则跳过进行下一次循环
		//	//FD_ACCEPT_BIT是存放accept错误码数组的下标，每一个下标对应一个错误码
		//	if (0 == netWorkEvent.iErrorCode[FD_ACCEPT_BIT])
		//	{
		//		//正常处理

		//		//接收客户端的socket，用于以后的处理
		//		SOCKET clientSocket = accept(seSet.sockAll[nIndex], NULL, NULL);
		//		//如果得到的客户端socket是无效的,跳过本次，进行下次循环
		//		if (INVALID_SOCKET == clientSocket)
		//		{
		//			cout << "客户端socket接受失败" << endl;
		//			continue;
		//		}

		//		//创建一个客户端事件
		//		WSAEVENT clientEvent = WSACreateEvent();
		//		//如果创建的事件是无效的
		//		if (WSA_INVALID_EVENT == clientEvent)
		//		{
		//			cout << "客户端时间创建失败" << endl;
		//			//关闭刚刚接收的客户端socket
		//			closesocket(clientSocket);
		//			continue;
		//		}
		//		//绑定客户端socket与客户端事件，并将事件投递给系统
		//		int bNum=WSAEventSelect(clientSocket, clientEvent, FD_READ | FD_WRITE | FD_CLOSE);
		//		//如果投递出错
		//		if(bNum==SOCKET_ERROR)
		//		{
		//			cout << "事件投递出错" << endl;
		//			closesocket(clientSocket);
		//			WSACloseEvent(clientEvent);
		//			continue;
		//		}

		//		//将投递出去的事件与socket加入结构体中
		//		seSet.eventAll[seSet.count] = clientEvent;
		//		seSet.sockAll[seSet.count] = clientSocket;
		//		seSet.count++;
		//	}
		//	else
		//	{
		//		continue;
		//	}
		//}
		////客户端请求与服务端连接时,会产生两个信号，一个是FD_ACCEPT，信号发生在服务端，用以连接
		//	//另一个信号是FD_WRITE,信号发生在客户端，且只发生一次，用以服务端向客户端发送信息


		//	//进行位与运算，得真，则说明是FD_WRITE信号
		//if (netWorkEvent.lNetworkEvents&FD_WRITE)
		//{
		//	//判断FD_WRITE无错误码，信号正常
		//	if (0 == netWorkEvent.iErrorCode[FD_WRITE_BIT])
		//	{
		//		//向此客户端socket发送数据
		//		int cNum = send(seSet.sockAll[nIndex], "连接成功", strlen("连接成功"), 0);
		//		if (cNum == SOCKET_ERROR)
		//		{
		//			cout << "send函数执行出错" << endl;
		//			continue;
		//		}
		//	}
		//	else
		//	{
		//		continue;
		//	}
		//}


		////进行位与运算，得真，则说明是FD_READ信号
		//if (netWorkEvent.lNetworkEvents&FD_READ)
		//{
		//	//判断FD_READ无错误码，信号正常
		//	if (0 == netWorkEvent.iErrorCode[FD_READ_BIT])
		//	{
		//		//读取客户端socket发送的数据
		//		char strRecv[1500] = { 0 };
		//		int dNum = recv(seSet.sockAll[nIndex], strRecv, 1499, 0);
		//		if (dNum == SOCKET_ERROR)
		//		{
		//			cout << "recv函数执行出错" << endl;
		//			continue;
		//		}
		//		//打印接收到的数据
		//		cout << strRecv << endl;
		//	}
		//	else
		//	{
		//		continue;
		//	}
		//}


		////进行位与运算，得真，则说明是FD_CLOSE信号
		//if (netWorkEvent.lNetworkEvents&FD_CLOSE)
		//{
		//	//判断FD_CLOSE无错误码，信号正常
		//	if (0 == netWorkEvent.iErrorCode[FD_CLOSE_BIT])
		//	{
		//		//客户端下线
		//		cout << "客户端下线" << endl;
		//		//清理客户端的套接字和事件
		//		closesocket(seSet.sockAll[nIndex]);
		//		//将最后一个socket放到已经清理掉的socket的位置
		//		seSet.sockAll[nIndex] = seSet.sockAll[seSet.count - 1];

		//		WSACloseEvent(seSet.eventAll[nIndex]);
		//		//将最后一个事件放到已经清理掉的event的位置
		//		seSet.eventAll[nIndex] = seSet.eventAll[seSet.count - 1];
		//		seSet.count--;
		//	}
		//	else
		//	{
		//		continue;
		//	}
		//}



		//////////////////////////////优化版本/////////////////////////////
		//为防止快速访问导致的一直在执行某一个客户端的要求，因此对代码进行了优化
		for (int i = 0; i < seSet.count; i++)
		{
			//每次只遍历一个socket，检查是否有信号，有信号就执行，执行完成后，再去遍历下一个，没有信号就直接遍历下一个
			DWORD nRes = WSAWaitForMultipleEvents(1, &seSet.eventAll[i], false, 0, false);
			if (WSA_WAIT_FAILED == nRes)
			{
				cout << "取出事件出错" << endl;
				continue;
			}
			

			//得到下标对应的具体操作
			WSANETWORKEVENTS netWorkEvent;
			if (SOCKET_ERROR == WSAEnumNetworkEvents(seSet.sockAll[i], seSet.eventAll[i], &netWorkEvent))
			{
				cout << "得到事件出错" << endl;
				continue;
			}


			//进行位与运算，得真，则说明是FD_ACCEPT信号
			if (netWorkEvent.lNetworkEvents&FD_ACCEPT)
			{
				//判断FD_ACCEPT没有错误码，则正常连接，否则跳过进行下一次循环
				//FD_ACCEPT_BIT是存放accept错误码数组的下标，每一个下标对应一个错误码
				if (0 == netWorkEvent.iErrorCode[FD_ACCEPT_BIT])
				{
					//正常处理

					//接收客户端的socket，用于以后的处理
					SOCKET clientSocket = accept(seSet.sockAll[i], NULL, NULL);
					//如果得到的客户端socket是无效的,跳过本次，进行下次循环
					if (INVALID_SOCKET == clientSocket)
					{
						cout << "客户端socket接受失败" << endl;
						continue;
					}

					//创建一个客户端事件
					WSAEVENT clientEvent = WSACreateEvent();
					//如果创建的事件是无效的
					if (WSA_INVALID_EVENT == clientEvent)
					{
						cout << "客户端时间创建失败" << endl;
						//关闭刚刚接收的客户端socket
						closesocket(clientSocket);
						continue;
					}
					//绑定客户端socket与客户端事件，并将事件投递给系统
					int bNum = WSAEventSelect(clientSocket, clientEvent, FD_READ | FD_WRITE | FD_CLOSE);
					//如果投递出错
					if (bNum == SOCKET_ERROR)
					{
						cout << "事件投递出错" << endl;
						closesocket(clientSocket);
						WSACloseEvent(clientEvent);
						continue;
					}

					//将投递出去的事件与socket加入结构体中
					seSet.eventAll[seSet.count] = clientEvent;
					seSet.sockAll[seSet.count] = clientSocket;
					seSet.count++;
				}
				else
				{
					continue;
				}
			}
			//客户端请求与服务端连接时,会产生两个信号，一个是FD_ACCEPT，信号发生在服务端，用以连接
				//另一个信号是FD_WRITE,信号发生在客户端，且只发生一次，用以服务端向客户端发送信息


				//进行位与运算，得真，则说明是FD_WRITE信号
			if (netWorkEvent.lNetworkEvents&FD_WRITE)
			{
				//判断FD_WRITE无错误码，信号正常
				if (0 == netWorkEvent.iErrorCode[FD_WRITE_BIT])
				{
					//向此客户端socket发送数据
					int cNum = send(seSet.sockAll[i], "连接成功", strlen("连接成功"), 0);
					if (cNum == SOCKET_ERROR)
					{
						cout << "send函数执行出错" << endl;
						continue;
					}
				}
				else
				{
					continue;
				}
			}


			//进行位与运算，得真，则说明是FD_READ信号
			if (netWorkEvent.lNetworkEvents&FD_READ)
			{
				//判断FD_READ无错误码，信号正常
				if (0 == netWorkEvent.iErrorCode[FD_READ_BIT])
				{
					//读取客户端socket发送的数据
					char strRecv[1500] = { 0 };
					int dNum = recv(seSet.sockAll[i], strRecv, 1499, 0);
					if (dNum == SOCKET_ERROR)
					{
						cout << "recv函数执行出错" << endl;
						continue;
					}
					//打印接收到的数据
					cout << strRecv << endl;
				}
				else
				{
					continue;
				}
			}


			//进行位与运算，得真，则说明是FD_CLOSE信号
			if (netWorkEvent.lNetworkEvents&FD_CLOSE)
			{
				//判断FD_CLOSE无错误码，信号正常
				if (0 == netWorkEvent.iErrorCode[FD_CLOSE_BIT])
				{
					//客户端下线
					cout << "客户端下线" << endl;
					//清理客户端的套接字和事件
					closesocket(seSet.sockAll[i]);
					//将最后一个socket放到已经清理掉的socket的位置
					seSet.sockAll[i] = seSet.sockAll[seSet.count - 1];

					WSACloseEvent(seSet.eventAll[i]);
					//将最后一个事件放到已经清理掉的event的位置
					seSet.eventAll[i] = seSet.eventAll[seSet.count - 1];
					seSet.count--;
				}
				else
				{
					continue;
				}
			}
		}
		
		
	}

	//将有信号的事件重置为无信号




	return 0;
}



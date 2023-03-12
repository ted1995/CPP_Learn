//#include<iostream>
//using namespace std;
//#include<WinSock2.h>
//#include <ws2tcpip.h> 
//#include<Mswsock.h>
//#pragma comment(lib,"Ws2_32.lib")
//#pragma comment(lib,"Mswsock.lib")
//#define MAX_COUNT 1024
//
//
////定义socket数组
//SOCKET allSocket[MAX_COUNT];
////定义重叠结构数组
//OVERLAPPED allLap[MAX_COUNT];
////定义计数器
//int ocount;
////接收缓冲区
//char str[1024] = { 0 };
//
//
//
//void CALLBACK sendCall();
//void CALLBACK recvCall();
//int postSend(int ocount);
//int postRecv(int ocount);
//
////recv的回调函数
//void CALLBACK recvCall(DWORD dwError, DWORD cbTransfer, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
//{
//	////由重叠事件获取socket下标，效率低
//	//int i = 0;
//	//for (i; i < ocount; i++)
//	//{
//	//	//获得下标
//	//	if (allLap[i].hEvent == lpOverlapped->hEvent)
//	//	{
//	//		break;
//	//	}
//	//}
//
//	//指针的本质是一个地址，而地址相减得到的是元素个数，而不是字节数的差值
//	//T *a, *b;
//	//a - b = (a与b值的算术差值) / sizeof(T);
//	//效率高的获取i的方法
//	int i = lpOverlapped - &allLap[0];
//
//	if (dwError == 10054|cbTransfer==0)
//	{
//		cout << "客户端强制退出或者正常下线" << endl;
//		//关闭客户端
//		closesocket(allSocket[i]);
//		WSACloseEvent(allLap[i].hEvent);
//		//数组中删除
//		//如果数组中只有一个客户端和一个服务端的socket，删除这个客户端，将最后一个空的socket直接移到删除的socket那里
//		if (ocount == 2)
//		{
//			allSocket[i] = allSocket[ocount];
//			allLap[i] = allLap[ocount];
//			ocount--;
//		}
//		else
//		{
//			allSocket[i] = allSocket[ocount - 1];
//			allSocket[ocount - 1] = allSocket[ocount];
//			allLap[i] = allLap[ocount - 1];
//			allLap[ocount - 1] = allLap[ocount];
//			ocount--;
//		}
//	}
//	else
//	{
//		cout << str << endl;
//		memset(str, 0, 1024);
//		//继续投递当前socket的recv信号，等待响应
//		postRecv(i);
//	}
//
//}
//
////send的回调函数
//void CALLBACK sendCall(DWORD dwError, DWORD cbTransfer, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
//{
//	cout << "发送完成" << endl;
//}
//
//int postRecv(int ocount)
//{
//	WSABUF wsabuf;
//	wsabuf.buf = str;
//	wsabuf.len = 1024;
//	DWORD recvLen;
//	DWORD dflag = 0;
//	//投递客户端的Recv
//	int recvNum = WSARecv(allSocket[ocount], &wsabuf, 1, &recvLen, &dflag, &allLap[ocount], recvCall);
//	if (recvNum == 0)
//	{
//		//投递recv立即成功
//		cout << "投递recv立即成功" << endl;
//		cout << wsabuf.buf << endl;
//		//清空缓冲区，用于下一次接收
//		memset(str, 0, 1024);
//		//继续下次投递
//		postRecv(ocount);
//		return 0;
//	}
//	else
//	{
//		int a = WSAGetLastError();
//		if (a == ERROR_IO_PENDING)
//		{
//			cout << "投递recv成功，但延迟处理" << endl;
//			return 0;
//		}
//		else
//		{
//			cout << "投递recv出错" << endl;
//			return 0;
//		}
//
//	}
//
//}
//
//
//int postSend(int ocount)
//{
//	WSABUF wsabuf;
//	wsabuf.buf = "您已成功连接服务器";
//	wsabuf.len = 1024;
//	DWORD sendLen;
//	DWORD dflag = 0;
//	//投递客户端的Recv
//	int recvNum = WSASend(allSocket[ocount], &wsabuf, 1, &sendLen, dflag, &allLap[ocount], sendCall);
//	if (recvNum == 0)
//	{
//		//投递recv立即成功
//		cout << "投递send立即成功" << endl;
//		return 0;
//	}
//	else
//	{
//		int a = WSAGetLastError();
//		if (a == ERROR_IO_PENDING)
//		{
//			cout << "投递send成功，但延迟处理" << endl;
//			return 0;
//		}
//		else
//		{
//			cout << "投递send出错" << endl;
//			return 0;
//		}
//	}
//}
//
//
////投递服务器的socket，异步接收链接请求
//int postAccept()
//{
//	while (1)
//	{
//		char str1[1];
//		DWORD dwRecvcount;
//		//创建一个socket，用来存储客户端的信息
//		allSocket[ocount] = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
//		//创建一个新的事件
//		allLap[ocount].hEvent = WSACreateEvent();
//		//绑定socket和客户端的信息，形成一个客户端的socket,同时可以接受客户端发送的第一条数据，并投递AcceptEx给系统
//		bool ANum = AcceptEx(allSocket[0], allSocket[ocount], str1, 0, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &dwRecvcount, &allLap[0]);
//		if (ANum == true)
//		{
//			cout << "投递成功，连接立即完成了" << endl;
//			//对刚刚连接的客户端socket投递recv
//			postRecv(ocount);
//			//根据情况投递send
//			//数组下标前进一格，用于下次存储
//			ocount++;
//		}
//		else
//		{
//			int a = WSAGetLastError();
//			if (a == ERROR_IO_PENDING)
//			{
//				//所谓延时执行就是当时没有客户端连接，单开一个线程进行等待连接
//				cout << "投递成功，连接延时执行" << endl;
//				break;
//			}
//			else
//			{
//				cout << "投递AcceptEx出错了" << endl;
//				break;
//			}
//		}
//	}
//	return 0;
//}
//
//
//
////io重叠完成例程的意思是，我们告诉系统，说“我想要在网络上接收网络数据，你去帮我办一下”（投递WSARecv操作），“不过我并不知道网络数据合适到达，总之在接收到网络数据之后，你直接就调用我给你的这个函数(比如_CompletionProess)，把他们保存到内存中或是显示到界面中等等，全权交给你处理了”，系统会给我们一个通知，同时自动调用回调函数。
//
//
////和事件通知相比，完成例程在信号接受完成以后系统直接调用回调函数，因此不需要像事件通知一样还要判断分类，分别执行。
//
//
////WSAWaitForMultipleEvents本来就会返回有信号的事件的下标，而在完成例程中，这个函数除了在事件有信号时返回，还会在信号的回调函数执行完成以后也会返回一个通知，告诉回调函数也就是完成例程已经执行完毕。
//
//
//
//int main()
//{
//
//	//打开网络库，进行网络编程
//	WORD wdVersion = MAKEWORD(2, 2);
//	WSADATA wdSockMsg;
//	int nRes = WSAStartup(wdVersion, &wdSockMsg);
//	if (nRes != 0)
//	{
//		//打开失败
//		cout << "网络库打开失败" << endl;
//	}
//
//	//校验版本
//	//高字节是副版本，低字节是主版本
//	if (HIBYTE(wdSockMsg.wVersion) != 2 && LOBYTE(wdSockMsg.wVersion) != 2)
//	{
//		//版本不对，关闭网络库，结束
//		WSACleanup();
//		return 0;
//	}
//
//
//	//创建一个用于异步操作的服务端socket
//	SOCKET serverSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
//	if (serverSocket == SOCKET_ERROR)
//	{
//		cout << "服务端socket创建失败" << endl;
//		closesocket(serverSocket);
//	}
//
//
//	//给socket绑定服务端的端口与ip地址
//	sockaddr_in server_sockin;
//	server_sockin.sin_family = AF_INET;
//	server_sockin.sin_port = htons(12345);
//	server_sockin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	int reBindNum = bind(serverSocket, (sockaddr*)&server_sockin, sizeof(server_sockin));
//	if (SOCKET_ERROR == reBindNum)
//	{
//		cout << "绑定失败" << endl;
//	}
//
//
//	//监听
//	int lNum = listen(serverSocket, SOMAXCONN);
//	if (lNum == SOCKET_ERROR)
//	{
//		int a = WSAGetLastError();
//		cout << "监听失败:" << a << endl;
//		closesocket(serverSocket);
//	}
//	else
//	{
//		cout << "开始监听" << endl;
//	}
//
//
//	
//
//
//	//创建服务端socket和重叠结构事件数组
//	allSocket[ocount] = serverSocket;
//	allLap[ocount].hEvent = WSACreateEvent();
//	ocount++;
//
//	//投递
//	postAccept();
//
//
//	while (1)
//	{
//		//等待服务器的socket产生信号
//		int wNum = WSAWaitForMultipleEvents(1, &(allLap[0].hEvent), FALSE, WSA_INFINITE, TRUE);
//		//函数执行出错
//		if (wNum == WSA_WAIT_FAILED)
//		{
//			cout << "等待信号函数执行失败" << endl;
//			continue;
//		}
//		//函数执行没有出错
//		else if (wNum == WSA_WAIT_IO_COMPLETION)
//		{
//			cout << "完成例程即回调函数执行完毕" << endl;
//			continue;
//		}
//		else
//		{
//			cout << "等待到服务器事件信号" << endl;
//			//重置事件信号
//			WSAResetEvent(allLap[0].hEvent);
//			postSend(ocount);
//			postRecv(ocount);
//			//投递下一个空的socket的accept，等待客户端的连接
//			ocount++;
//			postAccept();
//			continue;
//		}
//	}
//
//	return 0;
//}
//
//
//

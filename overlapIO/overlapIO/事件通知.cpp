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



int postRecv(int ocount)
{
	WSABUF wsabuf;
	wsabuf.buf = str;
	wsabuf.len = 1024;
	DWORD recvLen;
	DWORD dflag=0;
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
	wsabuf.buf = "您已成功连接服务器";
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


	//重叠io事件模型的主要思想就是，先创建一个socket，然后将这个socket的AcceptEx先投递出去，如果有客户端请求连接时，会在重叠结构中（即新开一个子线程中，不会影响主线程的程序运行），将这个客户端的信息存放到已经创建好的这个socket中，此时客户端的socket就创建完毕，然后将这个客户端socket的WSARecv投递出去，等待客户端发来消息，如果有客户端发来信息，就会在重叠结构中接收这个消息并打印，然后再次投递这个socket的WSARecv，然后再创建一个新的socket，将这个socket的AcceptEx投递出去，等待下一个请求连接的客户端。


	//重叠io的本质就是将socket的操作投递出去，等待信号来的时候在子线程中执行相应的操作，在主线程中投递出去以后，就不用了再管了，这样就可以同时处理很多个客户端的操作，效率很高，不会都在主线程中执行，造成拥塞。


	//创建服务端socket和重叠结构事件数组
	allSocket[ocount] = serverSocket;
	allLap[ocount].hEvent = WSACreateEvent();
	ocount++;

	//投递
	postAccept();


	while (1)
	{
		for (int i = 0; i < ocount; i++)
		{
			//一个一个遍历，重叠操作事件有信号就返回
			int wNum=WSAWaitForMultipleEvents(1, &(allLap[i].hEvent),FALSE,0,FALSE);
			//函数执行出错
			if (wNum == WSA_WAIT_FAILED)
			{
				cout << "等待信号函数执行失败" << endl;
				continue;
			}
			//函数执行没有出错
			else if (wNum == WSA_WAIT_TIMEOUT)
			{
				//cout << "没有等待到事件信号" << endl;
				continue;
			}
			else
			{
				cout << "等待到事件信号" << endl;
				DWORD dState;
				DWORD dFlag;
				//获取对应socket上的重叠操作事件的结果
				//设置为true，直到重叠操作完成，函数才会返回
				//重叠操作完成，就是投递出去的accept，recv等在子线程中执行完成。
				//如果是accept那么就在子线程中生成一个客户端的socket，如果是recv，那就在子线程中将数据接收到执行的缓冲区中。
				bool gNum = WSAGetOverlappedResult(allSocket[i], &allLap[i], &dState, TRUE, &dFlag);
				//重置事件的信号
				WSAResetEvent(allLap[i].hEvent);
				//重叠操作未完成
				if (gNum == FALSE)
				{
					int a = WSAGetLastError();
					//客户端强制关闭
					if (a == 10054)
					{
						cout << "客户端强制关闭下线" << endl;
						//关闭socket和事件
						closesocket(allSocket[i]);
						WSACloseEvent(allLap[i].hEvent);
						//数组中删除
						//如果数组中只有一个客户端和一个服务端的socket，删除这个客户端，将最后一个空的socket直接移到删除的socket那里
						if (ocount == 2)
						{
							allSocket[i] = allSocket[ocount];
							allLap[i] = allLap[ocount];
							ocount--;
						}
						else
						{
							allSocket[i] = allSocket[ocount - 1];
							allSocket[ocount - 1] = allSocket[ocount];
							allLap[i] = allLap[ocount - 1];
							allLap[ocount - 1] = allLap[ocount];
							ocount--;
						}
					}
					else
					{
						cout << "重叠操作未完成" << endl;
					}
					continue;
				}
				//重叠操作完成
				//事件有信号，且重叠操作完成，开始执行具体操作
				//如果是服务端socket，那一定是由客户端连接，如果是客户端那可能是接收或者发送消息
				else if (gNum == TRUE)
				{
					//服务端socket特殊，先进行判断
					if (i == 0)
					{
						//i==0,说明是服务端socket接受accept连接完成了
						//一个新的客户端socket被加入到数组中，此时可以对这个客户端投递recv和send
						cout << "接收连接完成了" << endl;
						//对当前刚生成的客户端socket投递recv和send，在重叠结构中接收客户端发来的消息以及向客户端发送信息
						postSend(ocount);
						postRecv(ocount);
						//投递下一个空的socket的accept，等待客户端的连接
						ocount++;
						postAccept();
						continue;
					}

					//如果i!=0，说明肯定是客户端的信号，那么肯定是接收或者发送数据。
					//dState是接收的字节数，如果是0，就表示没有接收到东西，那么客户端很可能下线了
					if (dState == 0)
					{
						cout << "客户端下线" << endl;
						//关闭socket和事件
						closesocket(allSocket[i]);
						WSACloseEvent(allLap[i].hEvent);
						//数组中删除
						//如果数组中只有一个客户端和一个服务端的socket，删除这个客户端，将最后一个空的socket直接移到删除的socket那里
						if (ocount == 2)
						{
							allSocket[i] = allSocket[ocount];
							allLap[i] = allLap[ocount];
							ocount--;
						}
						else
						{
							allSocket[i] = allSocket[ocount-1];
							allSocket[ocount - 1]= allSocket[ocount];
							allLap[i] = allLap[ocount-1];
							allLap[ocount - 1]= allLap[ocount];
							ocount--;
						}
						//继续遍历被换过来的那个socket
						i--;
						continue;
					}
					//如果接收的字节数不是0，说明确实接收到客户端的发送的数据了，直接打印即可
					if (dState != 0)
					{
						cout << "发送或者接收成功了" << endl;
						//打印接收到的数据
						cout << str << endl;
						memset(str, 0, 1024);
						//继续投递当前socket的recv信号，等待响应
						postRecv(i);
						continue;
					}
				}
				
			}
		}
		
	}

	return 0;
}




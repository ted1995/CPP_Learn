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
////����socket����
//SOCKET allSocket[MAX_COUNT];
////�����ص��ṹ����
//OVERLAPPED allLap[MAX_COUNT];
////���������
//int ocount;
////���ջ�����
//char str[1024] = { 0 };
//
//
//
//void CALLBACK sendCall();
//void CALLBACK recvCall();
//int postSend(int ocount);
//int postRecv(int ocount);
//
////recv�Ļص�����
//void CALLBACK recvCall(DWORD dwError, DWORD cbTransfer, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
//{
//	////���ص��¼���ȡsocket�±꣬Ч�ʵ�
//	//int i = 0;
//	//for (i; i < ocount; i++)
//	//{
//	//	//����±�
//	//	if (allLap[i].hEvent == lpOverlapped->hEvent)
//	//	{
//	//		break;
//	//	}
//	//}
//
//	//ָ��ı�����һ����ַ������ַ����õ�����Ԫ�ظ������������ֽ����Ĳ�ֵ
//	//T *a, *b;
//	//a - b = (a��bֵ��������ֵ) / sizeof(T);
//	//Ч�ʸߵĻ�ȡi�ķ���
//	int i = lpOverlapped - &allLap[0];
//
//	if (dwError == 10054|cbTransfer==0)
//	{
//		cout << "�ͻ���ǿ���˳�������������" << endl;
//		//�رտͻ���
//		closesocket(allSocket[i]);
//		WSACloseEvent(allLap[i].hEvent);
//		//������ɾ��
//		//���������ֻ��һ���ͻ��˺�һ������˵�socket��ɾ������ͻ��ˣ������һ���յ�socketֱ���Ƶ�ɾ����socket����
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
//		//����Ͷ�ݵ�ǰsocket��recv�źţ��ȴ���Ӧ
//		postRecv(i);
//	}
//
//}
//
////send�Ļص�����
//void CALLBACK sendCall(DWORD dwError, DWORD cbTransfer, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
//{
//	cout << "�������" << endl;
//}
//
//int postRecv(int ocount)
//{
//	WSABUF wsabuf;
//	wsabuf.buf = str;
//	wsabuf.len = 1024;
//	DWORD recvLen;
//	DWORD dflag = 0;
//	//Ͷ�ݿͻ��˵�Recv
//	int recvNum = WSARecv(allSocket[ocount], &wsabuf, 1, &recvLen, &dflag, &allLap[ocount], recvCall);
//	if (recvNum == 0)
//	{
//		//Ͷ��recv�����ɹ�
//		cout << "Ͷ��recv�����ɹ�" << endl;
//		cout << wsabuf.buf << endl;
//		//��ջ�������������һ�ν���
//		memset(str, 0, 1024);
//		//�����´�Ͷ��
//		postRecv(ocount);
//		return 0;
//	}
//	else
//	{
//		int a = WSAGetLastError();
//		if (a == ERROR_IO_PENDING)
//		{
//			cout << "Ͷ��recv�ɹ������ӳٴ���" << endl;
//			return 0;
//		}
//		else
//		{
//			cout << "Ͷ��recv����" << endl;
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
//	wsabuf.buf = "���ѳɹ����ӷ�����";
//	wsabuf.len = 1024;
//	DWORD sendLen;
//	DWORD dflag = 0;
//	//Ͷ�ݿͻ��˵�Recv
//	int recvNum = WSASend(allSocket[ocount], &wsabuf, 1, &sendLen, dflag, &allLap[ocount], sendCall);
//	if (recvNum == 0)
//	{
//		//Ͷ��recv�����ɹ�
//		cout << "Ͷ��send�����ɹ�" << endl;
//		return 0;
//	}
//	else
//	{
//		int a = WSAGetLastError();
//		if (a == ERROR_IO_PENDING)
//		{
//			cout << "Ͷ��send�ɹ������ӳٴ���" << endl;
//			return 0;
//		}
//		else
//		{
//			cout << "Ͷ��send����" << endl;
//			return 0;
//		}
//	}
//}
//
//
////Ͷ�ݷ�������socket���첽������������
//int postAccept()
//{
//	while (1)
//	{
//		char str1[1];
//		DWORD dwRecvcount;
//		//����һ��socket�������洢�ͻ��˵���Ϣ
//		allSocket[ocount] = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
//		//����һ���µ��¼�
//		allLap[ocount].hEvent = WSACreateEvent();
//		//��socket�Ϳͻ��˵���Ϣ���γ�һ���ͻ��˵�socket,ͬʱ���Խ��ܿͻ��˷��͵ĵ�һ�����ݣ���Ͷ��AcceptEx��ϵͳ
//		bool ANum = AcceptEx(allSocket[0], allSocket[ocount], str1, 0, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &dwRecvcount, &allLap[0]);
//		if (ANum == true)
//		{
//			cout << "Ͷ�ݳɹ����������������" << endl;
//			//�Ըո����ӵĿͻ���socketͶ��recv
//			postRecv(ocount);
//			//�������Ͷ��send
//			//�����±�ǰ��һ�������´δ洢
//			ocount++;
//		}
//		else
//		{
//			int a = WSAGetLastError();
//			if (a == ERROR_IO_PENDING)
//			{
//				//��ν��ʱִ�о��ǵ�ʱû�пͻ������ӣ�����һ���߳̽��еȴ�����
//				cout << "Ͷ�ݳɹ���������ʱִ��" << endl;
//				break;
//			}
//			else
//			{
//				cout << "Ͷ��AcceptEx������" << endl;
//				break;
//			}
//		}
//	}
//	return 0;
//}
//
//
//
////io�ص�������̵���˼�ǣ����Ǹ���ϵͳ��˵������Ҫ�������Ͻ����������ݣ���ȥ���Ұ�һ�¡���Ͷ��WSARecv���������������Ҳ���֪���������ݺ��ʵ����֮�ڽ��յ���������֮����ֱ�Ӿ͵����Ҹ�����������(����_CompletionProess)�������Ǳ��浽�ڴ��л�����ʾ�������еȵȣ�ȫȨ�����㴦���ˡ���ϵͳ�������һ��֪ͨ��ͬʱ�Զ����ûص�������
//
//
////���¼�֪ͨ��ȣ�����������źŽ�������Ժ�ϵͳֱ�ӵ��ûص���������˲���Ҫ���¼�֪ͨһ����Ҫ�жϷ��࣬�ֱ�ִ�С�
//
//
////WSAWaitForMultipleEvents�����ͻ᷵�����źŵ��¼����±꣬������������У���������������¼����ź�ʱ���أ��������źŵĻص�����ִ������Ժ�Ҳ�᷵��һ��֪ͨ�����߻ص�����Ҳ������������Ѿ�ִ����ϡ�
//
//
//
//int main()
//{
//
//	//������⣬����������
//	WORD wdVersion = MAKEWORD(2, 2);
//	WSADATA wdSockMsg;
//	int nRes = WSAStartup(wdVersion, &wdSockMsg);
//	if (nRes != 0)
//	{
//		//��ʧ��
//		cout << "������ʧ��" << endl;
//	}
//
//	//У��汾
//	//���ֽ��Ǹ��汾�����ֽ������汾
//	if (HIBYTE(wdSockMsg.wVersion) != 2 && LOBYTE(wdSockMsg.wVersion) != 2)
//	{
//		//�汾���ԣ��ر�����⣬����
//		WSACleanup();
//		return 0;
//	}
//
//
//	//����һ�������첽�����ķ����socket
//	SOCKET serverSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
//	if (serverSocket == SOCKET_ERROR)
//	{
//		cout << "�����socket����ʧ��" << endl;
//		closesocket(serverSocket);
//	}
//
//
//	//��socket�󶨷���˵Ķ˿���ip��ַ
//	sockaddr_in server_sockin;
//	server_sockin.sin_family = AF_INET;
//	server_sockin.sin_port = htons(12345);
//	server_sockin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	int reBindNum = bind(serverSocket, (sockaddr*)&server_sockin, sizeof(server_sockin));
//	if (SOCKET_ERROR == reBindNum)
//	{
//		cout << "��ʧ��" << endl;
//	}
//
//
//	//����
//	int lNum = listen(serverSocket, SOMAXCONN);
//	if (lNum == SOCKET_ERROR)
//	{
//		int a = WSAGetLastError();
//		cout << "����ʧ��:" << a << endl;
//		closesocket(serverSocket);
//	}
//	else
//	{
//		cout << "��ʼ����" << endl;
//	}
//
//
//	
//
//
//	//���������socket���ص��ṹ�¼�����
//	allSocket[ocount] = serverSocket;
//	allLap[ocount].hEvent = WSACreateEvent();
//	ocount++;
//
//	//Ͷ��
//	postAccept();
//
//
//	while (1)
//	{
//		//�ȴ���������socket�����ź�
//		int wNum = WSAWaitForMultipleEvents(1, &(allLap[0].hEvent), FALSE, WSA_INFINITE, TRUE);
//		//����ִ�г���
//		if (wNum == WSA_WAIT_FAILED)
//		{
//			cout << "�ȴ��źź���ִ��ʧ��" << endl;
//			continue;
//		}
//		//����ִ��û�г���
//		else if (wNum == WSA_WAIT_IO_COMPLETION)
//		{
//			cout << "������̼��ص�����ִ�����" << endl;
//			continue;
//		}
//		else
//		{
//			cout << "�ȴ����������¼��ź�" << endl;
//			//�����¼��ź�
//			WSAResetEvent(allLap[0].hEvent);
//			postSend(ocount);
//			postRecv(ocount);
//			//Ͷ����һ���յ�socket��accept���ȴ��ͻ��˵�����
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

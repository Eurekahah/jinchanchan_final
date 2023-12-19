# include "server_and_client.h"
# include "HelloWorldScene.h"

bool isServerExist() { 

    SOCKET testSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in testAddr;
    testAddr.sin_family = AF_INET;
    testAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // ��������������ڱ���
    testAddr.sin_port = htons(22222); // �����������Ķ˿�

    int result = connect(testSocket, (sockaddr*)&testAddr, sizeof(testAddr));
    closesocket(testSocket);
    return 
        (result != SOCKET_ERROR);

}

void startServer(){
    
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsadata;
	if (WSAStartup(wVersion, &wsadata) != 0)
		return ;
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
		return ;
	//bind/listen�󶨡������˿�
	//�˿ں����������ĸ�Ӧ�÷���������
	sockaddr_in add;
	memset(&add, 0, sizeof(add));
	int len = sizeof(sockaddr_in);
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");//��������ӿڷ���
	add.sin_port = htons(22222);//ѡ���Ķ˿ں�����������������
	int i = ::bind(s, (sockaddr*)&add, len);
	if ( i== SOCKET_ERROR) {
		cerr << WSAGetLastError() << endl;
		//�󶨶˿ںź�ip
	}
	listen(s, 2);//����˲����뼸����
	//accept�ȴ���������
	//��ȡ�ͻ���ip��ַ�Լ��˿�
	sockaddr_in caddr;
	caddr.sin_family = AF_INET;
	int caddr_len = sizeof(sockaddr_in);
	SOCKET sclient = accept(s, (sockaddr*)&caddr, &caddr_len);
	
	if (sclient == INVALID_SOCKET)
		return ;
	int ret = send(sclient, "my message", strlen("my message"), 0);
	cout << "Server_Established" << endl;
	char ackBuf[256] = { 0 };
	int ackRet = recv(sclient, ackBuf, 256, 0);
	if (ackRet > 0) {
		cout << "received";
	}
	

	closesocket(sclient);
	WSACleanup();


}
void startClient(){

	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsadata;
	if (WSAStartup(wVersion, &wsadata) != 0)
		return ;
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
		return ;

	sockaddr_in add;
	int len = sizeof(sockaddr_in);
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//��ʾ����ip
	add.sin_port = htons(22222);
	//�������ӷ�����
	int i = connect(s, (sockaddr*)&add, len);
	if (SOCKET_ERROR == i)
		return ;
	//���ա���������
	char sbuf[256] = { 0 };
	int ret = recv(s, sbuf, 256, 0);
	if (ret == 0)//ɶҲû���յ�
		return ;//���ӶϿ�
	else if (ret > 0) {


		cout << "Client connected" << endl;
		
	}


	closesocket(s);
	WSACleanup();

}
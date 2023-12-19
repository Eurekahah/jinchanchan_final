# include "server_and_client.h"
# include "HelloWorldScene.h"

bool isServerExist() { 

    SOCKET testSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in testAddr;
    testAddr.sin_family = AF_INET;
    testAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // 假设服务器运行在本地
    testAddr.sin_port = htons(22222); // 服务器监听的端口

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
	//bind/listen绑定、监听端口
	//端口号用于区分哪个应用发来的数据
	sockaddr_in add;
	memset(&add, 0, sizeof(add));
	int len = sizeof(sockaddr_in);
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");//允许任意接口访问
	add.sin_port = htons(22222);//选定的端口号用来运行这个程序的
	int i = ::bind(s, (sockaddr*)&add, len);
	if ( i== SOCKET_ERROR) {
		cerr << WSAGetLastError() << endl;
		//绑定端口号和ip
	}
	listen(s, 2);//可以瞬间接入几个人
	//accept等待别人链接
	//获取客户端ip地址以及端口
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
	add.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//表示本机ip
	add.sin_port = htons(22222);
	//主动连接服务器
	int i = connect(s, (sockaddr*)&add, len);
	if (SOCKET_ERROR == i)
		return ;
	//接收、发送数据
	char sbuf[256] = { 0 };
	int ret = recv(s, sbuf, 256, 0);
	if (ret == 0)//啥也没接收到
		return ;//连接断开
	else if (ret > 0) {


		cout << "Client connected" << endl;
		
	}


	closesocket(s);
	WSACleanup();

}
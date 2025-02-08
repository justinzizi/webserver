#include "webserver.h"


WebServer::WebServer(){
    m_port = 8080;
    m_OPT_LINGER = 0;
}

WebServer::~WebServer()
{
    close(m_listenfd);

}

void WebServer::eventListen(){
    m_listenfd = socket(PF_INET, SOCK_STREAM,0);//创建ipv4的tcp套接字
    assert(m_listenfd >=0);// 确保套接字创建成功，否则程序终止

    if(0 == m_OPT_LINGER)//立即关闭套接字，不等待未发送的数据
    {
        struct linger tmp = {0,1};
        setsockopt(m_listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
    }else if(m_OPT_LINGER){//等待1s以内未发送的数据，超时后强制关闭
        struct linger tmp = {1,1};
        setsockopt(m_listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
    }

    int ret = 0;
    struct sockaddr_in address;//服务器的地址信息
    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);//可以监听所有的网络接口
    address.sin_port = htons(m_port);


    int flag = 1;
    setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));//允许重用本地地址和端口
    ret = bind(m_listenfd, (struct sockaddr *)&address,sizeof(address));
    assert(ret >= 0);
    ret = listen(m_listenfd,5);
    assert(ret >= 0);




}


bool WebServer::dealclientdata()//处理客户端连接请求
{
    struct sockaddr_in client_address;//存储客户端的地址信息
    socklen_t client_addrlength = sizeof(client_address);
    if(m_LISTENrigmode == 0){
        int connfd = accept(m_listenfd,(struct sockaddr *)&client_address,&client_addrlength);
        if(connfd < 0){
            //LOG_ERROR???
            return false;

        }
    }
    else{
        while (1)
        {
            int connfd = accept(m_listenfd,(struct sockaddr *)&client_address, &client_addrlength);
            if(connfd < 0){
                //LOG???
            }
        }
        
    }

}


void WebServer::dealwithread(int socket){
    
}

/*

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};

 

    

    std::cout << "Server listening on port " << PORT << "...\n";

    // 接受客户端连接
    while (true) {
        if ((client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len)) < 0) {
            std::cerr << "Accept failed\n";
            continue;
        }

        // 读取客户端请求
        read(client_fd, buffer, BUFFER_SIZE);
        std::cout << "Request:\n" << buffer << "\n";

        // 发送响应
        const char* response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
        write(client_fd, response, strlen(response));

        // 关闭连接
        close(client_fd);
    }

    return 0;
}*/
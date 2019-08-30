//http服务器伪代码
#if 0
//服务器响应头
void http_respond_head(int cfd, char *type)
{
    //状态行
    sprintf(buf,"http/1.1 200 OK\r\n");
    write(cfd,buf,strlen(buf));
    //消息报头
    sprintf(buf,"Content-Type:%s\r\n",type);
    write(cfd,buf,strlen(buf));
    //空行
    write(cfd,'\r\n',2);
    

}
void main()
{
    //修改进程的工作目录
    chdir（argv[2]);

    //创建套接字
    int lfd = socket();
    //绑定
    struct sockaddr_in serv;
    serv.family = af_inet;
    sesrv.port = 8989;
    serv.addr = 'inaddr_any';
    bind(lfd,&serv,len);
    //监听
    listen();
    int cfd = accept();
    //读数据
    read(cfd,buf,sizeof(buf));
    //先将buf中的请求行拿出来
    //GET /hello.c http/1.1
    char method[12] ,path[1024],protocol[12];
    //拿到文件名
    char *file = path+1;//因为第一个字符是'/'所以得加一
    //打开文件
    int fdd = open(file,0_RDONLY);
    int len = 0;
    //发送协议头
    http_respond_head(fdd,file.st_size);
    //循环读数据 因为缓冲区没有那么大 用ulimit -a看缓冲区大小 satck
    while(len = read(fdd,buf,sizeof(buf))>0)
    {
        //发送数据
        write(fdd,buf,len);
        

    }



}
#endif
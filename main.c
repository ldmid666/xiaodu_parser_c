#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "parser.grpc-c.h"
#include "httpd.h"

#define MAXLINE 4096
#define TRUE 1
#define FALSE 0
#define RESIGER_ERR 1
#define RESIGER_SUCC 0
static grpc_c_server_t *test_server;
void parser__parser__un_marshal_cb(grpc_c_context_t *context)
{
    int i;
    int ret;
    parser__UpReq *h = NULL;
    printf("[Unmarshal]\r\n");
    /*
     * Read incoming message into h
     */
    if (grpc_c_read(context, (void **)&h, 0, -1))
    {
        printf("Failed to read data from client\n");
    }
    if (h)
    {
        parser__up_req_free(h);
    }
    parser__UpRsp r;
    parser__UpRsp__init(&r);
    char buf[1024];
    buf[0] = '\0';
    snprintf(buf, 1024, "hello, world! from server.");
    r.id = h->id;
    r.err = NULL;
    r.name = h->name;
    r.has_payload = TRUE;
    r.payload.len = strlen(buf);
    r.payload.data = buf;
    /*
     * Write reply back to the client
     */
    ret = grpc_c_write(context, &r, 0, -1);
    if (ret)
    {
        printf("Failed to write %d\n", ret);
    }

    grpc_c_status_t status;
    status.code = 0;
    status.message[0] = '\0';

    /*
     * Finish response for RPC
     */
    if (grpc_c_finish(context, &status, 0))
    {
        printf("Failed to write status\n");
    }
}

void parser__parser__marshal_cb(grpc_c_context_t *context)
{
    printf("[marshal]\r\n");
}

int registerService()
{
    FILE *fstream = NULL;
    char cmd[] = "curl --request PUT 'http://127.0.0.1:8500/v1/agent/service/register' --header 'Content-Type: application/json' --data-raw '{\"id\":\"smartLamp_c\",\"name\":\"smartLamp_c\",\"address\":\"127.0.0.1\",\"port\":3000,\"tags\":[\"ldm company\"],\"checks\":[{\"http\":\"http://39.100.117.189:3000/ping\",\"interval\":\"5s\",\"DeregisterCriticalServiceAfter\":\"5m\"}]}'";
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    // 返回空表示执行成功
    if (NULL == (fstream = popen(cmd, "r")))
    {
        fprintf(stderr, "execute command failed: %s", strerror(errno));
        return RESIGER_ERR;
    }
    //
    while (NULL != fgets(buff, sizeof(buff), fstream))
    {
        printf("%s", buff);
    }
    pclose(fstream);
    if (0 == strlen(buff))
    {
        return RESIGER_SUCC;
    }
    return RESIGER_ERR;
}
// 实现.h中的函数
void route()
{
    ROUTE_START()

    ROUTE_GET("/ping")
    {
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("Hello! You are using %s", request_header("User-Agent"));
    }

    ROUTE_POST("/ping")
    {
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("Wow, seems that you POSTed %d bytes. \r\n", payload_size);
        printf("Fetch the data using `payload` variable.");
    }

    ROUTE_END()
}

int main()
{
    int ret;
    printf("====waiting for client's request=======\r\n");
    ret = registerService();
    if (ret != RESIGER_SUCC)
    {
        printf("registerService error\r\n");
    }
    serve_forever("3000"); //要把ping绑定值主机ip上
    //accept 和recv,注意接收字符串添加结束符'\0'
    grpc_c_init();
    test_server = grpc_c_server_create("127.0.0.1:3000", NULL, NULL);
    if (test_server == NULL)
    {
        printf("Failed to create server\n");
        exit(1);
    }
    /*
     * Initialize greeter service
     */
    parser__parser__service_init(test_server);

    /*
     * Start server
     */
    grpc_c_server_start(test_server);

    /*
     * Blocks server to wait to completion
     */
    grpc_c_server_wait(test_server);

    /*
     * Destory server
     */
    grpc_c_server_destroy(test_server);

    /*
     * Destory grpc-c library.
     */
    grpc_c_shutdown();
    return 0;
}

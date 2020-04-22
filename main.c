#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "parser.grpc-c.h"
#include "gateway.pb-c.h"
#include "httpd.h"
#include "mbedtls/aes.h"
#include "mbedtls/compat-1.3.h"

#define MAXLINE 4096
#define TRUE 1
#define FALSE 0
#define RESIGER_ERR 1
#define RESIGER_SUCC 0
#define MAX_MSG_SIZE 1024

#define TYPE_CMD "cmd"
#define TYPE_CONFIG "config"
#define CMD_ON "on"
#define CMD_OFF "off"
#define CMD_LAMP "lamp"
const unsigned char *key = "B31F2A75FBF94099";
#define MAX_SIZE 256
unsigned char IV[16] = "1234567890123456";
static grpc_c_server_t *test_server;

int CreateMarshalDown(Proto__Payload *msg, uint8_t *cypher_buf)
{
    uint8_t *proto_buf;
    size_t proto_len = 0;
    size_t len = 0;
    int aes_len = 0;
    mbedtls_aes_context aes;
    int ret_len = 0;

    len = proto__payload__get_packed_size(msg);
    proto_buf = (uint8_t *)malloc(MAX_SIZE);
    proto_len = proto__payload__pack(msg, proto_buf);
    printf("msg len = %ld,ret len = %ld \r\n", len, proto_len);
    //数据长度非16字节整除，则补齐
    int TXT_VALID_LENGTH = ((proto_len % 16 == 0) ? proto_len : (proto_len / 16 + 1) * 16);
    mbedtls_aes_setkey_enc(&aes, key, 128); //  set encrypt key
    aes_len = mbedtls_aes_crypt_cbc(&aes, AES_ENCRYPT, TXT_VALID_LENGTH, IV, proto_buf, cypher_buf);
    printf("aes_len = %d\r\n", aes_len);

    return ret_len;
}
int CreateUnMarshalUp(ProtobufCBinaryData *cypher_buf, Proto__Payload *msg)
{
    mbedtls_aes_context aes;
    unsigned char plain_decrypt[MAX_SIZE];
    mbedtls_aes_setkey_enc(&aes, key, 128); //  set encrypt key
    // 已经加密好的数据长度应该就是16的倍数了
    mbedtls_aes_crypt_cbc(&aes, AES_DECRYPT, cypher_buf->len, IV, cypher_buf->data, plain_decrypt);
    msg = proto__payload__unpack(NULL, cypher_buf->len, plain_decrypt);
    if (msg == NULL)
    {
        printf("error unpacking incoming message\r\n");
        exit(1);
    }
    return 0;
}
void parser__parser__un_marshal_cb(grpc_c_context_t *context)
{
    int i;
    int ret;
    parser__UpRsp r;
    parser__UpRsp__init(&r);

    Proto__Payload msg = PROTO__PAYLOAD__INIT;
    parser__UpReq *req = NULL;
    printf("[Unmarshal]\r\n");
    /*
     * Read incoming message into req
     */
    if (grpc_c_read(context, (void **)&req, 0, -1))
    {
        printf("Failed to read data from client\n");
    }

    CreateUnMarshalUp(&req->payload, &msg);
    if (msg.kind == PROTO__CATEGORY__CMD)
    {
        r.kind = TYPE_CMD;
        if (msg.key == PROTO__DEVICE__LAMP)
        {
            r.field = CMD_LAMP;
            if (msg.val.data[0] == PROTO__OPERATION__ON)
            {
                r.val = CMD_ON;
            }
            else
            {
                r.val = CMD_OFF;
            }
        }
    }
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
    if (req)
    {
        parser__up_req_free(req);
    }
}

void parser__parser__marshal_cb(grpc_c_context_t *context)
{
    int ret;
    Proto__Payload msg = PROTO__PAYLOAD__INIT;
    parser__DownReq *req = NULL;
    char CMD_ON_VAL[1] = {PROTO__OPERATION__ON};
    char CMD_OFF_VAL[1] = {PROTO__OPERATION__OFF};
    uint8_t cypher_buf[1024] = {0};
    parser__DownRsp rsp;

    printf("[marshal]\r\n");
    if (grpc_c_read(context, (void **)&req, 0, -1))
    {
        printf("Failed to read data from client\n");
        goto exit;
    }

    printf("kind=%s,field = %s,val = %s\r\n", req->kind, req->field, req->val);
    if (strcmp(req->kind, TYPE_CMD) == 0)
    {
        msg.kind = PROTO__CATEGORY__CMD;
        if (strcmp(req->field, CMD_LAMP) == 0)
        {
            msg.key = PROTO__DEVICE__LAMP;
            if (strcmp(req->val, CMD_ON) == 0)
            {
                ProtobufCBinaryData cmd_val;
                cmd_val.len = sizeof(CMD_ON_VAL);
                cmd_val.data = CMD_ON_VAL;
                msg.val = cmd_val;
            }
            else
            {
                ProtobufCBinaryData cmd_val;
                cmd_val.len = sizeof(CMD_OFF_VAL);
                cmd_val.data = CMD_OFF_VAL;
                msg.val = cmd_val;
            }
            CreateMarshalDown(&msg, cypher_buf);
        }
    }
    else if (strcmp(req->kind, TYPE_CONFIG) == 0)
    {
        printf("not support set config, now\r\n");
        // TODO:do something
        goto exit;
    }
    else
    {
        printf("[Marshal]kind error\r\n");
        goto exit;
    }
exit:
    /*
     * Create a reply
     */
    parser__DownRsp__init(&rsp);
    rsp.id = req->id;
    rsp.name = req->name;
    rsp.has_payload = 1;
    ProtobufCBinaryData pld;
    pld.len = 1024;
    pld.data = cypher_buf;
    rsp.payload = pld;
    ret = grpc_c_write(context, &rsp, 0, -1);
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
    if (req)
    {
        parser__down_req_free(req);
    }
}

int registerService()
{
    FILE *fstream = NULL;
    char cmd[] = "curl --request PUT 'http://127.0.0.1:8500/v1/agent/service/register' --header 'Content-Type: application/json' --data-raw '{\"id\":\"smartLamp_c\",\"name\":\"smartLamp_c\",\"address\":\"127.0.0.1\",\"port\":3000,\"tags\":[\"ldm company\"],\"checks\":[{\"http\":\"http://39.100.117.189:4000/ping\",\"interval\":\"5s\",\"DeregisterCriticalServiceAfter\":\"5m\"}]}'";
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
        // printf("Fetch the data using `payload` variable.");
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
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("fork ping server\r\n");
        serve_forever("4000"); //要把ping绑定值主机ip上
    }

    //accept 和recv,注意接收字符串添加结束符'\0'
    printf("grpc_c_init\r\n");
    grpc_c_init();
    // grpc_c_init(GRPC_THREADS, NULL);

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
    printf("grpc wait \r\n");
    grpc_c_server_wait(test_server);

    /*
     * Destory server
     */
    grpc_c_server_destroy(test_server);

    /*
     * Destory grpc-c library.
     */
    grpc_c_shutdown();
    printf("the end !");
    return 0;
}

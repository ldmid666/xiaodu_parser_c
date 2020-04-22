### protobuf-c 使用说明

使用说明参考工程[iot_gateway](https://github.com/ldmid666/iot_gateway)


### 其他说明
[grpc-c](https://github.com/lixiangyun/grpc-c)，[protobuf-c](https://github.com/protobuf-c/protobuf-c)是第三方的库。

protobuf如果想节约内存占用，应该用nanopb的c插件

[aes](https://blog.csdn.net/easychang/article/details/51960264) 库参考使用[mbed](https://tls.mbed.org/aes-source-code),适合嵌入式平台和linux.




常用命令:

rsync -zvr ./xiaodu_parser_c root@aliyun:/root/temp

protoc-c --c_out=. gateway.proto


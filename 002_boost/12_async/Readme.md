
## 怎么编译？

在当前目录下创建一个 `build` 目录，并进入这个目录。
然后执行 `cmake ..` 生成 xxx.sln
最后执行 `msbuild xxx.sln` 开始编译代码

## 怎么执行？

编译完成后，在`Debug`目录下会生成`client.exe`和`server.exe`.
开两个命令行，一个运行服务端，一个运行客户端。

服务端：
```Shell
build\Debug> .\server.exe
accept from: 127.0.0.1
write finished
```

客户端：
```
build\Debug> .\client.exe
conn to: 127.0.0.1
hello asio

127.0.0.1
```

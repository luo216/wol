# 使用esp8266搭配blinker实现远程开机

<!-- vim-markdown-toc GFM -->

* [linux上配置环境](#linux上配置环境)
* [代码及依赖](#代码及依赖)

<!-- vim-markdown-toc -->

## linux上配置环境

- 安装arduino-ide
```shell
paru -S arduino-ide-bin
```

- 打开软件后,在 File -> Preferences -> additional boards manager URL's 处添加 http://arduino.esp8266.com/stable/package_esp8266com_index.json

- 然后可以在boards manager中找到esp8266, install安装

- 然后我们再选择 esp8266的串口和对应的board(一般选nodemcu)

- 然后确认后，到Serial Monitor查看是否能够正常连接（如果报错了，大概率是串口权限问题）

- 用 `ls -l /dev/ttyUSB0` (ttyUSB0为你的串口)查看串口用户组
```shell
crw-rw---- 1 root uucp 188, 0  8月20日 16:55 /dev/ttyUSB0
```
- 可以看到有个uucp的用户组，我们将当前用户加入到这个用户组，就有权限访问该串口了（有时候没有生效就重启一下）
```shell
sudo usermod -a -G uucp $USER
```

## 代码及依赖

- [wol.ino](./wol.ino)
- 在wol.ino中设置好相关信息
```c
char auth[] = "点灯给你密钥";
char ssid[] = "WIFI名称";
char pswd[] = "WIFI密码";
const char *MACAddress = "需要被激活设备的MAC地址";
```
- 还需要下载 wakeonlan 和 blinker,在ide里面下就好了，注意blinker,新版本据说不想支持esp8266，所以稳妥起见用0.3.8版本
- 点击upload，烧录后记得verify确认一遍

- [点灯的界面设置](./blinker.txt)
- 下载软件blinker,打开后添加自定义设备，然后它会给一个密钥添wol.ino里
- 然后可以选择模板，或者导入我这个，注意开机的按钮要改成`btn-abc`

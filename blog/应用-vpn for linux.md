
@[TOC](应用-vpn for linux)
# 概述
<hr style=" border:solid; width:100%; height:2px;" color=#000000 size=1">

> <font size=4>主题：学习vpn for Linux开源项目<br />
> 简述：
	这段时间刚刚入学，拿到实验室分配的主机后，想要试试github的开源项目，于是乎就写了这么一个环境配置应用的博客。
	基本环境是ubuntu20.04 iso镜像，装好以后其他的没做什么多的操作，配置了一个虚拟机的网络桥接模式，达成与物理主机的网络互通后，直接上手配置，感谢大佬的[clash for linux](https://github.com/wanhebin/clash-for-linux)开源项目。
</font>

<hr style=" border:solid; width:100%; height:2px;" color=#000000 size=1">

# 1. 环境配置

<hr style=" border:solid; width:100%; height:2px;" color=#000000 size=1">

## 1.1 目标环境
>物理主机系统：windows10专业版64位
>虚拟机系统：ubuntu20.04
>物理主机与虚拟机之间的网络通信方式：桥接

<hr style=" border:solid; width:100%; height:2px;" color=#000000 size=1">

## 1.2 配置步骤
### 1.2.1 拉取项目代码
```
cd /home/ymh
git clone https://github.com/wanhebin/clash-for-linux.git
```
### 1.2.2 配置项目
>进入到刚刚拉取的项目目录里，用你的文本编辑程序编辑 .env 文件
```
cd clash-for-linux
vim .env
```
>编辑后的文件如图所示
![配置项目后的文件](https://img-blog.csdnimg.cn/8d82ff1779ca4d4f821f5d28bfc7c454.png#pic_center)
### 1.2.3 启动程序
>在程序目录下运行脚本start.sh启动程序

```
bash start.sh
```
>如果操作无误，程序正确，那么会看到以下图片提示你成功配置，否则查看[2.1启动失败](#jump1)
![启动程序](https://img-blog.csdnimg.cn/23f954e92b324003bf1e4a980f794e40.png#pic_center)

### 1.2.4 开启服务
>成功启动程序后，还需要开启服务这样才可以使你的配置生效
>看到这样的提示就说明生效了![开启服务](https://img-blog.csdnimg.cn/3b080176824345e5998a27dafa10612f.png#pic_center)

### 1.2.5 验证配置
>开启服务后，先输入以下命令检查端口以及服务是否正常开启，如图所示是正确效果图，7890/9090端口已经开放，并且服务都是通过7890端口
>![查看端口配置](https://img-blog.csdnimg.cn/d9f3236baa3449138b2b3aeec6e8cf03.png#pic_center)

>确认端口无误以后打开虚拟机中的浏览器，访问某个网页查看效果，至此所有步骤结束，成功配置并应用开源项目[clash for linux](https://github.com/wanhebin/clash-for-linux)，感谢大佬提供的开源项目
<hr style=" border:solid; width:100%; height:2px;" color=#000000 size=1">


# 2. 配置过程出现的问题解决方案
## 2.1 <span id="jump1">启动程序失败</span>
>url填写正确，执行启动脚本时报错```curl command not found```，实际上就是curl这个命令虚拟机没有install，所以先```sudo apt install curl```安装之后再启动脚本就解决了。
![启动失败报错](https://img-blog.csdnimg.cn/ec998e6abf0e44f79debfbc303def3b9.png#pic_center)
# 3. 资源分享
> ==旗木白哉のGitHub：==
> https://github.com/YangMengHeng
> ==GitHub/Gitee源代码下载地址：==
> **GitHub**
> https://github.com/YangMengHeng/myCode/tree/master/VSCode
> https://github.com/YangMengHeng/myCode/tree/master/Java
> **Gitee**
> https://gitee.com/QMBZ/myCode/tree/master/VSCode
> https://gitee.com/QMBZ/myCode/tree/master/Java
> ==旗木白哉のblog源代码下载地址：==
>https://github.com/YangMengHeng/myCode/tree/master/%E6%97%97%E6%9C%A8%E7%99%BD%E5%93%89%E3%81%AEblog
>https://gitee.com/QMBZ/myCode/tree/master/%E6%97%97%E6%9C%A8%E7%99%BD%E5%93%89%E3%81%AEblog

<hr style=" border:solid; width:100%; height:2px;" color=#000000 size=1">

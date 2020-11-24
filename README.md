# NotiSync-Qt

------

[这个项目](https://github.com/SquareFong/NotiSync-Qt)是配合[NotiSync](https://github.com/SquareFong/Notisync)和[NotiSync-Server](https://github.com/SquareFong/NotiSync-Server)使用的，关于这两个项目的介绍在[这里](https://leanote.squarefong.com/blog/post/squarefong/NotiSync%EF%BC%8C)。在做到通知同步的通知的同时，增加手机信息概览和短信回复的功能。下面是使用方式的简单展示

# 1. 使用方式

程序启动时会直接进入一个类似于登录页面的界面，这里就是配置信息，包含通信协议，服务器地址，服务器端口，和UUID。协议支持http和https，地址可以是IP地址，也可以是域名。
![LoginView](https://leanote.squarefong.com/api/file/getImage?fileId=5fbd6e052fc01e02bb0036c9)

配置好后即可使用用登录按钮登录。

登录后即进入主界面：
![Detail](https://leanote.squarefong.com/api/file/getImage?fileId=5fbd6ff02fc01e02bb0036ca)

左侧是软件能查看的信息，分别是手机详情，手机通知和手机短信。主界面默认停留在手机详情页。

当点击左侧的Notifications时，进入手机通知页，这里将显示所有在本客户端启动之后手机收到的通知：
![Notifications](https://leanote.squarefong.com/api/file/getImage?fileId=5fbd70932fc01e02bb0036cb)

当点击Messages时，进入手机短信页。这里将显示所有的手机短信，并且可以当场回复短信。在最右侧下方输入框输入后点击Send按钮，短信就会发送出去。如果想要发送的联系人不在已有对话框中，可点击New Message以新建短信，在输入对方电话号码后即可向对方发送短信。
![Messages](https://leanote.squarefong.com/api/file/getImage?fileId=5fbd72162fc01e02bb0036cc)

# 2. 注意事项

v0.2依然不是正式版，在短信上存在功能性Bug，界面性能也需要优化。

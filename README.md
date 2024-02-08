# x11guard

一个不是很有用的aur包，安装后，当有进程（偷偷）截屏时会用通知烦死你。

做这个是为了分析某些应用的截屏行为，众所周知X11协议下任意应用都是可以不经授权随意截全屏的。

如果你不是因为某种原因不得不用X11，建议使用Wayland。

- TODO
  - 利用strace分析X11协议，尽可能从底层抓取所有截屏请求。（目前自带x11库的应用不会被Hook，比如飞书。）
  - 根据脚本规则降噪。
  - 看看apparmor有没有相关实现。

A not-so-useful package that, once installed, will annoy you with notifications whenever a process (surreptitiously) takes a screenshot.

This is done to analyze the screenshot behavior of certain applications. As is well known, under the X11 protocol, any application can take a screenshot of the entire screen without authorization.

If you're not constrained by certain reasons to use X11, I recommend using Wayland.

- TODO:
  - Utilize strace to analyze the X11 protocol and capture all screenshot requests as thoroughly as possible from a low level. (Currently, applications that come with the X11 library, like Feishu, are not hooked.)
  - Reduce noise according to script rules.
  - Explore whether AppArmor has a relevant implementation.

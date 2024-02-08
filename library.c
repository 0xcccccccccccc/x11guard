// hook.c
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>


typedef XImage* (*orig_XGetImage_f_type)(Display*, Drawable, int, int, unsigned int, unsigned int, unsigned long, int);

void send_kde_notification() {
    // 获取当前进程ID
    pid_t pid = getpid();

    // 打开 /proc/[pid]/comm 来获取进程名
    char proc_path[32];
    sprintf(proc_path, "/proc/%d/comm", pid);

    FILE *fp = fopen(proc_path, "r");
    if (fp != NULL) {
        char proc_name[256];
        if (fgets(proc_name, sizeof(proc_name), fp) != NULL) {
            // 去除可能的换行符
            proc_name[strcspn(proc_name, "\n")] = 0;

            // 构建通知命令
            char notify_command[512];
            snprintf(notify_command, sizeof(notify_command),
                     "notify-send 'XGetImage Call' 'XGetImage function has been called by %s(PID=%d)'", proc_name, pid);

            // 发送 KDE 通知
            system(notify_command);
        }
        fclose(fp);
    }
}

XImage *XGetImage(Display *display, Drawable d, int x, int y, unsigned int width, unsigned int height, unsigned long plane_mask, int format) {
    orig_XGetImage_f_type orig_XGetImage;
    orig_XGetImage = (orig_XGetImage_f_type)dlsym(RTLD_NEXT, "XGetImage");

    // 发送通知
    send_kde_notification();

    // 调用原始的 XGetImage 函数
    return orig_XGetImage(display, d, x, y, width, height, plane_mask, format);
}
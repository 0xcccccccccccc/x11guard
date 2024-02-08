#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>


typedef XImage* (*orig_XGetImage_f_type)(Display*, Drawable, int, int, unsigned int, unsigned int, unsigned long, int);
typedef Bool (*orig_XShmGetImage_f_type)(Display*, Drawable, XImage*, int, int, unsigned long);
typedef int (*orig_XCopyArea_f_type)(Display*, Drawable, Drawable, GC, int, int, unsigned int, unsigned int, int, int);


void send_kde_notification(const char *entry) {
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
                     "notify-send '%s Call' '%s function has been called by %s(PID=%d)'", entry, entry, proc_name, pid);

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
    send_kde_notification("XGetImage");


    // 调用原始的 XGetImage 函数
    return orig_XGetImage(display, d, x, y, width, height, plane_mask, format);
}

Bool XShmGetImage(Display* disp, Drawable d, XImage* image, int x, int y, unsigned long plane_mask) {
    // Get the original XShmGetImage function pointer
    static orig_XShmGetImage_f_type orig_XShmGetImage = NULL;
    if (!orig_XShmGetImage) {
        orig_XShmGetImage = (orig_XShmGetImage_f_type)dlsym(RTLD_NEXT, "XShmGetImage");
    }

    // Send a notification
    send_kde_notification("XShmGetImage");

    // Call the original XShmGetImage function
    return orig_XShmGetImage(disp, d, image, x, y, plane_mask);
}

int XCopyArea(Display* disp, Drawable src, Drawable dest, GC gc, int src_x, int src_y, unsigned int width, unsigned int height, int dest_x, int dest_y) {
    // Get the original XCopyArea function pointer
    static orig_XCopyArea_f_type orig_XCopyArea = NULL;
    if (!orig_XCopyArea) {
        orig_XCopyArea = (orig_XCopyArea_f_type)dlsym(RTLD_NEXT, "XCopyArea");
    }

    // Send a notification
    send_kde_notification("XCopyArea");

    // Call the original XCopyArea function
    return orig_XCopyArea(disp, src, dest, gc, src_x, src_y, width, height, dest_x, dest_y);
}
#ifndef X11GUARD_LIBRARY_H
#define X11GUARD_LIBRARY_H

#include <X11/Xlib.h>
typedef XImage* (*orig_XGetImage_f_type)(Display*, Drawable, int, int, unsigned int, unsigned int, unsigned long, int);
XImage *XGetImage(Display *display, Drawable d, int x, int y, unsigned int width, unsigned int height, unsigned long plane_mask, int format);

#endif //X11GUARD_LIBRARY_H

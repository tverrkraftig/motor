#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
//#include "interface2.h"

#define KEYMASK ButtonPressMask | KeyPressMask | KeyReleaseMask | ButtonReleaseMask | PointerMotionMask

Display *display;
Window window;
XEvent event;
 
void windowInit()
{
    
    int s;
 
    /* open connection with the server */
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
 
    s = DefaultScreen(display);
 
    /* create window */
    window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 500, 500, 1,
                           BlackPixel(display, s), WhitePixel(display, s));
 
    /* select kind of events we are interested in */
    XSelectInput(display, window, KEYMASK);
 
    /* map (show) the window */
    XMapWindow(display, window);

    //do not detect autorepeating events from keyboard
    XAutoRepeatOff(display);
}
void checkEvent(){

        XNextEvent(display, &event);
 	switch(event.type){
/*		case MotionNotify:*/
/*			if(button)*/
/*				printf("x: %d\t y: %d\n",e.xmotion.x,e.xmotion.y);*/
/*			break;*/
/*		case ButtonPress:*/
/*			button = 1;*/
/*			break;*/
/*		case ButtonRelease:*/
/*			button = 0;*/
/*			break;*/
		case KeyPress:
			printf( "KeyPress: %x\n", event.xkey.keycode );
			break;
		case KeyRelease:
			printf( "KeyRelease: %x\n", event.xkey.keycode );
			break;
/*		case Expose:*/
/*			draw_screen();*/
/*			break;*/
        }
}

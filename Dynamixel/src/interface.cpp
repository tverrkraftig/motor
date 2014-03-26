#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

#define KEYMASK ButtonPressMask | KeyPressMask | KeyReleaseMask | ButtonReleaseMask | PointerMotionMask

#define FORWARD 98
#define BACKWARD 104
#define LEFT 100
#define RIGHT 102

#define LEFT_MOUSE_BUTTON 	1
#define RIGHT_MOUSE_BUTTON 	3
#define MOUSE_WHEEL		2
#define MOUSE_WHEEL_FORWARD	4
#define MOUSE_WHEEL_BACKWARD	5

Display *display;
Window window;
XEvent event;
bool button = 0;
int xpos = 0;
int ypos = 100;
int zpos = 0;
int xzero = 0;
int yzero = 0;
 
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
    window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 200, 200, 1,
                           BlackPixel(display, s), WhitePixel(display, s));
 
    /* select kind of events we are interested in */
    XSelectInput(display, window, KEYMASK);
 
    /* map (show) the window */
    XMapWindow(display, window);

    //do not detect autorepeating events from keyboard
    XAutoRepeatOff(display);
}
void checkEvent(Manipulator man){
        XNextEvent (display, & event);
        switch(event.type){
		case MotionNotify:
			if(button){
				xpos += event.xmotion.x - xzero;
				ypos += event.xmotion.y - yzero;
				xzero = event.xmotion.x;
				yzero = event.xmotion.y;
				printf("xpos: %d\t ypos: %d\n", xpos, ypos);
				man.goToPosition(xpos,ypos,zpos);
			}	
			break;
		case ButtonPress:
			if(event.xkey.keycode == LEFT_MOUSE_BUTTON)
			{
				button = 1;
				xzero = event.xbutton.x;
				yzero = event.xbutton.y;
			}
			if(event.xkey.keycode == MOUSE_WHEEL_FORWARD)
			{
				zpos+=10;
				man.goToPosition(xpos,ypos,zpos);
			}
			if(event.xkey.keycode == MOUSE_WHEEL_BACKWARD)
			{
				zpos-=10;
				man.goToPosition(xpos,ypos,zpos);
			}
			
			printf( "KeyPress: %d\n", event.xkey.keycode );
			break;
		case ButtonRelease:
			if(event.xkey.keycode == LEFT_MOUSE_BUTTON)
				button = 0;
			break;
		case KeyPress:
			//printf( "KeyPress: %d\n", e.xkey.keycode );
			switch(event.xkey.keycode){
				case FORWARD:
					printf("forward\n");
					break;
				case BACKWARD:
					printf("backward\n");
					break;
				case RIGHT:
					printf("right\n");
					break;
				case LEFT:
					printf("left\n");
					break;
				default:
					printf("unknown\n");
			}
			break;
		case KeyRelease:
			//printf( "KeyRelease: %d\n", e.xkey.keycode );
			switch(event.xkey.keycode){
				case FORWARD:
					printf("forward\n");
					break;
				case BACKWARD:
					printf("backward\n");
					break;
				case RIGHT:
					printf("right\n");
					break;
				case LEFT:
					printf("left\n");
					break;
				default:
					printf("unknown\n");
			}
			break;
	}
}

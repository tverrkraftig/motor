#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define FORWARD 98
#define BACKWARD 104
#define LEFT 100
#define RIGHT 102

#define LEFT_MOUSE_BUTTON 	1
#define RIGHT_MOUSE_BUTTON 	3
#define MOUSE_WHEEL		2
#define MOUSE_WHEEL_FORWARD	4
#define MOUSE_WHEEL_BACKWARD	5

/* The window which contains the text. */

struct {
    int width;
    int height;
    char * text;
    int text_len;

    /* X Windows related variables. */

    Display * display;
    int screen;
    Window root;
    Window window;
    GC gc;
    XFontStruct * font;
    unsigned long black_pixel;    
    unsigned long white_pixel;
}
text_box;

/* Connect to the display, set up the basic variables. */

static void x_connect ()
{
    text_box.display = XOpenDisplay (NULL);
    if (! text_box.display) {
        fprintf (stderr, "Could not open display.\n");
        exit (1);
    }
    text_box.screen = DefaultScreen (text_box.display);
    text_box.root = RootWindow (text_box.display, text_box.screen);
    text_box.black_pixel = BlackPixel (text_box.display, text_box.screen);
    text_box.white_pixel = WhitePixel (text_box.display, text_box.screen);
}

/* Create the window. */

static void create_window ()
{
    text_box.width = 500;
    text_box.height = 500;
    text_box.window = 
        XCreateSimpleWindow (text_box.display,
                             text_box.root,
                             1, /* x */
                             1, /* y */
                             text_box.width,
                             text_box.height,
                             0, /* border width */
                             text_box.black_pixel, /* border pixel */
                             text_box.white_pixel  /* background */);

    /* We don't need to select the events here. */

    XSelectInput (text_box.display, text_box.window,
                  ExposureMask | ButtonPressMask | KeyPressMask | KeyReleaseMask | ButtonReleaseMask | PointerMotionMask);
    XMapWindow (text_box.display, text_box.window);

	//disable autorepeat
	XAutoRepeatOff(text_box.display);
}

/* Set up the GC (Graphics Context). */

static void set_up_gc ()
{
    text_box.screen = DefaultScreen (text_box.display);
    text_box.gc = XCreateGC (text_box.display, text_box.window, 0, 0);
    XSetBackground (text_box.display, text_box.gc, text_box.white_pixel); 
    XSetForeground (text_box.display, text_box.gc, text_box.black_pixel); 
}

/* Set up the text font. */

static void set_up_font ()
{
    const char * fontname = "-*-helvetica-*-r-*-*-14-*-*-*-*-*-*-*";
    text_box.font = XLoadQueryFont (text_box.display, fontname);
    /* If the font could not be loaded, revert to the "fixed" font. */
    if (! text_box.font) {
        fprintf (stderr, "unable to load font %s: using fixed\n", fontname);
        text_box.font = XLoadQueryFont (text_box.display, "fixed");
    }
    XSetFont (text_box.display, text_box.gc, text_box.font->fid);
}

/* Draw the window. */

static void draw_screen ()
{
    int x;
    int y;
    int direction;
    int ascent;
    int descent;
    XCharStruct overall;

    /* Centre the text in the middle of the box. */

    XTextExtents (text_box.font, text_box.text, text_box.text_len,
                  & direction, & ascent, & descent, & overall);
    x = (text_box.width - overall.width) / 2;
    y = text_box.height / 2 + (ascent - descent) / 2;
    XClearWindow (text_box.display, text_box.window);
    XDrawString (text_box.display, text_box.window, text_box.gc,
                 x, y, text_box.text, text_box.text_len);
}

/* Loop over events. */

static void event_loop ()
{
    /* "wm_delete_window" is the Atom which corresponds to the delete
       window message sent by the window manager. */

    Atom wm_delete_window;
    wm_delete_window =
        XInternAtom (text_box.display, "WM_DELETE_WINDOW", False);

    /* Set up the window manager protocols. The third argument here is
       meant to be an array, and the fourth argument is the size of
       the array. */

    XSetWMProtocols (text_box.display, text_box.window, &wm_delete_window, 1);

	XEvent e;
        bool button = 0;
        int xpos = 0;
        int ypos = 0;
        int xzero = 0;
        int yzero = 0;

    while (1) {
        
        XNextEvent (text_box.display, & e);
        switch(e.type){
		case MotionNotify:
			if(button){
				xpos += e.xmotion.x - xzero;
				ypos += e.xmotion.y - yzero;
				xzero = e.xmotion.x;
				yzero = e.xmotion.y;
				printf("xpos: %d\t ypos: %d\n", xpos, ypos);
			}	
			break;
		case ButtonPress:
			button = 1;
			xzero = e.xbutton.x;
			yzero = e.xbutton.y;
			printf( "KeyPress: %d\n", e.xkey.keycode );	
			break;
		case ButtonRelease:
			button = 0;
			break;
		case KeyPress:
			//printf( "KeyPress: %d\n", e.xkey.keycode );
			switch(e.xkey.keycode){
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
			switch(e.xkey.keycode){
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
//		case Expose:
//			if(e.xexpose.count==0)
//				draw_screen();
//			break;
        }

        /* Deal with a client message from the window manager telling
           us to delete the window. */

        if (e.type == ClientMessage) {
            printf ("Closed by the window manager.\n");
            if ((Atom)e.xclient.data.l[0] == wm_delete_window) {
                break;
            }
        }
    }

    /* Close the connection to the display. This also deletes any
       windows and other stuff which might have been created. */

    XCloseDisplay (text_box.display);
}

int main (int argc, char ** argv)
{
    text_box.text = "Hello World";
    text_box.text_len = strlen (text_box.text);
    
    x_connect ();
    create_window ();
    set_up_gc ();
    set_up_font ();
    event_loop ();
    return 0;
}

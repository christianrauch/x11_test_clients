#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Hints
{
  unsigned long flags;
  unsigned long functions;
  unsigned long decorations;
  long inputMode;
  unsigned long status;
} Hints;
 
int
main (void)
{
  Display *d;
  Window w;
  XEvent e;
  const char *msg = "Test client";
  int s;
  Hints hints;
  Atom property;

  d = XOpenDisplay (NULL);
  if (d == NULL)
    {
      fprintf (stderr, "Cannot open display\n");
      exit (1);
    }

  s = DefaultScreen (d);
  w = XCreateSimpleWindow (d, RootWindow (d, s),
			   10, 10, 100, 100, 1,
			   BlackPixel (d, s), WhitePixel (d, s));
  XStoreName (d, w, "testx11");
  XSelectInput (d, w, ExposureMask | KeyPressMask);

  hints.flags = 2;
  hints.decorations = 0;
  property = XInternAtom (d, "_MOTIF_WM_HINTS", True);
  XChangeProperty (d, w, property, property,
		   32, PropModeReplace,
		   (unsigned char *) &hints, 5);

  XMapWindow (d, w);
  XFlush (d);

  usleep (26);

  XCloseDisplay (d);
  return 0;
}

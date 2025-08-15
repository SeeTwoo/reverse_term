#ifndef WINDOW_H
# define WINDOW_H

#include <stdbool.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct s_x11    t_x11;

struct s_x11 {
	Display			*display;
	Window			root;
	Window			win;
	int				screen;
	XEvent			event;
	Atom			wm_delete;
	GC				gc;
	XFontStruct		*font;
	unsigned int    tile_height;
	unsigned int	tile_width;
	unsigned int	margin;
	bool			cursor_on;
};                                                                                  

void	destroy_term(t_x11 *x11);
int		init_window(t_x11 *x11);
void	gc_bg_fg_swap(t_x11 *x11);

#endif             

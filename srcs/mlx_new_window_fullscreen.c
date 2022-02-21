/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_new_window_fullscreen.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:53:23 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/21 21:54:58 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_new_window.c for MiniLibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Mon Jul 31 17:29:02 2000 Charlie Root
** Last update Thu Oct  4 15:44:43 2001 Charlie Root
*/

/*
** We do not use White/BlackPixel macro, TrueColor Visual make sure
** 0 is black & -1 is white
**
** With mlx_int_wait_first_expose, no flush is needed.
*/

#include "mlx_int.h"
#include "mlx.h"

static void	create_window(t_xvar *xvar, t_win_list *new_win, XVisualInfo vinfo,
				XSetWindowAttributes xswa);
static void	create_gc(t_xvar *xvar, t_win_list *new_win);

void	*mlx_new_window_fullscreen(t_xvar *xvar, char *title)
{
	t_win_list				*new_win;
	XSetWindowAttributes	xswa;
	XVisualInfo				vinfo;

	XMatchVisualInfo(xvar->display, DefaultScreen(xvar->display), 32,
		TrueColor, &vinfo);
	xswa.background_pixel = 0x00000000;
	xswa.colormap = XCreateColormap(xvar->display,
			DefaultRootWindow(xvar->display), vinfo.visual, AllocNone);
	xswa.override_redirect = 1;
	xswa.event_mask = 0xFFFFFF;
	new_win = malloc(sizeof(*new_win));
	if (!new_win)
		return ((void *)0);
	create_window(xvar, new_win, vinfo, xswa);
	XStoreName(xvar->display, new_win->window, title);
	XSetWMProtocols(xvar->display, new_win->window, &(xvar->wm_delete_window),
		1);
	create_gc(xvar, new_win);
	new_win->next = xvar->win_list;
	xvar->win_list = new_win;
	bzero(&(new_win->hooks), sizeof(new_win->hooks));
	XMapRaised(xvar->display, new_win->window);
	mlx_int_wait_first_expose(xvar, new_win->window);
	return (new_win);
}

static void	create_window(t_xvar *xvar, t_win_list *new_win, XVisualInfo vinfo,
				XSetWindowAttributes xswa)
{
	int	size_x;
	int	size_y;

	mlx_get_screen_size(xvar, &size_x, &size_y);
	new_win->window = XCreateWindow(xvar->display, xvar->root, 0, 0, size_x,
			size_y, 0, vinfo.depth, InputOutput, vinfo.visual,
			CWEventMask | CWBackPixel | CWBorderPixel
			| CWColormap | CWOverrideRedirect, &xswa);
	mlx_int_anti_resize_win(xvar, new_win->window, size_x, size_y);
}

static void	create_gc(t_xvar *xvar, t_win_list *new_win)
{
	XGCValues	xgcv;

	xgcv.foreground = -1;
	xgcv.function = GXcopy;
	xgcv.plane_mask = AllPlanes;
	new_win->gc = XCreateGC(xvar->display, new_win->window,
			GCFunction | GCPlaneMask | GCForeground, &xgcv);
}

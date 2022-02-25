/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goose.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:04:49 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/25 17:56:41 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "goose.h"

static void	generate_goose_pos(t_xvar *xvar, t_goose *goose);
static void	get_direction(t_couple *start, t_couple *end, t_couple_double *direction);
Bool		MakeAlwaysOnTop(Display* display, Window root, Window mywin);

void	goose(t_xvar *mlx_ptr, t_win_list *w_list, t_img *img)
{
	t_direction	direction;
	t_goose		goose;
	t_goose		goose_final;
	t_goose		goose_start;
	int			t;

	MakeAlwaysOnTop(mlx_ptr->display, mlx_ptr->root, w_list->window);
	generate_goose_pos(mlx_ptr, &goose);
	while (1)
	{
		generate_goose_pos(mlx_ptr, &goose_final);
		goose_start = goose;
		get_direction(&goose_start, &goose_final, &direction);
		t = 0;
		while (t < (goose_final.x - goose_start.x) / (direction.x * GOOSE_SPEED / 50))
		{
			XClearArea(mlx_ptr->display, w_list->window, goose.x, goose.y,
				img->width, img->height, 0);
			goose.x = goose_start.x + 1.0 * t * GOOSE_SPEED * direction.x / 50;
			goose.y = goose_start.y + 1.0 * t * GOOSE_SPEED * direction.y / 50;
			if (abs(goose_final.x - goose.x) <= 3 && abs(goose_final.y - goose.y) <= 3)
				goose = goose_final;
			mlx_put_image_to_window(mlx_ptr, w_list, img, goose.x, goose.y);
			usleep(20000);
			t++;
		}
		usleep(5000000);
	}
}

static void	generate_goose_pos(t_xvar *mlx_ptr, t_goose *goose)
{
	mlx_get_screen_size(mlx_ptr, &goose->x, &goose->y);
	goose->x = rand() % goose->x;
	goose->y = rand() % goose->y;
}

static void get_direction(t_couple *start, t_couple *end, t_couple_double *direction)
{
	double	dist;
	double	dist_x;
	double	dist_y;

	dist_x = end->x - start->x;
	dist_y = end->y - start->y;
	dist = sqrt(dist_x * dist_x + dist_y * dist_y);
	direction->x = dist_x / dist;
	direction->y = dist_y / dist;
}

#define _NET_WM_STATE_REMOVE        0    // remove/unset property
#define _NET_WM_STATE_ADD           1    // add/set property
#define _NET_WM_STATE_TOGGLE        2    // toggle property

Bool MakeAlwaysOnTop(Display* display, Window root, Window mywin)
{
    Atom wmStateAbove = XInternAtom( display, "_NET_WM_STATE_ABOVE", 1 );
    if( wmStateAbove != None ) {
        printf( "_NET_WM_STATE_ABOVE has atom of %ld\n", (long)wmStateAbove );
    } else {
        printf( "ERROR: cannot find atom for _NET_WM_STATE_ABOVE !\n" );
        return False;
    }

    Atom wmNetWmState = XInternAtom( display, "_NET_WM_STATE", 1 );
    if( wmNetWmState != None ) {
        printf( "_NET_WM_STATE has atom of %ld\n", (long)wmNetWmState );
    } else {
        printf( "ERROR: cannot find atom for _NET_WM_STATE !\n" );
        return False;
    }

    // set window always on top hint
    if( wmStateAbove != None )
    {
        XClientMessageEvent xclient;
        memset( &xclient, 0, sizeof (xclient) );
        //
        //window  = the respective client window
        //message_type = _NET_WM_STATE
        //format = 32
        //data.l[0] = the action, as listed below
        //data.l[1] = first property to alter
        //data.l[2] = second property to alter
        //data.l[3] = source indication (0-unk,1-normal app,2-pager)
        //other data.l[] elements = 0
        //
        xclient.type = ClientMessage;
        xclient.window = mywin;              // GDK_WINDOW_XID(window);
        xclient.message_type = wmNetWmState; //gdk_x11_get_xatom_by_name_for_display( display, "_NET_WM_STATE" );
        xclient.format = 32;
        xclient.data.l[0] = _NET_WM_STATE_ADD; // add ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        xclient.data.l[1] = wmStateAbove;      //gdk_x11_atom_to_xatom_for_display (display, state1);
        xclient.data.l[2] = 0;                 //gdk_x11_atom_to_xatom_for_display (display, state2);
        xclient.data.l[3] = 0;
        xclient.data.l[4] = 0;
        //gdk_wmspec_change_state( FALSE, window,
        //  gdk_atom_intern_static_string ("_NET_WM_STATE_BELOW"),
        //  GDK_NONE );
        XSendEvent( display,
          //mywin - wrong, not app window, send to root window!
          root, // <-- DefaultRootWindow( display )
          False,
          SubstructureRedirectMask | SubstructureNotifyMask,
          (XEvent *)&xclient );

        XFlush(display);

        return True;
    }

    return False;
}

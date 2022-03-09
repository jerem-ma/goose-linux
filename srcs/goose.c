/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goose.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:04:49 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/09 17:26:39 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "goose.h"
#include <math.h>

//static void	generate_goose_pos(t_xvar *xvar, t_goose *goose);
//static void	get_direction(t_couple *start, t_couple *end, t_couple_double *direction);
Bool	MakeAlwaysOnTop(Display* display, Window root, Window mywin);
t_img	*rotate(t_xvar *mlx_ptr, t_img *img, double angle);
void	shear(double angle, double *x, double *y);

void	goose(t_xvar *mlx_ptr, t_win_list *w_list, t_img *img)
{
	double	i;
	t_img	*r_img;

	MakeAlwaysOnTop(mlx_ptr->display, mlx_ptr->root, w_list->window);
	i = 0;
	while (i < 2 * M_PI)
	{
		XClearWindow(mlx_ptr->display, w_list->window);
		r_img = rotate(mlx_ptr, img, i);
		mlx_put_image_to_window(mlx_ptr, w_list, r_img, 40, 40);
		i += 0.1;
		usleep(100000);
		if (i > 2 * M_PI - 0.2)
			i = 0;
	}
}

t_img	*rotate(t_xvar *mlx_ptr, t_img *img, double angle)
{
	t_img			*r_img;
	int				new_width;
	int				new_height;
	t_couple		pos_old_img;
	t_couple		pos_new_img;
	int				junk;
	int				*data;
	int				*r_data;;

	new_width = round(fabs(img->width * cos(angle)) + fabs(img->height * sin(angle)))+1;
	new_height = round(fabs(img->height * cos(angle)) + fabs(img->width * sin(angle)))+1;
	r_img = mlx_new_image(mlx_ptr, new_width, new_height);
	if (!r_img)
		return (0);
//	double	original_centre_height = round(((double) img->height+1)/2);
//	double	original_centre_width = round(((double) img->width+1)/2);
//
//	double	new_centre_height = round(((double) new_height+1)/2);
//	double	new_centre_width = round(((double) new_width+1)/2);
	int	original_centre_height = img->height / 2;
	int	original_centre_width = img->width / 2;

	int	new_centre_height = new_height / 2;
	int	new_centre_width = new_width / 2;
	data = (int *) mlx_get_data_addr(img, &junk, &junk, &junk);
	r_data = (int *) mlx_get_data_addr(r_img, &junk, &junk, &junk);
	pos_new_img.y = 0;
	while (pos_new_img.y < new_height)
	{
		pos_new_img.x = 0;
		while (pos_new_img.x < new_width)
		{
			(void) new_centre_height;
			(void) new_centre_width;
			(void) original_centre_width;
			(void) original_centre_height;
			pos_old_img.x = (int) ((pos_new_img.x - new_centre_width) * cos(angle) - (pos_new_img.y - new_centre_height) * sin(angle) + new_centre_width);
			pos_old_img.y = (int) ((pos_new_img.x - new_centre_width) * sin(angle) + (pos_new_img.y - new_centre_height) * cos(angle) + new_centre_height);
			r_data[(int) pos_new_img.y * new_width + (int) pos_new_img.x] = data[(int) pos_old_img.y * img->width + (int) pos_old_img.x];
			pos_new_img.x++;
		}
		pos_new_img.y++;
	}
	return (r_img);
}

//static void	generate_goose_pos(t_xvar *mlx_ptr, t_goose *goose)
//{
//	mlx_get_screen_size(mlx_ptr, &goose->x, &goose->y);
//	goose->x = rand() % goose->x;
//	goose->y = rand() % goose->y;
//}
//
//static void get_direction(t_couple *start, t_couple *end, t_couple_double *direction)
//{
//	double	dist;
//	double	dist_x;
//	double	dist_y;
//
//	dist_x = end->x - start->x;
//	dist_y = end->y - start->y;
//	dist = sqrt(dist_x * dist_x + dist_y * dist_y);
//	direction->x = dist_x / dist;
//	direction->y = dist_y / dist;
//}

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

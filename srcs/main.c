/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:13:07 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/11 16:01:05 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/extensions/shape.h>
#include <X11/extensions/Xfixes.h>

#include "goose.h"

#include <unistd.h>
#include <time.h>

static void	remove_input(t_xvar *mlx_ptr, t_win_list *w_list);

int	main(void)
{	
	t_xvar					*mlx_ptr;
	t_win_list				*w_list;
	t_img					*img;

	srand(time(NULL));
	mlx_ptr = mlx_init();
	XSynchronize(mlx_ptr->display, True);
	if (!mlx_ptr)
		return (0);
	img = farbfeld_to_img(mlx_ptr, "res/little_goose.ff");
	if (!img)
	{
		destroy_everything(mlx_ptr, 0);
		return (0);
	}
	w_list = mlx_new_window_fullscreen(mlx_ptr, "Goose");
	if (!mlx_ptr->win_list)
	{
		destroy_everything(mlx_ptr, w_list);
		return (0);
	}
	remove_input(mlx_ptr, w_list);
	goose(mlx_ptr, w_list, img);
	destroy_everything(mlx_ptr, w_list);
}

static void	remove_input(t_xvar *mlx_ptr, t_win_list *w_list)
{
	XserverRegion	region;
	XRectangle		rect;

	region = XFixesCreateRegion(mlx_ptr->display, &rect, 1);
	XFixesSetWindowShapeRegion(mlx_ptr->display, w_list->window, ShapeInput,
		0, 0, region);
	XFixesDestroyRegion(mlx_ptr->display, region);
}

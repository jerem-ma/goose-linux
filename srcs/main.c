/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:13:07 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/07 21:34:14 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libgen.h>
#include <X11/extensions/shape.h>
#include <X11/extensions/Xfixes.h>

#include "goose.h"

#include <unistd.h>
#include <time.h>

static void	remove_input(t_xvar *mlx_ptr, t_win_list *w_list);

int	main(int ac, char **av)
{	
	t_xvar		*mlx_ptr;
	t_win_list	*w_list;
	t_img		*img;
	char		*path;

	(void) ac;
	srand(time(NULL));
	mlx_ptr = mlx_init();
	XSynchronize(mlx_ptr->display, True);
	if (!mlx_ptr)
		return (0);
	path = malloc(sizeof(*path) * 500);
	memcpy(path, dirname(strdup(av[0])), strlen(dirname(strdup(av[0]))));
	path[strlen(dirname(strdup(av[0])))] = 0;
	printf("%s\n", path);
	img = farbfeld_to_img(mlx_ptr, strcat(path, "/res/pouet.ff"));
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

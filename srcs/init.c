/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 01:24:23 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/02/20 01:25:18 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "capivara.h"

void	init_cap(t_c_data *data)
{
	data->mlx_ptr = mlx_init();
	XSynchronize(data->mlx_ptr->display, True);
	if (!data->mlx_ptr)
	{
		exit (0);
	}
	data->img = farbfeld_to_img(data->mlx_ptr, "res/little_goose.ff");
	if (!data->img)
	{
		destroy_everything(data->mlx_ptr, 0);
		exit (0);
	}
		data->w_list = mlx_new_window_fullscreen(data->mlx_ptr, "Capivara");
	if (!data->mlx_ptr->win_list)
	{
		destroy_everything(data->mlx_ptr, data->w_list);
		exit (0);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->w_list, data->img, 0, 0);
}
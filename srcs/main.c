/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:13:07 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/20 01:36:03 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "capivara.h"

int	main(void)
{
	t_c_data	data;
	int			x;
	int			y;

	init_cap(&data);
	while (1)
	{
		mlx_mouse_get_pos(data.mlx_ptr, data.w_list, &x, &y);
		mlx_put_image_to_window(data.mlx_ptr, data.w_list, data.img, x, y);
		usleep(100000);
	}
	sleep(500);
	destroy_everything(data.mlx_ptr, data.w_list);
}

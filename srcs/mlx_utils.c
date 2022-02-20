/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:13:28 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/20 01:14:35 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "capivara.h"

void	destroy_everything(t_xvar *mlx_ptr, t_win_list *w_list)
{
	if (!mlx_ptr)
		return ;
	if (w_list)
		mlx_destroy_window(mlx_ptr, w_list);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}

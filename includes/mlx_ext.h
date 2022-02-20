/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_ext.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:56:47 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/20 01:16:56 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_EXT_H
# define MLX_EXT_H

# include "capivara.h"

void	*mlx_new_window_fullscreen(t_xvar *xvar, char *title);
void	*mlx_new_window_without_border(t_xvar *xvar,int size_x,int size_y,char *title);

#endif

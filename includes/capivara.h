/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capivara.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:55:57 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/20 21:54:57 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAPIVARA_H
# define CAPIVARA_H

# include <X11/Xlib.h>
# include <X11/extensions/Xfixes.h>

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "mlx.h"
# include "mlx_int.h"

# include "farbfeld_to_img.h"
# include "files.h"
# include "mlx_ext.h"

# define UP		119
# define DOWN	115
# define LEFT	97
# define RIGHT	100
# define ESC	65307

typedef struct s_c_data
{
	t_xvar		*mlx_ptr;
	t_win_list	*w_list;
	t_img		*img;
}	t_c_data;

int		key_check(int keycode, t_c_data	*data);
void	init_cap(t_c_data *data);
void	destroy_everything(t_xvar *mlx_ptr, t_win_list *w_list);
#endif
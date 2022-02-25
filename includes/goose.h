/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goose.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:55:57 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/25 17:06:46 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GOOSE_H
# define GOOSE_H

# define GOOSE_SPEED 500

# include <X11/Xlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

# include "mlx.h"
# include "mlx_int.h"
# include "mlx_ext.h"

# include "farbfeld_to_img.h"

typedef struct s_couple
{
	int	x;
	int	y;
}	t_couple;

typedef struct s_couple_double
{
	double x;
	double y;
}	t_couple_double;

typedef t_couple t_goose;
typedef t_couple_double t_direction;

void	destroy_everything(t_xvar *mlx_ptr, t_win_list *w_list);
void	goose(t_xvar *mlx_ptr, t_win_list *w_list, t_img *img);

#endif

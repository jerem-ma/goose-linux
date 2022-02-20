/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farbfeld_to_img.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:21:31 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/20 01:16:29 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FARBFELD_TO_IMG
# define FARBFELD_TO_IMG

# include "capivara.h"

t_img	*farbfeld_to_img(t_xvar *mlx_ptr, const char *path);

#endif

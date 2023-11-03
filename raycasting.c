/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:37:30 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/03 15:26:33 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting(t_cub3d *data, float dist, float ray_angle, int id_ray,
		int color)
{
	double	height_wall;
	int		xstart;
	int		ystart;
	int		xend;
	int		yend;

	dist = dist * cos(to_rad(ray_angle) - to_rad(data->angle));
	height_wall = ((data->size_shape) * height_win) / dist;
	xstart = id_ray;
	xend = id_ray;
	ystart = (height_win / 2) - (height_wall / 2);
	yend = (height_win / 2) + (height_wall / 2);
	if (ystart < 0)
		ystart = 0;
	if (yend > height_win)
		yend = height_win;
	while (ystart < yend)
	{
		if (ystart >= 0 && ystart < height_win)
			mlx_put_pixel(data->img, (int)xstart, (int)ystart, color);
		ystart += 1;
	}
}
void	check_ray_draw_down(t_cub3d *data, float ray_angle, int id_ray)
{
	data->hores_inters_y = floor((data->py / data->size_shape) + 1)
		* data->size_shape;
	data->hores_inters_x = data->px + (data->hores_inters_y - data->py)
		/ tan(to_rad(ray_angle));
	data->next_hor_inters_y = data->hores_inters_y + data->size_shape;
	data->next_hor_inters_x = data->hores_inters_x + ((data->next_hor_inters_y
				- data->hores_inters_y) / tan(to_rad(ray_angle)));
	data->step_hor_y = data->size_shape;
	data->step_hor_x = data->next_hor_inters_x - data->hores_inters_x;
	while (((int)(data->hores_inters_x / data->size_shape)) < data->width_map
		&& ((int)(data->hores_inters_y / data->size_shape)) < data->height_map
		&& data->hores_inters_x >= 0 && data->hores_inters_y >= 0
		&& myMap[(int)(data->hores_inters_y
			/ data->size_shape)][(int)(data->hores_inters_x
			/ data->size_shape)] != '1')
	{
		data->hores_inters_y += data->step_hor_y;
		data->hores_inters_x += data->step_hor_x;
	}
}

void	check_ray_draw_up(t_cub3d *data, float ray_angle, int id_ray)
{
	data->hores_inters_y = floor((data->py / data->size_shape))
		* data->size_shape;
	data->hores_inters_x = data->px - ((data->py - data->hores_inters_y)
			/ tan(to_rad(ray_angle)));
	data->next_hor_inters_y = data->hores_inters_y - data->size_shape;
	data->next_hor_inters_x = data->hores_inters_x - ((data->hores_inters_y
				- data->next_hor_inters_y) / tan(to_rad(ray_angle)));
	data->step_hor_y = data->size_shape;
	data->step_hor_x = data->next_hor_inters_x - data->hores_inters_x;
	while (((int)(data->hores_inters_x / data->size_shape)) < data->width_map
		&& ((int)((data->hores_inters_y - 1)
				/ data->size_shape)) < data->height_map
		&& data->hores_inters_x >= 0 && data->hores_inters_y >= 0
		&& myMap[(int)((data->hores_inters_y - 1)
			/ data->size_shape)][(int)(data->hores_inters_x
			/ data->size_shape)] != '1')
	{
		data->hores_inters_y -= data->step_hor_y;
		data->hores_inters_x += data->step_hor_x;
	}
}

void	check_ray_draw_right(t_cub3d *data, float ray_angle, int id_ray)
{
	data->vertcl_inters_x = floor((data->px / data->size_shape) + 1)
		* data->size_shape;
	data->vertcl_inters_y = data->py - ((data->px - data->vertcl_inters_x)
			* tan(to_rad(ray_angle)));
	data->next_ver_inters_x = data->vertcl_inters_x + data->size_shape;
	data->next_ver_inters_y = data->vertcl_inters_y - ((data->vertcl_inters_x
				- data->next_ver_inters_x) * tan(to_rad(ray_angle)));
	data->step_ver_x = data->size_shape;
	data->step_ver_y = data->next_ver_inters_y - data->vertcl_inters_y;
	while (((int)(data->vertcl_inters_x / data->size_shape)) < data->width_map
		&& ((int)(data->vertcl_inters_y / data->size_shape)) < data->height_map
		&& data->vertcl_inters_x >= 0 && data->vertcl_inters_y >= 0
		&& myMap[(int)(data->vertcl_inters_y
			/ data->size_shape)][(int)(data->vertcl_inters_x
			/ data->size_shape)] != '1')
	{
		data->vertcl_inters_y += data->step_ver_y;
		data->vertcl_inters_x += data->step_ver_x;
	}
}

void	check_ray_draw_left(t_cub3d *data, float ray_angle, int id_ray)
{
	data->vertcl_inters_x = floor((data->px / data->size_shape))
		* data->size_shape;
	data->vertcl_inters_y = data->py - ((data->px - data->vertcl_inters_x)
			* tan(to_rad(ray_angle)));
	data->next_ver_inters_x = data->vertcl_inters_x - data->size_shape;
	data->next_ver_inters_y = data->vertcl_inters_y - ((data->vertcl_inters_x
				- data->next_ver_inters_x) * tan(to_rad(ray_angle)));
	data->step_ver_x = data->size_shape;
	data->step_ver_y = data->next_ver_inters_y - data->vertcl_inters_y;
	while (((int)((data->vertcl_inters_x - 1)
				/ data->size_shape)) < data->width_map
		&& ((int)(data->vertcl_inters_y / data->size_shape)) < data->height_map
		&& data->vertcl_inters_x >= 0 && data->vertcl_inters_y >= 0
		&& myMap[(int)(data->vertcl_inters_y
			/ data->size_shape)][(int)((data->vertcl_inters_x - 1)
			/ data->size_shape)] != '1')
	{
		data->vertcl_inters_y += data->step_ver_y;
		data->vertcl_inters_x -= data->step_ver_x;
	}
}
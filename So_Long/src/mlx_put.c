/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:31:18 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:31:21 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_put(int i, int j, t_data *data) //Hepsi için resim basar.
{
	if (data->map[i][j] == '1')
		mlx_put_image_to_window(data->mlx, data->win, data->img.wall, //Eğer 1 var ise o konuma bizim duvar olarak atadığımız resmi basar.
			j * IMG_SIZE, i * IMG_SIZE); //İ ve J'nin konumunda basacağımız resme göre boyutlandırır.
	else if (data->map[i][j] == '0')
		mlx_put_image_to_window(data->mlx, data->win, data->img.bg,
			j * IMG_SIZE, i * IMG_SIZE);
	else if (data->map[i][j] == 'C')
		mlx_put_image_to_window(data->mlx, data->win, data->img.coin,
			j * IMG_SIZE, i * IMG_SIZE);
	else if (data->map[i][j] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->img.door,
			j * IMG_SIZE, i * IMG_SIZE);
	else if (data->map[i][j] == 'P')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img.character, j * IMG_SIZE, i * IMG_SIZE);
}

static void	map_element_counter(int i, int j, t_data *data) //Maptaki eleman sayısını sayar ve structta tanımladığımız değişkenlerin içinde tutar.
{
	int	idiot;

	idiot = 0;
	if (data->map[i][j] == '1') //Duvar gördüyse wall_count arttır,
		data->wall_count++;
	else if (data->map[i][j] == '0') //0'da aynı işlem
		idiot++;
	else if (data->map[i][j] == 'C') //C' de aynı işlem
		data->coin_count++;
	else if (data->map[i][j] == 'E') //Exit'ta hem exit sayısını sayar hem de Exitin konumunu ex_x ve y'de tutar,
	{
		data->exit_count++;
		data->exit_x = j;
		data->exit_y = i;
	}
	else if (data->map[i][j] == 'P') //Exit'taki aynı işlemi yapar,
	{
		data->player_x = j;
		data->player_y = i;
		data->player_count++;
	}
	else
		data->unwanted_character_count++; //Tanımlanmayan karakteri sayar.
}

void	map_create(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			map_element_counter(i, j, data);
			map_put(i, j, data); //Aldığımız uzunluk ve Genişlik kadar map oluşturacağız.
			j++;
		}
		i++;
	}
}

void	map_bacgraund_put(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->img.bg,
				j * IMG_SIZE, i * IMG_SIZE); //Uzunluğum ve Genişliğim kadar arkaya gönderdiğimiz resmi basıyoruz.
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:31:03 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:31:07 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	image_create(t_data *data)
{
	data->img.bg = mlx_xpm_file_to_image(data->mlx, "img/bacgraund_grass.xpm", 
			&data->img.img_w, &data->img.img_h); 
	data->img.coin = mlx_xpm_file_to_image(data->mlx, "img/btc.xpm",
			&data->img.img_w, &data->img.img_h);
	data->img.wall = mlx_xpm_file_to_image(data->mlx, "img/wall.xpm",
			&data->img.img_w, &data->img.img_h);
	data->img.door = mlx_xpm_file_to_image(data->mlx, "img/door.xpm",
			&data->img.img_w, &data->img.img_h);
	data->img.character = mlx_xpm_file_to_image(data->mlx, "img/character.xpm",
			&data->img.img_w, &data->img.img_h); //Gönderdiğimiz xpm dosyalarını tanımlıyoruz, xpm uzantıılıları img uzantılı yapmak için.
}

void	map_read(t_data *data)
{
	int		fd;
	int		i;
	int		j;
	char	*area;

	i = 0;
	j = 0;
	fd = open(data->map_tmp, O_RDONLY); //map'imizi açtı, okudu.
	data->map = (char **)malloc(sizeof(char *) * data->map_height); //Map'in uzunluğu kadar data'daki map'in içinde yer açıyoruz,
	while (i < data->map_height) //Sayacımız map'in uzunluğunda gelene kadar,
	{
		j = 0; //j'yi 0'a eşitliyor.
		area = get_next_line(fd); //ilk satırı area'nın içinde tutuyor.
		data->map[i] = (char *)malloc(sizeof(char *) * data->map_width); //Data'nın içindeki *map'in içinde genişlik kadar yer açıyoruz
		if (area == NULL) //satır get_next_line'dan gelmediyse
			break ; //kırıyoruz,
		while (j < data->map_width) //j'miz map'in genişliğine gelene kadar 
		{
			data->map[i][j] = area[j]; //ilk satırımızı j'yi arttırarak map'in içine atıyoruz.
			j++;
		}
		data->map[i][j] = '\0'; //son'a null
		i++; //2.satır ve diğer satırlar için aynı işlemi yapmak için i'yi arttırıyoruz,
		free(area); //area'yı free'liyoruz.
	}
}

static void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->map_width * IMG_SIZE,
			data->map_height * IMG_SIZE, "SoLong"); //SoLong Adında Ekran oluşturuyor,
	data->coin_count = 0;
	data->coin_collected = 0;
	data->step_count = 0;
	data->exit_count = 0;
	data->wall_count = 0;
	data->player_count = 0;
	data->unwanted_character_count = 0; //Ekranda basılacak herşeyi 0'a eşitliyor.
}

void	mlx_create(t_data *data)
{
	int	map_finder_print_is_active;

	data_init(data); //
	image_create(data); //
	map_read(data);
	map_bacgraund_put(data);
	map_create(data);
	wall_control(data);
	placeholder(data, data->exit_x, data->exit_y, map_finder_print_is_active);
	if (data->i_map.read_count != data->coin_count + 1)
		err_msg(">>>The map is wrong");
	min_element_control(data); //Sayı kontrolleri
	hook(data);
	mlx_loop(data->mlx); //Loop,
}

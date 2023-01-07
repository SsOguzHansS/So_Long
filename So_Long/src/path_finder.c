/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:57:11 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:31:34 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	recur_func(int **int_map, t_data *list, int x, int y) //Tüm haritayı dolaşıyor.
{
    
	if (list->map[y][x] == 'P' || list->map[y][x] == 'C') //Playe veya coin varsa read count'u bir arttırıyor.
		list->i_map.read_count++;
	if (list->map[y][x + 1] != '1' && int_map[y][x + 1] < 1) //sağa
	{
		int_map[y][x + 1] = int_map[y][x] + 1;
		list->i_map.r = recur_func(int_map, list, x + 1, y);
	}
	if (list->map[y + 1][x] != '1' && int_map[y + 1][x] < 1) //aşağı
	{
		int_map[y + 1][x] = int_map[y][x] + 1;
		list->i_map.b = recur_func(int_map, list, x, y + 1);
	}
	if (list->map[y][x - 1] != '1' && int_map[y][x - 1] < 1) //sola
	{
		int_map[y][x - 1] = int_map[y][x] + 1;
		list->i_map.l = recur_func(int_map, list, x - 1, y);
	}
	if (list->map[y - 1][x] != '1' && int_map[y - 1][x] < 1) //yukarı
	{
		int_map[y - 1][x] = int_map[y][x] + 1;
		list->i_map.t = recur_func(int_map, list, x, y - 1);
	}
	if ((list->i_map.r || list->i_map.l || list->i_map.b || list->i_map.t))
		return (1);
	return (0);
}


static void	print(t_data *list, int **int_map, int print_active)
{
	int	x;
	int	k;

	x = 0;
	k = 0;
	if (print_active)
	{
		if (list->i_map.read_count == list->coin_count + 1)
			ft_printf("\n\n>>>> MAP OK\n");
		ft_printf("\n>>>>Toplanan ulaşılabilir: %d", list->i_map.read_count);
		ft_printf("\n>>>>Toplam Hareket: %d", list->i_map.step_count);
		ft_printf("\n\n↓ VIRTUAL MAP ↓\n");
		while (x < list->map_height)
		{
			k = 0;
			ft_printf("\n");
			while (k < list->map_width)
			{
				ft_printf("%d", int_map[x][k]);
				k++;
			}
			x++;
		}
		ft_printf("\n\n");
	}	
}

static void	int_map_free(int **int_map, t_data *list)
{
	int	i;

	i = 0;
	while (i < list->map_height) //sayacaımız mapin uzunluğuna gelene kadar freeliyor
	{
		free(int_map[i]);
		i++;
	}
	free(int_map);
}

void	placeholder(t_data *list, int x, int y, int print_active)
{
	int	**int_map; //çift matrisli bir değişken tanımlıyoruz x ve y ekseni.
	int	i;
	int	j;

	i = 0;
	j = 0;
	int_map = (int **)malloc(sizeof(int *) * list->map_height); //int map'in içine uzunluğu kadar yer açıyor,
	while (i < list->map_height) //sayacımız uzunluğa gelene kadar 
	{
		int_map[i] = (int *)malloc(sizeof(int) * list->map_width); //map'in genişliği kadar yer açıyor,
		j = 0; //j'yi 0 'a eşitliyor.
		while (j < list->map_width) //Genişliğe gelene 
		{
			int_map[i][j] = 0; //0 atıyoruz,
			j++;
		}
		i++;
	}	//Uzunluk ve Genişlik kadar tüm map'e 0 atıyoruz.
	int_map[y][x] = 1; //En sonunda oraya ulaşacağımız için exit'ın konumuna 1 veriyoruz.
	list->i_map.read_count = 0; //Player ve coinleri sayıyor.
	list->i_map.step_count = 0; //Attığı adımı saymıyoruz.
	recur_func(int_map, list, x, y); //recur fonksiyona exit'ın konumunu yani x ve y'yi gönderiyoruz.
	print(list, int_map, print_active); //
	int_map_free(int_map, list); //map'i freeliyor.
}

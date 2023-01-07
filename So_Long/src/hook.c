/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:41:06 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:17:39 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 2, key_hook, data); //Klavyeden gelen değerleri okuyor.Klavyeden bir değer alırsak çalıştırıyor.
	mlx_hook(data->win, 17, 1L << 2, mouse_hook, data); //Mouseden bir event alırsan, çalıştır, kırmızı x tuşu.
}

static void	step_count(t_data *data) //Attığımız adım sayısını yazdırır.
{
	data->step_count++;
	ft_printf("Step: %d\r", data->step_count);
}

static int	real_walking(int y, int x, t_data *data)
{
	if (data->map[data->player_y + y][data->player_x + x] == '1') //Başta player'İn konumunu x ve y olarak aldım ve önüme duvar çıkıp çıkmama durumuna göre devam ediyoruz.
		return (0);
	else if (data->map[data->player_y + y][data->player_x + x] == 'C') //Eğer geldiğimiz adım coinse;
	{
		data->map[data->player_y + y][data->player_x + x] = '0'; //Döndükten sonra tekrar coin olmasın diye yediğimiz coin yerine 0 atıyoruz.
		data->coin_collected++; //Toplanan coin sayısını 1 arttırıyoruz.
	}
	else if (data->map[data->player_y + y][data->player_x + x] == 'E') //Exit'a geldiysem, bütün coinler toplanmış mı kontrolü exitta yapılır, toplanmadıysa error.
	{
		exit_door(data);
		return (0);
	}
	return (1);
}

static int	walking(int keycode, t_data *data, int x)
{
	if (keycode == 2 || keycode == 0) //Sağ ve Aşağı
	{
		if (real_walking(0, x, data) == 0) //Eğer bu şartlar 0'a eşitse return (0); hareket edemez, yürünemez.
			return (0);
		mlx_put_image_to_window(data->mlx, data->win, data->img.bg, //Karakterin resmi arkada kalmaması için eski konuma background basılır. 
			data->player_x * IMG_SIZE, data->player_y * IMG_SIZE); //0'gelmediği durumda o anki bulunduğun yerin arkasına 1 tane background bastır. 
		data->player_x += x; //1 sağ veya aşağı gider.
	}
	if (keycode == 13 || keycode == 1) //Sol ve Yukarı
	{
		if (real_walking(-x, 0, data) == 0) //Eğer bu şartlar 0'a eşitse return (0); hareket edemez, yürünemez.
			return (0);
		mlx_put_image_to_window(data->mlx, data->win, data->img.bg, //Karakterin resmi arkada kalmaması için eski konuma background basılır. 
			data->player_x * IMG_SIZE, data->player_y * IMG_SIZE); //0'gelmediği durumda o anki bulunduğun yerin arkasına 1 tane background bastır.
		data->player_y -= x; //sol ve yukarı gider.
	}
	step_count(data); //Adım sayıyor.
	mlx_put_image_to_window(data->mlx, data->win, data->img.bg, //Attığı adıma background basar,
		data->player_x * IMG_SIZE, data->player_y * IMG_SIZE);
	mlx_put_image_to_window(data->mlx, data->win, data->img.character, //Attığı adıma karakter basar.
		data->player_x * IMG_SIZE, data->player_y * IMG_SIZE);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53) //Esc Tuşu
		err_msg("Exit Success");
	else if (keycode == 2 || keycode == 13) //Sağ ve yukarı 
		walking(keycode, data, 1); //Keycode yanındaki 1'i de gönderiyoruz ki hangi yöne gideceğini buradan belli ediyoruz.
	else if (keycode == 0 || keycode == 1) //Sol ve aşşağı
		walking(keycode, data, -1); //Yanına -1 yazıyoruz ki hangi eksende hangi yönde hareket edeceği belli olsun,
	return (0);
}

//Koordinat düzlemine göre sağ ve aşağı artacaktır 
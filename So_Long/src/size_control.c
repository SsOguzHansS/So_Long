/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:31:41 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:31:47 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	size_control(t_data *data)
{
	int		fd;
	char	*line;
	int		y;
	int		x;

	y = 0; //y'yi 0'a eşitliyoruz.
	fd = open(data->map_tmp, O_RDONLY); //map_tmp içinde tuttuğumuz map1.ber'i okuyup açıyor,
	line = get_next_line(fd); //get_next_line ile tek bir satırı alıp, line'ın içinde tutuyor,
	x = ft_strlen(line); //line'ın uzunluğunu'da x'in içinde tutuyoruz.
	while (1)
	{
		free(line); //leaks
		y++; //y'yi 1 arttırıp   
		line = get_next_line(fd); //diğer satırı line içinde tutuyoruz,
		if (line[0] == '\0') //satırların 0.indisleri NULL'a eşit olduğu durumda,
			break ; //kırıyor,
		if (x != ft_strlen(line) && line[0] != '\0') //Her satırın uzunluğunun birbirine eşit olması lazım,
			err_msg("Error : Map is not rectangular"); //Error: Map dikdörtgen değil,
	}
	if (!line) //ilk satır yoksa
		free(line); //line freele
	data->map_height = y; //bu sırada kaç satır olduğunu map_height'in içinde tutuyoruz.
	data->map_width = x - 1; //uzunluğunda 1 eksiğini map_width'in içinde tutuyoruz, "NULL" almamak için,
	close (fd); //fd'yi kapatıyoruz.
}

void	wall_control(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < data->map_width)
		if (data->map[0][x++] != '1')
			err_msg("Error : The map has to be surrounded by walls"); //Map'in ilk satırınınn 1. indeksi 1'e eşit değilse direkt error.
	while (y < data->map_height)
	{
		if (data->map[y][0] != '1' || data->map[y][data->map_width - 1] != '1') 
			err_msg("Error : The map has to be surrounded by walls"); //Map'in ilk satırının son'dan 1 önceki indeksi ve ilk indeksi 1 değilse error yazdırıyor.
		y++; //Her satır kontrolü için y'yi arttırıyor.
	}
	x = 0;
	while (x < data->map_width) 
		if (data->map[data->map_height - 1][x++] != '1') //
			err_msg("Error : The map has to be surrounded by walls"); //En alttan bir önceki satırın elemanları eşit değilse 1'e error.
}

void	min_element_control(t_data *data)
{
	if (data->player_count != 1)
		err_msg("There must be 1 player on the map");  //Oyuncu yoksa veya Oyuncu Sayısı 1'den fazla ise exit.
	if (data->exit_count != 1)
		err_msg("There must be 1 exit on the map"); //Çıkış yoksa error.
	if (data->coin_count < 1)
		err_msg("Must have at least 1 collectible on the map"); //Coin sayısı 1'de azsa error,
	if (data->wall_count < 9)
		err_msg("Wrong on the map"); //Oyuncunun hareket edemeyeceği yer kaldığı için duvarlarımızın 9'dan küçükse error,
	if (data->unwanted_character_count != 0)
		err_msg("The map must contain only [0,1,E,P,C] characters"); //Tanımlanmayan karakter varsa error.
}

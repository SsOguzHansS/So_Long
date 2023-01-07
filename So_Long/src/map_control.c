/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:25:51 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:30:57 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ber_control(char *map_name, t_data *data) //.ber kontrolü yapıyor, subject'te istediği gibi,
{
	int	arg_len;

	arg_len = ft_strlen(map_name); //strlen ile map_name'nin uzunluğunu alıyor,
	if (map_name[arg_len - 1] != 'r' || map_name[arg_len - 2] != 'e'
		|| map_name[arg_len - 3] != 'b' || map_name[arg_len - 4] != '.') //Null'dan önce r,e,b,. yani .ber var mı diye bakıyor yoksa error veriyor.
		err_msg("Error : Map file is not .ber"); //.ber yoksa .ber uzantılı değil diyor.
}

void	tmp_control(char *map_name, t_data *data)
{
	int		fd;

	fd = open(ft_strjoin("map/", map_name), O_RDONLY); //joinle birleştirdiği, map_mapname'i açıyor, readonly ile okuyor.
	if (fd == -1) //Eğer fd -1 ise yani map dosyası yoksa,
		err_msg("Error : Map file is not found"); //map dosyası bulunamadı.
	close(fd); //close ile kapatıyor,
	if (!map_name) //mapname oluşmadıysa
		free(map_name); //freeliyor çıkıyor.
}

void	map_control(char **argv, t_data *data)
{
	char	*map_name;
	char	*map_names;

	if (argv[1] == NULL) //Argüman var mı yok mu kontrolü girilmiş mi,
		err_msg("Error : No map file");   //Argüman yoksa map dosyası yok error veriyor,
	map_name = argv[1]; //Argüman'ı map_name'ye atıyor,
	map_names = ft_strjoin("map/", map_name); //dosya yolunu birleştiriyor,
	data->map_tmp = map_names; //map_names'i map_tmp olarak struct'ta belirliyor,
	free(map_names); //map_names'i free'liyor,
	ber_control(argv[1], data); //1. argümanı ber_control'e yolluyor,
	tmp_control(argv[1], data); //1. argümanı tmp_control'e yolluyor.
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:16:33 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:30:47 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;

	map_control(argv, &data); //Argümanı map kontrole yolluyor,
	size_control(&data); //Map'in uzunluğunu kontrol edeceğiz,
	mlx_create(&data); //Map oluşturma.
}

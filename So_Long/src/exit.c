/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:58:34 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:30:18 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	err_msg(char *msg)
{
	ft_printf("%s", msg); //error message yazdırır.
	exit(0);
}

int	mouse_hook(int mousecode, t_data *data)
{
	err_msg("Exit Success"); //Esc veya Mouse ile kapatma işleminde error massage.
	return (0);
}

void	exit_door(t_data *data)
{
	if (data->coin_collected == data->coin_count) //coinlerin hepsi toplandıysa
		err_msg("FINISH"); //finish yazar,
	else
		ft_printf("Sorry, you can't exit.\n"); //Coinler toplanmadan exit'e gidilirse error verir.
}

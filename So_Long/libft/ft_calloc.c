/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:01:14 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:26:51 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*bytes;

	bytes = malloc(count * size);
	if (bytes)
		ft_bzero(bytes, size * count);
	return (bytes);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:04:45 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:23:40 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			a;

	a = ft_strlen(s);
	while (a >= 0)
	{
		if (s[a] == (char)c)
			return ((char *)&s[a]);
		a--;
	}
	return (0);
}

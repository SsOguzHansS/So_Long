/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:01:50 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:26:29 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

static char	*array(char *str, int n, int len)
{
	while (n)
	{
		*(str + len--) = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_len(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	if (n == 0)
		*str = '0';
	else if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_strlcpy(str, "-2147483648", len + 1);
			return (str);
		}
		str[0] = '-';
		n *= -1;
	}
	*(str + len--) = '\0';
	return (array(str, n, len));
}

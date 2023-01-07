/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogozturk <ogozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:04:57 by ogozturk          #+#    #+#             */
/*   Updated: 2023/01/07 16:23:27 by ogozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	i = 0;
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (sub == NULL || !s)
		return (NULL);
	while (len-- && start < ft_strlen(s))
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

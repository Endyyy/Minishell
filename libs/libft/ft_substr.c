/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:00:09 by achretie          #+#    #+#             */
/*   Updated: 2023/02/15 02:19:51 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
	{
		str = ft_calloc(sizeof(char), 1);
		if (!str)
			return (NULL);
		return (str);
	}
	str = ft_calloc(sizeof(char), (len + 5));
	if (!s || !str)
		return (NULL);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		str[j++] = s[i++];
	str[j] = 0;
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: typok <typok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:54:52 by achretie          #+#    #+#             */
/*   Updated: 2023/01/11 14:44:16 by typok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_find_number(const char *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (s[0] != c)
		count++;
	while (s[++i])
		if (s[i] != c && s[i - 1] == c)
			count++;
	return (count);
}

static char	**ft_fill_tab(char **tab, char const *s, char c, size_t nb_word)
{
	size_t		word_len;
	size_t		j[2];
	size_t		start;
	size_t		i;

	i = 0;
	j[1] = 0;
	j[0] = 0;
	word_len = 0;
	while (j[1] < nb_word)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i++] != c && s[i - 1])
			word_len++;
		tab[j[1]] = malloc(sizeof(char) * word_len + 1);
		while (j[0] < word_len)
			tab[j[1]][j[0]++] = s[start++];
		tab[j[1]++][j[0]] = '\0';
		j[0] = 0;
		word_len = 0;
	}
	tab[j[1]] = NULL;
	return (tab);
}

static char	*ft_fill_string(char const *str)
{
	int		i;
	char	*s;

	i = -1;
	s = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[++i])
		s[i] = (char)str[i];
	s[i] = 0;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char		**tab;
	size_t		nb_word;
	char const	*temp;

	temp = s;
	if (s[0] == 0)
	{
		tab = malloc(sizeof(char *) * 1);
		tab[0] = NULL;
		return (tab);
	}
	if (!c)
	{
		tab = malloc(sizeof(char *) * 2);
		tab[0] = ft_fill_string(s);
		tab[1] = NULL;
		return (tab);
	}
	nb_word = ft_find_number(temp, c);
	tab = malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return (NULL);
	tab = ft_fill_tab(tab, s, c, nb_word);
	return (tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:53:08 by achretie          #+#    #+#             */
/*   Updated: 2023/02/06 17:04:55 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	complete(t_token *token, char *str)
{
	int	index;

	index = 1;
	while (str[index] && str[index] != str[0])
		index++;
	if (str[index])
		index++;
	token->type = T_WORD;
	token->data = ft_substr(str, 0, index);
	return (index);
}

int	complete2(t_token *token, char *str, t_type type)
{
	int	index;

	index = 0;
	while (str[index] && str[index] == str[0])
		index++;
	token->type = type;
	token->data = ft_substr(str, 0, index);
	if (index > (int)type - 1)
		token->type = T_ERROR;
	return (index);
}

int	complete3(t_token *token, char *str)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != '|' && str[index] != '\'' \
	&& str[index] != '\"' && str[index] != '<' && str[index] != '>' \
	&& !((str[index] > 8 && str[index] < 14) || str[index] == 32))
		index++;
	token->type = T_WORD;
	token->data = ft_substr(str, 0, index);
	return (index);
}

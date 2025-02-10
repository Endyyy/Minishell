/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 08:33:45 by achretie          #+#    #+#             */
/*   Updated: 2023/02/22 17:56:04 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	merge_token(t_token *token)
{
	t_token	*prev;
	char	*str;

	while (token)
	{
		prev = token;
		if (!token->next)
			break ;
		token = token->next;
		if (token->type == T_WORD && prev->type == T_WORD)
		{
			str = ft_strjoin(prev->data, token->data);
			free(prev->data);
			prev->data = str;
			prev->next = token->next;
			if (token->next)
				token->next->prev = prev;
			prev = token;
			token = token->prev;
			free(prev->data);
			free(prev);
			prev = NULL;
		}
	}
}

void	delete_space(t_token *token)
{
	t_token	*prev;

	while (token)
	{
		prev = token;
		if (!token->next)
			break ;
		token = token->next;
		if (token->type == T_SPACE)
		{
			free(token->data);
			token->data = NULL;
			prev->next = token->next;
			if (token->next)
				token->next->prev = prev;
			prev = token;
			token = token->next;
			free(prev);
			prev = NULL;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 03:49:41 by achretie          #+#    #+#             */
/*   Updated: 2023/02/06 17:04:13 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_token	*create_token(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = token;
	new->data = NULL;
	new->type = T_UNDEFINED;
	if (token)
		token->next = new;
	return (new);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next)
	{
		token = token->next;
		free(tmp->data);
		tmp->data = NULL;
		token = tmp->next;
		free(tmp);
		tmp = token;
	}
	free(tmp->data);
	tmp->data = NULL;
	free(tmp);
	tmp = NULL;
}

void	tmp_show(t_token *token)
{
	while (token)
	{
		printf("str = %s, type = %i\n", token->data, token->type);
		token = token->next;
	}
}

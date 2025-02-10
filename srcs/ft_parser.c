/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 00:46:43 by achretie          #+#    #+#             */
/*   Updated: 2023/02/22 17:53:26 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_token	*split_token_loop(t_token *token, char *str, int index)
{
	while (str[index])
	{
		token = create_token(token);
		if ((str[index] == '\"' || str[index] == '\'') \
		&& str[index + 1] == str[index] && index)
			index += 2;
		if (str[index] == '\"' || str[index] == '\'')
			index += complete(token, &str[index]);
		else if (str[index] == '<' || str[index] == '>')
			index += complete2(token, &str[index], T_REDIRECT);
		else if (str[index] == '|')
			index += complete2(token, &str[index], T_PIPE);
		else if ((str[index] > 8 && str[index] < 14) || str[index] == 32)
		{
			token->data = ft_strdup(" ");
			token->type = T_SPACE;
			while ((str[index] > 8 && str[index] < 14) || str[index] == 32)
				index++;
		}
		else
			index += complete3(token, &str[index]);
	}
	return (token);
}

static t_token	*split_token(char *str)
{
	t_token	*token;
	int		index;

	token = NULL;
	index = 0;
	token = split_token_loop(token, str, index);
	return (token);
}

static t_token	*delete_first_space(t_token *token)
{
	t_token	*tmp;

	if (token->data[0] == ' ')
	{
		tmp = token;
		token = token->next;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp);
		tmp = NULL;
	}
	return (token);
}

static void	delete_quote(t_token *token)
{
	char	*tmp;
	int		size;

	while (token)
	{
		if (token->data[0] == '\'' || token->data[0] == '\"')
		{
			tmp = token->data;
			size = ft_strlen(tmp);
			if (tmp[size - 1] == tmp[0])
				size--;
			token->data = ft_substr(tmp, 1, size - 1);
			if (token->data == NULL)
				token->data = ft_calloc(sizeof(char), 1);
			free(tmp);
			tmp = NULL;
		}
		token = token->next;
	}
}

t_token	*parser(char *str, t_env *env)
{
	t_token	*token;

	token = split_token(str);
	while (token->prev)
		token = token->prev;
	token = delete_first_space(token);
	env_var(token, env);
	delete_quote(token);
	merge_token(token);
	delete_space(token);
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:59:27 by achretie          #+#    #+#             */
/*   Updated: 2023/02/03 17:37:54 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	strindex(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char	*before_var(char *s)
{
	char	*str;

	str = NULL;
	if (s[0] != '$')
		str = ft_substr(s, 0, strindex(s, '$'));
	return (str);
}

static void	new_value(t_token *token, char *value, int index)
{
	char	*str;
	char	*tmp;
	char	*tmp1;

	tmp = before_var(token->data);
	if (tmp)
	{
		str = ft_strjoin(tmp, value);
		free(tmp);
		tmp = NULL;
		free(value);
	}
	else
		str = value;
	if (token->data[index - 1] && token->data[index])
		tmp = ft_substr(token->data, index, ft_strlen(token->data) - index);
	if (tmp)
	{
		tmp1 = ft_strjoin(str, tmp);
		free(str);
		free(tmp);
		str = tmp1;
	}
	free(token->data);
	token->data = str;
}

static void	replace_var(t_env *env, t_token *token)
{
	char	*str;
	char	*key;
	int		i;

	str = NULL;
	key = NULL;
	i = strindex(token->data, '$') + 1;
	if (token->data[i] == '?')
		str = ft_itoa(g_ret_val);
	else
	{
		while (token->data[i] && ft_isalnum(token->data[i]))
			i++;
		if (token->data[i])
			i--;
		key = ft_substr(token->data, strindex(token->data, '$') + 1, \
		i - strindex(token->data, '$'));
		str = ft_strdup(get_value(env, key, false));
	}
	if (key)
		free(key);
	new_value(token, str, i + 1);
}

void	env_var(t_token *token, t_env *env)
{
	while (token)
	{
		while (ft_strchr(token->data, '$') && token->data[0] != '\'' \
		&& ft_strlen(token->data) > 1 \
		&& token->data[strindex(token->data, '$') + 1] \
		&& token->data[strindex(token->data, '$') + 1] != '"' \
		&& token->data[strindex(token->data, '$') + 1] != ' ')
			replace_var(env, token);
		token = token->next;
	}
}

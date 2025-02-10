/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 01:48:03 by achretie          #+#    #+#             */
/*   Updated: 2023/02/05 17:47:46 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

size_t	get_index(char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '=')
		i++;
	return (i);
}

static t_env	*create(char **envp, int i, t_env *prev)
{
	t_env	*env;
	int		index;

	if (!envp[i])
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	index = get_index(envp[i]);
	env->prev = prev;
	env->key = ft_substr(envp[i], 0, index);
	env->content = ft_substr(envp[i], index + 1, \
	ft_strlen(envp[i]) - index - 1);
	env->next = create(envp, i + 1, env);
	return (env);
}

t_env	*create_env(char **envp)
{
	t_env	*env;

	env = create(envp, 0, NULL);
	return (env);
}

char	*get_value(t_env *env, char *key, bool nullValue)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->content);
		env = env->next;
	}
	if (nullValue)
		return (NULL);
	return ("");
}

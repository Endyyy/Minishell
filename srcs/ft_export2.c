/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:13:23 by achretie          #+#    #+#             */
/*   Updated: 2023/02/20 15:32:05 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_add_to_env_plus_inloop(t_data *data, char *arg, char *key)
{
	char	*tmp;

	if (!data->envp->content)
	{
		data->envp->content = ft_substr(arg, get_index(arg) + 1, \
			ft_strlen(arg) - get_index(arg) - 1);
	}
	else
	{
		tmp = data->envp->content;
		data->envp->content = ft_strjoin(data->envp->content, arg + \
		ft_strlen(key) + 2);
		free(tmp);
	}
}

void	ft_add_to_env_plus(t_data *data, char *arg)
{
	t_env	*save;
	char	*key;

	key = ft_get_key(arg);
	save = data->envp;
	while (data->envp)
	{
		if (ft_strcmp(data->envp->key, key) == 0)
		{
			ft_add_to_env_plus_inloop(data, arg, key);
			data->envp = save;
			free(key);
			return ;
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
	data->envp = ft_lstadd_front_env(key, data->envp, 0);
	free(key);
}

void	ft_add_to_env(t_data *data, char *arg)
{
	t_env	*save;
	char	*key;

	key = ft_get_key(arg);
	save = data->envp;
	while (data->envp)
	{
		if (ft_strcmp(data->envp->key, key) == 0 && \
		ft_strlen(key) == ft_strlen(data->envp->key))
		{
			free(data->envp->content);
			data->envp->content = ft_substr(arg, get_index(arg) + 1, \
			ft_strlen(arg) - get_index(arg) - 1);
			data->envp = save;
			free(key);
			return ;
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
	free(key);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_env2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:13:52 by achretie          #+#    #+#             */
/*   Updated: 2023/02/11 18:38:42 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**ft_env_loop(t_data *data, char **envp)
{
	char	*tmp_envp;
	int		i;

	i = 0;
	tmp_envp = NULL;
	while (data->envp)
	{
		envp[i] = ft_strdup(data->envp->key);
		tmp_envp = ft_strdup(envp[i]);
		free(envp[i]);
		ft_free_env_loop(data, envp, i, tmp_envp);
		data->envp = data->envp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	**ft_env_to_tab(t_data *data)
{
	t_env	*tmp;
	int		i;
	char	**envp;

	i = 0;
	tmp = data->envp;
	while (data->envp)
	{
		i++;
		data->envp = data->envp->next;
	}
	data->envp = tmp;
	envp = ft_calloc(sizeof(char *), i + 1);
	if (!envp)
		return (NULL);
	envp = ft_env_loop(data, envp);
	data->envp = tmp;
	return (envp);
}

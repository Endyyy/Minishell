/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:13:52 by achretie          #+#    #+#             */
/*   Updated: 2023/02/22 16:13:19 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_setenv(t_data *data, char *var, char *content)
{
	t_env	*save;

	save = data->envp;
	while (data->envp)
	{
		if (!ft_strcmp(data->envp->key, var))
		{
			free(data->envp->content);
			data->envp->content = ft_strdup(content);
			data->envp = save;
			return (1);
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
	return (0);
}

char	*ft_getenv(t_data *data, char *var)
{
	t_env	*save;
	char	*content;

	save = data->envp;
	while (data->envp)
	{
		if (!ft_strcmp(data->envp->key, var) && \
		ft_strlen(var) == ft_strlen(data->envp->key))
		{
			content = ft_strdup(data->envp->content + ft_strlen(var) + 1);
			data->envp = save;
			return (content);
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
	return (NULL);
}

void	ft_env_pipe(t_data *data, t_env *save)
{
	while (data->envp)
	{
		ft_putstr_fd(data->envp->key, 1);
		if (data->envp->content)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd(data->envp->content, 1);
		}
		ft_putstr_fd("\n", 1);
		data->envp = data->envp->next;
	}
	data->envp = save;
}

void	ft_env_print(t_data *data, t_env *save)
{
	while (data->envp)
	{
		ft_putstr_fd(data->envp->key, data->out);
		if (data->envp->content)
		{
			ft_putstr_fd("=", data->out);
			ft_putstr_fd(data->envp->content, data->out);
		}
		ft_putstr_fd("\n", data->out);
		data->envp = data->envp->next;
	}
	data->envp = save;
}

void	ft_free_env_loop(t_data *data, char **envp, int i, char	*tmp_envp)
{
	if (data->envp->content)
	{
		envp[i] = ft_strjoin(tmp_envp, "=");
		free(tmp_envp);
		tmp_envp = ft_strdup(envp[i]);
		free(envp[i]);
		envp[i] = ft_strjoin(tmp_envp, data->envp->content);
		free(tmp_envp);
	}
	else
		envp[i] = tmp_envp;
}

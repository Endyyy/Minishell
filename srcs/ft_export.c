/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:06:00 by achretie          #+#    #+#             */
/*   Updated: 2023/02/21 17:52:09 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_find_key(t_data *data, char *arg)
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
			data->envp = save;
			free(key);
			return (1);
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
	free(key);
	return (0);
}

int	ft_check_export_key(char *arg, int i)
{
	int	j;

	j = 1;
	while (j < i)
	{
		if ((arg[j] < 'A' || arg[j] > 'Z') && \
		(arg[j] < 'a' || arg[j] > 'z') && \
		(arg[j] < '0' || arg[j] > '9') && arg[j] != '+')
			return (1);
		if (arg[j] == '+')
		{
			if (j + 1 != i)
				return (1);
			else
				return (2);
		}
		j++;
	}
	return (0);
}

int	ft_parse_export_arg(char *arg)
{
	int		i;
	int		ret;

	ret = 0;
	i = -1;
	if ((arg[0] < 'A' || arg[0] > 'Z') && (arg[0] < 'a' || arg[0] > 'z'))
		return (1);
	if (arg[1])
		if ((arg[1] < 'A' || arg[1] > 'Z') && (arg[1] < 'a' || arg[1] > 'z') \
		&& (arg[1] < '0' || arg[1] > '9') && arg[1] != '=' && arg[1] != '+')
			return (1);
	while (arg[++i])
	{
		if (arg[i] == '=')
		{
			ret = ft_check_export_key(arg, i);
			if (ret == 1)
				return (1);
			else if (ret == 2)
				return (2);
			else
				return (0);
		}
	}
	return (3);
}

int	ft_check_ret(t_data *data, char *arg, int ret)
{
	if (ret == 0)
	{
		if (!ft_find_key(data, arg))
			data->envp = ft_lstadd_front_env(arg, data->envp, 2);
		else
			ft_add_to_env(data, arg);
	}
	else if (ret == 1)
	{
		ft_putstr_fd("Minishell: export: not a valid identifier\n", 2);
		g_ret_val = 1;
		return (1);
	}
	else if (ret == 2)
	{
		if (!ft_find_key(data, arg))
			data->envp = ft_lstadd_front_env(arg, data->envp, 0);
		else
			ft_add_to_env_plus(data, arg);
	}
	return (0);
}

void	ft_export(t_data *data, char *arg, t_pex *p)
{
	int	ret;

	ret = 0;
	(void)p;
	if (!arg)
	{
		ft_print_export(data);
		return ;
	}
	if (ft_strlen(arg) == 1 && arg[0] == '_')
		return ;
	ret = ft_parse_export_arg(arg);
	if (ft_check_ret(data, arg, ret))
		return ;
	if (ret == 3)
	{
		if (!ft_find_key(data, arg))
			data->envp = ft_lstadd_front_env(arg, data->envp, 1);
	}
}

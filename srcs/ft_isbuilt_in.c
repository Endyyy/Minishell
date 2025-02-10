/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuilt_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/20 19:23:22 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_builtin_forest(t_token *args, t_data *data, char **tabl, t_pex *p)
{
	if (!ft_strcmp(tabl[0], "echo"))
	{
		ft_echo(tabl, data);
		return (1);
	}
	if (!ft_strcmp(tabl[0], "pwd"))
	{
		ft_pwd(data);
		return (1);
	}
	if (!ft_strcmp(tabl[0], "env"))
	{
		ft_env(data);
		return (1);
	}
	if (!ft_strcmp(tabl[0], "exit"))
	{
		ft_exit(args, data, p);
		return (1);
	}
	return (0);
}

int	ft_builtin_forest_pipe(t_token *args, t_data *data, char **tabl, t_pex *p)
{
	(void)p;
	(void)args;
	if (!ft_strcmp(tabl[0], "echo"))
	{
		if (data->out != -1)
			ft_echo_pipe(tabl, data);
		else
			exit (1);
		return (1);
	}
	if (!ft_strcmp(tabl[0], "pwd"))
	{
		ft_pwd(data);
		return (1);
	}
	if (!ft_strcmp(tabl[0], "env"))
	{
		ft_env(data);
		return (1);
	}
	return (0);
}

int	ft_builtin_forest_bis(int length, t_data *data, char **tabl, int i)
{
	if (!ft_strcmp(tabl[0], "cd"))
	{
		if (length > 2)
		{
			ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
			g_ret_val = 1;
			return (1);
		}
		ft_cd(data, tabl);
		return (1);
	}
	if (!ft_strcmp(tabl[0], "unset"))
	{
		if (tabl[i])
		{
			while (tabl[i])
			{
				ft_unset(data, tabl[i]);
				i++;
			}
		}
		return (1);
	}
	return (0);
}

int	ft_isbuiltin(t_token *args, t_data *data, char **tabl, t_pex *p)
{
	int	i;
	int	length;

	length = ft_get_length(tabl);
	i = 1;
	data->builtin = 1;
	if (ft_builtin_forest(args, data, tabl, p) == 1 || \
	ft_builtin_forest_bis(length, data, tabl, i) == 1)
		return (1);
	if (!ft_strcmp(tabl[0], "export"))
	{
		if (length < 2)
			ft_export(data, NULL, p);
		else
		{
			while (tabl[i])
			{
				ft_export(data, tabl[i], p);
				i++;
			}
		}
		return (1);
	}
	data->builtin = 0;
	return (0);
}

int	ft_isbuiltin_pipe(t_token *args, t_data *data, char **tabl, t_pex *p)
{
	int	i;
	int	length;

	length = ft_get_length(tabl);
	i = 1;
	data->builtin = 1;
	if (ft_builtin_forest_pipe(args, data, tabl, p) == 1 || \
	ft_builtin_forest_bis(length, data, tabl, i) == 1)
		return (1);
	if (!ft_strcmp(tabl[0], "export"))
	{
		if (length < 2)
			ft_export(data, NULL, p);
		else
		{
			while (tabl[i])
			{
				ft_export(data, tabl[i], p);
				i++;
			}
		}
		return (1);
	}
	data->builtin = 0;
	return (0);
}

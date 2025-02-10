/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:13:52 by achretie          #+#    #+#             */
/*   Updated: 2023/02/06 19:08:29 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_echo_print(char **args, t_data *data, int i)
{
	int	j;

	j = 0;
	while (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		j = ft_check_echo_flag(args, i, data);
		if (!j)
		{
			i++;
			break ;
		}
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], data->out);
		i++;
		if (args[i])
			ft_putchar_fd(' ', data->out);
	}
	if (!j)
		ft_putchar_fd('\n', data->out);
}

void	ft_echo(char **args, t_data *data)
{
	int		i;

	i = 0;
	if (ft_strcmp(args[0], "echo"))
		i++;
	if (!args[1])
	{
		g_ret_val = 0;
		return ;
	}
	i++;
	ft_echo_print(args, data, i);
	g_ret_val = 0;
}

int	ft_check_echo_flag_pipe(char **args, int i)
{
	int	j;

	j = 1;
	while (args[i][j])
	{
		if (args[i][j] != 'n')
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			return (0);
		}
		j++;
	}
	return (1);
}

void	ft_echo_print_pipe(char **args, int i)
{
	int	j;

	j = 0;
	while (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		j = ft_check_echo_flag_pipe(args, i);
		if (!j)
		{
			i++;
			break ;
		}
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (!j)
		printf("\n");
}

void	ft_echo_pipe(char **args, t_data *data)
{
	int		i;

	i = 0;
	(void)data;
	if (ft_strcmp(args[0], "echo"))
		i++;
	if (!args[1])
	{
		g_ret_val = 0;
		return ;
	}
	i++;
	ft_echo_print_pipe(args, i);
}

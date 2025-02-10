/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:13:52 by achretie          #+#    #+#             */
/*   Updated: 2023/02/20 16:03:29 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_tryhard(int signal)
{
	(void)signal;
	g_ret_val = -1;
	printf("\n");
}

int	ft_check_echo_flag(char **args, int i, t_data *data)
{
	int	j;

	j = 1;
	while (args[i][j])
	{
		if (args[i][j] != 'n')
		{
			ft_putstr_fd(args[i], data->out);
			if (args[i + 1])
				ft_putchar_fd(' ', data->out);
			return (0);
		}
		j++;
	}
	return (1);
}

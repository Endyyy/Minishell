/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:13:52 by achretie          #+#    #+#             */
/*   Updated: 2023/02/22 16:04:45 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_cd(t_data *data, char **tabl)
{
	char	str[10000];
	char	*old_pwd;

	if (!tabl[1])
		return (0);
	old_pwd = ft_getenv(data, "PWD");
	if (chdir(tabl[1]) == -1)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		g_ret_val = 1;
		free(old_pwd);
		return (-1);
	}
	getcwd(str, 10000);
	ft_setenv(data, "PWD", str);
	if (old_pwd)
		ft_setenv(data, "OLDPWD", old_pwd);
	free(old_pwd);
	return (0);
}

void	ft_exit_not_num_error(t_token *args, t_data *data, t_pex *p)
{
	g_ret_val = 2;
	printf("exit\n");
	ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	ft_free_all(args, data, p);
	exit (g_ret_val);
}

int	ft_exit_loop(t_token *args, t_data *data, t_pex *p)
{
	if (args->next->next)
	{
		if (ft_check_is_num(args->next->data))
			ft_exit_not_num_error(args, data, p);
		g_ret_val = 1;
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (ft_check_is_num(args->next->data))
		ft_exit_not_num_error(args, data, p);
	return (0);
}

int	ft_exit(t_token *args, t_data *data, t_pex *p)
{
	long long int	test;
	unsigned char	testt;

	(void)data;
	if (args->next)
	{
		test = ft_atoi(args->next->data);
		testt = test;
		g_ret_val = testt;
		if (ft_exit_loop(args, data, p) == 1)
			return (0);
	}
	ft_free_all(args, data, p);
	printf("exit\n");
	exit (g_ret_val);
}

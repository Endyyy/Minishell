/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/21 17:56:55 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_max_sleep(void)
{
	int	i;

	i = 0;
	while (i < 10000000)
		i++;
}

void	ft_get_case(t_pex *p, t_data *data, t_token *args, t_token *tmp)
{
	if (p->pid[p->i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (p->i == 0)
			ft_case_first(p, data, args, tmp);
		else if (p->i < p->nb_cmd - 1)
			ft_case_mid(p, data, args, tmp);
		else
			ft_case_last(p, data, args, tmp);
	}
	else
		ft_get_case_bis(p);
}

int	ft_exec_pipe(t_pex *p, t_data *data, t_token *args, t_token *tmp)
{
	if (pipe(p->fd[p->i]) == -1)
		ft_putstr_fd("Minishell : Broken pipe", 2);
	p->pid[p->i] = fork();
	if (p->pid[p->i] < 0)
	{
		perror("Minishell");
		return (-1);
	}
	ft_get_case(p, data, args, tmp);
	return (0);
}

int	ft_case_first(t_pex *p, t_data *data, t_token *args, t_token *tmp)
{
	if (data->in != 0)
	{
		dup2(data->in, STDIN_FILENO);
		close(data->in);
	}
	if (data->out != 1)
	{
		dup2(data->out, STDOUT_FILENO);
		close(data->out);
	}
	else
		dup2(p->fd[p->i][1], STDOUT_FILENO);
	close(p->fd[p->i][0]);
	close(p->fd[p->i][1]);
	ft_isbuiltin_pipe(args, data, p->full_cmd, p);
	ft_case_first_bis(p, data, args, tmp);
	free(p->cmd);
	args = tmp;
	ft_free_all(args, data, p);
	exit (0);
}

int	ft_case_mid(t_pex *p, t_data *data, t_token *args, t_token *tmp)
{
	dup2(p->fd[p->i - 1][0], STDIN_FILENO);
	dup2(p->fd[p->i][1], STDOUT_FILENO);
	if (data->in != 0)
	{
		dup2(data->in, STDIN_FILENO);
		close(data->in);
	}
	if (data->out != 1)
	{
		dup2(data->out, STDOUT_FILENO);
		close(data->out);
	}
	if (data->pre_builtin && !ft_check_if_builtin(p->cmd))
		ft_max_sleep();
	close(p->fd[p->i][0]);
	close(p->fd[p->i][1]);
	ft_isbuiltin_pipe(args, data, p->full_cmd, p);
	ft_case_mid_bis(p, data, args, tmp);
	free(p->cmd);
	args = tmp;
	ft_free_all(args, data, p);
	exit (0);
}

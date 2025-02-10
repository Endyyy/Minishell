/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/21 17:56:49 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_get_case_bis(t_pex *p)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (p->i == 0)
		close(p->fd[p->i][1]);
	else if (p->i < p->nb_cmd)
	{
		close(p->fd[p->i - 1][0]);
		close(p->fd[p->i][1]);
	}
	else
		close(p->fd[p->i - 1][0]);
}

void	ft_case_first_bis(t_pex *p, t_data *data, t_token *args, t_token *tmp)
{
	if (data->builtin)
	{
		free(p->cmd);
		args = tmp;
		ft_free_all(args, data, p);
		exit (0);
	}
	if (!data->bug)
	{
		if (execve(p->cmd, p->full_cmd, p->envp) == -1)
		{
			free(p->cmd);
			args = tmp;
			ft_free_all(args, data, p);
			exit (1);
		}
	}
}

void	ft_case_mid_bis(t_pex *p, t_data *data, t_token *args, t_token *tmp)
{
	if (data->builtin)
	{
		free(p->cmd);
		args = tmp;
		ft_free_all(args, data, p);
		exit (0);
	}
	if (!data->bug)
	{
		if (execve(p->cmd, p->full_cmd, p->envp) == -1)
		{
			free(p->cmd);
			args = tmp;
			ft_free_all(args, data, p);
			exit (1);
		}
	}
}

void	ft_case_last_bis(t_pex *p, t_data *data, t_token *args, t_token *tmp)
{
	if (data->builtin)
	{
		free(p->cmd);
		args = tmp;
		ft_free_all(args, data, p);
		exit (0);
	}
	if (!data->bug)
	{
		if (execve(p->cmd, p->full_cmd, p->envp) == -1)
		{
			free(p->cmd);
			args = tmp;
			ft_free_all(args, data, p);
			exit (1);
		}
	}
}

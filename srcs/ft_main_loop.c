/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/22 15:41:06 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_main_loop(t_pex *p, t_data *data, t_token *args)
{
	int		status;
	t_token	*tmp;
	t_token	*start;

	status = 0;
	tmp = args;
	start = args;
	if (ft_main_loop_bis(p, start) == 1)
		return ;
	if (p->nb_cmd == 1)
	{
		p->full_cmd = ft_clean_to_tab(args);
		args = tmp;
		if (ft_one_cmd(data, args, p, status))
			return ;
	}
	else if (p->nb_cmd > 1)
	{
		data->pipe = 1;
		ft_multi_cmd(p, data, args, start);
		ft_wait_pipe(status, p, data);
		args = tmp;
	}
	ft_free_path(p->envp);
}

void	ft_reset(t_data *data, t_pex *p)
{
	data->out = 1;
	data->in = 0;
	data->bug = 0;
	data->builtin = 0;
	data->pipe = 0;
	data->pre_builtin = 0;
	free_tabint(p->fd, p->nb_cmd);
	free(p->pid);
	p->pid = NULL;
	if (data->heredoc)
		unlink("heredoc_tmp_file_1");
	data->heredoc = 0;
}

int	ft_check_pipe(t_token *start)
{
	t_token	*tmp;

	tmp = start;
	while (start)
	{
		if (ft_check_pipe_bis(start, tmp) == -1)
			return (-1);
		if (start->next && !ft_strncmp(start->data, start->next->data, 1) \
		&& !ft_strncmp(start->data, "|", 1))
		{
			start = tmp;
			return (-1);
		}
		if (start->next && start->prev && !ft_strncmp(start->data, "|", 1) && \
		(start->prev->type == T_REDIRECT || start->next->type == T_REDIRECT))
		{
			start = tmp;
			return (-1);
		}
		start = start->next;
	}
	start = tmp;
	return (0);
}

int	ft_check_syntax(t_token *start)
{
	if ((start->type == T_REDIRECT || start->type == T_PIPE) && !start->next)
		return (-1);
	if (ft_check_pipe(start) == -1)
		return (-1);
	if (!ft_strncmp(start->data, ">>>", 3) || \
	!ft_strncmp(start->data, "<<<", 3))
		return (-1);
	if (start->type == T_REDIRECT)
	{
		if (start->next)
		{
			if (start->next->type == T_PIPE)
				return (-1);
			if (start->next->type == T_REDIRECT && \
			ft_strcmp(start->next->data, start->data))
				return (-1);
		}
	}
	return (0);
}

int	ft_start_commands(t_data *data, t_token *args)
{
	t_pex	p;
	int		check;
	t_token	*tmp;

	tmp = args;
	check = ft_check_syntax(args);
	args = tmp;
	if (check == -1)
	{
		g_ret_val = 2;
		ft_putstr_fd("Minishell: syntax error near unexpected token\n", 2);
		return (0);
	}
	p.i = 0;
	p.envp = ft_env_to_tab(data);
	p.nb_cmd = ft_get_nb_cmd(args, &p);
	p.solo_pid = 0;
	p.cmd = NULL;
	ft_main_loop(&p, data, args);
	ft_reset(data, &p);
	return (0);
}

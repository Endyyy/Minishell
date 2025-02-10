/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_one_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/22 16:00:08 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_init_data(t_data *data, char **envp)
{
	data->envp = create_env(envp);
	data->input = NULL;
	data->ret_value = 0;
	data->exit = 0;
	data->cmd = NULL;
	data->full_cmd = NULL;
	data->pid = 0;
	data->in = 0;
	data->out = 1;
	data->bug = 0;
	data->heredoc = 0;
	data->builtin = 0;
	data->pipe = 0;
	data->pre_builtin = 0;
}

void	ft_env(t_data *data)
{
	t_env	*save;

	save = data->envp;
	if (data->out != 1)
		ft_env_print(data, save);
	else if (data->pipe)
		ft_env_pipe(data, save);
	else
		ft_env_print(data, save);
}

int	ft_one_cmd_bis(t_pex *p)
{
	if (p->full_cmd[0] == NULL)
	{
		ft_free_path(p->envp);
		ft_free_path(p->full_cmd);
		return (1);
	}
	return (0);
}

int	ft_one_cmd_loop(t_data *data, t_token *args, t_pex *p, int status)
{
	p->cmd = ft_execve_path(p->full_cmd, p->envp);
	if (!p->cmd)
	{
		ft_free_path(p->full_cmd);
		free(p->cmd);
		ft_putstr_fd("Minishell: No such file or directory\n", 2);
		g_ret_val = 127;
		return (1);
	}
	if (!data->bug)
	{
		ft_exec_cmd(p, p->envp, data, args);
		waitpid(p->solo_pid, &status, 0);
		ft_check_status(status);
	}
	ft_free_path(p->full_cmd);
	free(p->cmd);
	return (0);
}

int	ft_one_cmd(t_data *data, t_token *args, t_pex *p, int status)
{
	ft_redir_parse(data, args, args, p);
	if (ft_one_cmd_bis(p) == 1)
		return (1);
	if (data->bug)
	{
		ft_free_path(p->envp);
		ft_free_path(p->full_cmd);
		return (1);
	}
	ft_isbuiltin(args, data, p->full_cmd, p);
	if (data->builtin)
	{
		ft_free_path(p->envp);
		ft_free_path(p->full_cmd);
		return (1);
	}
	else
		if (ft_one_cmd_loop(data, args, p, status))
			return (0);
	return (0);
}

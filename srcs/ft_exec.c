/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/06 17:47:31 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_exec_error_bis(int ret)
{
	if (ret == -1)
	{
		ft_putstr_fd("Minishell: No such file or directory\n", 2);
		exit (127);
	}
}

void	ft_exec_error(char *file)
{
	int	ret;

	ret = open(file, O_WRONLY, 0644);
	free(file);
	file = NULL;
	if (errno == EISDIR)
	{
		ft_putstr_fd("Minishell: Is a directory\n", 2);
		exit (126);
	}
	if (errno == 13)
	{
		ft_putstr_fd("Minishell: Permission denied\n", 2);
		exit (126);
	}
	ft_exec_error_bis(ret);
	if (errno == EACCES)
	{
		ft_putstr_fd("Minishell: command not found\n", 2);
		exit (127);
	}
	else
		exit (0);
}

void	ft_execve(t_pex *p, char **envp, t_data *data, t_token *args)
{
	if (execve(p->cmd, p->full_cmd, envp) == -1)
	{
		if (p->cmd[0] == '/')
		{
			ft_putstr_fd("Minishell: No such file or directory\n", 2);
			free(p->cmd);
			p->cmd = NULL;
			ft_free_all(args, data, p);
			exit (127);
		}
		else if (p->cmd[0] == '.' && p->cmd[1] == '/')
		{
			ft_free_all(args, data, p);
			ft_exec_error(p->cmd);
		}
		else
		{
			ft_putstr_fd("Minishell: command not found\n", 2);
			free(p->cmd);
			p->cmd = NULL;
			ft_free_all(args, data, p);
			exit (127);
		}
	}
}

void	ft_redir_exec(t_pex *p, char **envp, t_data *data, t_token *args)
{
	if (data->out != 1)
	{
		dup2(data->out, STDOUT_FILENO);
		close(data->out);
	}
	if (data->in != 0)
	{
		dup2(data->in, STDIN_FILENO);
		if (data->in != -1)
			close(data->in);
	}
	ft_execve(p, envp, data, args);
}

void	ft_exec_cmd(t_pex *p, char **envp, t_data *data, t_token *args)
{
	p->solo_pid = fork();
	if (p->solo_pid == -1)
		perror("fork");
	else if (p->solo_pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_redir_exec(p, envp, data, args);
		exit(0);
	}
}

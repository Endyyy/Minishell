/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/22 15:58:30 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_check_if_builtin(char *arg)
{
	if (ft_strstr(arg, "env") || !ft_strcmp(arg, "pwd") || \
	!ft_strcmp(arg, "export") || !ft_strcmp(arg, "unset"))
		return (1);
	return (0);
}

void	ft_pipe_reset(t_pex *p, t_data *data)
{
	if (data->heredoc)
		unlink("heredoc_tmp_file_1");
	free(p->cmd);
	p->cmd = NULL;
	ft_free_path(p->full_cmd);
	data->out = 1;
	data->in = 0;
	data->bug = 0;
}

void	ft_multi_cmd(t_pex *p, t_data *data, t_token *args, t_token *start)
{
	t_token	*tmp;

	tmp = args;
	while (args)
	{
		if (args->type == T_PIPE || !args->next)
		{
			data->pipe = 1;
			ft_redir_parse(data, start, tmp, p);
			p->full_cmd = ft_clean_to_tab(start);
			if (p->full_cmd[0][0] == '\0')
				ft_putstr_fd("Minishell : command not found\n", 2);
			p->cmd = ft_execve_path(p->full_cmd, p->envp);
			if (ft_check_if_builtin(p->cmd))
				data->pre_builtin = 1;
			ft_exec_pipe(p, data, start, tmp);
			ft_pipe_reset(p, data);
			if (args->next)
				start = args->next;
			p->i++;
		}
		args = args->next;
	}
}

int	ft_main_loop_bis(t_pex *p, t_token *start)
{
	int	length;

	length = ft_get_length_start(start);
	if (length == -1)
	{
		g_ret_val = 2;
		ft_putstr_fd("Minishell: syntax error near unexpected token\n", 2);
		ft_free_path(p->envp);
		return (1);
	}
	return (0);
}

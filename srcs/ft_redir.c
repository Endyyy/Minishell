/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/13 19:49:18 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_redir_less_bis(char *pos, t_data *data)
{
	if (access(pos, F_OK) != 0)
	{
		ft_putstr_fd("Minishell: No such file or directory\n", 2);
		g_ret_val = 1;
		data->bug = 1;
		return (2);
	}
	else
	{
		data->in = open(pos, O_RDONLY, 0644);
		if (data->in == -1)
		{
			perror("Minishell");
			g_ret_val = 1;
			data->bug = 1;
			return (0);
		}
		return (2);
	}
	return (2);
}

int	ft_redir_less(char *pos, t_data *data)
{
	if (pos)
	{
		if (!ft_strcmp(pos, "&") || !ft_strcmp(pos, "|") || \
			!ft_strcmp(pos, "<") || !ft_strcmp(pos, ">") || \
			!ft_strcmp(pos, ";") || !ft_strcmp(pos, "(") || \
			!ft_strcmp(pos, ")"))
		{
			ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
			data->bug = 1;
			return (2);
		}
		else
			if (ft_redir_less_bis(pos, data) == 0)
				return (0);
	}
	return (2);
}

int	ft_redir_db_less(char *pos, t_data *data, t_token *head, t_pex *p)
{
	if (!pos)
	{
		ft_putstr_fd("Minishell: syntax error near \
		unexpected token \'newline\'\n", 2);
		data->bug = 1;
		return (2);
	}
	data->bug = ft_heredoc(pos, head, data, p);
	data->in = open("heredoc_tmp_file_1", O_RDONLY, 0644);
	data->heredoc = 1;
	return (2);
}

int	ft_redir_great(char *pos, t_data *data)
{
	if (pos)
	{
		if (!ft_strcmp(pos, "&") || !ft_strcmp(pos, "|") || \
			!ft_strcmp(pos, "<") || !ft_strcmp(pos, ">") || \
			!ft_strcmp(pos, ";") || !ft_strcmp(pos, "(") || \
			!ft_strcmp(pos, ")"))
		{
			ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
			data->bug = 1;
			return (2);
		}
		data->out = open(pos, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->out == -1)
		{
			perror("Minishell");
			g_ret_val = 1;
			data->bug = 1;
			return (2);
		}
		return (2);
	}
	return (2);
}

int	ft_redir_db_great(char *pos, t_data *data)
{
	if (pos)
	{
		if (!ft_strcmp(pos, "&") || !ft_strcmp(pos, "|") || \
			!ft_strcmp(pos, "<") || !ft_strcmp(pos, ">") || \
			!ft_strcmp(pos, ";") || !ft_strcmp(pos, "(") || \
			!ft_strcmp(pos, ")"))
		{
			ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
			data->bug = 1;
			return (2);
		}
		data->out = open(pos, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->out == -1)
		{
			perror("Minishell");
			g_ret_val = 1;
			data->bug = 1;
			return (2);
		}
	}
	return (2);
}

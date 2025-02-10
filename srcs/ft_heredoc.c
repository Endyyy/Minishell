/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:13:52 by achretie          #+#    #+#             */
/*   Updated: 2023/02/06 19:08:29 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_check_input_heredoc(char *input)
{
	if (!input)
	{
		ft_putstr_fd("Minishell: warning: here-document ", 2);
		ft_putstr_fd("delimited by end-of-file\n", 2);
		return (1);
	}
	return (0);
}

int	ft_heredoc_loop(char *delim)
{
	char	*input;
	int		tmp_fd;
	char	*stock;

	stock = ft_calloc(sizeof(char), 1);
	tmp_fd = 0;
	signal(SIGINT, ft_x);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("> ");
		if (ft_check_ret_val(stock, tmp_fd) == 130)
			return (130);
		if (ft_check_input_heredoc(input) == 1)
			break ;
		if (!ft_strcmp(input, delim))
			break ;
		stock = ft_heredoc_loop_bis(stock, input);
	}
	tmp_fd = open("heredoc_tmp_file_1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_putstr_fd(stock, tmp_fd);
	if (tmp_fd > -1)
		close(tmp_fd);
	free(stock);
	return (0);
}

int	ft_heredoc(char *delim, t_token *head, t_data *data, t_pex *p)
{
	pid_t	tmp_f;
	int		status;

	if (!delim || !*delim)
		return (0);
	g_ret_val = 0;
	signal(SIGINT, SIG_IGN);
	tmp_f = fork();
	if (tmp_f == 0)
	{
		if (ft_heredoc_loop(delim) == 130)
			g_ret_val = 130;
		if (data->pipe)
			ft_free_all_heredoc(head, data, p);
		else
			ft_free_all(head, data, p);
		exit (g_ret_val);
	}
	waitpid(tmp_f, &status, 0);
	signal(SIGINT, ft_tryhard);
	g_ret_val = WEXITSTATUS(status);
	if (g_ret_val == 130)
		return (1);
	return (0);
}

int	ft_check_is_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
		{
			if (ft_strcmp(s, "-9223372036854775808") > 0 || ft_strlen(s) > 20)
				return (1);
		}
		else if (ft_strcmp(s, "+9223372036854775807") > 0 || ft_strlen(s) > 20)
			return (1);
		i++;
	}
	else if (ft_strcmp(s, "9223372036854775807") > 0 || ft_strlen(s) > 19)
		return (1);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_all(t_token *args, t_data *data, t_pex *p)
{
	free_tabint(p->fd, p->nb_cmd);
	free_token(args);
	free(p->pid);
	free_envp(&data->envp);
	ft_free_path(p->full_cmd);
	ft_free_path(p->envp);
}

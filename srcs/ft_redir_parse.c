/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/06 17:47:31 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_check_isredir(t_data *data, t_token *args, t_token *head, t_pex *p)
{
	int	j;

	j = 0;
	if (args->type == T_REDIRECT && !args->next)
	{
		ft_putstr_fd("Minishell: syntax error near \
		unexpected token \'newline\'\n", 2);
		data->bug = 1;
		g_ret_val = 2;
		return (2);
	}
	else if (!ft_strcmp(args->data, "<<") && args->type == T_REDIRECT)
		j = ft_redir_db_less(args->next->data, data, head, p);
	else if (!ft_strcmp(args->data, "<") && args->type == T_REDIRECT)
		j = ft_redir_less(args->next->data, data);
	else if (!ft_strcmp(args->data, ">>") && args->type == T_REDIRECT)
		j = ft_redir_db_great(args->next->data, data);
	else if (!ft_strcmp(args->data, ">") && args->type == T_REDIRECT)
		j = ft_redir_great(args->next->data, data);
	return (j);
}

void	ft_redir_parse(t_data *data, t_token *args, t_token *head, t_pex *p)
{
	int		j;

	j = 0;
	while (args)
	{
		j = ft_check_isredir(data, args, head, p);
		if (j == 2)
		{
			if (data->bug)
				return ;
			args = args->next;
			if (args->next)
				if (args->next->type == T_PIPE)
					return ;
		}
		args = args->next;
		if (args)
			if (args->type == T_PIPE)
				return ;
		j = 0;
		if (data->bug)
			return ;
	}
	return ;
}

char	*ft_remove_plus(char *arg)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(arg));
	while (arg[i])
	{
		if (arg[i] == '+')
			i++;
		tmp[j] = arg[i];
		i++;
		j++;
	}
	tmp[j] = 0;
	free(arg);
	return (tmp);
}

void	ft_pwd(t_data *data)
{
	char	buffer[10000];

	getcwd(buffer, 10000);
	ft_putstr_fd(buffer, data->out);
	ft_putstr_fd("\n", data->out);
}

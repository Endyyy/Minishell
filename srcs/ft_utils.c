/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/07 19:23:14 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_get_length_start_loop(t_token *start, t_token *tmp)
{
	int	i;

	i = 0;
	while (start)
	{
		if (start->type == T_REDIRECT)
		{
			if (!start->next || start->next->type == T_REDIRECT || \
			start->next->type == T_PIPE)
				return (-1);
			start = start->next;
			if (start->next)
				start = start->next;
			else
			{
				start = tmp;
				return (i);
			}
		}
		i++;
		start = start->next;
	}
	return (i);
}

int	ft_get_length_start(t_token *start)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = start;
	if (!start)
		return (-1);
	if ((start->type == T_REDIRECT || start->type == T_PIPE) && !start->next)
		return (-1);
	i = ft_get_length_start_loop(start, tmp);
	if (i == -1)
		return (-1);
	else
		return (i);
	start = tmp;
	return (i);
}

char	**ft_clean_to_tab_loop(t_token *start, char **tabl, int i)
{
	while (start)
	{
		if (start->type == T_PIPE)
			break ;
		if (start->type == T_REDIRECT)
		{
			start = start->next;
			if (start->next)
				start = start->next;
			else
			{
				tabl[i] = NULL;
				return (tabl);
			}
			if (start->type == T_REDIRECT)
				continue ;
		}
		if (start->type == T_PIPE)
			break ;
		tabl[i] = ft_strdup(start->data);
		i++;
		start = start->next;
	}
	tabl[i] = NULL;
	return (tabl);
}

char	**ft_clean_to_tab(t_token *start)
{
	char	**tabl;
	int		i;
	int		length;
	t_token	*tmp;

	i = 0;
	tmp = start;
	tabl = NULL;
	length = ft_get_length_start(start);
	tabl = ft_calloc(sizeof(char *), length + 1);
	tabl = ft_clean_to_tab_loop(start, tabl, i);
	start = tmp;
	return (tabl);
}

void	ft_wait_pipe(int status, t_pex *p, t_data *data)
{
	p->i = 0;
	while (p->i < p->nb_cmd)
	{
		close(p->fd[p->i][0]);
		close(p->fd[p->i][1]);
		waitpid(p->pid[p->i], &status, 0);
		ft_check_status(status);
		p->i++;
	}
	if (!data->bug)
		g_ret_val = WEXITSTATUS(status);
}

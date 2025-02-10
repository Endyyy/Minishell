/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/20 17:39:57 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_check_pipe_bis(t_token *start, t_token *tmp)
{
	if (!ft_strncmp(start->data, "|", 1) && !start->next)
	{
		start = tmp;
		return (-1);
	}
	if (!ft_strncmp(start->data, "||", 2))
	{
		start = tmp;
		return (-1);
	}
	return (0);
}

void	ft_free_all_heredoc(t_token *args, t_data *data, t_pex *p)
{
	free_tabint(p->fd, p->nb_cmd);
	free_token(args);
	free(p->pid);
	free_envp(&data->envp);
	ft_free_path(p->envp);
}

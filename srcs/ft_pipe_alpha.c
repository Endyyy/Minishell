/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_alpha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:56:11 by mafissie          #+#    #+#             */
/*   Updated: 2023/02/21 17:56:41 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_case_last(t_pex *p, t_data *data, t_token *args, t_token *tmp)
{
	dup2(p->fd[p->i - 1][0], STDIN_FILENO);
	if (data->in != 0)
	{
		dup2(data->in, STDIN_FILENO);
		close(data->in);
	}
	if (data->out != 1)
	{
		dup2(data->out, STDOUT_FILENO);
		close(data->out);
	}
	if (data->pre_builtin)
		ft_max_sleep();
	close(p->fd[p->i][0]);
	close(p->fd[p->i][1]);
	ft_isbuiltin_pipe(args, data, p->full_cmd, p);
	ft_case_last_bis(p, data, args, tmp);
	free(p->cmd);
	args = tmp;
	ft_free_all(args, data, p);
	exit (0);
}

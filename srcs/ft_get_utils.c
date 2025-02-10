/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2023/02/06 17:47:31 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_get_nb_cmd(t_token *args, t_pex *p)
{
	int		j;
	int		c;
	t_token	*tmp;

	c = 1;
	j = 0;
	tmp = args;
	while (args)
	{
		if (args->type == T_PIPE)
			c++;
		args = args->next;
	}
	args = tmp;
	p->fd = ft_calloc(sizeof(int *), c + 1);
	while (j < c)
		p->fd[j++] = ft_calloc(sizeof(int), 3);
	p->pid = ft_calloc(sizeof(int), c + 1);
	return (c);
}

int	ft_get_length(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
		i++;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:21:45 by achretie          #+#    #+#             */
/*   Updated: 2023/02/17 10:53:43 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

void	free_envp(t_env **envp)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = *envp;
	if (tmp == NULL)
		return ;
	while (tmp->next)
	{
		free(tmp->content);
		free(tmp->key);
		tmp->content = NULL;
		tmp->key = NULL;
		*envp = tmp->next;
		free(tmp);
		tmp = *envp;
	}
	free(tmp->content);
	free(tmp->key);
	tmp->content = NULL;
	tmp->key = NULL;
	free(*envp);
	*envp = NULL;
}

void	free_tabint(int	**tabl, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tabl[i]);
		tabl[i] = NULL;
		i++;
	}
	free(tabl);
}

void	ft_check_status(int status)
{
	if (status == 2)
	{
		printf("\n");
		g_ret_val = 130;
	}
	else if (status == 131)
	{
		printf("Quit (core dumped)\n");
		g_ret_val = 131;
	}
	else
		g_ret_val = WEXITSTATUS(status);
}

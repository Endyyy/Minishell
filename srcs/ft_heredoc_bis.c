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

int	ft_unset_bis(t_data *data, char *var, t_env *save, t_env *tmp)
{
	if (data->envp && !ft_strcmp(data->envp->key, var))
	{
		tmp = data->envp;
		data->envp = tmp;
		free(tmp->key);
		if (tmp->content)
			free(tmp->content);
		data->envp = save->next;
		free(tmp);
		return (1);
	}
	return (0);
}

void	ft_unset(t_data *data, char *var)
{
	t_env	*save;
	t_env	*tmp;

	tmp = NULL;
	save = data->envp;
	if (ft_unset_bis(data, var, save, tmp))
		return ;
	while (data->envp)
	{
		if (data->envp->next && !ft_strcmp(data->envp->next->key, var) && \
		ft_strlen(var) == ft_strlen(data->envp->next->key))
		{
			tmp = data->envp->next;
			data->envp->next = tmp->next;
			free(tmp->key);
			if (tmp->content)
				free(tmp->content);
			free(tmp);
			break ;
		}
		data->envp = data->envp->next;
	}
	data->envp = save;
}

char	*ft_heredoc_loop_bis(char *stock, char *input)
{
	char	*tmpsstr;

	tmpsstr = stock;
	stock = ft_strjoin(stock, input);
	free(tmpsstr);
	if (!stock)
		return (stock);
	tmpsstr = stock;
	stock = ft_strjoin(stock, "\n");
	free(tmpsstr);
	if (!stock)
		return (stock);
	return (stock);
}

void	ft_x(int signal)
{
	(void) signal;
	g_ret_val = 130;
	printf("\n");
	close(0);
}

int	ft_check_ret_val(char *stock, int tmp_fd)
{
	if (g_ret_val == 130)
	{
		tmp_fd = open("heredoc_f_1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_putstr_fd(stock, tmp_fd);
		if (tmp_fd > -1)
			close(tmp_fd);
		unlink("heredoc_f_1");
		free(stock);
		stock = NULL;
		return (130);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:13:23 by achretie          #+#    #+#             */
/*   Updated: 2023/02/21 17:50:48 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_get_length_list(t_data *data)
{
	t_env	*save;
	int		i;

	i = 0;
	save = data->envp;
	while (data->envp)
	{
		i++;
		data->envp = data->envp->next;
	}
	data->envp = save;
	return (i);
}

void	ft_manage_sort(t_data *data, char *tmp, char *tmp_content)
{
	tmp = data->envp->key;
	tmp_content = data->envp->content;
	data->envp->key = data->envp->next->key;
	data->envp->content = data->envp->next->content;
	data->envp->next->key = tmp;
	data->envp->next->content = tmp_content;
}

void	ft_sort_export(t_data *data)
{
	t_env	*save;
	char	*tmp;
	char	*tmp_content;
	int		i;
	int		j;

	tmp = NULL;
	tmp_content = NULL;
	j = 0;
	i = ft_get_length_list(data);
	save = data->envp;
	while (j < i)
	{
		while (data->envp)
		{
			if (data->envp->next && ft_strcmp(data->envp->key, \
			data->envp->next->key) > 0)
				ft_manage_sort(data, tmp, tmp_content);
			data->envp = data->envp->next;
		}
		data->envp = save;
		j++;
	}
	data->envp = save;
}

void	ft_print_export_alpha(t_data *data, t_env *save)
{
	while (data->envp)
	{
		ft_putstr_fd("declare -x ", data->out);
		ft_putstr_fd(data->envp->key, data->out);
		if (data->envp->content)
		{
			ft_putstr_fd("=\"", data->out);
			ft_putstr_fd(data->envp->content, data->out);
			ft_putstr_fd("\"", data->out);
		}
		ft_putchar_fd('\n', data->out);
		data->envp = data->envp->next;
	}
	data->envp = save;
}

void	ft_print_export(t_data *data)
{
	t_env	*save;

	save = data->envp;
	ft_sort_export(data);
	if (data->out != 1)
		ft_print_export_alpha(data, save);
	else if (data->pipe)
	{
		while (data->envp)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(data->envp->key, 1);
			if (data->envp->content)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(data->envp->content, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putchar_fd('\n', 1);
			data->envp = data->envp->next;
		}
		data->envp = save;
	}
	else
		ft_print_export_alpha(data, save);
}

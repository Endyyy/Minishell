/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:35:22 by achretie          #+#    #+#             */
/*   Updated: 2023/02/15 07:45:43 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_get_key(char *content)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '=' || content[i] == '+')
			break ;
		i++;
	}
	tmp = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		tmp[j] = content[j];
		j++;
	}
	tmp[j] = 0;
	return (tmp);
}

t_env	*ft_lstnew_env(char *content)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->content = ft_substr(content, get_index(content) + 1, \
	ft_strlen(content) - get_index(content) - 1);
	list->key = ft_get_key(content);
	list->prev = NULL;
	list->next = NULL;
	return (list);
}

t_env	*ft_lstnew_env_key(char *content)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->content = NULL;
	list->key = ft_strdup(content);
	list->prev = NULL;
	list->next = NULL;
	return (list);
}

t_env	*ft_lstnew_env_content(char *content)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->content = ft_substr(content, get_index(content) + 1, \
	ft_strlen(content) - get_index(content) - 1);
	list->key = ft_get_key(content);
	list->prev = NULL;
	list->next = NULL;
	return (list);
}

t_env	*ft_lstadd_front_env(char *content, t_env *head, int i)
{
	t_env	*list;

	if (!i)
		list = ft_lstnew_env(content);
	else if (i == 1)
		list = ft_lstnew_env_key(content);
	else
		list = ft_lstnew_env_content(content);
	list->next = head;
	head->prev = list;
	head = list;
	return (head);
}

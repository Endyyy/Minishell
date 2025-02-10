/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:13:52 by achretie          #+#    #+#             */
/*   Updated: 2023/02/12 21:47:21 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_env	*ft_fill_list(t_env *head, char **envp, int envp_len)
{
	int	i;

	i = envp_len;
	head = ft_lstnew_env(envp[--i]);
	while (i > 0)
		head = ft_lstadd_front_env(envp[--i], head, 0);
	return (head);
}

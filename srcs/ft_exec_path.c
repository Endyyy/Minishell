/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:31:34 by achretie          #+#    #+#             */
/*   Updated: 2023/02/21 17:14:47 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_free_path(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		data[i] = NULL;
		i++;
	}
	free(data);
	data = NULL;
	return (0);
}

int	ft_free_pathh(char **data)
{
	int	i;

	i = 1;
	while (data[i])
	{
		free(data[i]);
		data[i] = NULL;
		i++;
	}
	free(data);
	data = NULL;
	return (0);
}

char	**ft_parse_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	return (path);
}

char	*ft_execve_path_loop(char **cmd, char **path)
{
	int		i;
	char	*word;
	char	*full_word;

	i = -1;
	while (path[++i])
	{
		word = ft_strjoin(path[i], "/");
		full_word = ft_strjoin(word, cmd[0]);
		if (access(full_word, F_OK) == 0)
		{
			free(word);
			word = NULL;
			ft_free_path(path);
			return (full_word);
		}
		free(word);
		word = NULL;
		free(full_word);
		full_word = NULL;
	}
	return (NULL);
}

char	*ft_execve_path(char **cmd, char **envp)
{
	char	**path;
	char	*stock;
	char	*tmp;

	if (!cmd || !cmd[0])
	{
		tmp = ft_calloc(sizeof(char), 1);
		return (tmp);
	}
	if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0])))
	{
		tmp = ft_strdup(cmd[0]);
		return (tmp);
	}
	path = ft_parse_path(envp);
	if (!path)
		return (NULL);
	stock = ft_execve_path_loop(cmd, path);
	if (stock)
		return (stock);
	ft_free_path(path);
	tmp = ft_strdup(cmd[0]);
	return (tmp);
}

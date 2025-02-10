/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:42:40 by achretie          #+#    #+#             */
/*   Updated: 2023/02/22 17:49:08 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	g_ret_val = 0;

void	ft_trap(int signal)
{	
	(void)signal;
	if (g_ret_val != -1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_ret_val = 130;
}

int	ft_check_input(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] != '\t' && input[i] != '\n' && input[i] != ' ')
			j++;
		i++;
	}
	return (j);
}

int	ft_check_pwd(char *input)
{
	if (!ft_strcmp(input, "$PWD"))
	{
		g_ret_val = 126;
		ft_putstr_fd("Minishell: Is a directory\n", 2);
		return (0);
	}
	if (!ft_strcmp(input, "$EMPTY"))
	{
		g_ret_val = 0;
		return (0);
	}
	return (1);
}

int	ft_start(char *input, t_token *token, t_data data)
{
	while (1)
	{
		signal(SIGINT, ft_trap);
		signal(SIGQUIT, SIG_IGN);
		input = readline("$> ");
		if (!input)
		{
			free_envp(&data.envp);
			printf("exit\n");
			exit (0);
		}
		if (!input[0] || !ft_check_input(input) || !ft_check_pwd(input))
			continue ;
		add_history(input);
		token = parser(input, data.envp);
		ft_start_commands(&data, token);
		free_token(token);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	data;
	t_token	*token;

	(void)av;
	token = NULL;
	input = NULL;
	signal(SIGINT, ft_trap);
	signal(SIGQUIT, SIG_IGN);
	ft_init_data(&data, envp);
	if (ac != 1)
	{
		write(2, "No arguments needed !\n", 23);
		return (0);
	}
	ft_start(input, token, data);
	return (0);
}

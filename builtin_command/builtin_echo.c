/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:19:18 by user              #+#    #+#             */
/*   Updated: 2023/04/14 08:10:28 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_option(char *option)
{
	size_t	i;

	if (option[0] == '-')
	{
		i = 1;
		while (option[i] == 'n')
			i++;
		if (option[i] != '\0' || i == 1)
			return (false);
		else
			return (true);
	}
	return (false);
}

static void	print_with_newline(char **commands, t_command *command)
{
	size_t	i;

	i = 1;
	if (commands[i] == NULL)
		ft_putstr_fd("", 1);
	while (commands[i] != NULL)
	{
		ft_putstr_fd(commands[i++], command->out_fd[1]);
		if (commands[i] != NULL)
			ft_putstr_fd(" ", command->out_fd[1]);
	}
	ft_putstr_fd("\n", command->out_fd[1]);
}

static void	print_without_newline(char **commands)
{
	size_t	i;

	i = 1;
	while (commands[i] != NULL && check_option(commands[i]))
		i++;
	if (!commands[i])
		ft_putchar_fd('\0', 1);
	else
	{
		while (commands[i] != NULL)
		{
			ft_putstr_fd(commands[i++], 1);
			if (commands[i] != NULL)
				ft_putstr_fd(" ", 1);
		}
	}
}

int	ms_echo(char *line, t_command *command)
{
	char	**commands;
	size_t	i;

	(void)line;
	i = 1;
	commands = command_to_array(command);
	if (!commands)
		fatal_error("malloc");
	if (commands[1] != NULL && check_option(commands[i]))
		print_without_newline(commands);
	else if (commands[1])
		print_with_newline(commands, command);
	else
		ft_putchar_fd('\n', 1);
	free_commands(commands);
	g_env->err_status = 0;
	return (0);
}

/*int	ms_echo(char *line, t_command *command)
{
	char	**commands;
	size_t	position;

	(void)line;
	position = 1;
	commands = command_to_array(command);
	if (!commands)
		fatal_error("malloc");
	if (commands[1] != NULL && check_option(commands[position]))
	{
		while (commands[position] != NULL && check_option(commands[position]))
			position++;
		if (!commands[position])
			ft_putchar_fd('\0', 1);
		else
		{
			while (commands[position] != NULL)
			{
				ft_putstr_fd(commands[position++], 1);
				if (commands[position] != NULL)
					ft_putstr_fd(" ", 1);
			}
		}
	}
	else
	{
		if (commands[position] == NULL)
			ft_putstr_fd("", 1);
		while (commands[position] != NULL)
		{
			ft_putstr_fd(commands[position++], 1);
			ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
	}
	free_commands(commands);
	g_env->err_status = 0;
	return (0);
}*/
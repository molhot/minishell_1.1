/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:23:35 by user              #+#    #+#             */
/*   Updated: 2023/04/04 22:13:25 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_pwd(t_command *command)
{
	char	buf[PATH_MAX];
	char	**commands;

	commands = command_to_array(command);
	if (commands[1] != NULL)
	{
		printf("toooooooooooo many argments!! :)\n");
		free_commands(commands);
		return ;
	}
	if (getcwd(buf, PATH_MAX))
		printf("%s\n", buf);
	else
		printf("%s\n", g_env->ms_pwd);
	g_env->err_status = 0;
	free_commands(commands);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:20:06 by user              #+#    #+#             */
/*   Updated: 2023/04/03 23:03:56 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_env(t_command *command)
{
	t_item	*itr;
	char	**commands;

	commands = command_to_array(command);
	if (commands[1])
	{
		ft_putstr_fd("env: does not accept any arguments\n", 2);
		free_commands(commands);
		return ;
	}
	itr = g_env->item_head;
	while (itr != NULL)
	{
		if (itr->value != NULL)
			printf("%s=%s\n", itr->name, itr->value);
		itr = itr->next;
	}
	free_commands(commands);
	g_env->err_status = 0;
}

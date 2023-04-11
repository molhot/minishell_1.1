/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:39:39 by user              #+#    #+#             */
/*   Updated: 2023/04/08 01:01:21 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_env->err_status = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(int signum)
{
	(void)signum;
	g_env->heredoc = true;
}

// void  signal_handler2(int signal)
// {
//   if (signal == SIGINT)
//   {
//     write(1, "\n", 1);
//     g_env->err_status = 130;
//   }
//   else if (signal == SIGQUIT)
//   {
//     write(1, "\n", 1);
//     g_env->err_status = 131;
//   }
// }

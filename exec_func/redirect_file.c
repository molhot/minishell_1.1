/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:32:50 by satushi           #+#    #+#             */
/*   Updated: 2023/04/12 08:33:41 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = 10;
	while (is_valid_fd(stashfd))
		stashfd++;
	stashfd = xdup2(fd, stashfd);
	xclose(fd);
	return (stashfd);
}

void	ready_redirection_file(t_node *node)
{
	int			fd;
	t_redirect	*redirect;

	while (node != NULL)
	{
		redirect = *(node->command->redirect);
		while (redirect != NULL)
		{
			fd = obtain_fd(redirect);
			if (fd != -1)
				fd = stashfd(fd);
			else
			{
				redirect->redirectfile = fd;
				break ;
			}
			redirect->redirectfile = fd;
			redirect = redirect->next;
		}
		node = node->next;
	}
}

int	redirect_reconect(t_command *command)
{
	t_redirect	*redirect;
	int			flag;

	flag = 0;
	if (command->redirect == NULL)
		return (flag);
	redirect = *(command->redirect);
	while (redirect != NULL)
	{
		if (redirect->redirectfile == -1 || redirect->ambigous == true)
			return (1);
		if (redirect->type == IN || redirect->type == HEREDOC)
		{
			redirect->stashed_fd = stashfd(0);
			inout_reconnect(redirect->redirectfile, 0, command);
		}
		if (redirect->type == OUT || redirect->type == APPEND)
		{
			redirect->stashed_fd = stashfd(1);
			inout_reconnect(redirect->redirectfile, 1, command);
		}
		redirect = redirect->next;
	}
	return (flag);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:41:17 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/03/17 12:41:17 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	inout_reconnect(int file_fd, int fd, t_command *command)
{
	dup2(file_fd, fd);
	if (file_fd != -1)
		close(file_fd);
	command->now_in = file_fd;
}

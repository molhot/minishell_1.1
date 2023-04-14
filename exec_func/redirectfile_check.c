/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectfile_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:48:33 by kazuki            #+#    #+#             */
/*   Updated: 2023/04/14 20:49:11 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirectfile_check_noexe(t_redirect *redirect)
{
	while (redirect != NULL)
	{
		if (redirect->redirectfile == -1 || redirect->ambigous == true)
			redirectfile_check(redirect);
		redirect = redirect->next;
	}
}

void	redirectfile_check(t_redirect *redirect)
{
	int	fd;

	if (redirect->file_path == NULL || redirect->ambigous == true)
		printf("minishell: %s: ambiguous redirect\n", \
		redirect->file_path);
	else
	{
		if (redirect->type == IN)
			fd = open(redirect->file_path, O_RDONLY);
		if (redirect->type == OUT)
			fd = open(redirect->file_path, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (redirect->type == APPEND)
			fd = open(redirect->file_path, \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd != -1)
			close (fd);
		write(2, "minishell: ", 12);
		perror(redirect->file_path);
	}
	g_env->err_status = 1;
}

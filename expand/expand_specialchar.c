/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specialchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:08:20 by user              #+#    #+#             */
/*   Updated: 2023/03/16 12:12:03 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_num(char **dst, unsigned int num)
{
	if (num == 0)
	{
		append_char(dst, '0');
		return ;
	}
	if (num / 10 != 0)
		append_num(dst, num / 10);
	append_char(dst, '0' + num % 10);
}

void	expand_dolleeques(char **dst, char **rest, char *p)
{
	unsigned int	status;

	status = g_env->err_status;
	p = p + 2;
	append_num(dst, status);
	*rest = p;
}

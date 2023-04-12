/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_tokenutil.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:31:57 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/12 20:35:03 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remake_token_insplit(char **wd, char **new_wd)
{
	char	type;

	type = **wd;
	append_char(new_wd, **wd);
	(*wd)++;
	while ((**wd) != type)
	{
		if (**wd == '\\')
		{
			append_char(new_wd, **wd);
			(*wd)++;
		}
		append_char(new_wd, **wd);
		(*wd)++;
	}
	append_char(new_wd, **wd);
	(*wd)++;
}

void	remaking_blank(char **new_wd, char \
**token_wd, t_token **re_token)
{
	append_char(new_wd, '\0');
	(*re_token)->word = *new_wd;
	(*re_token)->kind = TK_WORD;
	while (**token_wd == ' ' || **token_wd == '\t')
		(*token_wd)++;
	if (**token_wd == '\0')
		return ;
	else
	{
		(*re_token)->next = (t_token *)malloc(sizeof(t_token) * 1);
		*re_token = (*re_token)->next;
		*new_wd = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:13:34 by marvin            #+#    #+#             */
/*   Updated: 2023/02/24 08:13:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	check_opsyntax(t_token *tok)
{
	if (tok->next->kind == TK_EOF)
	{
		printf("-minishell: syntax error near unexpected token `newline'\n");
		return (false);
	}
	if (ft_strcmp(tok->word, "||") == 0)
	{
		printf("-minishell: syntax error near unexpected token \
		`%s'\n", tok->word);
		return (false);
	}
	if (tok->next->kind == TK_OP)
	{
		printf("-minishell: syntax error near unexpected token \
		`%s'\n", tok->next->word);
		return (false);
	}
	return (true);
}

static bool	errorsyntax(char *str)
{
	printf("-minishell: syntax error near unexpected token \
	`%s'\n", str);
	g_env->err_status = 258;
	return (false);
}

static bool	check_redirectsyntax(t_token *tok)
{
	if (tok->next->kind == TK_EOF)
	{
		printf("-minishell: syntax error near unexpected token `newline'\n");
		g_env->err_status = 258;
		return (false);
	}
	if (tok->next->kind == TK_REDIRECT && tok->word[0] != tok->next->word[0])
		return (errorsyntax(tok->next->word));
	if (tok->kind == TK_REDIRECT && tok->next->kind == TK_REDIRECT \
	&& tok->next->next->kind == TK_REDIRECT)
		return (errorsyntax(tok->next->word));
	if (tok->next->kind == TK_OP)
		return (errorsyntax(tok->next->word));
	return (true);
}

bool	tokcheck(t_token *tok)
{
	bool	f_action;

	f_action = true;
	while (tok != NULL)
	{
		if (f_action == true && tok->kind == TK_OP)
			return (errorsyntax(tok->word));
		if (tok->kind == TK_REDIRECT)
		{
			if (false == check_redirectsyntax(tok))
				return (false);
		}
		if (tok->kind == TK_OP)
		{
			if (false == check_opsyntax(tok))
			{
				g_env->err_status = 258;
				return (false);
			}
		}
		tok = tok->next;
		f_action = false;
	}
	return (true);
}

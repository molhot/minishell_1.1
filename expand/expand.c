/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:37:31 by satushi           #+#    #+#             */
/*   Updated: 2023/04/12 11:43:19 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*remove_quote(char *s1, char *s2)
{
	char	*new;
	char	type;

	new = NULL;
	while (*s1 != '\0')
	{
		if (*s1 == '\'' || *s1 == '\"')
		{
			type = *s1;
			s1++;
			while (*s1 != type)
				append_char(&new, *s1++);
			s1++;
		}
		else
			append_char(&new, *s1++);
	}
	free(s2);
	return (new);
}

t_redirect	*expand_redirect_ten(t_redirect *redirect)
{
	t_redirect	*f_redirect;

	f_redirect = redirect;
	specialparam_check(redirect);
	while (redirect != NULL)
	{
		if (redirect->ambigous == false)
		{
			if (redirect->type == HEREDOC)
				redirect->file_path = \
				remove_quote(redirect->file_path, redirect->file_path);
			else
				redirect->file_path = \
				expand_args_redirect(redirect->file_path, redirect->file_path);
		}
		redirect = redirect->next;
	}
	return (f_redirect);
}

t_token	*expand_simplecommand(t_token *token)
{
	t_token	*re_token;
	t_token	*f_re_tok;

	re_token = (t_token *)malloc(sizeof(t_token) * 1);
	f_re_tok = re_token;
	if (ft_strcmp(token->word, "export") != 0)
	{
		expand_specialparam(token);
		remake_token(token, re_token);
		expand_quote(re_token);
		return (f_re_tok);
	}
	else
	{
		free(re_token);
		expand_export(token);
		export_argsremake(token);
		return (token);
	}
}

void	expand(t_node *node)
{
	t_redirect	*redirect;
	t_token		*token;

	while (node != NULL)
	{
		token = node->command->args;
		if (node->command->args != NULL)
			node->command->args = expand_simplecommand(token);
		if (node->command->redirect != NULL)
		{
			redirect = *(node->command->redirect);
			*(node->command->redirect) = expand_redirect_ten(redirect);
		}
		node = node->next;
	}
}

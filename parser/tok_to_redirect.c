/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_to_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:35:30 by kazuki            #+#    #+#             */
/*   Updated: 2023/04/02 22:35:44 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirect	*tok_to_redirect_f(bool *is_first, t_node *node, t_token **tok)
{
	parse_redirect(&(*node->command->redirect), &(*tok));
	(*node->command->redirect)->ambigous = false;
	*is_first = false;
	(*node->command->redirect)->before = NULL;
	return (*node->command->redirect);
}

t_redirect	*tok_to_redirect(t_redirect *redirect, t_token **tok)
{
	parse_redirect(&(redirect->next), &(*tok));
	redirect->next->ambigous = false;
	redirect->next->before = redirect;
	return (redirect->next);
}

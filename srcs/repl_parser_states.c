/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_parser_states.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:02:21 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/12 23:05:01 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "repl_parser.h"

t_repl_parser_state	repl_parser_parse_double_quote(
		t_repl_parser_state current_state)
{
	if (current_state == RP_IN_WORD_DOUBLE_QUOTED)
		return (RP_END_WORD);
	if (current_state == RP_IN_WORD_SINGLE_QUOTED)
		return (RP_IN_WORD_SINGLE_QUOTED);
	return (RP_IN_WORD_DOUBLE_QUOTED_NEW);
}

t_repl_parser_state	repl_parser_parse_single_quote(
	t_repl_parser_state current_state)
{
	if (current_state == RP_IN_WORD_SINGLE_QUOTED)
		return (RP_END_WORD);
	if (current_state == RP_IN_WORD_DOUBLE_QUOTED)
		return (RP_IN_WORD_DOUBLE_QUOTED);
	return (RP_IN_WORD_SINGLE_QUOTED_NEW);
}

t_repl_parser_state	repl_parser_parse_whitespace(
	t_repl_parser_state current_state)
{
	if (current_state == RP_IN_WORD)
		return (RP_END_WORD);
	if (current_state == RP_IN_WORD_DOUBLE_QUOTED
		|| current_state == RP_IN_WORD_SINGLE_QUOTED)
	{
		if (current_state == RP_IN_WORD_DOUBLE_QUOTED)
			return (RP_IN_WORD_DOUBLE_QUOTED);
		return (RP_IN_WORD_SINGLE_QUOTED);
	}
	return (RP_WHITESPACE);
}

t_repl_parser_state	repl_parser_parse_null(
	t_repl_parser_state current_state)
{
	if (current_state == RP_IN_WORD_DOUBLE_QUOTED
		|| current_state == RP_IN_WORD_SINGLE_QUOTED)
		return (RP_ERROR);
	if (current_state == RP_END_WORD
		|| current_state == RP_WHITESPACE)
		return (RP_EOL);
	return (RP_END_WORD);
}

t_repl_parser_state	repl_parser_parse_printable(
	t_repl_parser_state current_state)
{
	if (current_state == RP_IN_WORD_DOUBLE_QUOTED
		|| current_state == RP_IN_WORD_SINGLE_QUOTED)
		return (current_state == RP_IN_WORD_DOUBLE_QUOTED
			? RP_IN_WORD_DOUBLE_QUOTED
			: RP_IN_WORD_SINGLE_QUOTED);
	else
		return (RP_IN_WORD);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_parser_states.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:02:08 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/12 20:03:37 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPL_PARSER_STATES_H
# define REPL_PARSER_STATES_H
# include "repl_parser.h"

t_repl_parser_state	repl_parser_parse_double_quote(
		t_repl_parser_state current_state);
t_repl_parser_state	repl_parser_parse_single_quote(
	t_repl_parser_state current_state);
t_repl_parser_state	repl_parser_parse_whitespace(
	t_repl_parser_state current_state);
t_repl_parser_state	repl_parser_parse_null(
	t_repl_parser_state current_state);
t_repl_parser_state	repl_parser_parse_printable(
	t_repl_parser_state current_state);

#endif

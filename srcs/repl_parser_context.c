/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_parser_context.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:04:42 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/12 20:04:51 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "repl_parser.h"

void	repl_parser_context_init(t_repl_parser_context *ctx)
{
	*ctx = (t_repl_parser_context){
		.state = RP_WHITESPACE,
		.input_index = 0,
		.temporary_index = 0,
		.word_beginning = -1,
		.words_count = 0,
	};
}

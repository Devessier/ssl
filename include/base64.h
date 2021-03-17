/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:38:39 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/16 19:49:48 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64
# define BASE64
# include "ssl.h"
# define BASE64_INPUT_BLOCK_LENGTH 3
# define BASE64_OUTPUT_BLOCK_LENGTH 4
# define BASE64_PADDING_CHAR 64

void			bind_base64_args(t_context *ctx);
void			base64_log_command_usage(t_context *ctx);
void			base64_algo(t_context *ctx);

extern t_arg	g_base64_arguments[];

#endif

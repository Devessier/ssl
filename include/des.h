/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 11:13:16 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 20:58:50 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H
# include "ssl.h"
# define DES_KEY_BYTES_SIZE 8
# define DES_MAX_KEY_HEX_CHARACTERS (DES_KEY_BYTES_SIZE * 2)

typedef struct	s_des_algo_context
{
	uint64_t	salt;
	uint64_t	key;
}				t_des_algo_context;

void			bind_des_args(t_context *ctx);
void			des_log_command_usage(t_context *ctx);

extern t_arg	g_des_arguments[];

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 11:13:16 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 11:22:15 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H
# include "ssl.h"

void			bind_des_args(t_context *ctx);
void			des_log_command_usage(t_context *ctx);

extern t_arg	g_des_arguments[];

#endif

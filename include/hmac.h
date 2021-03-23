/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:51:01 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 14:16:26 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMAC_H
# define HMAC_H
# include "ssl.h"

void			hmac_log_command_usage(t_context *ctx);

extern t_arg	g_hmac_arguments[];

#endif

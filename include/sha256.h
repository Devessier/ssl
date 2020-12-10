/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:38:57 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/10 19:08:16 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H
# include "ssl.h"

void			bind_sha256_args(t_context *ctx);
void			sha256_cmd(t_context *ctx);
extern t_arg	g_sha256_arguments[];

#endif

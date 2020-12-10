/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:39:01 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/10 18:10:02 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include "ssl.h"

void			bind_md5_args(t_context *ctx);
void			md5_cmd(t_context *ctx);
extern t_arg	g_md5_arguments[];

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:38:57 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/17 13:09:50 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H
# include "ssl.h"

void			bind_sha256_args(t_context *ctx);
void			sha256_cmd(t_context *ctx);

#endif

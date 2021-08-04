/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 13:37:47 by gmelisan          #+#    #+#             */
/*   Updated: 2021/08/04 14:45:07 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
#define INIT_H

namespace init
{
	void start(int argc, char **argv);
	void parse_args(int argc, char **argv);
	void parse_args_network(char *str);
	
} // namespace init


#endif

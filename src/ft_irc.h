// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ft_irc.h                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/08/04 12:55:00 by gmelisan          #+#    #+#             //
/*   Updated: 2022/01/17 22:34:14 by gmelisan         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#ifndef FT_IRC_H
# define FT_IRC_H

# include <cstdio>
# include <cerrno>
# include <cstdlib>
# include <cstring>

# define DEBUG			// undef on release

namespace ft_irc
{
	extern const char *program_name;
	extern const char *program_version;
	extern const char *logpath;
	extern const char *usage;
	extern const char *server_name;

	extern const int host_maxsize;
	extern const int password_maxsize;

	extern struct s_args
	{
		std::string host; 
		int port_network;
		std::string password_network;
		int port;
		std::string password;
	} args;
}

#endif

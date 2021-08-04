// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   init.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/08/04 13:37:12 by gmelisan          #+#    #+#             //
//   Updated: 2021/08/04 16:44:10 by gmelisan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

#include "init.h"
#include "ft_irc.h"
#include "Logger.h"

void sighandler(int n)
{
	switch (n) {
	case SIGINT:
	case SIGTERM:
	case SIGABRT:
		logger.info("Catched signal %d", n);
		exit(0);
	}
}

namespace init
{
	void start(int argc, char **argv)
	{
		signal(SIGINT, sighandler);
		signal(SIGTERM, sighandler);
		signal(SIGABRT, sighandler);

		parse_args(argc, argv);
		logger.info("host: '%s'", ft_irc::args.host.c_str());
		logger.info("port_network: %d", ft_irc::args.port_network);
		logger.info("password_network: '%s'", ft_irc::args.password_network.c_str());
		logger.info("port: %d", ft_irc::args.port);
		logger.info("password: '%s'", ft_irc::args.password.c_str());
	}

	void parse_args(int argc, char **argv)
	{
		if (argc < 3) {
			std::cerr << "Not enough arguments" << std::endl;
			std::cerr << ft_irc::usage;
			exit(1);
		}
		if (argc == 3) {
			ft_irc::args.port = atoi(argv[1]);
			ft_irc::args.password = argv[2];
		} else {
			parse_args_network(argv[1]);
			ft_irc::args.port = atoi(argv[2]);
			ft_irc::args.password = argv[3];
		}
	}

	void parse_args_network(char *str)
	{
		const char *delim = ":";
		char *token;
		int i = 0;

		token = strtok(str, delim);
		while (token) {
			if (i == 0) {
				ft_irc::args.host = token;
			} else if (i == 1) {
				ft_irc::args.port_network = atoi(token);
			} else if (i == 2) {
				ft_irc::args.password_network = token;
			} else {
				break ;
			}
			++i;
			token = strtok(nullptr, delim);
		}
		if (i != 3) {
			std::cerr << "Wrong arguments" << std::endl;
			std::cerr << ft_irc::usage;
			exit(1);
		}
	}

} // namespace init

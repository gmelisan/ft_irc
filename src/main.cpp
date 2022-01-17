#include <unistd.h>
#include <signal.h>

#include "Logger.h"
#include "init.h"
#include "ft_irc.h"
#include "Server.h"

namespace ft_irc
{
	const char *program_name = "ircserv";
	const char *program_version = "0.1.0";
	const char *logpath = "ircserv.log";
	const char *server_name = "ft_irc.gmelisan.42";
	
	const char *usage =
		"Usage: ./ircserv [host:port_network:password_network] <port> <password>\n"
		"where\n"
		"	host               - hostname of server in existing network [NOT IMPLEMENTED]\n"
		"	port_network       - port on witch must connect to host [NOT IMPLEMENTED]\n"
		"	password_network   - password needed to connect to host [NOT IMPLEMENTED]\n"
		"	port               - port on which server will accept connections\n"
		"	password           - password for clients to be able to connect\n";
	struct s_args args;
}

int		main(int argc, char **argv)
{
	init::start(argc, argv);
	Server server(ft_irc::args.port);
	server.start();
	return 0;
}

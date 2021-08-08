/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 11:26:31 by gmelisan          #+#    #+#             */
//   Updated: 2021/08/08 14:45:14 by gmelisan         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/select.h>
# include <list>

# include "Client.h"
# include "MessageHandler.h"

class Server
{
public:
	Server(int port);
	~Server();
	void start();
	
private:
	int m_fd;
	struct {
		fd_set readfds;
		fd_set writefds;
		int nfds;
	} m_select_data;
	
	void create(int port);
	void prepareSelectData();
	void doSelect();
	void process();
	void doAccept();

	std::list<Client> m_clients;
	int m_client_maxfd; // update when new client connects and disconnects

	MessageHandler m_message_handler;
};

#endif

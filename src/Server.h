/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 11:26:31 by gmelisan          #+#    #+#             */
//   Updated: 2021/08/06 18:37:05 by gmelisan         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/select.h>
# include <list>

# define BUFSIZE		4096

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

	class Client
	{
	public:
		Client(int fd);
		~Client();
		bool operator<(const Client &c) const;
		bool operator==(const Client &c) const;
		int fd() const;
		bool alive() const;
		bool pendingSend() const;
		void send();
		void receive();
		
	private:
		bool m_alive;
		int m_fd;
		char m_buf_write[BUFSIZE];
		char m_buf_read[BUFSIZE];
		bool m_pending_send;
	};
	std::list<Client> clients;
	int m_client_maxfd; // update when new client connects and disconnects
};

#endif

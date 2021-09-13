/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 14:06:13 by gmelisan          #+#    #+#             */
//   Updated: 2021/09/13 13:36:56 by gmelisan         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

#include <string>

# define BUFSIZE		4096

class Client
{
public:
	Client(int fd, std::string host, int port);
	bool operator<(const Client &c) const;
	bool operator==(const Client &c) const;
	std::string host() const;
	int port() const;
	int fd() const;
	bool alive() const;
	std::string getReadBuffer() const;
	bool pendingSend() const;
	void readySend(const char *data);
	void send();
	void receive();
		
private:
	std::string m_host;
	int m_port;
	bool m_alive; // set to false on disconnect and remove from list
	int m_fd; // socket got from ::accept()
	char m_buf_write[BUFSIZE];
	char m_buf_read[BUFSIZE];
	bool m_pending_send; // raise this flag when need to send something

	std::string m_read_command; // past tense `read', build from multiple data in m_buf_read

	std::string username;
};

#endif

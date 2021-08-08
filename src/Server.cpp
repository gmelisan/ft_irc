// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/08/05 11:27:35 by gmelisan          #+#    #+#             //
//   Updated: 2021/08/06 18:51:38 by gmelisan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/errno.h>

#include "Server.h"
#include "Logger.h"
#include "utils.h"

Server::Server(int port) : m_client_maxfd(-1)
{
	create(port);
}
Server::~Server()
{
	clients.clear();
	::close(m_fd);
}

void Server::start()
{
	while (21) {
		prepareSelectData();
		doSelect();
		process();
	}
}

void Server::create(int port)
{
	struct sockaddr_in sin;
	struct protoent *pe;

	logger.debug("create server");
	pe = (struct protoent*)Xv(NULL, ::getprotobyname("tcp"), "getprotobyname");
	m_fd = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
	logger.debug("server socket fd = %d", m_fd);
	::fcntl(m_fd, F_SETFL, O_NONBLOCK);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	X(-1, ::bind(m_fd, (struct sockaddr*)&sin, sizeof(sin)), "bind");
	X(-1, ::listen(m_fd, 42), "listen");
	logger.info("Listening on port %d", port);
}

void Server::prepareSelectData()
{
	std::list<Client>::iterator it;

	logger.debug("prepare select data");
	FD_ZERO(&m_select_data.readfds);
	FD_ZERO(&m_select_data.writefds);

	m_select_data.nfds = m_fd;
	FD_SET(m_fd, &m_select_data.readfds);
	
	if (!clients.empty()) {
		m_select_data.nfds = std::max(m_select_data.nfds, m_client_maxfd); 
	}
	++m_select_data.nfds;
	for (it = clients.begin(); it != clients.end(); ++it) {
		FD_SET(it->fd(), &m_select_data.readfds);
		if (it->pendingSend()) {
			FD_SET(it->fd(), &m_select_data.writefds);
		}
	}
}

void Server::doSelect()
{
	logger.debug("select()");
	int ret = ::select(m_select_data.nfds,
								 &m_select_data.readfds,
								 &m_select_data.writefds,
								 nullptr, nullptr);
	if (ret < 0) {
		logger.error("select() error: %s", strerror(errno));
	}
}

void Server::process()
{
	std::list<Client>::iterator it;
	for (it = clients.begin(); it != clients.end();) {
		if (FD_ISSET(it->fd(), &m_select_data.readfds)) {
			it->receive();
		}
		if (FD_ISSET(it->fd(), &m_select_data.writefds)) {
			it->send();
		}
		if (!it->alive()) {
			logger.debug("erase client %d", it->fd());
			close(it->fd());
			it = clients.erase(it);
			m_client_maxfd = max_element(clients.begin(), clients.end())->fd();
			continue ;
		}
		++it;
	}
	if (FD_ISSET(m_fd, &m_select_data.readfds)) {
		doAccept();
	}
}

void Server::doAccept()
{
	int cs;
	struct sockaddr_in csin;
	socklen_t csin_len;

	csin_len = sizeof(csin);
	cs = ::accept(m_fd, (struct sockaddr*)&csin, &csin_len);
	logger.info("New client #%d from %s:%d", cs,
		   inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	clients.push_front(Client(cs));
	if (cs > m_client_maxfd)
		m_client_maxfd = cs;
}

// class Server::Client

Server::Client::Client(int fd) : m_alive(true), m_fd(fd), m_pending_send(0)
{}

Server::Client::~Client()
{}

bool Server::Client::operator<(const Client &c) const
{
	return m_fd < c.m_fd;
}

bool Server::Client::operator==(const Client &c) const
{
	return m_fd == c.m_fd;
}

int Server::Client::fd() const
{
	return m_fd;
}

bool Server::Client::alive() const
{
	return m_alive;
}

bool Server::Client::pendingSend() const
{
	return m_pending_send;
}

void Server::Client::send()
{
	if (!m_alive)
		return ;
	logger.debug("send to client %d", m_fd);

	int r = ::send(m_fd, m_buf_write, strlen(m_buf_write), 0);
	if (r <= 0) {
		logger.info("Client #%d disconnected", m_fd);
		m_alive = false;
		return ;
	}
	m_pending_send = false;
}

void Server::Client::receive()
{
	if (!m_alive)
		return ;
	int r;

	logger.debug("receive from client %d", m_fd);
	memset(m_buf_read, 0, BUFSIZE);
	r = recv(m_fd, m_buf_read, BUFSIZE, 0);
	if (r <= 0) {
		logger.info("Client #%d disconnected", m_fd);
		m_alive = false;
		return ;
	}
	logger.info("get string '%s'", m_buf_read);
	if (std::string(m_buf_read) == "hui\n") {
		memcpy(m_buf_write, "mocha\n", 7);
		m_pending_send = true;
	}
}

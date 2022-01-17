// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Client.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/08/08 14:06:55 by gmelisan          #+#    #+#             //
//   Updated: 2022/01/17 18:25:57 by gmelisan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstring>
#include <sys/socket.h>

#include "Client.h"
#include "Logger.h"

Client::Client(int fd, std::string host, int port)
	: m_host(host), m_port(port), m_alive(true), m_fd(fd), m_pending_send(0)
{}

bool Client::operator<(const Client &c) const
{
	return m_fd < c.m_fd;
}

bool Client::operator==(const Client &c) const
{
	return m_fd == c.m_fd;
}

std::string Client::host() const
{
	return m_host;
}

int Client::port() const
{
	return m_port;
}

int Client::fd() const
{
	return m_fd;
}

bool Client::alive() const
{
	return m_alive;
}

std::string Client::getReadBuffer() const
{
	return m_buf_read;
}

bool Client::pendingSend() const
{
	return m_pending_send;
}

void Client::readySend(const char *data)
{
	memset(m_buf_write, 0, BUFSIZE);
	int len = strlen(data);
	if (len >= BUFSIZE) {
		logger.error("Trying to send too much data to client %d", m_fd);
		return ;
	}
	memcpy(m_buf_write, data, strlen(data));
	m_pending_send = true;
}

void Client::send()
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

void Client::receive()
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
}

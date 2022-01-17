// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Message.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/09/13 13:54:14 by gmelisan          #+#    #+#             //
//   Updated: 2022/01/18 00:57:03 by gmelisan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstring>
#include "Message.h"
#include "Logger.h"

Message::Message()
{}

void Message::clear()
{
	m_data.clear();
	m_prefix.clear();
	m_command.clear();
	m_params.clear();
	m_type = UNKNOWN;
}

bool Message::parse(const std::string &data)
{
	clear();
	(void)m_type;
	if (data.size() > 510) {
		logger.error("Message exceeds 510 char limit");
		return false;
	}
	// numeric reply not allowed for clients (2.4)

	char buf[512];
	char *token;
	memcpy(buf, data.c_str(), data.size());
	for (int i = 0; i < 512; ++i) {
		if (buf[i] == '\r')
			buf[i] = 0;
		if (buf[i] == '\n')
			buf[i] = 0;
	}
	token = strtok(buf, " ");
	if (token[0] == ':')
		m_prefix = token;
	else
		m_command = token;
	while ((token = strtok(NULL, " "))) {
		if (m_command.empty()) {
			m_command = token;
		} else {
			m_params.push_back(token);
		}
	}
	parse_command();
	logger.debug("parsed command: '%s' '%s' <%d>", m_prefix.c_str(), m_command.c_str(), m_type);
	for (size_t i = 0; i < m_params.size(); ++i)
		logger.debug("arg %lu: '%s'", i, m_params[i].c_str());
	
	return true;
}

const std::string &Message::data() const
{
	return m_data;
}
const std::string &Message::command() const
{
	return m_command;
}
const std::vector<std::string> &Message::params() const
{
	return m_params;
}
MessageType Message::type() const
{
	return m_type;
}

void Message::parse_command()
{
	if (m_command == "PASS")
		m_type = PASS;
	if (m_command == "NICK")
		m_type = NICK;
	if (m_command == "USER")
		m_type = USER;
	if (m_command == "SERVER")
		m_type = SERVER;
	if (m_command == "OPER")
		m_type = OPER;
	if (m_command == "QUIT")
		m_type = QUIT;
	if (m_command == "SQUIT")
		m_type = SQUIT;
	if (m_command == "JOIN")
		m_type = JOIN;
	if (m_command == "PART")
		m_type = PART;
	if (m_command == "MODE")
		m_type = MODE;
	if (m_command == "TOPIC")
		m_type = TOPIC;
	if (m_command == "NAMES")
		m_type = NAMES;
	if (m_command == "LIST")
		m_type = LIST;
	if (m_command == "INVITE")
		m_type = INVITE;
	if (m_command == "KICK")
		m_type = KICK;
	if (m_command == "VERSION")
		m_type = VERSION;
	if (m_command == "STATS")
		m_type = STATS;
	if (m_command == "LINKS")
		m_type = LINKS;
	if (m_command == "TIME")
		m_type = TIME;
	if (m_command == "CONNECT")
		m_type = CONNECT;
	if (m_command == "TRACE")
		m_type = TRACE;
	if (m_command == "ADMIN")
		m_type = ADMIN;
	if (m_command == "INFO")
		m_type = INFO;
	if (m_command == "PRIVMSG")
		m_type = PRIVMSG;
	if (m_command == "NOTICE")
		m_type = NOTICE;
	if (m_command == "WHO")
		m_type = WHO;
	if (m_command == "WHOIS")
		m_type = WHOIS;
	if (m_command == "WHOWAS")
		m_type = WHOWAS;
	if (m_command == "KILL")
		m_type = KILL;
	if (m_command == "PING")
		m_type = PING;
	if (m_command == "PONG")
		m_type = PONG;
	if (m_command == "ERROR")
		m_type = ERROR;
}

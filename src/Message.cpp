// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Message.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/09/13 13:54:14 by gmelisan          #+#    #+#             //
//   Updated: 2022/01/17 18:27:41 by gmelisan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstring>
#include "Message.h"
#include "Logger.h"

Message::Message(std::string data)
{
	m_data = data;
}

bool Message::parse()
{
	(void)m_type;
	if (m_data.size() > 510) {
		logger.error("Message exceeds 510 char limit");
		return false;
	}
	// TODO parse m_data
	// numeric reply not allowed for clients (2.4)

	char data[512];
	char *token;
	memcpy(data, m_data.c_str(), m_data.size());
	token = strtok(data, " ");
	if (token[0] == ':')
		m_prefix = token;
	else
		m_command = token;
	while (token) {
		token = strtok(NULL, " ");
	}
	
	
	return true;
}

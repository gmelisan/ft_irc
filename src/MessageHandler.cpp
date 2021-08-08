// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MessageHandler.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/08/08 14:18:23 by gmelisan          #+#    #+#             //
//   Updated: 2021/08/08 15:32:00 by gmelisan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "MessageHandler.h"
#include "utils.h"
#include "Logger.h"

#define COMMANDS_NUM			3
const char *commands[] =
{
	"help",
	"list",
	"send"
};

MessageHandler::MessageHandler(std::list<Client> *clients) : m_clients(clients)
{}

void MessageHandler::newMessage(std::list<Client>::iterator it)
{
	// Two cases:
	// 1 - full command
	// 2 - part command

	// 1
	m_it_current_client = it;
	std::string buf_read = m_it_current_client->getReadBuffer();
	for (int i = 0; i < COMMANDS_NUM; ++i) {
		if (buf_read.find(commands[i], 0) == 0) {
			std::string arg = buf_read.substr(strlen(commands[i]));
			handleCommand(commands[i], arg);
		}
	}
}

void MessageHandler::handleCommand(std::string cmd, std::string arg)
{
	std::list<Client>::iterator it;
	
	if (cmd == "help") {
		logger.debug("handle 'help'");
		const char *help_text =
			"Sample chat\n"
			"Commands:\n"
			" help - this help\n"
			" list - list connected clients\n"
			" send N TEXT - send message 'TEXT' to client N\n";
		m_it_current_client->readySend(help_text);
	} else if (cmd == "list") {
		logger.debug("handle 'list'");
		std::string list_text = "Clients:\n";
		for (it = m_clients->begin(); it != m_clients->end(); ++it) {
			char buf[32] = {0};
			sprintf(buf, "%d", it->fd());
			list_text += buf;
			if (it->fd() == m_it_current_client->fd())
				list_text += " (you)";
			list_text += "\n";
			m_it_current_client->readySend(list_text.c_str());
		}
	} else if (cmd == "send") {
		logger.debug("handle 'send'");
		std::vector<std::string> args = split_string(arg);
		for (size_t i = 0; i < args.size(); ++i) {
			logger.debug("arg %lu: %s", i, args[i].c_str());
		}
		if (args.size() < 2) {
			m_it_current_client->readySend("Need 2 args\n");
			return ;
		}
		int target = atoi(args[0].c_str());
		bool found = false;
		for (it = m_clients->begin(); it != m_clients->end(); ++it) {
			if (it->fd() == target) {
				it->readySend(args[1].c_str());
				found = true;
			}
		}
		if (!found) {
			m_it_current_client->readySend("Client not found\n");
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageHandler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 14:02:48 by gmelisan          #+#    #+#             */
//   Updated: 2022/01/18 00:45:37 by gmelisan         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGEHANDLER_H
# define MESSAGEHANDLER_H

#include <list>
#include "Client.h"
#include "Message.h"

extern const char *commands[];

class MessageHandler
{
public:
	MessageHandler(std::list<Client> *clients);
	void newMessage(std::list<Client>::iterator it);	
	void newMessageTest(std::list<Client>::iterator it);
	
private:
	std::list<Client> *m_clients;
	std::list<Client>::iterator m_it_current_client;

	void handleCommand(std::string cmd, std::string arg);
	void handleCommandTest(std::string cmd, std::string arg);
	void handleMessage_Registration(const Message &message);
};

#endif

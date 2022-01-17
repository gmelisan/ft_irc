// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Logger.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/08/04 11:36:28 by gmelisan          #+#    #+#             //
//   Updated: 2022/01/17 23:29:58 by gmelisan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <ctime>
#include <cstdarg>
#include <iostream>

#include "Logger.h"
#include "ft_irc.h"

Logger logger(0);

Logger::Logger(int use_file)
{
	if (use_file) {
		m_file = fopen(ft_irc::logpath, "a");
		if (!m_file) {
			std::cerr << "Can't open logfile '" << ft_irc::logpath << "': "
					  << strerror(errno);
			exit(1);
		}
	} else {
		m_file = stdout;
	}
	setbuf(m_file, NULL);
	info("Started, version %s", ft_irc::program_version);
}

Logger::~Logger()
{
	info("Exited");
	fclose(m_file);
}

void			Logger::info(const char *format, ...)
{
	va_list ap;
	const int buf_maxsize = 1024;
	char buf[buf_maxsize] = {};
	
	va_start(ap, format);
	vsnprintf(buf, buf_maxsize - 1, format, ap);
	va_end(ap);
	fprintf(m_file, "%s [INFO] %s\n", getTime().c_str(), buf);
}

void			Logger::error(const char *format, ...)
{
	va_list ap;
	const int buf_maxsize = 1024;
	char buf[buf_maxsize] = {};
	
	va_start(ap, format);
	vsnprintf(buf, buf_maxsize - 1, format, ap);
	va_end(ap);
	fprintf(m_file, "%s [ERROR] %s\n", getTime().c_str(), buf);
}

void			Logger::debug(const char *format, ...)
{
#ifndef DEBUG
	(void)format;
	return ;
#endif
	
	va_list ap;
	const int buf_maxsize = 1024;
	char buf[buf_maxsize] = {};
	
	va_start(ap, format);
	vsnprintf(buf, buf_maxsize - 1, format, ap);
	va_end(ap);
	fprintf(m_file, "%s [DEBUG] %s\n", getTime().c_str(), buf);
}

std::string		Logger::getTime()
{
	time_t rawtime;
	struct tm *timeinfo;
	char buf[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buf, 80, "%d.%m.%Y %H:%M:%S", timeinfo);
	return buf;
}

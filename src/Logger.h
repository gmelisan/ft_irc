// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Logger.h                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/08/04 13:25:35 by gmelisan          #+#    #+#             //
//   Updated: 2021/08/04 13:28:09 by gmelisan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LOGGER_H
#define LOGGER_H

#include <cstdio>
#include <string>

class Logger
{
public:
	Logger();
	~Logger();
	void info(const char *format, ...) __attribute__ ((format (printf, 2, 3)));
	void error(const char *format, ...) __attribute__ ((format (printf, 2, 3)));

private:
	FILE *m_file;

	std::string getTime();
};

extern Logger logger;

#endif

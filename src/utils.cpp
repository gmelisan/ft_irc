// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   utils.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/08/05 11:45:20 by gmelisan          #+#    #+#             //
//   Updated: 2021/08/08 15:11:25 by gmelisan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/errno.h>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "utils.h"

int x_int(int err, int res, const char *str, const char *file, int line)
{
	if (res == err)
    {
		fprintf(stderr, "%s error (%s, %d): %s\n", 
				str, file, line, strerror(errno));
		exit (1);
    } 
	return (res);
}

void *x_void(void *err, void *res, const char *str, const char *file, int line)
{
	if (res == err)
    {
		fprintf(stderr, "%s error (%s, %d): %s\n", 
				str, file, line, strerror(errno));
		exit (1);
    } 
	return (res);
}

// https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
std::vector<std::string> split_string(std::string str)
{
	using namespace std;

	istringstream iss(str);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
		 istream_iterator<string>(),
		 back_inserter(tokens));
	return tokens;
}

// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   utils.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/08/05 11:45:20 by gmelisan          #+#    #+#             //
//   Updated: 2021/08/06 12:26:06 by gmelisan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/errno.h>
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

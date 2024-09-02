/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:56:53 by mcarneir          #+#    #+#             */
/*   Updated: 2024/08/13 17:08:16 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <string>
#include <signal.h>
#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include "Server.hpp"
#include "Client.hpp"
#include <vector>
#include <fcntl.h>


#define BUFFER_SIZE 1024


void log(const std::string &message);
void exitError(const std::string &error);



#endif

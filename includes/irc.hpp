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
#include <map>
#include <fcntl.h>
#include <algorithm>
#include <cctype>
#include <sstream>
#define CRLF "\r\n"

#define BUFFER_SIZE 1024
#define ERR_NEEDMOREPARAMS(nickname) (": 461 " + nickname + "Need more parameters" + CRLF)
#define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + "Unauthorized command (already registered)" + CRLF)
#define ERR_NICKNAMEINUSE(nickname) (": 433 " + nickname + "Nickname is already in use" + CRLF)
#define ERR_INCORPASS(nickname) (": 464 " + nickname + "Password incorrect !" + CRLF)
#define ERR_ERRONEUSNICKNAME(nickname) (": 432 " + nickname + "Erroneus nickname" + CRLF)
#define ERR_NOSUCHCHANNEL(channelName) (": 403 " + channelName + "No such channel" + CRLF)
#define ERR_NOTONCHANNEL(channelName) (": 442 " + channelName + "You're not on that channel" + CRLF)

#define RPL_CONNECTED(nickname) (": 001 " + nickname + " : Welcome to the IRC server!" + CRLF)


void log(const std::string &message);
void exitError(const std::string &error);
void removeNewlines(std::string &str);
std::string trim(const std::string& str);





#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:12:05 by mcarneir          #+#    #+#             */
/*   Updated: 2024/08/26 17:16:49 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client(){}

int Client::getFd()
{
	return this->_fd;
}

void Client::setFd(int fd)
{
	this->_fd = fd;
}

std::string Client::getIp()
{
	return this->_ip;
}

void Client::setIp(std::string ip)
{
	this->_ip = ip;
}

Client::~Client(){}
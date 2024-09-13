/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:12:05 by mcarneir          #+#    #+#             */
/*   Updated: 2024/09/12 15:41:33 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client(): _authenticated(false), _registered(false){}

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

bool Client::isAuthenticated()
{
	return this->_authenticated;
}

void Client::authenticate()
{
	_authenticated = true;
}

std::string Client::getNick()
{
	return this->_nickname;
}

void Client::setNick(std::string nickname)
{
	_nickname = nickname;
}

std::string Client::getUsername()
{
	return this->_username;
}

void Client::setUsername(std::string username)
{
	if (username.empty())
		return ;
	else
		_username = username;
}

bool Client::isRegistered()
{
	return this->_registered;
}

void Client::registerClient()
{
	_registered = true;
}

void Client::setRealname(std::string realname)
{
	_realname = realname;
}

std::string Client::getRealname()
{
	return this->_realname;
}

void Client::setHostname(std::string hostname)
{
	_hostname = hostname;
}

std::string Client::getHostname()
{
	return this->_hostname;
}

void Client::setServername(std::string servername)
{
	_servername = servername;
}

std::string Client::getServername()
{
	return this->_servername;
}

std::vector<std::string> Client::getChannels()
{
	return this->_channels;
}

void Client::joinChannel(const std::string &channel)
{
	_channels.push_back(channel);
}

void Client::leaveChannel(const std::string &channel)
{
	std::vector<std::string>::iterator it = std::find(_channels.begin(), _channels.end(), channel);
	if (it != _channels.end())
		_channels.erase(it);
}


Client::~Client()
{
	for(std::vector<std::string>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		leaveChannel(*it);
	}
}
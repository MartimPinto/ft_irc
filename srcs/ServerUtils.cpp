/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:14:32 by mcarneir          #+#    #+#             */
/*   Updated: 2024/10/24 16:47:07 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"


void Server::sendResponse(std::string response, int client_index)
{
	if (send(client_index, response.c_str(), response.length(), 0) == -1)
		std::cerr << "Error sending response" << std::endl;
}

void Server::printChannelNames() const
{
    for (std::map<std::string, Channel>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
    {
        std::cout << "Channel name stored: '" << it->first << "'" << std::endl;
    }
}

void Server::verifyPassword(std::string cmd, Client &cli, int client_index)
{
	std::string pass = cmd.substr(5);
	pass = pass.substr(0, pass.find("\n"));
	if (pass.empty())
	{
		sendResponse(ERR_NEEDMOREPARAMS(getClient(client_index).getNick()), client_index);
		return ;
	}
	if (cli.isAuthenticated())
		sendResponse(ERR_ALREADYREGISTERED(getClient(client_index).getNick()), client_index);
	if (pass == _password)
	{

		cli.authenticate();
		log("Client authenticated sucessfully");
	}
	else
		sendResponse(ERR_INCORPASS(getClient(client_index).getNick()), client_index);
}

void Server::closeServer()
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		std::cout << "Client " << _clients[i].getFd() << " disconnected" << std::endl;
		close(_clients[i].getFd());
	}
	close(_socket);
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		delete &it->second;
	_clients.clear();
	_channels.clear();
	exit(0);
}

void Server::clearClients(int fd)
{
	for (size_t i = 0; i < _fds.size(); i++)
	{
		if (_fds[i].fd == fd)
		{
			_fds.erase(_fds.begin() + i);
			break ;
		}
	}
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if(_clients[i].getFd() == fd)
		{
			_clients.erase(_clients.begin() + i);
			break;
		}
	}	
}

void Server::clearChannels(int fd)
{
	std::map<std::string, Channel>::iterator it = _channels.begin();
	while (it != _channels.end())
	{
		Channel &channel = it->second;
		int flag = 0;
		if (channel.getClient(fd))
		{
			channel.removeClientFd(fd);
			flag = 1;
		}
		if (channel.getOperator(fd))
		{
			channel.removeOperatorFd(fd);
			flag = 1;
		}
		if (channel.getNumUsers() == 0)
		{
			log("Channel " + it->first + " removed due to empty state.");
			_channels.erase(it++);
			continue;
		}
		if (flag)
		{
			std::string rpl = ":" + getClient(fd).getNick() + "@localhost QUIT Quit\r\n";
			channel.sendAll(rpl);
		}
		++it;
	}
}
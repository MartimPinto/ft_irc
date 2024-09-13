/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:47:43 by mcarneir          #+#    #+#             */
/*   Updated: 2024/09/12 16:12:29 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel(const std::string &name): _name(name){}

Channel::Channel(const Channel &src)
{
	*this = src;
}

Channel::~Channel()
{
	this->_clients.clear();
	this->_operators.clear();
}

const std::string &Channel::getName() const
{
	return this->_name;
}

void Channel::addClient(Client *client)
{
	this->_clients.push_back(client);
}

void Channel::removeClient(Client *client)
{
	std::vector<Client *>::iterator it = std::find(this->_clients.begin(), this->_clients.end(), client);
	if (it != this->_clients.end())
		this->_clients.erase(it);
}

std::vector<Client *> &Channel::getClients()
{
	return this->_clients;
}

bool Channel::isOperator(Client &client)
{
	std::vector<Client *>::iterator it = std::find(this->_operators.begin(), this->_operators.end(), &client);
	if (it != this->_operators.end())
		return true;
	return false;
}

void Channel::addOperator(Client &client)
{
	this->_operators.push_back(&client);
}

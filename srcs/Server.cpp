/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:17:26 by mcarneir          #+#    #+#             */
/*   Updated: 2024/08/28 16:13:15 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

bool Server::Signal = false;

void Server::sigHandler(int signum)
{
	(void)signum;
	std::cout << std::endl;
	log("Signal Recieved!");
	Server::Signal = true;
}

Server::Server(int port, std::string pass): _socket(), _port(port),
_newSocket(), _socketAddress(), _socketAddressLen(sizeof(_socketAddress)), _password(pass)
{
	struct pollfd pfd;
	_socketAddress.sin_family = AF_INET;
	_socketAddress.sin_port = htons(_port);
	_socketAddress.sin_addr.s_addr = INADDR_ANY;
	memset(_socketAddress.sin_zero, 0, sizeof(_socketAddress.sin_zero));
	if (startServer() == 0)
	{
		pfd.fd = _socket;
		pfd.events = POLLIN;
		pfd.revents = 0;
		_fds.push_back(pfd);
		
	}
}

int Server::startServer()
{
	if ((_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0)
	{
		exitError("Cannot create socket");
		return 1;
	}
	if(bind(_socket, (sockaddr*)&_socketAddress, _socketAddressLen) < 0)
	{
		exitError("Cannot connect socket to address");
		return 1;
	}
	if (listen(_socket, SOMAXCONN) < 0)
	{
		exitError("Socket listen failed");
	}
	return 0;
}

void Server::startListen()
{
	std::ostringstream ss;
	ss << "\n *** Server: " 
	<< _socket << " Connected" <<" ***\n";
	log(ss.str());

	while (Server::Signal == false)
	{
		if ((poll(&_fds[0], _fds.size(), -1) == -1) && Server::Signal == false)
			exitError("Poll failed");
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].revents & POLLIN)
			{
				if(_fds[i].fd == _socket)
					handleNewConnection();
				else
					handleClient(_fds[i].fd);
			}
		}	
	}
	this->closeServer();
}

void Server::handleNewConnection()
{
	Client cl;
	struct sockaddr_in claddr;
	struct pollfd npoll;
	socklen_t len = sizeof(claddr);
	
	_newSocket = accept(_socket,(sockaddr *)&(claddr), &len);
	if (_newSocket < 0)
		exitError("accept() failed");
	if (fcntl(_newSocket, F_SETFL, O_NONBLOCK) < 0)
		exitError("fcntl() failed");
		
	npoll.fd = _newSocket;
	npoll.events = POLLIN;
	npoll.revents = 0;

	cl.setFd(_newSocket);
	cl.setIp(inet_ntoa(claddr.sin_addr));
	_clients.push_back(cl);
	_fds.push_back(npoll);
		
	log("New connection accepted");
}

void Server::handleClient(int client_index)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, sizeof(buffer));
	Client &cli = _clients[client_index - 1];
	int bytesReceived = recv(client_index, buffer, BUFFER_SIZE - 1, 0);
	if (bytesReceived <= 0)
	{
		close(client_index);
		_fds.erase(_fds.begin() + client_index);
		log("Client disconnected");
	}
	else
	{
		buffer[bytesReceived] = '\0';
		log("Received message from client");
		std::string cmd(buffer);
		if(!cli.isAuthenticated())
		{
			if (cmd.find("PASS") == 0)
			{
				std::string pass = cmd.substr(5);
				pass = pass.substr(0, pass.find("\n"));
				if (pass == _password)
				{
					cli.authenticate();
					log("Client authenticated sucessfully");
				}
				else
				{
					log("Client provided incorrect password");
                    close(client_index);
                    clearClients(client_index);
				}
			}
			else
			{
				std::string error = "ERROR: Use PASS command and type password to authenticate client\r\n";
                send(client_index, error.c_str(), error.length(), 0);
			}
		}
		
	}
}

void Server::closeServer()
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		std::cout << "Client " << _clients[i].getFd() << " disconnected" << std::endl;
		close(_clients[i].getFd());
	}
	close(_socket);
	exit(0);
}

void Server::clearClients(int fd)
{
	for(size_t i = 0; i < _fds.size(); i++)
	{
		if (_fds[i].fd == fd)
		{
			_fds.erase(_fds.begin() + i);
			break ;
		}
	}
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if(_clients[i].getFd() == fd)
		{
			_clients.erase(_clients.begin() + i);
			break;
		}
	}
}

Server::~Server()
{
	closeServer();
}
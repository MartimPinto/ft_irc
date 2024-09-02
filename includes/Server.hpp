/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:06:14 by mcarneir          #+#    #+#             */
/*   Updated: 2024/09/02 16:43:24 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

class Client;

#include "irc.hpp"
#include <vector>
#include "Client.hpp"

class Server
{
	public:
			Server(int port, std::string pass);
			~Server();
			void startListen();
			static void sigHandler(int signum);
			void clearClients(int fd);
			void closeServer();
	
	private:
			std::string m_ip_address;
			int	_socket;
			int _port;
			int _newSocket;
			struct sockaddr_in _socketAddress;
			unsigned int _socketAddressLen;
			std::string _password;
			std::string _serverMessage;
			std::vector<struct pollfd> _fds;
			std::vector<Client> _clients;
			static bool Signal;
			

			int startServer();
			void handleNewConnection();
			void handleClient(int client_index);
			void parseCommand(std::string cmd, Client &cli, int client_index);
			void verifyPassword(std::string cmd, Client &cli, int client_index);
			void handleNick(std::string cmd, Client &cli);

};

#endif
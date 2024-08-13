/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:06:14 by mcarneir          #+#    #+#             */
/*   Updated: 2024/08/13 17:10:44 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "webserver.hpp"
#include <vector>

class Server
{
	public:
			Server(std::string ip, int port);
			~Server();
			void startListen();
			void acceptConnection(int &new_socket);
			
	
	private:
			std::string m_ip_address;
			int	m_socket;
			int m_port;
			int m_new_socket;
			//long m_incomingMessage;
			struct sockaddr_in m_socketAddress;
			unsigned int m_socketAddress_len;
			std::string m_serverMessage;
			std::vector<pollfd> m_fds;
			int m_timeout;

			
			int startServer();
			void closeServer();
			std::string buildResponse();
			void sendResponse(int client_socket);
			void handleNewConnection();
			void handleClient(int client_index);
	
};

#endif
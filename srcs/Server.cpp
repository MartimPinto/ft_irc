/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:17:26 by mcarneir          #+#    #+#             */
/*   Updated: 2024/08/13 14:32:41 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server(std::string ip, int port): m_ip_address(ip), m_socket(), m_port(port),
m_new_socket(), m_socketAddress(), m_socketAddress_len(sizeof(m_socketAddress)),
m_serverMessage(buildResponse())
{
	m_socketAddress.sin_family = AF_INET;
	m_socketAddress.sin_port = htons(m_port);
	m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
	startServer();
}

int Server::startServer()
{
	if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		exitError("Cannot create socket");
		return 1;
	}
	if(bind(m_socket, (sockaddr*)&m_socketAddress, m_socketAddress_len) < 0)
	{
		exitError("Cannot connect socket to address");
		return 1;
	}
	return 0;
}

void Server::startListen()
{
	if (listen(m_socket, 20) < 0)
	{
		exitError("Socket listen failed");
	}
	std::ostringstream ss;
	ss << "\n *** Listening on Address: " 
	<< inet_ntoa(m_socketAddress.sin_addr)
	<< " Port: " << ntohs(m_socketAddress.sin_port)
	<<" ***\n\n";
	log(ss.str());

	int bytesReceived;

	while (true)
	{
		log("==== Waiting for a new Connection ====");
		acceptConnection(m_new_socket);
		char buffer[BUFFER_SIZE] = {0};
		if ((bytesReceived = read(m_new_socket, buffer, BUFFER_SIZE)) < 0)
			exitError("Failed to read bytes from client socket");
		log("---- Received Request from Client ----");
		sendResponse();
		close(m_new_socket);
	}
}

void Server::acceptConnection(int &new_socket)
{
	new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, &m_socketAddress_len);
	if (new_socket < 0)
	{
		std::ostringstream ss;
		ss << "\n *** Server failed to accept connection from Address: " 
		<< inet_ntoa(m_socketAddress.sin_addr)
		<< " Port: " << ntohs(m_socketAddress.sin_port)
		<<" ***\n\n";
		exitError(ss.str());
	}
}

void Server::closeServer()
{
	close(m_socket);
	close(m_new_socket);
	exit(0);
}

std::string Server::buildResponse()
{
	std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
    std::ostringstream ss;
    ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"
        << htmlFile;

    return ss.str();
}

void Server::sendResponse()
{
	unsigned long bytesSent;
	bytesSent = write(m_new_socket, m_serverMessage.c_str(), m_serverMessage.size());
	if (bytesSent == m_serverMessage.size())
	{
		log("Response sent successfully");
	}
	else
	{
		exitError("Failed to send response");
	}
}

Server::~Server()
{
	closeServer();
}
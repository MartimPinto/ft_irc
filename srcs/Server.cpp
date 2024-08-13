/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:17:26 by mcarneir          #+#    #+#             */
/*   Updated: 2024/08/13 17:11:30 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server(std::string ip, int port): m_ip_address(ip), m_socket(), m_port(port),
m_new_socket(), m_socketAddress(), m_socketAddress_len(sizeof(m_socketAddress)),
m_serverMessage(buildResponse()), m_timeout(3000)
{
	m_socketAddress.sin_family = AF_INET;
	m_socketAddress.sin_port = htons(m_port);
	m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
	memset(m_socketAddress.sin_zero, 0, sizeof(m_socketAddress.sin_zero));
	if (startServer() == 0)
	{
		pollfd pfd = {m_socket, POLLIN, 0};
		m_fds.push_back(pfd);
	}
}

int Server::startServer()
{
	if ((m_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0)
	{
		exitError("Cannot create socket");
		return 1;
	}
	if(bind(m_socket, (sockaddr*)&m_socketAddress, m_socketAddress_len) < 0)
	{
		exitError("Cannot connect socket to address");
		return 1;
	}
	if (listen(m_socket, 20) < 0)
	{
		exitError("Socket listen failed");
	}
	return 0;
}

void Server::startListen()
{
	int poll_count;
	std::ostringstream ss;
	ss << "\n *** Listening on Address: " 
	<< inet_ntoa(m_socketAddress.sin_addr)
	<< " Port: " << ntohs(m_socketAddress.sin_port)
	<<" ***\n\n";
	log(ss.str());

	while (true)
	{
		if ((poll_count = poll(m_fds.data(), m_fds.size(), m_timeout)) < 0)
			exitError("Poll failed");
		for (unsigned long i = 0; i < m_fds.size(); ++i)
		{
			if (m_fds[i].revents & POLLIN)
			{
				if(m_fds[i].fd == m_socket)
					handleNewConnection();
				else
					handleClient(i);
			}
		}
			
	}
}

void Server::handleNewConnection()
{
	acceptConnection(m_new_socket);
	pollfd pfd = {m_new_socket, POLLIN, 0};
	m_fds.push_back(pfd);
	log("New connection accepted");
}

void Server::handleClient(int client_index)
{
	int client_socket = m_fds[client_index].fd;
	char buffer[BUFFER_SIZE] = {0};
	int bytesReceived;
	bytesReceived = read(client_socket, buffer, BUFFER_SIZE);
	if (bytesReceived < 0)
	{
		exitError("Failed to read from client");
	}
	else if (bytesReceived == 0)
	{
		close(client_socket);
		m_fds.erase(m_fds.begin() + client_index);
		log("Client disconnected");
	}
	else
	{
		log("Received message from client");
		sendResponse(client_socket);
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

void Server::sendResponse(int client_socket)
{
	unsigned long bytesSent;
	bytesSent = write(client_socket, m_serverMessage.c_str(), m_serverMessage.size());
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
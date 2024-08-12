/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:17:26 by mcarneir          #+#    #+#             */
/*   Updated: 2024/08/12 16:58:57 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserver.hpp"

int main()
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	std::string hello = "Hello from Server";
	
	if (server_fd = socket(AF_INET, SOCK_STREAM, 0) < 0)
	{
		std::cerr << "Cannot create socket" << std::endl;
		return 1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	memset(address.sin_zero, '\0', sizeof(address.sin_zero));
	
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "Cannot bind" << std::endl;
		return 1;
	}
	
	if (listen(server_fd, 3) < 0)
	{
		std::cerr << "Cannot listen" << std::endl;
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		printf("\n+++++++ Waiting for new connection ++++++++\n\n");
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
		{
			std::cerr << "Cannot accept" << std::endl;
			exit(EXIT_FAILURE);
		}
		char buffer[30000] = {0};
		valread = read(new_socket, buffer, 30000);
		write(new_socket, hello, hello.size());
	}
}
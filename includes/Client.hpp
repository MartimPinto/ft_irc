/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:56:24 by mcarneir          #+#    #+#             */
/*   Updated: 2024/08/26 17:16:21 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../includes/irc.hpp"

class Client
{
	public:
			Client();
			~Client();

			int getFd();
			void setFd(int fd);
			std::string getIp();
			void setIp(std::string ip);

	private:
			int _fd;
			std::string _ip;
};

#endif
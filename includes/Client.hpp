/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:56:24 by mcarneir          #+#    #+#             */
/*   Updated: 2024/08/28 13:20:01 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"

class Client
{
	public:
			Client();
			~Client();

			int getFd();
			void setFd(int fd);
			std::string getIp();
			void setIp(std::string ip);
			bool isAuthenticated();
			void authenticate();

	private:
			int _fd;
			std::string _ip;
			bool _authenticated;
};

#endif
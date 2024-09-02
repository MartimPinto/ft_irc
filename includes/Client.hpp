/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:56:24 by mcarneir          #+#    #+#             */
/*   Updated: 2024/09/02 15:32:18 by mcarneir         ###   ########.fr       */
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
			std::string getNick();
			void setNick(std::string nickname);
			std::string getUsername();
			void setUsername(std::string username);

	private:
			int _fd;
			std::string _ip;
			bool _authenticated;
			std::string _nickname;
			std::string _username;
};

#endif
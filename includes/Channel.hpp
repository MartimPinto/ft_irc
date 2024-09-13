/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:42:11 by mcarneir          #+#    #+#             */
/*   Updated: 2024/09/12 16:14:46 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "irc.hpp"

class Channel
{
	private:
			std::string _name;
			std::vector<Client *> _clients;
			std::vector<Client *> _operators;

	public:
			Channel(const std::string &name);
			Channel(const Channel &src);
			~Channel();
			const std::string &getName() const;
			void addClient(Client *client);
			void removeClient(Client *client);
			std::vector<Client *> &getClients();
			bool isOperator(Client &client);
			void addOperator(Client &client);			
};

#endif
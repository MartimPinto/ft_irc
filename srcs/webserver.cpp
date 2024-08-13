/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:25:38 by mcarneir          #+#    #+#             */
/*   Updated: 2024/08/13 14:26:01 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserver.hpp"

void log(const std::string &message)
{
	std::cout << message << std::endl;	
}

void exitError(const std::string &error)
{
	log("Error: " + error);
	exit(1);		
}
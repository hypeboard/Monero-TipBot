/*
 Copyright(C) 2018 Brandan Tyler Lasley

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
*/
#include "Discord.h"
#include <string>
#include <iostream>
#include "Poco/File.h"
#include <fstream>

#define TOKEN_FILE "token.discord"
std::string myToken;

void setup()
{
	Poco::File discordToken(TOKEN_FILE);

	if (discordToken.exists())
	{
		std::ifstream infile(TOKEN_FILE);
		assert(infile.is_open());
		myToken.assign(std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>());
		infile.close();
		return; // Exit Setup
	}

	std::cout	<< "Welcome to ITNS Tipbot!\n"
				<< "Created by Brandan Tyler Lasley\n"
				<< "Please enter Discord Token: "; 
	
	std::cin >> myToken;

	std::ofstream out(TOKEN_FILE, std::ios::trunc);
	assert(out.is_open());
	out << myToken;
	out.close();

	std::cout << "Token saved to " << TOKEN_FILE << ", delete this file to rerun setup. \n";
}

int main()
{
	// Setup routine
	setup();

	// Run bot with token.
	ITNS_TIPBOT client(myToken, 2);
	client.run();
	return 0;
}

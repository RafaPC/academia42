#include <iostream>
#include <string>
#include "Karen.hpp"

void	Karen::complain( std::string level )
{
	for (int i = 0; i < 4; i++)
	{
		if (this->modes[i] == level)
		{
			(this->*function_ptrs[i])();
			return ;
		}
	}
	std::cout << "I literally don't know what to say...\n";
}

Karen::Karen( void )
{
	this->function_ptrs[0] = &Karen::debug;
	this->function_ptrs[1] = &Karen::info;
	this->function_ptrs[2] = &Karen::warning;
	this->function_ptrs[3] = &Karen::error;
	this->modes[0] = "DEBUG";
	this->modes[1] = "INFO";
	this->modes[2] = "WARNING";
	this->modes[3] = "ERROR";
}

void		Karen::debug( void )
{
	std::cout << "I love to get extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup"
	" burger. I just love it!\n\n";
}

void		Karen::info( void )
{
	std::cout << "I cannot believe adding extra bacon cost more money. "
	"You don’t put enough! If you did I would not have to ask for it!\n\n";
}

void		Karen::warning( void )
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been"
	" coming here for years and you just started working here last month.\n\n";
}

void		Karen::error( void )
{
	std::cout << "This is unacceptable, I want to speak to the manager now.\n\n";
}

void		Karen::filter( std::string mode )
{
	int	i = 0;
	for (; i < 4; i++)
	{
		if (this->modes[i] == mode)
			break ;
	}
	switch (i)
	{
		case 0:
			std::cout << "[ DEBUG ]" << "\n";
			this->complain("DEBUG");
		case 1:
			std::cout << "[ INFO ]" << "\n";
			this->complain("INFO");
		case 2:
			std::cout << "[ WARNING ]" << "\n";
			this->complain("WARNING");
		case 3:
			std::cout << "[ ERROR ]" << "\n";
			this->complain("ERROR");
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]\n";
	}
}

#include "ShrubberyCreationForm.hpp"
#include <fstream>
#include <iostream>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ShrubberyCreationForm::ShrubberyCreationForm( std::string target ):
Form("Shrubbery Form", 145, 137, target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm( const ShrubberyCreationForm & src )
{
	(void)src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ShrubberyCreationForm &				ShrubberyCreationForm::operator=( ShrubberyCreationForm const & rhs )
{

	(void)rhs;
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void				ShrubberyCreationForm::executeAction( void ) const
{
	std::string	target = getTarget();
	std::ofstream file(target.append("_shrubbery").c_str());
	file << "    \\|/                \\|/\n"
			"   --0--              --0--\n"
			"    /|\\                /|\\\n"
			"   //|\\\\              //|\\\\\n"
			"  ///|\\\\\\            ///|\\\\\\\n"
			" ////|\\\\\\\\          ////|\\\\\\\\\n"
			"/////|\\\\\\\\\\        /////|\\\\\\\\\\\n"
			"    |||                |||\n"
			"____|||____        ____|||____\n";
	file.close();
}

/* ************************************************************************** */
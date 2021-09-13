#include <fstream>
#include <iostream>

void	replace_strings(std::string& buffer, std::string string1, std::string string2);

int main(int argc, char const *argv[])
{
	if (argc != 4)
		return (1);
	std::string	filename_input = argv[1];
	std::string	buffer;
	std::fstream fstream;
	fstream.open(filename_input, std::fstream::in);
	// Stores the whole file into buffer
	buffer.assign(	(std::istreambuf_iterator<char>(fstream)), 
					(std::istreambuf_iterator<char>()));
	fstream.close();
	// Replaces string1 by string2 in buffer
	replace_strings(buffer, argv[2], argv[3]);
	// Writes buffer with replaced strings to outfile
	fstream.open(filename_input + ".replace", std::fstream::out | std::fstream::trunc);
	fstream << buffer;
	fstream.close();
	return (0);
}

/*
**	Searches the position for every occurence of string1 in the file text
**	Then erases the occurrence with string.erase() givin the position and the number
**	of characters to erase as arguments, and insert string2 in the same position 
*/
void	replace_strings(std::string& buffer, std::string string1, std::string string2)
{
	size_t	match_position = 0;
	do
	{
		match_position = buffer.find(string1, match_position);
		if (match_position != buffer.npos)
		{
			buffer.erase(match_position, string1.length());
			buffer.insert(match_position, string2);
		}
	} while (match_position != buffer.npos);
}

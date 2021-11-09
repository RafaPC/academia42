#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <exception>

template <typename T>
typename T::const_iterator	easyfind(T &haystack, int needle)
{
	typename T::const_iterator	it = find(haystack.begin(), haystack.end(), needle);

	if (it == haystack.end())
		throw std::runtime_error("Element not found in the container");
	else
		return (it);
}

#endif
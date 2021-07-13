#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


int main(int argc, char **argv)
{
	int repeated_number;
	int length = 10;
	if (argc == 2)
		length = atoi(argv[1]);
	
	int array[length];

	//Gets time in milliseconds
	struct timeval  tv;
	gettimeofday(&tv, NULL);
	double time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
	srand(time_in_mill);
	
	for (int i = 0; i < length;)
	{
		int number = rand() % 1000 + 1;
		array[i] = number;
		repeated_number = 0;
		for (int j = 0; j < i; j++)
		{
			if (array[j] == number)
			{
				repeated_number = 1;
				break ;
			}
		}
		if (!repeated_number)
			i++;
	}
	for (int i = 0; i < length; i++)
		printf("%d ", array[i]);
	return 0;
}

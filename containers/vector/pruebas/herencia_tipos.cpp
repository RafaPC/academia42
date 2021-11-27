template <typename T>
class Padre 
{
	public: 
		typedef T cosa;
};

template <typename T>
class Hijo: Padre<T>
{
	static typename Padre<T>::cosa numerito = 0;
};

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

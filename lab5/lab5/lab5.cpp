#include "CTime.h"
#include <iostream>

int main()
{
	CTime t1(14, 30, 25);
	CTime t2(3, 18, 44);

	std::cout << "t1 = " << t1 << std::endl;
	std::cout << "t2 = " << t2 << std::endl;
	std::cout << "t1 + t2 = " << (t1 + t2) << std::endl;
	std::cout << "t1 * 3 = " << (t1 * 3) << std::endl;
	std::cout << "t1 / 3 = " << (t1 / 3) << std::endl;

	CTime midnight(23, 59, 59);
	++midnight;
	std::cout << "23:59:59++ = " << midnight << std::endl;

	return 0;
}

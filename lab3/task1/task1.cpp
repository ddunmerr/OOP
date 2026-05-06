#include "stdafx.h"
#include "RemoteControl.h"
#include "TVSet.h"

int main()
{
	CTVSet tv;
	CRemoteControl remoteControl(tv, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			std::cout << UNKNOWN_COMMAND << std::endl;
		}
	}
	return 0;
}

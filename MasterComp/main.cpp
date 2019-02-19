#include "header.h"

int main(int argc, char** argv)
{
	try
	{
		menu();
	}
	catch (quitting& stop)
	{
		return 1;
	}

	return 0;
}

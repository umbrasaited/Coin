#include "pch.h"


int main()
{
	Blockchain FBlock = Blockchain();
	vector <User> users;
	vector <Transaction> trans;
	vector <Transaction> chosen;
	reading(users);
	size_t MaxNonce = 100;
	uint32_t index = 2;
	bool found = false;


	making(users, trans);

	while (trans.size() > 0)
	{
		for (int i = 0; i < 5; i++)
		{
			Creating_Block(trans, users, FBlock, index, found, MaxNonce, i);
			if (found)
			{
				index++;
				break;
			}
			else if (!found)
			{
				cout << "Mining of block " << i + 1 << " was unsuccsesfull" << endl;
				MaxNonce += 100;
			}
		}
		found = false;
	}

	//return 0;
}

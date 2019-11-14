#include "pch.h"
#include "Block.h"
#include "Blockchain.h"
#include "transaction.h"
#include "user.h"


int main()
{
	Blockchain FBlock = Blockchain();
	vector <User> users;
	vector <Transaction> trans;
	reading(users);

	int start = 0, end = 100;
	while (end <= 10000)
	{
		making(users, trans);
		FBlock.AddBlock(Block(1, "Block 1 Data"), trans);
		start += 100;
		end += 100;
		trans.clear();
	}

	return 0;
}

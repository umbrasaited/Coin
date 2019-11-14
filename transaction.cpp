#include "pch.h"
#include "transaction.h"


void Trans(User x, User y, int amount, vector<Transaction>& AllTrans)
{
	int size = AllTrans.size();
	if (x.GetFAmount() >= amount)
	{
		x.SetFAmount(x.GetFAmount() - amount);
		y.SetFAmount(y.GetFAmount() + amount);
		AllTrans.push_back(Transaction());
		AllTrans[size].SetTransaction(amount, x.GetName(), y.GetName());
	}
}

Transaction::Transaction()
{
	from_ = "";
	to_ = "";
	amount_ = 0;
}

void Transaction::SetTransaction(int amount, string from, string to)
{
	from_ = from;
	to_ = to;
	amount_ = amount;
}
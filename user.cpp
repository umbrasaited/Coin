#include "pch.h"


User::User()
{
	name_ = "";
	f_amount_ = 0;
	public_key = "";
}

void User::input(istringstream& input)
{
	input >> name_;
	input >> f_amount_;
	stringstream ss;
	ss << name_ << f_amount_;
	//public_key = hash(ss.str());
	public_key = sha256(ss.str());
}

void reading(vector <User> &Users)
{
	ifstream iff;
	iff.open("list.txt");
	int temp = 0;
	string line;
	while (getline(iff, line))
	{
		istringstream read_l(line);
		Users.push_back(User());
		Users[temp].input(read_l);
		temp++;
	}
	iff.close();
}

void making(vector <User>& users, vector <Transaction> trans)
{
	random_device r;
	default_random_engine el(r());
	uniform_int_distribution<int> uniform_dist(1, 1000);
	uniform_int_distribution<int> uni(1, 100000);

	int amount = 0, x, y;

	while (trans.size() != 10000)
	{
		amount = uni(el);
		x = uniform_dist(el) - 1;
		do
		{
			y = uniform_dist(el) - 1;

		} while (x == y);

		Trans(users[x], users[y], amount, trans);
	}
}

bool validation(vector <User>& users, Transaction chosen)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].GetKey() == chosen.GetFrom() && users[i].GetFAmount() < chosen.GetAmount())
			return true;
	}
	return false;
}

void choosing(vector <Transaction>& trans, vector <Transaction>& chosen, vector <User>& users)
{
	random_device r;
	default_random_engine el(r());
	uniform_int_distribution<int> uniform_dist(0, trans.size() - 1);

	int x;

	bool Repeat_error = false, Val_error = false;

	vector <Transaction> temp;

	while (!((chosen.size() == 100) || (chosen.size() == trans.size())))
	{
		x = uniform_dist(el);

		Val_error = validation(users, trans[x]);

		if (Val_error)
		{
			trans.erase(trans.begin() + x);
			Val_error = false;
		}
		else
		{
			for (int i = 0; i < temp.size(); i++)
			{
				if (temp[i].GetID() == trans[x].GetID())
				{
					Repeat_error = true;
					break;
				}
			}
			if (!Repeat_error)
			{
				chosen.push_back(trans[x]);
				temp.push_back(trans[x]);
			}
			else
				Repeat_error = false;
		}
	}
	cout << chosen.size() << "  " << trans.size() << endl;
}

void Creating_Block(vector<Transaction>& trans, vector<User>& users, Blockchain& FBlock, uint32_t& index, bool& found, size_t& MaxNonce, int i)
{
fail:
	vector<Transaction> A;

	choosing(trans, A, users);

	bool error = false;

	int k = 0;

	string test;

	for (int i = 0; i < A.size(); i++)
	{
		stringstream ss;
		ss << A[i].GetFrom() << A[i].GetTo() << A[i].GetAmount();
		test = hash(ss.str());
		if (A[i].GetID() == test)
			k++;
	}

	if (k < A.size())
	{
		error = true;
	}
	if (error)
	{
		cout << "Transaction is unsuccesfull" << endl;
		goto fail;
	}

	Block B(index, A);
	while (B.GetNonce() != MaxNonce)
	{
		B.MineBlock(FBlock.GetDiff());
		//char cstr[FBlock.GetDiff() + 1];
		char cstr[4];
		for (uint32_t i = 0; i < FBlock.GetDiff(); i++)
		{
			cstr[i] = '0';
		}
		cstr[FBlock.GetDiff()] = '\0';

		string str(cstr);

		if (B.GetHash().substr(0, FBlock.GetDiff()) == str)
		{
			FBlock.AddBlock(B);

			found = true;


			for (int i = 0; i < 100; i++)
			{
				for (int w = 0; w < trans.size(); w++)
				{
					if (A[i].GetID() == trans[w].GetID())
					{
						trans.erase(trans.begin() + w);
						w--;
						break;
					}
				}
			}
			cout << "Block mined from " << i + 1 << " " << B.GetHash() << endl;
			break;
		}
	}
}

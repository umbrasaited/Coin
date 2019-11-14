#include "pch.h"
#include "user.h"
#include "transaction.h"
#include "user.h"


User::User()
{
	name_ = "";
	//surname_ = "";
	f_amount_ = 0;
	public_key = "";
}

void User::input(std::istringstream& input)
{
	input >> name_;
	//input >> surname_;
	input >> f_amount_;
	stringstream ss;
	ss << name_ << f_amount_;
	//public_key = sha256(ss.str());
	public_key = hash(ss.str());
}

void reading(vector <User> &Users)
{
	std::ifstream iff;
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
	std::random_device r;
	std::default_random_engine el(r());
	std::uniform_int_distribution<int> uniform_dist(1, 1000);

	int amount = 0, x, y;

	while (trans.size() != 100)
	{
		amount = uniform_dist(el);
		x = uniform_dist(el) - 1;
		do
		{
			y = uniform_dist(el) - 1;

		} while (x == y);

		if (users[x].GetFAmount() >= amount)
			Trans(users[x], users[y], amount, trans);
	}
}
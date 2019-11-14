#ifndef PCH_H
#define PCH_H

#include <cstdint>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <vector>

using std::endl;
using std::cout;
using std::hex;
using std::istringstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;

const int length = 8;
string hash(string str);
string write_hash(string str);

class Transaction
{
public:
	Transaction();
	void SetTransaction(int amount, string from, string to);
	int GetAmount() const { return amount_; }
	string GetFrom() const { return from_; }
	string GetTo() const { return to_; }

private:
	string from_;
	string to_;
	int amount_;
};


class Block
{
public:
	string sPrevHash;
	Block(uint32_t nIndexIn, const string &sDataIn);
	string GetHash();
	void MineBlock(uint32_t Difficulty, vector<Transaction>& temp);
	void AddInfo(int start, int end, vector <Transaction> Trans)
	{
		for (int i = start; i < end; i++)
		{
			Info_.push_back(Trans[i]);
		}
	}

private:
	uint32_t _nIndex;
	int64_t _nNonce;
	string _sData;
	string _sHash;
	time_t _tTime;
	vector <Transaction> Info_;
	string _CalculateHash() const;
};

class Blockchain
{
public:
	Blockchain();
	void AddBlock(Block bNew, vector<Transaction>& temp);

private:
	uint32_t _nDifficulty;
	vector<Block> _vChain;
	Block _GetLastBlock() const;
};


class User
{
public:
	User();
	void input(istringstream& input);
	string GetName() const { return name_; }
	string GetKey() const { return public_key; }
	int GetFAmount() const { return f_amount_; }
	void SetFAmount(int temp) { f_amount_ = temp; }

private:
	string name_;
	//string surname_;
	string public_key;
	int f_amount_;

};

void making(vector <User>& vartotojai, vector <Transaction> trans);
void reading(vector <User> &Users);
void Trans(User x, User y, int amount, vector <Transaction>& AllTrans);
#endif 

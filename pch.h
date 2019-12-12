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
using std::default_random_engine;
using std::hex;
using std::ifstream;
using std::istringstream;
using std::ofstream;
using std::random_device;
using std::size_t;
using std::string;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

const int length = 21;
string hash(string str);

class Transaction
{
public:
	Transaction();
	void SetTransaction(int amount, string from, string to);
	int GetAmount() const { return amount_; }
	string GetFrom() const { return from_; }
	string GetTo() const { return to_; }
	string GetID() const { return ID_; }

private:
	string ID_;
	string from_;
	string to_;
	int amount_;
};


class Block
{
public:
	string sPrevHash;
	Block(uint32_t nIndexIn, vector<Transaction> &sDataIn);
	string GetHash();
	int64_t GetNonce() const { return _nNonce; }
	void MineBlock(uint32_t Difficulty);

private:
	uint32_t _nIndex;
	int64_t _nNonce;
	string _sHash;
	time_t _tTime;
	vector <Transaction> _Info;
	string _CalculateHash() const;
	string _mMerkle;
	void Merkle();
};

class Blockchain
{
public:
	Blockchain();
	void AddBlock(Block bNew);
	uint32_t GetDiff() const { return _nDifficulty; }

private:
	uint32_t _nDifficulty;
	vector<Block> _vChain;
	Block _GetLastBlock() const;
	Block _GetAnyBlock(int n) const;
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
	string public_key;
	int f_amount_;

};

void making(vector <User>& vartotojai, vector <Transaction> trans);
void reading(vector <User> &Users);
void Trans(User x, User y, int amount, vector <Transaction>& AllTrans);
void Creating_Block(vector<Transaction>& trans, vector<User>& users, Blockchain& FBlock, uint32_t& index, bool& found, size_t& MaxNonce, int i);
string sha256(string input);
#endif 

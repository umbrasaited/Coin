#include "Block.h"
#include "pch.h"
#include "Blockchain.h"


Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn) 
{
	_nNonce = -1;
	_tTime = time(nullptr);
	Info_.reserve(100);
}

string Block::GetHash() { return _sHash; }

void Block::MineBlock(uint32_t nDifficulty, vector<Transaction>& temp)
{
	char cstr[2 + 1]; //nDifficulty
	for (uint32_t i = 0; i < nDifficulty; ++i) 
	{
		cstr[i] = '0';
	}
	cstr[nDifficulty] = '\0';

	string str(cstr);

	do {
		_nNonce++;
		_sHash = _CalculateHash();
	} while (_sHash.substr(0, nDifficulty) != str);
	Info_ = temp;
	cout << "Block mined: " << _sHash << endl;
}


inline string Block::_CalculateHash() const 
{
	stringstream ss;
	ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;

	return hash(ss.str());
	//return sha256(ss.str());
}

string hash(string str)
{
	unsigned int hash = 0;
	stringstream stream;

	for (int i = 0; i < str.length(); i++)
	{
		hash = (str[i]) + (hash << 5) + (hash << 15) - hash;
	}

	stream << hex << hash;
	string output(stream.str()), out;
	int x = 0;
	for (int i = 0; i < length; i++)
	{
		if (x <output.length())
		{
			out = output[x];
			x++;
		}
		else
		{
			x = 0;
			out = output[x];
		}
	}
	return out;
}

/*string write_hash(string str)
{
	int x = 0;
	string output;
	for (int i = 0; i < length; i++)
	{
		if (x < hash(str).length())
		{
			output = hash(str)[x];
			x++;
		}
		else
		{
			x = 0;
			output = hash(str)[x];
		}
	}
	return output;
}*/

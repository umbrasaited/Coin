#include "pch.h"


Block::Block(uint32_t nIndexIn, vector<Transaction> &sDataIn) : _nIndex(nIndexIn) 
{
	for (int i = 0; i < sDataIn.size(); i++)
	{
		_Info.push_back(sDataIn[i]);
	}
	_nNonce = -1;
	_tTime = time(nullptr);
	Merkle();
}

string Block::GetHash() { return _sHash; }

void Block::MineBlock(uint32_t nDifficulty)
{
	_nNonce++;
	_sHash = _CalculateHash();
}


inline string Block::_CalculateHash() const 
{
	stringstream ss;
	ss << _nIndex << _tTime;
	
	for (int i = 0; i < _Info.size(); i++)
	{
		ss << _Info[i].GetFrom() << _Info[i].GetTo() << _Info[i].GetAmount();
	}

	ss << _nNonce << sPrevHash;
	//return hash(ss.str());
	return sha256(ss.str());
}

string hash(string str)
{
	unsigned int hash = 0;
	stringstream stream;

	unsigned int pt1 = 0x811C9DC5;
	unsigned int pt2 = 1315423911;
	unsigned int pt3 = 5381;

	for (size_t i = 0; i < str.length(); i++)
	{
		pt1 ^= ((i & 1) == 0) ? ((pt1 << 7) ^ str[i] * (pt1 >> 3)) : (~((pt1 << 11) + (str[i] ^ (pt1 >> 5)) * 63689));
		pt2 ^= ((pt1 << 5) + str[i] + (pt1 >> 2));
		pt3 = ((pt2 << 5) + pt2) + str[i];

	}

	stream << hex << pt1 << hex << pt2 << hex << pt3;
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
	return output;
}

void Block::Merkle()
{
	vector<string> merkle;

	for (int i = 0; i < _Info.size(); i++)
	{
		merkle.push_back(_Info[i].GetID());
	}

	if (merkle.size() == 0)
	{
		_mMerkle = "0000000000000000000000000000000000000000000000000000000000000000";
		return;
	}

	if (merkle.size() == 1)
	{
		_mMerkle = merkle[0];
		return;
	}

	while (merkle.size() > 1)
	{
		if (merkle.size() % 2 != 0)
			merkle.push_back(merkle.back());

		vector<string> new_merkle;

		for (auto it = merkle.begin(); it != merkle.end(); it += 2)
		{
			string concat = (*it) + (*(it + 1));
			string hash = sha256(concat);
			new_merkle.push_back(hash);
		}

		merkle = new_merkle;
	}
	_mMerkle = merkle[0];
	return;
}

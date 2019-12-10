#include "pch.h"

Blockchain::Blockchain()
{
	vector<Transaction> Genesis;

	for (int i = 0; i < 100; i++)
	{
		Genesis.push_back(Transaction());
		Genesis[i].SetTransaction(1, "Genesis", "Genesis");
	}
	_vChain.emplace_back(Block(1, Genesis));
	_nDifficulty = 3;
}

void Blockchain::AddBlock(Block bNew)
{
	bNew.sPrevHash = _GetLastBlock().GetHash();
	_vChain.push_back(bNew);
}

Block Blockchain::_GetLastBlock() const
{
	return _vChain.back();
}

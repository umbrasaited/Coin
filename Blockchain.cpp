#include "pch.h"
#include "Block.h"
#include "Blockchain.h"
#include "transaction.h"

Blockchain::Blockchain()
{
	_vChain.emplace_back(Block(0, "Genesis Block"));
	_nDifficulty = 2;
}

void Blockchain::AddBlock(Block bNew, vector<Transaction>& temp)
{
	bNew.sPrevHash = _GetLastBlock().GetHash();
	bNew.MineBlock(_nDifficulty, temp);
	_vChain.push_back(bNew);
}

Block Blockchain::_GetLastBlock() const
{
	return _vChain.back();
}
#pragma once
#include <fstream>
#include "Block.h"
#include "DestBlock.h"
#include "DieBlock.h"
#include "PotalBlock.h"
#include "WallBlock.h"
#include "MoveAbleBlock.h"
class MapCreator
{
public:
	MapCreator();
	~MapCreator();
	void Release();

	void ReadMap(std::string filePath);
	void CreateMap();
	void CreateBlock(int blockNum, Vector2 position);
	void ReleaseMap();

private:
	std::ifstream	m_fileStream;

	std::list<CBlock*>		m_blockList;
};
#include "stdafx.h"
#include "MapCreator.h"


MapCreator::MapCreator()
{
}


MapCreator::~MapCreator()
{
}


void MapCreator::Release()
{
	ReleaseMap();
	m_fileStream.close();
	delete this;
}


void MapCreator::ReadMap(std::string filePath)
{
	m_fileStream.open(filePath);

	if (m_fileStream.is_open() == false)
	{
		CString errorLog = "Entered File Path : ";
		errorLog += filePath.c_str();

		MessageBox(g_hwnd,
			L"MapCreator::ReadMap\n파일을 읽을 수 없습니다.",
			errorLog,
			MB_ICONERROR);
	}


}


void MapCreator::CreateMap()
{
	int blockData, width;
	int nowLine = 0;

	m_fileStream >> width;

	// 그리는 순서때문에
	for (int i = 0;m_fileStream.eof() == false ; ++i)
	{
		m_fileStream >> blockData;
		if (!(blockData >= 10 && blockData <= 19))
			continue;
		CreateBlock(blockData, Vector2((i % width) * 100, -(i / width) * 100));
	}

	m_fileStream.seekg(0, std::ios::beg);
	m_fileStream >> blockData; // 첫번째 꺼는 width값이므로.
	nowLine = 0;
	for (int i = 0;m_fileStream.eof() == false; ++i)
	{
		m_fileStream >> blockData;
		if ((blockData >= 10 && blockData <= 19))
			continue;
		CreateBlock(blockData, Vector2((i % width) * 100, -(i / width) * 100));
	}
}


void MapCreator::CreateBlock(int blockNum, Vector2 position)
{
	if (blockNum == 0)
	{
		return;
	}
	else if (blockNum >= 10 && blockNum <= 19)
	{
		m_blockList.push_back(new WallBlock);
		m_blockList.back()->Initialize();
	}
	else if (blockNum >= 20 && blockNum <= 29)
	{
		m_blockList.push_back(new DestBlock);
		m_blockList.back()->Initialize();
	}
	else if (blockNum >= 30 && blockNum <= 39)
	{
		PotalBlock* temp = new PotalBlock();
		temp->SetPotalId(blockNum % 30);
		m_blockList.push_back(temp);
		m_blockList.back()->Initialize();
	}
	else if (blockNum >= 40 && blockNum <= 49)
	{
		m_blockList.push_back(new DieBlock);
		m_blockList.back()->Initialize();
	}
	else if (blockNum >= 50 && blockNum < 59)
	{
		m_blockList.push_back(new MyCharacter);
		m_blockList.back()->Initialize();
	}
	else if (blockNum >= 60 && blockNum < 69)
	{
		m_blockList.push_back(new MoveAbleBlock);
		m_blockList.back()->Initialize();
	}

	m_blockList.back()->GetComponentHub()->m_pTransform->SetPosition(position);

}


void MapCreator::ReleaseMap()
{

	for (std::list<CBlock*>::iterator it = m_blockList.begin(); it != m_blockList.end();)
	{
		CBlock* temp = *it;
		it = m_blockList.erase(it);
		temp->Release();
	}

}
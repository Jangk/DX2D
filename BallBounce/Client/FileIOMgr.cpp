#include "stdafx.h"
#include "FileIOMgr.h"
#include "Block.h"

IMPLEMENT_SINGLETON(FileIOMgr)

FileIOMgr::FileIOMgr()
{
}

FileIOMgr::~FileIOMgr()
{
}

bool FileIOMgr::SaveEditor(const wstring& wstrFilePath, vector<Block*>& vecBlock)
{
	// WinAPI 파일 개방
	HANDLE hFile = CreateFile(
		wstrFilePath.c_str(), /* 파일 경로 */
		GENERIC_WRITE, /* 입출력 모드 */
		0,
		0,
		CREATE_ALWAYS, /* 파일 생성 방식 */
		FILE_ATTRIBUTE_NORMAL, /* 생성된 파일 특성 */
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return false;

	DWORD dwBytes = 0;

	SAVE_INFO save;
	for (size_t i = 0; i < vecBlock.size(); ++i)
	{
		save.tInfo = vecBlock[i]->GetInfo();
		save.eBlockType = vecBlock[i]->GetBlockType();
		// WinAPI 파일 출력
		WriteFile(
			hFile,	/* 개방된 파일의 핸들 */
			&save, /* 출력할 데이터의 메모리 주소 */
			sizeof(SAVE_INFO), /* 출력할 데이터의 크기 */
			&dwBytes, /* 얼마만큼 출력이 진행됐는지 바이트 수를 기록 */
			nullptr);
	}

	CloseHandle(hFile);

	return true;
}

bool FileIOMgr::LoadEditor(const wstring& wstrFilePath, vector<Block*>& vecBlock)
{
	// WinAPI 파일 개방
	HANDLE hFile = CreateFile(
		wstrFilePath.c_str(), /* 파일 경로 */
		GENERIC_READ, /* 입출력 모드 */
		0,
		0,
		OPEN_EXISTING, /* 파일 생성 방식 */
		FILE_ATTRIBUTE_NORMAL, /* 생성된 파일 특성 */
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return false;

	if (!vecBlock.empty())
	{
		for_each(vecBlock.begin(), vecBlock.end(), SafeDelete<Block*>);
		vecBlock.clear();
	}

	DWORD dwBytes = 0;
	SAVE_INFO save;
	Block* temp;

	while (true)
	{
		// WinAPI 파일 입력
		ReadFile(
			hFile,	/* 개방된 파일의 핸들 */
			&save, /* 입력 받을 데이터의 메모리 주소 */
			sizeof(SAVE_INFO), /* 입력 받을 데이터의 크기 */
			&dwBytes, /* 입력할 데이터가 얼마나 남았는지 바이트 수를 기록 */
			nullptr);

		if (0 == dwBytes)
			break;

		temp = Block::Create();
		temp->SetSaveInfo(save);
		//CObjectMgr::GetInstance()->AddObject(OBJECT_TERRAIN, temp);
		vecBlock.push_back(temp);
	}
	CloseHandle(hFile);
	return true;
}

bool FileIOMgr::LoadStage(const wstring& wstrFilePath, vector<Block*>& vecBlock)
{
	// WinAPI 파일 개방
	HANDLE hFile = CreateFile(
		wstrFilePath.c_str(), /* 파일 경로 */
		GENERIC_READ, /* 입출력 모드 */
		0,
		0,
		OPEN_EXISTING, /* 파일 생성 방식 */
		FILE_ATTRIBUTE_NORMAL, /* 생성된 파일 특성 */
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return false;

	if (!vecBlock.empty())
	{
		for_each(vecBlock.begin(), vecBlock.end(), SafeDelete<Block*>);
		vecBlock.clear();
	}

	DWORD dwBytes = 0;
	SAVE_INFO save;
	Block* temp;

	while (true)
	{
		// WinAPI 파일 입력
		ReadFile(
			hFile,	/* 개방된 파일의 핸들 */
			&save, /* 입력 받을 데이터의 메모리 주소 */
			sizeof(SAVE_INFO), /* 입력 받을 데이터의 크기 */
			&dwBytes, /* 입력할 데이터가 얼마나 남았는지 바이트 수를 기록 */
			nullptr);

		if (0 == dwBytes)
			break;

		temp = Block::Create();
		temp->SetSaveInfo(save);
		CObjectMgr::GetInstance()->AddObject(OBJECT_TERRAIN, temp);
		vecBlock.push_back(temp);
	}
	CloseHandle(hFile);
	return true;
}

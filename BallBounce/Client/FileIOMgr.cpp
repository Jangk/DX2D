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
	// WinAPI ���� ����
	HANDLE hFile = CreateFile(
		wstrFilePath.c_str(), /* ���� ��� */
		GENERIC_WRITE, /* ����� ��� */
		0,
		0,
		CREATE_ALWAYS, /* ���� ���� ��� */
		FILE_ATTRIBUTE_NORMAL, /* ������ ���� Ư�� */
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return false;

	DWORD dwBytes = 0;

	SAVE_INFO save;
	for (size_t i = 0; i < vecBlock.size(); ++i)
	{
		save.tInfo = vecBlock[i]->GetInfo();
		save.eBlockType = vecBlock[i]->GetBlockType();
		// WinAPI ���� ���
		WriteFile(
			hFile,	/* ����� ������ �ڵ� */
			&save, /* ����� �������� �޸� �ּ� */
			sizeof(SAVE_INFO), /* ����� �������� ũ�� */
			&dwBytes, /* �󸶸�ŭ ����� ����ƴ��� ����Ʈ ���� ��� */
			nullptr);
	}

	CloseHandle(hFile);

	return true;
}

bool FileIOMgr::LoadEditor(const wstring& wstrFilePath, vector<Block*>& vecBlock)
{
	// WinAPI ���� ����
	HANDLE hFile = CreateFile(
		wstrFilePath.c_str(), /* ���� ��� */
		GENERIC_READ, /* ����� ��� */
		0,
		0,
		OPEN_EXISTING, /* ���� ���� ��� */
		FILE_ATTRIBUTE_NORMAL, /* ������ ���� Ư�� */
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
		// WinAPI ���� �Է�
		ReadFile(
			hFile,	/* ����� ������ �ڵ� */
			&save, /* �Է� ���� �������� �޸� �ּ� */
			sizeof(SAVE_INFO), /* �Է� ���� �������� ũ�� */
			&dwBytes, /* �Է��� �����Ͱ� �󸶳� ���Ҵ��� ����Ʈ ���� ��� */
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
	// WinAPI ���� ����
	HANDLE hFile = CreateFile(
		wstrFilePath.c_str(), /* ���� ��� */
		GENERIC_READ, /* ����� ��� */
		0,
		0,
		OPEN_EXISTING, /* ���� ���� ��� */
		FILE_ATTRIBUTE_NORMAL, /* ������ ���� Ư�� */
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
		// WinAPI ���� �Է�
		ReadFile(
			hFile,	/* ����� ������ �ڵ� */
			&save, /* �Է� ���� �������� �޸� �ּ� */
			sizeof(SAVE_INFO), /* �Է� ���� �������� ũ�� */
			&dwBytes, /* �Է��� �����Ͱ� �󸶳� ���Ҵ��� ����Ʈ ���� ��� */
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

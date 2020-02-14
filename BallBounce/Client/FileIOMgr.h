#pragma once
class Block;
class FileIOMgr
{
	DECLARE_SINGLETON(FileIOMgr)
private:
	FileIOMgr();
	~FileIOMgr();

public:
	bool SaveEditor(const wstring& wstrFilePath, vector<Block*>& vecBlock);
	bool LoadEditor(const wstring& wstrFilePath, vector<Block*>& vecBlock);
	bool LoadStage(const wstring& wstrFilePath, vector<Block*>& vecBlock);
};


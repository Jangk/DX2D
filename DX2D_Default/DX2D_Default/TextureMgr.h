#pragma once
class Texture;
class TextureMgr
{
	DECLARE_SINGLETON(TextureMgr)
private:
	TextureMgr();
	~TextureMgr();


private:
	map<wstring, Texture*>	m_mapTexture;
};


#pragma once
#include <d3dx9.h>
#include <map>
class TextureManager
{
private:
	std::map<char*, LPDIRECT3DTEXTURE9> textureMap;
public:
	TextureManager();
	~TextureManager();
	LPDIRECT3DTEXTURE9 LoadTextureFromFile(char* path);

};


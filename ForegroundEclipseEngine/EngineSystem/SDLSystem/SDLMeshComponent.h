#pragma once
#include "../../pch.h"
#include "../../GameElements/Behaviour.h"
#include "../../Components/IMesh.h"
class SDLSystem;
class SDLMeshComponent : public Behaviour, public IMesh
{
public:
	// 이미지 파일 로드
	SDLMeshComponent(std::string fileName);
	// 단순 도형 로드
	SDLMeshComponent(int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool Fill = false);
	~SDLMeshComponent();

	virtual void DrawMesh() override;
	virtual void SetActive(bool isActive) override { enabled = isActive; }

private:
	void DrawSimpleRect();
	void DrawTexture();
	// 텍스쳐 로드
	bool load(std::string fileName);

	// 텍스쳐
	SDL_Texture* texture;
	// 도형
	SDL_Rect m_simpleRect;
	SDL_Color m_simpleColor;
	bool bFill;
	// 렌더러
	SDL_Renderer* renderRef;
};

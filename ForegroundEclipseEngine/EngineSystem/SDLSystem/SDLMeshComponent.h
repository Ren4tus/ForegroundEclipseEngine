#pragma once
#include "../../pch.h"
#include "../../GameElements/Behaviour.h"
#include "../../Components/IMesh.h"
class SDLSystem;
class SDLMeshComponent : public Behaviour, public IMesh
{
public:
	// �̹��� ���� �ε�
	SDLMeshComponent(std::string fileName);
	// �ܼ� ���� �ε�
	SDLMeshComponent(int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool Fill = false);
	~SDLMeshComponent();

	virtual void DrawMesh() override;
	virtual void SetActive(bool isActive) override { enabled = isActive; }

private:
	void DrawSimpleRect();
	void DrawTexture();
	// �ؽ��� �ε�
	bool load(std::string fileName);

	// �ؽ���
	SDL_Texture* texture;
	// ����
	SDL_Rect m_simpleRect;
	SDL_Color m_simpleColor;
	bool bFill;
	// ������
	SDL_Renderer* renderRef;
};

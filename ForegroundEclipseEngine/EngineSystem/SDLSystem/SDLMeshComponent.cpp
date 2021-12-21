#include "SDLMeshComponent.h"

#include <iostream>
#include "../GameManager.h"
#include "../SystemBase/SDLSystem.h"
#include "../GameElements/GameObject.h"
SDLMeshComponent::SDLMeshComponent(std::string fileName)
{
	renderRef = dynamic_cast<SDLSystem*>(GM::Instance()->GetCurrentEngine())->GetRenderer();
	if (!load(fileName)) {
		std::cout << "File load fail" << std::endl;
	}
}

SDLMeshComponent::SDLMeshComponent(int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool Fill) : texture(NULL)
{
	renderRef = dynamic_cast<SDLSystem*>(GM::Instance()->GetCurrentEngine())->GetRenderer();
	m_simpleRect.x = 0;
	m_simpleRect.y = 0;
	m_simpleRect.w = width;
	m_simpleRect.h = height;
	m_simpleColor.r = r;
	m_simpleColor.g = g;
	m_simpleColor.b = b;
	m_simpleColor.a = a;
	bFill = Fill;
}

SDLMeshComponent::~SDLMeshComponent()
{
}

void SDLMeshComponent::DrawMesh()
{
	if (texture == NULL) {
		DrawSimpleRect();
	}
	else {
		DrawTexture();
	}
}

void SDLMeshComponent::DrawSimpleRect()
{
	SDL_Rect drawRect{
		owner->m_worldPosition.x,
		owner->m_worldPosition.y,
		m_simpleRect.w,
		m_simpleRect.h
	};
	SDL_SetRenderDrawColor(renderRef, m_simpleColor.r, m_simpleColor.g, m_simpleColor.b, m_simpleColor.a);
	SDL_SetRenderDrawBlendMode(renderRef, SDL_BLENDMODE_BLEND);
	if (bFill)
		SDL_RenderFillRect(renderRef, &drawRect);
	else
		SDL_RenderDrawRect(renderRef, &drawRect);
	SDL_SetRenderDrawBlendMode(renderRef, SDL_BLENDMODE_NONE);
}

void SDLMeshComponent::DrawTexture()
{
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);

	SDL_Rect destRect;
	destRect.x = owner->m_worldPosition.x;
	destRect.y = owner->m_worldPosition.y;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	SDL_RenderCopyEx(renderRef, texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

bool SDLMeshComponent::load(std::string fileName)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0) {
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderRef, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0) {
		texture = pTexture;
		return true;
	}
	return true;
}
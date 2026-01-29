#pragma once

#include "scene.h"

class Result : public Scene
{
private:
	class Audio* m_BGM;

	XMFLOAT2 m_enterTextSizeXY = { 0.0f, 0.0f };

public:
	void Init() override;//‰Šú‰»
	void Uninit() override;
	void Update() override;//XV
	
	XMFLOAT2 GetEnterTextSizeXY() { return m_enterTextSizeXY; }
	void SetEnterTextSizeXY(XMFLOAT2 entertextsizexy) { m_enterTextSizeXY = entertextsizexy; }

};

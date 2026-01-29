#pragma once

#include "gameObject.h"
#include "polygon.h"

class EnterText : public Polygon2D
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	ID3D11ShaderResourceView* m_Texture;

	XMFLOAT2 m_enterTextSizeXY = { 400.0f, 70.0f };

	bool m_scaleSwitch = true;
	unsigned int m_switchCount = 0;

public:
	void Init() {};//âºëzä÷êî
	void Init(float x, float y, float Width, float Height, bool scaleswitch);
	void Uninit();
	void Update();
	void Draw();

	XMFLOAT2 GetEnterTextSizeXY() { return m_enterTextSizeXY; }
	void SetEnterTextSizeXY(XMFLOAT2 entertextsizexy) { m_enterTextSizeXY = entertextsizexy; }

	bool GetScaleSwitch() { return m_scaleSwitch; }
	void SetScaleSwitch(bool scaleswitch) { m_scaleSwitch = scaleswitch; }

	unsigned int GetSwitchCount() { return m_switchCount; }
	void SetSwitchCount(unsigned int switchcount) { m_switchCount = switchcount; }
	void AddSwitchCount(unsigned int add) { m_switchCount += add; }
};
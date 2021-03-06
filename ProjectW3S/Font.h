#pragma once

#include <d3dx9.h>
#include <string>
#include <memory>
#include "Point.h"

class Font {
public:
	Font(LPDIRECT3DDEVICE9 device, int size, const std::string& fontName, bool bold) {
		HRESULT hr = D3DXCreateFont(device,
			size, 0, bold ? FW_BOLD : FW_NORMAL, 0, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
			fontName.c_str(),
			&m_font);
		if (FAILED(hr))
			throw std::runtime_error("Error createfont");
	}

	~Font() {
		if (m_font)
			m_font->Release();
	}

	void drawStr(const std::string& str, const Point& pos, D3DCOLOR color = 0xFFFFFFFF) {
		RECT rect = { pos.x, pos.y, 0, 0 };
		m_font->DrawText(NULL, str.c_str(), -1, &rect, DT_NOCLIP, color);
	}

	static void addFont(const std::string& filePath) {
		if (AddFontResourceEx(filePath.c_str(), FR_PRIVATE, NULL) == 0) {
			throw std::runtime_error("Failed load " + filePath);
		}
	}
private:
	ID3DXFont* m_font;
};

using FontPtr = std::shared_ptr<Font>;

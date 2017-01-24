#pragma once

template <typename Type> inline const Type& Clamp(const Type& x, const Type& min, const Type& max) {
	return (x < min) ? min : ((max < x) ? max : x);
}

template <typename Type> inline Type Wrap(const Type& x, const Type& min, const Type& max) {
	const Type n = (x - min) % (max - min);
	return (n >= 0) ? (n + min) : (n + max);
}

template <typename Type> inline bool InRange(const Type& x, const Type& min, const Type& max) {
	return (min <= x) && (x <= max);
}

template <typename Container, typename Pred> inline void Erase_if(Container& c, Pred pred) {
	c.erase(std::remove_if(c.begin(), c.end(), pred), c.end());
}

template <typename Type> inline void OutputDebugValue(const Type& value) {
#ifdef _DEBUG
	OutputDebugString(std::to_string(value).c_str());
	OutputDebugString("\n");
#endif
}

inline bool IsCollied(const D3DXVECTOR3& pos1, const D3DXVECTOR3& pos2, float r1, float r2) {
	D3DXVECTOR3 tmp = pos2 - pos1;
	return tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z < (r1 + r2)*(r1 + r2);
}

inline void drawRectangle2D(LPDIRECT3DDEVICE9 d3dDevice, const D3DXVECTOR2& topLeft, const D3DXVECTOR2& bottomRight, const D3DXCOLOR& color = 0xFFFFFFFF) {
	struct PlateVtx {
		D3DXVECTOR3 pos;
		float rhw;
		DWORD color;
	};
	std::vector<PlateVtx> vtx {
		{ { topLeft.x, topLeft.y, 0 }, 1, color },
		{ { bottomRight.x, topLeft.y, 0 }, 1, color },
		{ { topLeft.x, bottomRight.y, 0 }, 1, color },
		{ { bottomRight.x, bottomRight.y, 0 }, 1, color },
	};
	d3dDevice->SetTexture(0, NULL);
	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx.data(), sizeof(PlateVtx));
}

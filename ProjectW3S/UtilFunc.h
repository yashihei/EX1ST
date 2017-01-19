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

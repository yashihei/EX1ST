#pragma once

#include <d3dx9.h>
#include <cmath>

//unit vector
static const D3DXVECTOR3 UP_VEC3(0, 1, 0);
static const D3DXVECTOR3 DOWN_VEC3(0, -1, 0);
static const D3DXVECTOR3 LEFT_VEC3(-1, 0, 0);
static const D3DXVECTOR3 RIGHT_VEC3(1, 0, 0);
static const D3DXVECTOR3 FORWARD_VEC3(0, 0, 1);
static const D3DXVECTOR3 BACK_VEC3(0, 0, -1);
static const D3DXVECTOR3 ONE_VEC3(1, 1, 1);
static const D3DXVECTOR3 ZERO_VEC3(0, 0, 0);

static const float Pi = D3DX_PI;
static const float TwoPi = Pi*2;

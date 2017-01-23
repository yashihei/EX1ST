#pragma once

#pragma warning(disable : 4018) //unsigned signed��r
#pragma warning(disable : 4244) //float int�ϊ�

static const int ScreenWidth = 800;
static const int ScreenHeight = 600;

//--------------------------------------------------------------------------------
// STL����
//--------------------------------------------------------------------------------
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <deque>
#include <memory>
#include <functional>
#include <stdexcept>

//--------------------------------------------------------------------------------
// dx9����
//--------------------------------------------------------------------------------
#include "Graphics.h"
#include "Texture.h"
#include "Font.h"
#include "Camera.h"
#include "Light.h"
#include "XModel.h"
#include "Sprite.h"
#include "Sprite2D.h"
#include "Render.h"

//--------------------------------------------------------------------------------
// �֗��w�b�_
//--------------------------------------------------------------------------------
#include "Actor.h"
#include "Color.h"
#include "Easing.h"
#include "Point.h"
#include "Random.h"
#include "Scene.h"
#include "UtilFunc.h"
#include "Vector2.h"
#include "FPS.h"
#include "Time.h"
#include "Math.h"

#include "FPS.h"
#include "Input.h"
#include "Sound.h"

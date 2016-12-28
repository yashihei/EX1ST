#pragma once

#include "Common.h"
#include "Shape.h"

class Play : public Scene {
public:
	Play(LPDIRECT3DDEVICE9 d3dDevice) :
		m_d3dDevice(d3dDevice)
	{
		m_camera = std::make_shared<Camera>(d3dDevice, D3DXVECTOR3(0, 0, -5), D3DXVECTOR3(0, 0, 0));
		m_light = std::make_shared<Light>(d3dDevice, D3DXVECTOR3(0, -1, 1), D3DCOLORVALUE{1.0f, 1.0f, 1.0f});
		m_model = std::make_shared<Model>(d3dDevice, "dlang.x");
		D3DXCreateTeapot(d3dDevice, &m_mesh, NULL);
		m_shape = std::make_shared<Shape>(d3dDevice);
	}
	void update() override {
		m_count++;
	}
	void draw() override {
		D3DMATERIAL9 mat = { {1, 1, 0, 1} };
		D3DXMATRIX world;
		D3DXMatrixIdentity(&world);
		m_d3dDevice->SetTransform(D3DTS_WORLD, &world);
		m_d3dDevice->SetMaterial(&mat);
		//m_mesh->DrawSubset(0);

		m_shape->draw(world);
	}
private:
	int m_count = 0;

	LPDIRECT3DDEVICE9 m_d3dDevice;
	CameraPtr m_camera;
	LightPtr m_light;
	LPD3DXMESH m_mesh;
	ModelPtr m_model;
	ShapePtr m_shape;
};

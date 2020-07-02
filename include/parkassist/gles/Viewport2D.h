#pragma once
#include <vector>
#include "parkassist/gles/Def.h"
#include "parkassist/gles/Camera.h"
#include "parkassist/gles/Projection.h"

namespace nb {
	
class RenderObject;
class NB_API Viewport2D
{
public:
	void viewport(int x, int y, unsigned int width, unsigned height);

	//����һ����Ⱦ��
	void queue(std::shared_ptr<RenderObject> renderObject);

	std::vector<std::shared_ptr<RenderObject>> &renderers();

	//��Ⱦ������Ⱦ��
	void draw();

	Camera		camera;
	Projection	projection;

private:
	std::vector<std::shared_ptr<RenderObject>>	m_renderObjects;
};

}
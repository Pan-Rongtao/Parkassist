#pragma once
#include <vector>
#include "parkassist/gles/Def.h"
#include "glm/glm.hpp"

namespace nb {
	
class Brush;
class Renderer;
class Camera;
using BrushPtr = std::shared_ptr<Brush>;
using RendererPtr = std::shared_ptr<Renderer>;
using CameraPtr = std::shared_ptr<Camera>;

class NB_API DrawingContext
{
public:
	static DrawingContext* get();

	CameraPtr camera();
	void resize(int width, int height);

	//����һ�������
	void drawPolygon(const std::vector<glm::vec2> &side0, const std::vector<glm::vec2> &side1, BrushPtr brush, int controlPointsCount, int sampleCount, uint8_t drawMode);


	//�����Ⱦ��
	void clear();

	//��Ⱦ������Ⱦ��
	void renderAll();

private:
	DrawingContext();

	CameraPtr m_camera;
	std::vector<RendererPtr> m_renderers;
};



}
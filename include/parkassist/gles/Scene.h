#pragma once
#include "parkassist/gles/Polygon.h"
#include "parkassist/gles/DrawingContext.h"

namespace nb {

class NB_API Scene
{
public:
	Scene(int width, int height);
	~Scene() = default;

	//���һ�������
	void add(std::shared_ptr<Polygon> polygon);

	//���
	void clear();

	//ִ����Ⱦ����Ⱦ���ж���Σ�
	void doRender();

private:
	DrawingContext m_dc;
	std::vector<std::shared_ptr<Polygon>> m_polygons;
};

}
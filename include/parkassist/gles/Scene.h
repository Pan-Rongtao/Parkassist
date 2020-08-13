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

	//
	void enableBorder(bool enable);
	bool isBorderEnable() const;

private:
	void draw(const std::vector<std::shared_ptr<Polygon>> polygons);

	DrawingContext m_dc;
	std::vector<std::shared_ptr<Polygon>> m_polygons;
	std::vector<std::shared_ptr<Polygon>> m_polygonsBorder;
	bool m_enableBorder;
};

using ScenePtr = std::shared_ptr<Scene>;
}
#pragma once
#include "parkassist/gles/Mesh.h"

namespace nb {

class NB_API Rectangle : public Mesh
{
public:
	Rectangle();

	void set(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3);
};

class NB_API Polygon : public Mesh
{
public:
	//���ã�һ����ԣ�����������̫��Ҳ������̫�̫࣬���򲻹�˳����̫����Ӱ�챴�������ԣ�
	void set(const std::vector<glm::vec2> &side0, const std::vector<glm::vec2> &side1, int controlPointsCount = 10, int sampleCount = 50);

private:
	std::vector<glm::vec2> doBezier(const std::vector<glm::vec2> &inputs, int controlPointsCount, int sampleCount);

};

using RectanglePtr = std::shared_ptr<Rectangle>;
using PolygonPtr = std::shared_ptr<Polygon>;
}
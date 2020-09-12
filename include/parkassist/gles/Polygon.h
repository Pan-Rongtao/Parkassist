#pragma once
#include "parkassist/gles/Mesh.h"
#include "glm/glm.hpp"

namespace nb {

class NB_API Polygon : public Mesh
{
public:
	//���ã�һ����ԣ�����������̫��Ҳ������̫�̫࣬���򲻹�˳����̫����Ӱ�챴�������ԣ�
	void set(const std::vector<glm::vec2> &side0, const std::vector<glm::vec2> &side1, int controlPointsCount = 10, int sampleCount = 50);

private:
	std::vector<glm::vec2> doBezier(const std::vector<glm::vec2> &inputs, int controlPointsCount, int sampleCount);

};

using PolygonPtr = std::shared_ptr<Polygon>;
}
#pragma once
#include "parkassist/gles/Def.h"
#include "glm/glm.hpp"

namespace nb {

class Brush;
using BrushPtr = std::shared_ptr<Brush>;
class NB_API Polygon
{
public:
	//����һ������Σ�������Ķ���Ϊside0��side1��һ����ԣ�����������̫��Ҳ������̫�̫࣬���򲻹�˳����̫����Ӱ�챴�������ԣ�
	Polygon();
	Polygon(const std::vector<glm::vec2> &side0, const std::vector<glm::vec2> &side1);

	//���ö���
	void setSide0(const std::vector<glm::vec2> &side0);
	void setSide1(const std::vector<glm::vec2> &side1);

	//����������
	//controlPointsCount��ÿ�ο��Ƶ�����Ĭ��ֵΪ5
	//sampleCount��ÿ�α������ɼ�������Ĭ��ֵ20
	void setBezierParams(int controlPointsCount, int sampleCount);

	//���û�ˢ
	void setBrush(BrushPtr brush);

	//
	void setMode(uint8_t mode);

	void draw();

private:
	std::vector<glm::vec2> m_side0;
	std::vector<glm::vec2> m_side1;
	int m_controlPointsCount;
	int m_sampleCount;
	BrushPtr m_brush;
	uint8_t m_drawMode;
};

}
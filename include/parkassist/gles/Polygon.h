#pragma once
#include "Model.h"

namespace nb {

class NB_API Polygon : public Model
{
public:
	Polygon();

	//���õ㼯��
	//side0����0�ĵ㼯��
	//side1����1�ĵ㼯��
	//ControlPointsCount��ÿ�ο��Ƶ�ĸ�����0��ʾ�����ñ�������
	//sampleCount��ÿ�α������Ĳ���������0��ʾ�����ñ�������
	void setPoint(const std::vector<glm::vec2> &side0, const std::vector<glm::vec2> &side1, int controlPointsCount = 5, int sampleCount = 20);

private:
	std::vector<glm::vec2> doBezier(const std::vector<glm::vec2> &inputs, int controlPointsCount, int sampleCount);

};

}
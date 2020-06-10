#pragma once
#include <vector>
#include "newbrush/gles/Model.h"
#include "newbrush/media/Media.h"

namespace nb{

class NB_API Strips : public Model
{
public:
	//����һ���յĴ�״
	Strips();

	//
	void update(const std::vector<glm::vec2> &breaks, float thickness, const std::vector<float> &dashArray, float offset, PenLineJoinE lineJionStyle);

private:
	//�߶��� y = kx + b
	class LineSegment
	{
	public:
		LineSegment(const glm::vec2 &p0, const glm::vec2 &p1);
		
		//ˮƽ�ʹ�ֱ����ľ���ֵ������Ϊ����
		//�߶γ���
		float xDiff() const;
		float yDiff() const;
		float length() const;

		//ִ�����߼���
		void dashing(float offset, const std::vector<float> &array, float thickness, std::vector<glm::vec2> &points, const glm::vec4 &box, std::vector<glm::vec2> &texCoords, bool innerLine);

		glm::vec2	p0;
		glm::vec2	p1;
	};

};

}
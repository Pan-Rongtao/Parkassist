#include "parkassist/gles/Polygon.h"
#include "bezier.h"

using namespace nb;

void Polygon::setPoint(const std::vector<glm::vec2>& side0, const std::vector<glm::vec2>& side1)
{
	if (side0.size() != side1.size())
	{
		nbThrowException(std::logic_error, "side0.size is not same with side1.size");
	}

	//ִ�б�����
	auto bzPts0 = doBezier(side0);
	auto bzPts1 = doBezier(side1);
	if (side0.size() != side1.size())
	{
		nbThrowException(std::runtime_error, "do doBezier bzPts0.size != bzPts1.size");
	}

	std::vector<Vertex> vertexs(bzPts0.size() + bzPts1.size());
	for (size_t i = 0; i < vertexs.size() / 2; ++i)
	{
		vertexs[i * 2].position.x = bzPts0[i].x;
		vertexs[i * 2].position.y = bzPts0[i].y;
		vertexs[i * 2].position.z = 0;
		vertexs[i * 2 + 1].position.x = bzPts1[i].x;
		vertexs[i * 2 + 1].position.y = bzPts1[i].y;
		vertexs[i * 2 + 1].position.z = 0;
	}

	auto indicesCount = (vertexs.size() - 2) * 3;
	std::vector<uint16_t> indices(indicesCount);
	auto x = 0;
	for (size_t i = 0; i < indices.size() / 6; ++i)
	{
		indices[x++] = (unsigned short)(2 * i + 0);
		indices[x++] = (unsigned short)(2 * i + 1);
		indices[x++] = (unsigned short)(2 * i + 3);
		indices[x++] = (unsigned short)(2 * i + 0);
		indices[x++] = (unsigned short)(2 * i + 3);
		indices[x++] = (unsigned short)(2 * i + 2);
	}
	meshes.push_back(Mesh(vertexs, indices));
}

std::vector<glm::vec2> Polygon::doBezier(const std::vector<glm::vec2>& inputs)
{
	auto bezier2 = [](const std::vector<Bezier::Point> &bzPts)->std::vector<glm::vec2>
	{
		std::vector<glm::vec2> ret;
		Bezier::Bezier<2> bz(bzPts);
		for (float i = 0.0f; i <= 1.000001; i += 0.1f)
		{
			Bezier::Point p = bz.valueAt(i);
			ret.push_back({ p.x, p.y });
		}
		return ret;
	};

	auto bezier3 = [](const std::vector<Bezier::Point> &bzPts)->std::vector<glm::vec2>
	{
		std::vector<glm::vec2> ret;
		Bezier::Bezier<3> bz(bzPts);
		for (float i = 0.0f; i <= 1.000001; i += 0.1f)
		{
			Bezier::Point p = bz.valueAt(i);
			ret.push_back({ p.x, p.y });
		}
		return ret;
	};

	//���С��3���㣬����Ҫִ�б���������Ϊ���η�������������Ҫ�����㣩
	if (inputs.size() < 3)
	{
		return inputs;
	}

	std::vector<glm::vec2> ret;
	for (size_t i = 0; i + 2 <= inputs.size();)
	{
		std::vector<glm::vec2> segPts;
		//���ʣ���ĸ��㣬���������η���ʣ�������������ö��η���������������η���ֻʣ�������㣬��Ӧ����ǰһ���������ö��η����Ա�֤���һ���ܹ����ö��η���������
		//�����ʣ���ĸ��㣬��ʾ���������η����������ڲ������ж�
			//ʹ���ĸ������Ȼʣ�������������ö��η�������ʽ�ж�Ϊ���������η�
		if (i + 4 == inputs.size() || i + 4 + 2 <= inputs.size())
		{
			std::vector<Bezier::Point> bzPts{ { inputs[i].x, inputs[i].y },{ inputs[i + 1].x, inputs[i + 1].y }, { inputs[i + 2].x, inputs[i + 2].y },{ inputs[i + 3].x, inputs[i + 3].y } };
			segPts = bezier3(bzPts);
			i += 3; //�ƶ�i�����η���ĩλ�㣬�õ꼴Ϊ��һ���η�����ʼ��
		}
		//����ִ�ж��η�
		else
		{
			std::vector<Bezier::Point> bzPts{ { inputs[i].x, inputs[i].y },{ inputs[i + 1].x, inputs[i + 1].y }, { inputs[i + 2].x, inputs[i + 2].y }};
			segPts = bezier2(bzPts);
			i += 2;
		}
		ret.insert(ret.end(), segPts.begin(), segPts.end());
	}
	return ret;
}

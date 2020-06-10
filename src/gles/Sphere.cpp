#include "newbrush/gles/Sphere.h"
#include <vector>
#include <math.h>
#include <GLES2/gl2.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace nb;
//�򶥵��㷨��ַ��
//https://www.jianshu.com/p/123c5884f635;
//https://blog.csdn.net/martin20150405/article/details/53888204

constexpr int SphereVSlices						= 50;										//����ά�ȷֳɵ���Ƭ��
constexpr int SphereHSlices						= SphereVSlices / 2;						//����ѭ��Ϊγ����Ƭ����һ��
//constexpr int SphereIndicesCountVertextCount	= (SphereHSlices + 1) * (SphereVSlices + 1);//������

Sphere::Sphere(float x, float y, float z, float r, bool cartesian)
{
	constexpr auto angleStep = 2 * M_PI / SphereVSlices;
	std::vector<Vertex> vertexs;
	for (int i = 0; i < SphereHSlices + 1; ++i)
	{
		for (int j = 0; j < SphereVSlices + 1; ++j)
		{
			auto x = r * sin(angleStep * i) * sin(angleStep * j);
			auto y = r * cos(angleStep * i);
			auto z = r * sin(angleStep * i) * cos(angleStep * j);
			auto texCoor = cartesian ? glm::vec2((float)j / SphereVSlices, 1.0 - ((float)i / SphereHSlices)) : glm::vec2(1.0 - (float)j / SphereVSlices, ((float)i / SphereHSlices));
			vertexs.push_back(Vertex(glm::vec3(x, y, z), glm::vec4(), texCoor));
		}
	}

	auto getIndices = []()->std::vector<uint16_t>
	{
		int x = 0;
		constexpr auto count = SphereHSlices * SphereVSlices * 6;
		std::vector<uint16_t> indices(count);
		for (int i = 0; i < SphereHSlices; i++)
		{
			for (int j = 0; j < SphereVSlices; j++)
			{
				indices[x++] = i * (SphereVSlices + 1) + j;
				indices[x++] = (i + 1) * (SphereVSlices + 1) + j;
				indices[x++] = (i + 1) * (SphereVSlices + 1) + (j + 1);
				indices[x++] = i * (SphereVSlices + 1) + j;
				indices[x++] = (i + 1) * (SphereVSlices + 1) + (j + 1);
				indices[x++] = i * (SphereVSlices + 1) + (j + 1);
			}
		}
		return indices;
	};

	meshes.push_back(Mesh(vertexs, getIndices()));
	matrix = glm::translate(matrix, glm::vec3(x, y, z));
}

void Sphere::preprocess()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

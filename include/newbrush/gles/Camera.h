/*******************************************************
**	Camera
**
**	�������
**		Camera�������۲��������ݽṹ
**	���ṩlookat�����Ծ�����б任��
**
**		������
**
********************************************************/
#pragma once
#include "newbrush/gles/Def.h"
#include "glm/glm.hpp"

namespace nb{

class NB_API Camera
{
public:
	//����һ�������������λ��Ϊ(0.0, 0.0, 1.0)��Ŀ���Ϊ(0.0, 0.0, 0.0)����������Ϊ(0.0, 1.0, 0.0)
	Camera();

	glm::mat4	matrix;	//�۲����

	//lookup
	void lookat(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &upVec);
	void lookat2D(float width, float height);

	glm::vec3 position() const;

};

}

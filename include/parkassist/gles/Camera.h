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
#include "parkassist/gles/Def.h"
#include "glm/glm.hpp"

namespace nb{

class NB_API Camera
{
public:
	//����һ�������������λ��Ϊ(0.0, 0.0, 1.0)��Ŀ���Ϊ(0.0, 0.0, 0.0)����������Ϊ(0.0, 1.0, 0.0)
	Camera();

	//�۲����
	const glm::mat4 &viewMatrix() const;

	//͸�Ӿ���
	const glm::mat4 &projectionMatrix() const;

	//lookup
	void lookat(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &upVec);
	void lookat2D(float width, float height);

	//����ͶӰ
	void ortho(float left, float right, float bottom, float top, float near, float far);

	//͸��ͶӰ
	//fovy������
	void perspective(float fovy, float aspect, float near, float far);

	glm::vec3 position() const;

private:
	glm::mat4 m_viewMatrix;			//�۲����
	glm::mat4 m_projectionMatrix;	//ͶӰ����
};

using CameraPtr = std::shared_ptr<Camera>;
}

/*******************************************************
**	Sphere
**
**	��ģ��
**		������������ģ�͵����ݽṹ
**	
**
**		������
**
********************************************************/
#pragma once
#include "newbrush/gles/Model.h"

namespace nb{

class NB_API Sphere : public Model
{
public:
	//����һ�����壬����Բ����centerPoint�����İ뾶��r
	Sphere(float x, float y, float z, float r, bool cartesian);

private:
	virtual void preprocess() override;

};

}

/*******************************************************
**	Cube
**
**	������ģ��
**		Cube������������ģ�͵����ݽṹ
**
**
**		������
**
********************************************************/
#pragma once
#include "newbrush/gles/Model.h"

namespace nb{

//һ��mesh��mesh��8�����㣬36����������
class NB_API Cube : public Model
{
public:
	//����һ�������壬����������(0.0, 0.0, 0.0)�����ĳ���߶���0.0
	Cube();

	//����һ�������壬�������ĵ���x, y, z�����ĳ������lenght, wide, height
	Cube(float x, float y, float z, float lenght, float width, float height);

private:
	virtual void preprocess() override;
};

}

/*******************************************************
**	Shader
**
**	��ɫ��
**	
**		ģ����Opengl�ɱ�̵�Ƭ�Σ���������GPU�Ĵ���Ρ�һ����ԣ�
**	Shader��Ϊ������ɫ��VertexShader ��ƬԪ��ɫ��FragmentShader��
**	Shader������辭��Program link��������
**
**		Shader����ɫ�����ࣩ
**		VertexShader��������ɫ����
**		FragmentShader��ƬԪ��ɫ����
**		
**		������
**	
********************************************************/
#pragma once
#include "parkassist/gles/Def.h"
#include <string>

namespace nb{

class NB_API Shader
{
public:
	virtual ~Shader();
	Shader(const Shader &other) = delete;
	void operator =(const Shader &other) = delete;

	//����Դ��
	void setSource(const std::string &source);

	//Դ��
	std::string &source();
	const std::string &source() const;

	//����
	//�쳣������ʧ��
	void compile();

	//�Ƿ��ѱ���
	bool hasCompiled() const;

	//��ȡshader���
	unsigned int handle() const;

protected:
	Shader();
	Shader(const std::string &source);

	std::string			m_source;
	unsigned int		m_shaderHandle;
};

class NB_API VertexShader : public Shader
{
public:
	//����һ��������ɫ����Դ��Ϊ��
	VertexShader();

	//����һ��������ɫ����Դ��Ϊsource
	VertexShader(const std::string &source);

};

class NB_API FragmentShader : public Shader
{
public:
	//����һ��ƬԴ��ɫ����Դ��Ϊ��
	FragmentShader();

	//����һ��ƬԴ��ɫ����Դ��Ϊsource
	FragmentShader(const std::string &source);

};

using ShaderPtr = std::shared_ptr<Shader>;
using VertexShaderPtr = std::shared_ptr<VertexShader>;
using FragmentShaderPtr = std::shared_ptr<FragmentShader>;
}

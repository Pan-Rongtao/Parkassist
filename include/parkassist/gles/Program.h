/*******************************************************
**	Program/Programs
**
**	Program����
**	
**		��������������GPU�ĳ���һ����ԣ�����Ҫ������Shader
**	�������壬link�����Ϳ�����ʱʹ��
**
**	Programs���ṩ���õ�Program������primitive��phong��cube��
**
**		������
**	
********************************************************/
#pragma once
#include "parkassist/gles/Shader.h"
#include "parkassist/gles/Any.h"
#include "glm/glm.hpp"

namespace nb{

class NB_API Program
{
public:
	//nb�̶�location��locationStr
	static constexpr int nbPositionLocation				= 0;
	static constexpr int nbColorLocation				= 1;
	static constexpr int nbTexCoordLocaltion			= 2;
	static constexpr int nbNormalLocation				= 3;
	static constexpr const char *nbPositionLocationStr	= "nbPos";
	static constexpr const char *nbColorLocationStr		= "nbColor";
	static constexpr const char *nbTexCoordLocaltionStr	= "nbTexCoord";
	static constexpr const char *nbNormalLocationStr	= "nbNormal";
	static constexpr const char *nbMvpStr				= "nbMvp";
	static constexpr const char *nbMStr					= "nbM";
	static constexpr const char *nbVStr					= "nbV";
	static constexpr const char *nbPStr					= "nbP";

public:
	//����һ��Program��δָ��������ɫ����ƬԪ��ɫ��
	Program();

	//����һ��Program����Ϊ��ָ���˶�����ɫ����ƬԪ��ɫ��
	Program(VertexShaderPtr verShader, FragmentShaderPtr fragShader);
	virtual ~Program();

public:
	//���ö�����ɫ��
	void setVertexShader(VertexShaderPtr verShader);

	//��ȡ������ɫ��
	VertexShaderPtr vertexShader();

	//����ƬԪ��ɫ��
	void setFragmentShader(FragmentShaderPtr fragShader);

	//��ȡƬԪ��ɫ��
	FragmentShaderPtr fragmentShader();

	//����
	//�쳣��
	void link();

	//��ȡprogram��attribute���ͱ���sName��λ��/��ַ
	//���δ�ҵ�����������-1
	int getAttributeLocation(const char *name) const;

	//��ȡprogram��uniform���ͱ���sName��λ��/��ַ
	//���δ�ҵ�����������-1
	int getUniformLocation(const char *name) const;

	//��attributeλ��
	void bindAttributeLocation(unsigned int location, const char *name);

	//ʹ��
	//�쳣��
	void use();

	//ȡ��ʹ��
	//�쳣��
	void disuse();

	//����λ��Ϊlocation��attribute
	void vertexAttribute(int location, float v);
	void vertexAttribute(int location, const glm::vec2 &vec);
	void vertexAttribute(int location, const glm::vec3 &vec);
	void vertexAttribute(int location, const glm::vec4 &vec);
	void vertexAttributePointer(int location, int dimension, int stride, const void *data);

	//����λ��Ϊlocation��unform
	void uniform(int location, bool v);
	void uniform(int location, float v);
	void uniform(int location, const std::vector<float> &v);
	void uniform(int location, const glm::vec2 &v);
	void uniform(int location, const std::vector<glm::vec2> &v);
	void uniform(int location, const glm::vec3 &v);
	void uniform(int location, const std::vector<glm::vec3> &v);
	void uniform(int location, const glm::vec4 &v);
	void uniform(int location, const std::vector<glm::vec4> &v);

	//int
	void uniform(int location, int v);
	void uniform(int location, const std::vector<int> &v);
	void uniform(int location, const glm::ivec2 &vec);
	void uniform(int location, const std::vector<glm::ivec2> &v);
	void uniform(int location, const glm::ivec3 &vec);
	void uniform(int location, const std::vector<glm::ivec3> &v);
	void uniform(int location, const glm::ivec4 &vec);
	void uniform(int location, const std::vector<glm::ivec4> &v);

	//mat
	void uniform(int location, const glm::mat2x2 &matrix);
	void uniform(int location, const std::vector<glm::mat2x2> &v);
	void uniform(int location, const glm::mat3x3 &matrix);
	void uniform(int location, const std::vector<glm::mat3x3> &v);
	void uniform(int location, const glm::mat4x4 &matrix);
	void uniform(int location, const std::vector<glm::mat4x4> &v);

	void uniformVar(int location, const var &v);

private:
	VertexShaderPtr	m_vertexShader;
	FragmentShaderPtr m_fragmentShader;
	unsigned int m_programHandle;
};

using ProgramPtr = std::shared_ptr<Program>;

class NB_API Programs
{
public:
	//��program
	static ProgramPtr primitive();

	//����ͼԪ
	static ProgramPtr gradientPrimitive();

	//ͼƬprogram
	static ProgramPtr image();

	//phong program
	static ProgramPtr phong();

	//cube program
	static ProgramPtr cube();

private:
	static ProgramPtr compileBindLink(const std::string &vs, const std::string &fs);
};

}

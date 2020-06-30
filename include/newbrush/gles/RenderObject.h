/*******************************************************
**	RenderObject
**
**	��Ⱦ��
**	
**	��Ⱦ������������Ⱦ��������ݽṹ
**
**	һ����ԣ���Ⱦ�ﶼ���Լ���ģ�ͽṹ�����ʵ�
**		
**		
**		������
**	
********************************************************/
#pragma once
#include <string>
#include "newbrush/gles/Model.h"
#include "newbrush/gles/Material.h"
#include "newbrush/gles/Camera.h"
#include "newbrush/gles/Projection.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/gles/TextureMipmap.h"
#include "rttr/variant.h"

struct aiNode;
struct aiMesh;
struct aiScene;
namespace nb{
	
using var = rttr::variant;

class NB_API RenderObject
{
public:
	//����һ���յ�RenderObject�����Ŀ���Ⱦ״̬Ϊtrue
	RenderObject();

	//����һ���յ�RenderObject�����Ŀ���Ⱦ״̬ΪbRenderable
	RenderObject(std::shared_ptr<Model> model);

	//����һ��RenderObject������ģ��Ϊmodel������Ϊprogram������Ⱦ״̬Ϊtrue
	RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Program> program);

public:	
	//�����Ƿ����Ⱦ���⽫���������Ƿ����
	void setRenderable(bool bRenderable);

	//�Ƿ����Ⱦ
	bool renderable() const;

	//����ģ��
	void setModel(std::shared_ptr<Model> model);

	//��ȡģ��
	std::shared_ptr<Model> model();

	//����program
	void setProgram(std::shared_ptr<Program> program);

	//��ȡprogram
	std::shared_ptr<Program> program();

	//�洢uniform�������Ա��´�ˢ��ʹ��
	template<class T>
	void storeUniform(const std::string &name, const T &v)
	{
		static_assert(
			std::is_same<T, short>::value ||
			std::is_same<T, unsigned short>::value ||
			std::is_same<T, int>::value ||
			std::is_same<T, unsigned int>::value ||
			std::is_same<T, long>::value ||
			std::is_same<T, unsigned long>::value ||
			std::is_same<T, float>::value ||
			std::is_same<T, double>::value ||
			std::is_same<T, glm::vec2>::value ||
			std::is_same<T, glm::vec3>::value ||
			std::is_same<T, glm::vec4>::value ||
			std::is_same<T, glm::ivec2>::value ||
			std::is_same<T, glm::ivec3>::value ||
			std::is_same<T, glm::ivec4>::value ||
			std::is_same<T, glm::mat2x2>::value ||
			std::is_same<T, glm::mat3x3>::value ||
			std::is_same<T, glm::mat4x4>::value ||

			std::is_same<T, std::vector<float>>::value ||
			std::is_same<T, std::vector<glm::vec2>>::value ||
			std::is_same<T, std::vector<glm::vec3>>::value ||
			std::is_same<T, std::vector<glm::vec4>>::value ||
			std::is_same<T, std::vector<int>>::value ||
			std::is_same<T, std::vector<glm::ivec2>>::value ||
			std::is_same<T, std::vector<glm::ivec3>>::value ||
			std::is_same<T, std::vector<glm::ivec4>>::value ||
			std::is_same<T, std::vector<glm::mat2x2>>::value ||
			std::is_same<T, std::vector<glm::mat3x3>>::value ||
			std::is_same<T, std::vector<glm::mat4x4>>::value
			, "only support type[short, int, long, float, double, vec2, vec3, vec4, mat2x2, mat3x3, mat4x4 or their vector types].");

		m_uniforms[name] = v;
	}
	
	//���ƣ���д�˷����Թ����Լ�����Ⱦ��ʽ
	virtual void draw(const Camera &camera, const Projection &projection) const;

private:
	std::shared_ptr<Model>		m_model;
	std::shared_ptr<Program>	m_program;
	std::map<std::string, var>	m_uniforms;
	bool						m_renderable;
};

}

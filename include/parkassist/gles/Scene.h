#pragma once
#include "parkassist/gles/Shape.h"

namespace nb {

class NB_API Scene
{
public:
	Scene(int width, int height);
	~Scene() = default;

	//���һ�������
	void add(MeshPtr mesh);

	//���
	void clear();

	//ִ����Ⱦ����Ⱦ���ж���Σ�
	void doRender();

	//
	void enableBorder(bool enable);
	bool isBorderEnable() const;

private:
	void draw(const std::vector<MeshPtr> meshes);

	std::vector<MeshPtr> m_meshes;
	std::vector<MeshPtr> m_meshesBorder;
	bool m_enableBorder;
	CameraPtr m_camera;
};

using ScenePtr = std::shared_ptr<Scene>;
}
#pragma once
#include "parkassist/Shape.h"

namespace nb {

class NB_API Scene
{
public:
	Scene(float width, float height);
	~Scene() = default;

	//���һ�������
	void add(MeshPtr mesh);

	//���
	void clear();

	//ִ����Ⱦ����Ⱦ���ж���Σ�
	void doRender();

	int width() const;

	int height() const;

	void enableBorder(bool enable);
	bool isBorderEnable() const;

	//��ɫ�����.bmp
	void SaveToBMP(const char* fileName);

	//��ɫ������ı��ļ�
	void SaveToFile(const std::string &fileName);

	//��ɫ�����buffer����RGBA˳��
	void SaveToFrameBuffer(std::string& buffer);

private:
	void draw(const std::vector<MeshPtr> meshes);

	std::vector<MeshPtr> m_meshes;
	std::vector<MeshPtr> m_meshesBorder;
	bool m_enableBorder;
	CameraPtr m_camera;
	int m_width, m_height;
};

using ScenePtr = std::shared_ptr<Scene>;
}
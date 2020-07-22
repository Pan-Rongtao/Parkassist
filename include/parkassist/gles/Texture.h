﻿/*******************************************************
**	::Texture(纹理，虚基类)
**	
**		纹理是描述不同维度数据的数据结构，比如颜色数据，
**	亮度数据等。2D纹理可简单的理解为一个2维结构的像素数组。
**	一般情况下，纹理需要绑定纹理处理单元，若不指定，将绑定
**	到默认的纹理处理单元上。
**
**		纹理在映射到表面时有可能被放大或者缩小，所以可以指定
**	所采用的纹理过滤方式
**
**	::TextureFilter(纹理纹理过滤)
**	
**		纹理过滤的需求，是由于纹理在映射到不同表面上，纹理
**	尺寸与表面尺寸不一致从而导致放大或缩小所参数的失真现象。
**	不同的情况设置恰当的过滤方式可以解决一些现实问题。 比如
**	Bilinear消除马赛克现象；而需要经常做移动的表面可以设置
**	过滤方式为Trilinear，来消除闪烁问题。
**
**		过滤方式有两个维度：放大过滤和缩小过滤
**	
**		潘荣涛
**	
********************************************************/
#pragma once
#include "parkassist/gles/Def.h"
#include "glm/glm.hpp"

namespace nb{

//class TextureWrapping
class NB_API TextureWrapping
{
public:
	//纹理环绕方式
	enum class WrappingModeE
	{
		Repeat,			//重复
		MirroredRepeat,	//镜像重复
		ClampToEdge,	//边缘延伸
		ClampToBorder,	//用户颜色边缘延伸
	};

	WrappingModeE	s;				//S轴
	WrappingModeE	t;				//T轴
	glm::vec4		borderColor;	//边框颜色

	//转到gl的值
	static int glValue(WrappingModeE wrapping);

};

//class TextureFilter
class NB_API TextureFilter
{
public:
	//纹理过滤方式，依次向下，纹理细节表现质量越好，性能要求越大
	//放大过滤只支持Point和Bilinear
	//缩小过滤支持所有的过滤方式
	enum class FilterE
	{
		Point = 0,		//最邻近过滤，指取最接近浮点的整型像素点位置
		Bilinear,		//双线性过滤，对邻近的四个点进行线性插值算法，两个维度三次运算
		Trilinear,		//三线性过滤。三线性过滤以双线性过滤为基础。会对pixel大小与texel大小最接近的两层Mipmap level分别进行双线性过滤，然后再对两层得到的结果进生线性插值。
		Anisotropic,	//各向异性过滤，当需要贴图的三维表面平行于屏幕(viewport)，则是各向同性的。当要贴图的三维表面与屏幕有一定角度的倾斜，则是各向异性的。
	};

	//获取放大/缩小过滤方式
	FilterE magnifyFilter;
	FilterE narrowFilter;

	//获取gl值
	static int glValue(FilterE filter);

};

//class Texture
class NB_API Texture
{
public:
	virtual ~Texture();

	//绑定当前纹理，表示之后的gl操作都是针对当前纹理。在每次的Gles纹理操作都应该调用此函数
	virtual void bind() = 0;

	//解除纹理绑定
	virtual void unbind() = 0;

	//设置纹理环绕方式
	virtual void setWrapping(const TextureWrapping &wrapping) = 0;

	//获取纹理环绕方式
	TextureWrapping &wrapping();
	const TextureWrapping &wrapping() const;

	//设置纹理过滤方式，假若不显示设置，将采用默认的过滤方式TextureFilter::Default
	virtual void setFilter(const TextureFilter &filter) = 0;

	//获取纹理过滤方式
	TextureFilter &filter();
	const TextureFilter &filter() const;

	//设置、获取纹理采样单元
	void setSamplerUnit(int unit);
	int samplerUnit();

	//激活当前采用单元
	void active();

	//获取glFormat和glType
	static std::pair<int, int> getGlFormatAndType(int bmChannels);

protected:
	Texture();

	TextureWrapping		m_wrapping;
	TextureFilter		m_filter;
	unsigned int		m_handle;
	int					m_samplerUnit;
};

}

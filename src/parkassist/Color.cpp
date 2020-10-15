﻿#include <algorithm>
#include <math.h>
#include "parkassist/Color.h"
#include <regex>

using namespace nb;

Color::Color()
	: Color(0, 0, 0, 255)
{
}

Color::Color(uint8_t r, uint8_t g, uint8_t b)
	: Color(r, g, b, 255)
{
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	setRgba(r, g, b, a);
}

Color::Color(const Color &other)
	: Color(other.red(), other.green(), other.blue(), other.alpha())
{
}

void Color::operator =(const Color &other) &
{
	setRgba(other.red(), other.green(), other.blue(), other.alpha());
}

bool Color::operator ==(const Color &other) const
{
	return !(operator!=(other));
}

bool Color::operator !=(const Color &other) const
{
	return (alpha() != other.alpha()) || (red() != other.red() || green() != other.green()) || (blue() != other.blue());
}

uint8_t &Color::alpha()
{
	return m_alpha;
}

const uint8_t &Color::alpha() const
{
	return m_alpha;
}

uint8_t &Color::red()
{
	return m_red;
}

const uint8_t &Color::red() const
{
	return m_red;
}

uint8_t &Color::green()
{
	return m_green;
}

const uint8_t &Color::green() const
{
	return m_green;
}

uint8_t &Color::blue()
{
	return m_blue;
}

const uint8_t &Color::blue() const
{
	return m_blue;
}

void Color::setAlpha(uint8_t a) &
{
	m_alpha = a;
}

void Color::setRed(uint8_t r) &
{
	m_red = r;
}

void Color::setGreen(uint8_t g) &
{
	m_green = g;
}

void Color::setBlue(uint8_t b) &
{
	m_blue = b;
}

void Color::setRgb(uint8_t r, uint8_t g, uint8_t b) &
{
	setRed(r);
	setGreen(g);
	setBlue(b);
}

void Color::setRgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) &
{
	setAlpha(a);
	setRgb(r, g, b);
}

float Color::alphaF() const
{
	return argb2ArgbF(alpha());
}

float Color::redF() const
{
	return argb2ArgbF(red());
}

float Color::greenF() const
{
	return argb2ArgbF(green());
}

float Color::blueF() const
{
	return argb2ArgbF(blue());
}

void Color::setAlphaF(float a) &
{
	setRgbaF(redF(), greenF(), blueF(), a);
}

void Color::setRedF(float r) &
{
	setRgbaF(r, greenF(), blueF(), alphaF());
}

void Color::setGreenF(float g) &
{
	setRgbaF(redF(), g, blueF(), alphaF());
}

void Color::setBlueF(float b) &
{
	setRgbaF(redF(), greenF(), b, alphaF());
}

void Color::setRgbF(float r, float g, float b) &
{
	setRgbaF(r, g, b, alphaF());
}

void Color::setRgbaF(float a, float r, float g, float b) &
{
	if (!isValidArgbF(a, r, g, b))
		nbThrowException(std::out_of_range, "a[%.2f] or r[%.2f] or g[%.2f] or b[%.2f] is out of range [0.0, 1.0]", a, r, g, b);

	setAlpha(argbF2Argb(a));
	setRed(argbF2Argb(r));
	setGreen(argbF2Argb(g));
	setBlue(argbF2Argb(b));
}

bool Color::isValidArgbF(float a, float r, float g, float b)
{
	return (a >= 0.0 && a <= 1.0) && (r >= 0.0 && r <= 1.0) && (g >= 0.0 && g <= 1.0) && (b >= 0.0 && b <= 1.0);
}

bool Color::isValidHsv(float h, float s, float v)
{
	return (h >= 0.0 && h <= 360.0) && (s >= 0.0 && s <= 1.0) && (v >= 0.0 && v <= 1.0);
}

uint8_t Color::argbF2Argb(float f)
{
	if (f < 0.0 || f > 1.0)
		nbThrowException(std::out_of_range, "f[%.2f] is out of range [0.0, 1.0]", f);

	return (uint8_t)std::round(f * 255);
}

float Color::argb2ArgbF(uint8_t n)
{
	return n / 255.0f;
}

Color Colors::aliceBlue()
{
	return Color(240, 248, 255);
}

Color Colors::antiqueWhite()
{
	return Color(250, 235, 215);
}

Color Colors::aqua()
{
	return Color(0, 255, 255);
}

Color Colors::aquamarine()
{
	return Color(127, 255, 212);
}

Color Colors::azure()
{
	return Color(240, 255, 255);
}

Color Colors::beige()
{
	return Color(245, 245, 220);
}

Color Colors::bisque()
{
	return Color(255, 228, 196);
}

Color Colors::black()
{
	return Color(0, 0, 0);
}

Color Colors::blanchedAlmond()
{
	return Color(255, 255, 205);
}

Color Colors::blue()
{
	return Color(0, 0, 255);
}

Color Colors::blueViolet()
{
	return Color(138, 43, 226);
}

Color Colors::brown()
{
	return Color(165, 42, 42);
}

Color Colors::burlyWood()
{
	return Color(222, 184, 135);
}

Color Colors::cadetBlue()
{
	return Color(95, 158, 160);
}

Color Colors::chartreuse()
{
	return Color(127, 255, 0);
}

Color Colors::chocolate()
{
	return Color(210, 105, 30);
}

Color Colors::coral()
{
	return Color(255, 127, 80);
}

Color Colors::cornflowerBlue()
{
	return Color(100, 149, 237);
}

Color Colors::cornsilk()
{
	return Color(255, 248, 220);
}

Color Colors::crimson()
{
	return Color(220, 20, 60);
}

Color Colors::cyan()
{
	return Color(0, 255, 255);
}

Color Colors::darkBlue()
{
	return Color(0, 0, 139);
}

Color Colors::darkCyan()
{
	return Color(0, 139, 139);
}

Color Colors::darkGoldenrod()
{
	return Color(184, 134, 11);
}

Color Colors::darkGray()
{
	return Color(169, 169, 169);
}

Color Colors::darkGreen()
{
	return Color(0, 100, 0);
}

Color Colors::darkKhaki()
{
	return Color(189, 183, 107);
}

Color Colors::darkMagenta()
{
	return Color(139, 0, 139);
}

Color Colors::darkOliveGreen()
{
	return Color(85, 107, 47);
}

Color Colors::darkOrange()
{
	return Color(255, 140, 0);
}

Color Colors::darkOrchid()
{
	return Color(153, 50, 204);
}

Color Colors::darkRed()
{
	return Color(139, 0, 0);
}

Color Colors::darkSalmon()
{
	return Color(233, 150, 122);
}

Color Colors::darkSeaGreen()
{
	return Color(143, 188, 143);
}

Color Colors::darkSlateBlue()
{
	return Color(72, 61, 139);
}

Color Colors::darkSlateGray()
{
	return Color(40, 79, 79);
}

Color Colors::darkTurquoise()
{
	return Color(0, 206, 209);
}

Color Colors::darkViolet()
{
	return Color(148, 0, 211);
}

Color Colors::deepPink()
{
	return Color(255, 20, 147);
}

Color Colors::deepSkyBlue()
{
	return Color(0, 191, 255);
}

Color Colors::dimGray()
{
	return Color(105, 105, 105);
}

Color Colors::dodgerBlue()
{
	return Color(30, 144, 255);
}

Color Colors::firebrick()
{
	return Color(178, 34, 34);
}

Color Colors::floralWhite()
{
	return Color(255, 250, 240);
}

Color Colors::forestGreen()
{
	return Color(34, 139, 34);
}

Color Colors::fuchsia()
{
	return Color(255, 0, 255);
}

Color Colors::gainsboro()
{
	return Color(220, 220, 220);
}

Color Colors::ghostWhite()
{
	return Color(248, 248, 255);
}

Color Colors::gold()
{
	return Color(255, 215, 0);
}

Color Colors::goldenrod()
{
	return Color(218, 165, 32);
}

Color Colors::gray()
{
	return Color(128, 128, 128);
}

Color Colors::green()
{
	return Color(0, 128, 0);
}

Color Colors::greenYellow()
{
	return Color(173, 255, 47);
}

Color Colors::honeydew()
{
	return Color(240, 255, 240);
}

Color Colors::hotPink()
{
	return Color(255, 105, 180);
}

Color Colors::indianRed()
{
	return Color(205, 92, 92);
}

Color Colors::indigo()
{
	return Color(75, 0, 130);
}

Color Colors::ivory()
{
	return Color(255, 240, 240);
}

Color Colors::khaki()
{
	return Color(240, 230, 140);
}

Color Colors::lavender()
{
	return Color(230, 230, 250);
}

Color Colors::lavenderBlush()
{
	return Color(255, 240, 245);
}

Color Colors::lawnGreen()
{
	return Color(124, 252, 0);
}

Color Colors::lemonChiffon()
{
	return Color(255, 250, 205);
}

Color Colors::lightBlue()
{
	return Color(173, 216, 230);
}

Color Colors::lightCoral()
{
	return Color(240, 128, 128);
}

Color Colors::lightCyan()
{
	return Color(224, 255, 255);
}

Color Colors::lightGoldenrodYellow()
{
	return Color(250, 250, 210);
}

Color Colors::lightGray()
{
	return Color(211, 211, 211);
}

Color Colors::lightGreen()
{
	return Color(144, 238, 144);
}

Color Colors::lightPink()
{
	return Color(255, 182, 193);
}

Color Colors::lightSalmon()
{
	return Color(255, 160, 122);
}

Color Colors::lightSeaGreen()
{
	return Color(32, 178, 170);
}

Color Colors::lightSkyBlue()
{
	return Color(135, 206, 250);
}

Color Colors::lightSlateGray()
{
	return Color(119, 136, 153);
}

Color Colors::lightSteelBlue()
{
	return Color(176, 196, 222);
}

Color Colors::lightYellow()
{
	return Color(255, 255, 224);
}

Color Colors::lime()
{
	return Color(0, 255, 0);
}

Color Colors::limeGreen()
{
	return Color(50, 205, 50);
}

Color Colors::linen()
{
	return Color(250, 240, 230);
}

Color Colors::magenta()
{
	return Color(255, 0, 255);
}

Color Colors::maroon()
{
	return Color(128, 0, 0);
}

Color Colors::mediumAquamarine()
{
	return Color(102, 205, 170);
}

Color Colors::mediumBlue()
{
	return Color(0, 0, 205);
}

Color Colors::mediumOrchid()
{
	return Color(186, 85, 211);
}

Color Colors::mediumPurple()
{
	return Color(147, 112, 219);
}

Color Colors::mediumSeaGreen()
{
	return Color(60, 179, 113);
}

Color Colors::mediumSlateBlue()
{
	return Color(123, 104, 238);
}

Color Colors::mediumSpringGreen()
{
	return Color(0, 250, 154);
}

Color Colors::mediumTurquoise()
{
	return Color(72, 209, 204);
}

Color Colors::mediumVioletRed()
{
	return Color(199, 21, 112);
}

Color Colors::midnightBlue()
{
	return Color(25, 25, 112);
}

Color Colors::mintCream()
{
	return Color(245, 255, 250);
}

Color Colors::mistyRose()
{
	return Color(255, 228, 225);
}

Color Colors::moccasin()
{
	return Color(255, 228, 181);
}

Color Colors::navajoWhite()
{
	return Color(255, 222, 173);
}

Color Colors::navy()
{
	return Color(0, 0, 128);
}

Color Colors::oldLace()
{
	return Color(253, 245, 230);
}

Color Colors::olive()
{
	return Color(128, 128, 0);
}

Color Colors::oliveDrab()
{
	return Color(107, 142, 45);
}

Color Colors::orange()
{
	return Color(255, 165, 0);
}

Color Colors::orangeRed()
{
	return Color(255, 69, 0);
}

Color Colors::orchid()
{
	return Color(218, 112, 214);
}

Color Colors::paleGoldenrod()
{
	return Color(238, 232, 170);
}

Color Colors::paleGreen()
{
	return Color(152, 251, 152);
}

Color Colors::paleTurquoise()
{
	return Color(175, 238, 238);
}

Color Colors::paleVioletRed()
{
	return Color(219, 112, 147);
}

Color Colors::papayaWhip()
{
	return Color(255, 239, 213);
}

Color Colors::peachPuff()
{
	return Color(255, 218, 155);
}

Color Colors::peru()
{
	return Color(205, 133, 63);
}

Color Colors::pink()
{
	return Color(255, 192, 203);
}

Color Colors::plum()
{
	return Color(221, 160, 221);
}

Color Colors::powderBlue()
{
	return Color(176, 224, 230);
}

Color Colors::purple()
{
	return Color(128, 0, 128);
}

Color Colors::red()
{
	return Color(255, 0, 0);
}

Color Colors::rosyBrown()
{
	return Color(188, 143, 143);
}

Color Colors::royalBlue()
{
	return Color(65, 105, 225);
}

Color Colors::saddleBrown()
{
	return Color(139, 69, 19);
}

Color Colors::salmon()
{
	return Color(250, 128, 114);
}

Color Colors::sandyBrown()
{
	return Color(244, 164, 96);
}

Color Colors::seaGreen()
{
	return Color(46, 139, 87);
}

Color Colors::seaShell()
{
	return Color(255, 245, 238);
}

Color Colors::sienna()
{
	return Color(160, 82, 45);
}

Color Colors::silver()
{
	return Color(192, 192, 192);
}

Color Colors::skyBlue()
{
	return Color(135, 206, 235);
}

Color Colors::slateBlue()
{
	return Color(106, 90, 205);
}

Color Colors::slateGray()
{
	return Color(112, 128, 144);
}

Color Colors::snow()
{
	return Color(255, 250, 250);
}

Color Colors::springGreen()
{
	return Color(0, 255, 127);
}

Color Colors::steelBlue()
{
	return Color(70, 130, 180);
}

Color Colors::tan()
{
	return Color(210, 180, 140);
}

Color Colors::teal()
{
	return Color(0, 128, 128);
}

Color Colors::thistle()
{
	return Color(216, 191, 216);
}

Color Colors::tomato()
{
	return Color(253, 99, 71);
}

Color Colors::transparent()
{
	return Color(0, 255, 255, 255);
}

Color Colors::turquoise()
{
	return Color(64, 224, 208);
}

Color Colors::violet()
{
	return Color(238, 130, 238);
}

Color Colors::wheat()
{
	return Color(245, 222, 179);
}

Color Colors::white()
{
	return Color(255, 255, 255);
}

Color Colors::whiteSmoke()
{
	return Color(245, 245, 245);
}

Color Colors::yellow()
{
	return Color(255, 255, 0);
}

Color Colors::yellowGreen()
{
	return Color(154, 205, 50);
}

#include "Parser.h"
#include <fstream>
#include "spdlog/spdlog.h"
#include "glm/glm.hpp"
#include "Exceptions.h"
#include "parkassist/gles/Program.h"
#include "parkassist/gles/RenderObject.h"
#include "parkassist/gles/Polygon.h"
#include "GLES2/gl2.h"

using namespace nb;
using namespace nlohmann;

constexpr char *CfgFile = "config.json";
constexpr char *StateFileHead = "state";

void Parser::setDir(const std::string & dir)
{
	m_dir = dir + "/";
	spdlog::info("set dir [{}]", m_dir);
}

std::string Parser::getDir() const
{
	return m_dir;
}

bool Parser::parse()
{
	try {
		auto k = getTickCount();
		parseConfig();
		parseStates();
		spdlog::info("{} cost [{}] ms", __FUNCTION__, getTickCount() - k);
		return true;
	}
	catch (std::exception &ex)
	{
		spdlog::error("{}", ex.what());
		return false;
	}
}

int Parser::getContextWidth() const
{
	return m_contextWidth;
}

int Parser::getContextHeight() const
{
	return m_contextHeight;
}

void Parser::enablePointsObjects(bool bOn)
{
	m_bEnablePiontsObject = bOn;
}

bool Parser::isPointsObjectsOn() const
{
	return m_bEnablePiontsObject;
}

int nb::Parser::drawingStatesCount() const
{
	return m_drawingStates.size();
}

DrawingState nb::Parser::getDrawingState(int index) const
{
	if (index < 0 || index >= m_drawingStates.size())
	{
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %zu)", index, m_drawingStates.size());
	}
	if (m_bEnablePiontsObject)
	{
		DrawingState state = m_drawingStates[index];
		state.insert(state.end(), m_drawingStates_Points[index].begin(), m_drawingStates_Points[index].end());
		return state;
	}
	else
	{
		return m_drawingStates[index];
	}
}

void Parser::parseConfig()
{
	spdlog::info("parsing [{}] ...", CfgFile);
	json obj = parseOneFile(CfgFile);

	auto check = [&obj](const std::string &nodeName, int minuxLimit)->int
	{
		int ret = 0;
		json j;
		try {
			j = obj.at(nodeName);
		}
		catch (...)
		{
			throw Exception(fmt::format("can't find field [{}] as int type in file [{}]", nodeName, CfgFile));
		}

		if (!j.is_number_integer())
		{
			throw Exception(fmt::format("can't find field [{}] as int type in file [{}]", nodeName, CfgFile));
		}
		else
		{
			ret = j;
			if (ret < minuxLimit)
			{
				throw Exception(fmt::format("[{}] must >= 1 but not [{}]", nodeName, ret));
			}
		}
		return ret;
	};

	m_contextWidth = check("ContextWidth", 0);
	m_contextHeight = check("ContextHeight", 0);
	m_stateCount = check("StateCount", 0);
	m_bezierControlPointsCount = check("BezierControlPointsCount", 0);
	m_bezierSampleCount = check("BezierSampleCount", 0);
	m_drawPointMode = check("DrawPointMode", 0);

	spdlog::info("parsing [{}] success, ContextWidth=[{}], ContextHeight=[{}], StateCount=[{}], BezierControlPointsCount=[{}], BezierSampleCount=[{}]", 
		CfgFile, m_contextWidth, m_contextHeight, m_stateCount, m_bezierControlPointsCount, m_bezierSampleCount);
}

void Parser::parseStates()
{
	m_drawingStates.resize(m_stateCount);
	m_drawingStates_Points.resize(m_stateCount);
	for (size_t i = 0; i != m_drawingStates.size(); ++i)
	{
		m_parsingFileName = fmt::format("{}{}.json", StateFileHead, i);
		spdlog::info("parsing [{}] ...", m_parsingFileName);
		json obj = parseOneFile(m_parsingFileName);
		auto statePair = makeDrawingState(obj);
		m_drawingStates[i] = statePair.first;
		m_drawingStates_Points[i] = statePair.second;
	}
}

json Parser::parseOneFile(const std::string & fileName)
{
	std::ifstream stream(m_dir + fileName.data());
	if (!stream)
	{
		throw FileNotExistsException(fileName);
	}

	json obj;
	try {
		stream >> obj;
	}
	catch (std::exception &e) 
	{
		stream.close();
		throw JsonParsingException(fileName, e.what());
	}
	return obj;
}

std::pair<DrawingState, DrawingState> Parser::makeDrawingState(const json &obj)
{
	DrawingState state;
	DrawingState state_Points;
	for (auto iter = obj.begin(); iter != obj.end(); ++iter)
	{
		auto item = iter.value();
		if (!item.is_object())
		{
			throw Exception(fmt::format("[{}] is not a [Polygon Type] in file [{}], please remove it", iter.key(), m_parsingFileName));
		}

		//�����if��ʵû�б������壬��Ϊ�������true���Ѿ��׳��쳣�ˡ�������ﲻ��Ҫelse
		if (isPolygon(item, iter.key()))
		{
			std::vector<float> s0 = item["Side0"];
			std::vector<float> s1 = item["Side1"];
			if (s0.size() > s1.size())	s0.resize(s1.size());
			else if(s1.size() > s0.size())	s1.resize(s0.size());
			std::vector<int> arr = item["SolidColor"];
			std::vector<glm::vec2> side0(s0.size() / 2);
			std::vector<glm::vec2> side1(s0.size() / 2);
			glm::vec4 solidColor{ arr[0] / 255.0f, arr[1] / 255.0f, arr[2] / 255.0f, arr[3] / 255.0f };
			for (size_t i = 0; i != side0.size(); ++i)
			{
				side0[i] = { s0[i * 2], s0[i * 2 + 1] };
				side1[i] = { s1[i * 2], s1[i * 2 + 1] };
			}
			auto polygon = std::make_shared<Polygon>();
			polygon->setPoint(side0, side1, m_bezierControlPointsCount, m_bezierSampleCount);
			auto renderObj = std::make_shared<RenderObject>(polygon, Programs::primitive());
			renderObj->model()->unifyColor(solidColor);
			renderObj->model()->mode = GL_TRIANGLES;
			state.push_back(renderObj);

			auto polygon_Points = std::make_shared<Polygon>();
			polygon_Points->setPoint(side0, side1, 0, 0);
			auto renderObj_Pionts = std::make_shared<RenderObject>(polygon_Points, Programs::primitive());
			renderObj_Pionts->model()->unifyColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
			renderObj_Pionts->model()->mode = GL_POINTS;
			state_Points.push_back(renderObj_Pionts);
		}
	}
	return{ state, state_Points };
}

bool Parser::isPoints(const json & arr)
{
	if (arr.size() % 2 != 0)
	{
		throw InvalidArraySizeException();
	}

	bool bIsIntegerArray = false;
	try {
		bIsIntegerArray = isIntegerArray(arr);
	}
	catch (InvalidArrayValueException &ex)
	{
		throw ex;
	}
	return bIsIntegerArray;
}

bool Parser::isSolidColor(const json & arr)
{
	if (arr.size() != 4)
	{
		throw InvalidArraySizeException();
	}

	bool bIsIntegerArray = false;
	try {
		bIsIntegerArray = isIntegerArray(arr);
	}
	catch (InvalidArrayValueException &ex)
	{
		throw ex;
	}
	return bIsIntegerArray;
}

bool Parser::isPolygon(const json & obj, const std::string &polygonName)
{
	json side0, side1, solidColor;
	try { side0 = obj.at("Side0"); }catch(...) { throw Exception(fmt::format("[{}.Side0] not found in file [{}]", polygonName, m_parsingFileName)); }
	try { side1 = obj.at("Side1"); }catch(...) { throw Exception(fmt::format("[{}.Side1] not found in file [{}]", polygonName, m_parsingFileName)); }
	try { solidColor = obj.at("SolidColor"); }catch(...) { throw Exception(fmt::format("[{}.SolidColor] not found in file [{}]", polygonName, m_parsingFileName)); }
	bool sizeEqual = side0.size() == side1.size();

	bool ret = false;
	try { ret = isPoints(side0); }
	catch (InvalidArrayValueException &e)	{ throw Exception(fmt::format("[{}.Side0] must be a int array as [Points Type], invalid value index=[{}]", polygonName, e.InvalidIndex)); }
	catch (InvalidArraySizeException &e)	{ (void)e; throw Exception(fmt::format("[{}.Side0].size must be a multiple of 2", polygonName)); }

	try { ret &= isPoints(side1); }
	catch (InvalidArrayValueException &e)	{ throw Exception(fmt::format("[{}.Side1] must be a int array as [Points Type], invalid value index=[{}]", polygonName, e.InvalidIndex)); }
	catch (InvalidArraySizeException &e)	{ (void)e; throw Exception(fmt::format("[{}.Side1].size must be a multiple of 2", polygonName)); }

	try { ret &= isSolidColor(solidColor); }
	catch (InvalidArrayValueException &e)	{ throw Exception(fmt::format("[{}.SolidColor] must be a int array as [SolidColor Type], invalid value index=[{}]", polygonName, e.InvalidIndex)); }
	catch (InvalidArraySizeException &e)	{ (void)e; throw Exception(fmt::format("[{}.SolidColor].size must be 4 as [SolidColor Type]", polygonName)); }

	if (!sizeEqual)
	{
		int x = 10;
		++x;
	//	throw Exception(fmt::format("[{}.Side0.size={}], [{}.Side1.size={}] are not same in file [{}]", polygonName, side0.size(), polygonName, side1.size(), m_parsingFileName));
	}
	return ret;
}

bool Parser::isIntegerArray(const json & arr)
{
	for (size_t i = 0; i != arr.size(); ++i)
	{
		if (!arr[i].is_number())
			throw InvalidArrayValueException(i);
	}
	return true;
}

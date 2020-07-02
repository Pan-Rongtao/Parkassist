#pragma once
#include <string>
#include "newbrush/gles/Def.h"
#include "nlohmann/json.hpp"

using nlohmann::json;

namespace nb {

class RenderObject;
using RenderObjectPtr = std::shared_ptr<RenderObject>;
using DrawingState = std::vector<RenderObjectPtr>;

enum class ValueType
{
	null,
	boolean,
	integer,
	real,
	string,
	Polygon,
	Points,
	SolidColor,

};

class NB_API Parser
{
public:
	void setDir(const std::string &dir);
	std::string getDir() const;

	bool parse();

	const std::vector<DrawingState> &drawingStates() const;

private:
	void parseConfig();
	void parseStates();

	//�쳣��FileNotExistsException
	//�쳣��JsonParsingException
	json parseOneFile(const std::string &fileName);

	//
	DrawingState makeDrawingState(const json &obj);

	ValueType testType(const json &j);
	ValueType testArray(const json &arr);
	ValueType testObject(const json &obj);

	bool isPoints(const json &arr);
	bool isSolidColor(const json &arr);
	bool isPolygon(const json &obj, const std::string &polygonName = "");
	bool isIntegerArray(const json &arr);

	std::string m_dir;
	json m_commonCfg;

	int m_stateCount;
	std::vector<DrawingState>	m_drawingStates;
	std::string m_parsingFileName;
};

}
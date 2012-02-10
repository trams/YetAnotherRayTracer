#ifndef TIXMLTEST_H_
#define TIXMLTEST_H_

#include "../material.h"
#include "../common.h"
#include "../tinyxml/tinyxml.h"

#include <string>
#include <sstream>
#include <map>

TEST(TiXMLTest, Basic)
{
	TiXmlDocument doc("scenes/test1.xml");
	doc.LoadFile();
	
	TiXmlHandle docHandle(&doc);
	TiXmlElement* integerNode = docHandle.FirstChild("ints").FirstChild("int").ToElement();

	int expected = 1;
	while(integerNode != NULL)
	{
		int actual;
		integerNode->QueryIntAttribute("value", &actual);
		
		EXPECT_EQ(expected,actual);
		
		integerNode = integerNode->NextSiblingElement("int");
		expected *= 2;
	}	
}

TEST(TiXMLTest, TestSceneFile)
{
	TiXmlDocument doc("scenes/test2.xml");
	doc.LoadFile();
	
	TiXmlHandle docHandle(&doc);
	TiXmlElement* material = docHandle.FirstChild("scene").FirstChild("materials").FirstChild("material").ToElement();
	
	typedef std::map<std::string, Material> MaterialMap;
	MaterialMap materialMap;
	
	while(material != NULL)
	{
		const std::string name = material->Attribute("name");

		float diffuse;
		float reflection = 0.0;
		float refractionRate = 1.0;
		float absorptionRate = 0.0;
		
		Vector3 color = readVector(material->Attribute("color"));
		EXPECT_EQ(TIXML_SUCCESS, material->QueryFloatAttribute("diffuse", &diffuse));
		EXPECT_NE(TIXML_WRONG_TYPE, material->QueryFloatAttribute("reflection", &reflection));
		EXPECT_NE(TIXML_WRONG_TYPE, material->QueryFloatAttribute("refractionrate", &refractionRate));
		EXPECT_NE(TIXML_WRONG_TYPE, material->QueryFloatAttribute("absorbtionrate", &absorptionRate));
		
		materialMap[name] = Material(color, diffuse, reflection, refractionRate, absorptionRate);	
			
		material = material->NextSiblingElement("material");
	}
	
	EXPECT_EQ(4, materialMap.size());
	EXPECT_EQ(1, materialMap.count("DullGreen"));
	EXPECT_EQ(1, materialMap.count("DullWhite"));
	EXPECT_EQ(0, materialMap.count("DullRed"));
	
	EXPECT_EQ(Color(0,1,0), materialMap["DullGreen"].GetColor());
	EXPECT_EQ(Color(1,1,1), materialMap["DullWhite"].GetColor());
	
	EXPECT_EQ(1.0, materialMap["DullGreen"].GetDiffuse());
	EXPECT_EQ(0.0, materialMap["DullGreen"].GetReflection());
	
	EXPECT_EQ(1.33f, materialMap["WaterWhite"].GetRefractionRate());
	EXPECT_EQ(0.2f, materialMap["WaterWhite"].GetAbsorptionRate());
	
	TiXmlElement* primitivesNode = docHandle.FirstChild("scene").FirstChild("primitives").ToElement();
	
	EXPECT_FALSE(primitivesNode == NULL);
	
	TiXmlElement* ballNode = primitivesNode->FirstChildElement("ball");
	
	while(ballNode != NULL)
	{
		float radius;
		bool islight;

		EXPECT_EQ(TIXML_SUCCESS, ballNode->QueryFloatAttribute("radius", &radius));
		
		Vector3 center = readVector(ballNode->Attribute("center"));
		if (std::string(ballNode->Attribute("islight")) == std::string("true"))
			islight = true;
		else
			islight = false;
			
		const char* materialName = ballNode->Attribute("materialname");
		EXPECT_TRUE(materialName != NULL);
		EXPECT_EQ(1, materialMap.count(materialName));

				
		ballNode = ballNode->NextSiblingElement("ball");
	}
}

#endif /*TIXMLTEST_H_*/

#include "catch.hpp"

#include <maxwell/material.h>
#include <maxwell/common.h>
#include <tinyxml/tinyxml.h>

#include <string>
#include <sstream>
#include <map>

TEST_CASE("TiXMLTest/Basic", "")
{
    TiXmlDocument doc("../scenes/test1.xml");
    doc.LoadFile();

    TiXmlHandle docHandle(&doc);
    TiXmlElement* integerNode = docHandle.FirstChild("ints").FirstChild("int").ToElement();

    int expected = 1;
    while(integerNode != NULL)
    {
        int actual;
        integerNode->QueryIntAttribute("value", &actual);

        REQUIRE(expected == actual);

        integerNode = integerNode->NextSiblingElement("int");
        expected *= 2;
    }
}

TEST_CASE("TiXMLTest/TestSceneFile", "")
{
    TiXmlDocument doc("../scenes/test2.xml");
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
        REQUIRE(TIXML_SUCCESS == material->QueryFloatAttribute("diffuse", &diffuse));
        REQUIRE((TIXML_WRONG_TYPE != material->QueryFloatAttribute("reflection", &reflection)));
        REQUIRE((TIXML_WRONG_TYPE != material->QueryFloatAttribute("refractionrate", &refractionRate)));
        REQUIRE((TIXML_WRONG_TYPE != material->QueryFloatAttribute("absorbtionrate", &absorptionRate)));

        materialMap[name] = Material(color, diffuse, reflection, refractionRate, absorptionRate);

        material = material->NextSiblingElement("material");
    }

    REQUIRE(4 == materialMap.size());
    REQUIRE(1 == materialMap.count("DullGreen"));
    REQUIRE(1 == materialMap.count("DullWhite"));
        REQUIRE(0 == materialMap.count("DullRed"));

    REQUIRE(Color(0,1,0) == materialMap["DullGreen"].GetColor());
    REQUIRE(Color(1,1,1) == materialMap["DullWhite"].GetColor());

    REQUIRE(1.0 == materialMap["DullGreen"].GetDiffuse());
    REQUIRE(0.0 == materialMap["DullGreen"].GetReflection());

    REQUIRE(1.33f == materialMap["WaterWhite"].GetRefractionRate());
    REQUIRE(0.2f == materialMap["WaterWhite"].GetAbsorptionRate());

    TiXmlElement* primitivesNode = docHandle.FirstChild("scene").FirstChild("primitives").ToElement();

    REQUIRE(primitivesNode != NULL);

    TiXmlElement* ballNode = primitivesNode->FirstChildElement("ball");

    while(ballNode != NULL)
    {
        float radius;
        bool islight;

        REQUIRE(TIXML_SUCCESS == ballNode->QueryFloatAttribute("radius", &radius));

        Vector3 center = readVector(ballNode->Attribute("center"));
        if (std::string(ballNode->Attribute("islight")) == std::string("true"))
            islight = true;
        else
            islight = false;

        const char* materialName = ballNode->Attribute("materialname");
        REQUIRE((materialName != NULL));
        REQUIRE(1 == materialMap.count(materialName));


        ballNode = ballNode->NextSiblingElement("ball");
    }
}


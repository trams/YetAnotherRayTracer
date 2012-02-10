#include <maxwell/scene.h>

#include <tinyxml/tinyxml.h>
#include <maxwell/primitives/ball.h>
#include <maxwell/primitives/plane.h>
#include <maxwell/primitives/parallelogram.h>

#include <string>
#include <sstream>
#include <map>
#include <stdexcept>

Scene::Iterator Scene::Begin()
{
    return m_primitives.begin();
}

Scene::Iterator Scene::End()
{
    return m_primitives.end();
}

Scene::ConstIterator Scene::Begin() const
{
    return m_primitives.begin();
}

Scene::ConstIterator Scene::End() const
{
    return m_primitives.end();
}

void Scene::Add(Primitive* primitive)
{
    m_primitives.push_back(primitive);
}

void Scene::LoadFromFile(const std::string& filename)
{
    TiXmlDocument doc(filename);
    bool result = doc.LoadFile();

    if (!result)
        throw std::runtime_error("Can't load the scene");

    TiXmlHandle docHandle(&doc);
    TiXmlElement* material = docHandle.FirstChild("scene").FirstChild("materials").FirstChild("material").ToElement();

    typedef std::map<std::string, Material> MaterialMap;
    MaterialMap materialMap;

    while(material != NULL)
    {
        const std::string name = material->Attribute("name");

        double diffuse;
        double reflection = 0.0;
        double refractionRate = 1.0;
        double absorptionRate = 0.0;

        Vector3 color = readVector(material->Attribute("color"));
        if (TIXML_SUCCESS != material->QueryDoubleAttribute("diffuse", &diffuse))
            throw std::runtime_error("material node hasn't a diffuse attribute!");

        if (TIXML_WRONG_TYPE == material->QueryDoubleAttribute("reflection", &reflection))
            throw std::runtime_error("attribute reflection must be double number");

        if (TIXML_WRONG_TYPE == material->QueryDoubleAttribute("refractionrate", &refractionRate))
            throw std::runtime_error("refractionrate attribute must be double number");

        if (TIXML_WRONG_TYPE == material->QueryDoubleAttribute("absorbtionrate", &absorptionRate))
            throw std::runtime_error("absorbtionrate attribute must be double number");

        materialMap[name] = Material(color, diffuse, reflection, refractionRate, absorptionRate);

        material = material->NextSiblingElement("material");
    }

    TiXmlElement* primitivesNode = docHandle.FirstChild("scene").FirstChild("primitives").ToElement();

    if (primitivesNode == NULL)
        throw std::runtime_error("There are no any primitive nodes in this scene file!");

    TiXmlElement* primitiveNode = primitivesNode->FirstChildElement();

    while(primitiveNode != NULL)
    {
        Primitive* result = NULL;

        bool islight;
        if (std::string(primitiveNode->Attribute("islight")) == std::string("true"))
            islight = true;
        else
            islight = false;

        const char* materialName = primitiveNode->Attribute("materialname");
        if (materialName == NULL)
            throw std::runtime_error("There are no such material name.");

        const char* nodeName = primitiveNode->Value();
        if (nodeName == std::string("ball"))
        {
            double radius;

            if (TIXML_SUCCESS != primitiveNode->QueryDoubleAttribute("radius", &radius))
                throw std::runtime_error("the node hasn't radius attribute or its type isn't double");

            Vector3 center = readVector(primitiveNode->Attribute("center"));

            result = new Ball(center, radius, materialMap[materialName], islight, std::string());
        }
        else
        {
            if ((nodeName == std::string("plane")) || (nodeName == std::string("parallelogram")))
            {
                Vector3 point = readVector(primitiveNode->Attribute("point"));
                Vector3 normal = readVector(primitiveNode->Attribute("normal"));

                if (nodeName == std::string("plane"))
                {
                    result = new Plane(point, normal, materialMap[materialName], islight, std::string());
                }
                else
                {
                    double length1;
                    if (TIXML_SUCCESS != primitiveNode->QueryDoubleAttribute("length1", &length1))
                        throw std::runtime_error("the node hasn't length1 attribute or its type isn't double number");

                    double length2;
                    if (TIXML_SUCCESS != primitiveNode->QueryDoubleAttribute("length2", &length2))
                        throw std::runtime_error("the node hasn't length2 attribute or its type isn't double number");

                    int area;
                    if (TIXML_SUCCESS != primitiveNode->QueryIntAttribute("area", &area))
                        throw std::runtime_error("the node hasn't area attribute or its type isn't int number");

                    Vector3 e1 = readVector(primitiveNode->Attribute("e1"));
                    Vector3 e2 = readVector(primitiveNode->Attribute("e2"));

                    result = new Parallelogram(point, normal, materialMap[materialName], islight,
                                               length1, length2, e1, e2,
                                               area, std::string());
                }
            }
        }

        assert(result != NULL);
        m_primitives.push_back(result);

        primitiveNode = primitiveNode->NextSiblingElement();
    }
}

Scene::Scene()
{
}

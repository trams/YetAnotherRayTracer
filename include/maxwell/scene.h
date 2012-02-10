#ifndef SCENE_H_
#define SCENE_H_

#include "primitives/primitive.h"
#include <vector>

class Scene
{
public:
    typedef std::vector<Primitive*>::iterator Iterator;
    typedef std::vector<Primitive*>::const_iterator ConstIterator;

    Iterator Begin();
    ConstIterator Begin() const;
    Iterator End();
    ConstIterator End() const;

    void Add(Primitive* primitive);
    void LoadFromFile(const std::string& filename);

    Scene();
private:
    std::vector<Primitive*> m_primitives;
};

#endif /*SCENE_H_*/

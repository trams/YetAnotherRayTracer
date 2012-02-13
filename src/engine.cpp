#include <maxwell/primitives/illuminative.h>
#include <maxwell/engine.h>
#include <SDL/SDL.h>
#include <string>
#include <sstream>

void findNearsetIntersection(const Scene& scene, const Ray ray,
                            Primitive const* * primitive, double* distance, int* intersectionType)
{
    Scene::ConstIterator nearestPrimitive = scene.End();
    IntersectionPoint nearestIntersection;

    for (Scene::ConstIterator it = scene.Begin(); it != scene.End(); it++)
    {
	IntersectionPoint intersection = (*it)->getIntersection(ray);

        if (!intersection.isNull())
        {
	    double distance = intersection.getDistanceFromOrigin(ray);
	    double minDistance = nearestIntersection.getDistanceFromOrigin(ray);
            if ((nearestPrimitive == scene.End()) || (distance < minDistance))
            {
		nearestIntersection = intersection;
                nearestPrimitive = it;
             }
        }
    }

    if (distance != NULL)
    {
        *distance = nearestIntersection.getDistanceFromOrigin(ray);
    }

    if (intersectionType != NULL)
    {
        *intersectionType = nearestIntersection.m_intersectionType;
    }
    if (nearestPrimitive == scene.End())
    {
	*primitive = NULL;
    }
    else
    {
        *primitive = (*nearestPrimitive);
    }
}

//Get intensity of light from this element in particular point of the scene.
//`place` is a point in which intensity is calculated
//`n` is a normal vector at the `place` point
//`scene` is a scene
double getIntensity(const Primitive* element, Vector3 place, Vector3 n, const Scene& scene)
{
    if (element->IsIlluminative())
    {
        const Illuminative* light = dynamic_cast<const Illuminative*>(element);
        assert(light != NULL);

        const int count = light->GetArea();
        double intensity = 0;

        for (int i = 0; i < count; i++)
        {
            const Vector3 l = (light->GetRandomPoint() - place).Normalize();
            const double dot = Dot(n, l);
            if (dot > 0)
            {
                const Primitive* nearest = NULL;
                double distanceToNearest = 0;
                findNearsetIntersection(scene, Ray(place, l), &nearest, &distanceToNearest, NULL);

                if (nearest == element)
                    intensity += dot;
            }
        }
        return (intensity / count);
    }

    return .0;
}

Color trace(const Scene& scene, Ray ray, int depth)
{
    const Color background(0,0,0);
    const int maxDepth = 3;
    if (depth >= maxDepth)
        return background;

    Color color(0,0,0);
    double distance = 0;
    const Primitive* prim = NULL;
    int intersectionType = 0;

    findNearsetIntersection(scene, ray, &prim, &distance, &intersectionType);

    if (prim != NULL)
    {
        if (prim->IsIlluminative())
        {
            return prim->GetMaterial().GetColor();
        }

        const Vector3 intersectionPoint = ray.GetPoint(distance);
        const Vector3 n = prim->GetNormal(intersectionPoint);

        if (prim->GetMaterial().GetDiffuse() > 0)
        {
            for (Scene::ConstIterator it = scene.Begin(); it != scene.End(); it++)
            {
                const double intensive = getIntensity((*it), intersectionPoint, n, scene);

                if (intensive != .0)
                {
                    Vector3 x = (prim->GetMaterial().GetColor());
                    Vector3 y = ((*it)->GetMaterial().GetColor());

                    color = color + (intensive * prim->GetMaterial().GetDiffuse()) * x * y;
                }
            }
        }

        //refraction
        {
            const Vector3 x = ray.GetDirection();
            const Vector3 y = intersectionType * (-n);

            double n;
            if (intersectionType == IntersectOutside)
                n = 1.0 / prim->GetMaterial().GetRefractionRate();
            else
                n = prim->GetMaterial().GetRefractionRate();

            const double sin_1 = sqrt(1 - Dot(x,y));
            const double sin_2 = n * sin_1;

            if (sin_2 < 1)
            {
                const double cos_2 = sqrt(1 - sin_2);
                Vector3 xPerpendicular = x - Dot(x,y)*y;
                Vector3 z = cos_2 * y + sin_2 * xPerpendicular;
                z.Normalize();

                if (prim->GetMaterial().GetRefraction() > 0)
                {
                    if (intersectionType == IntersectInside)
                    {
                        color = color +
                            prim->GetMaterial().GetRefraction() *
                            exp(-prim->GetMaterial().GetAbsorptionRate()*distance) *
                            trace(scene, Ray(intersectionPoint, z), depth + 1);
                    }
                    else
                        color = color +
                            prim->GetMaterial().GetRefraction() * trace(scene, Ray(intersectionPoint, z), depth + 1);
                }
            }
        }

        //reflection
        if (prim->GetMaterial().GetReflection() > 0)
        {
            const Vector3 a = ray.GetDirection();
            Vector3 newA = a - 2 * (Dot(a,n)) * n;
            color = color + prim->GetMaterial().GetReflection() * trace(scene, Ray(intersectionPoint, newA), depth + 1);
        }
    }
    return color;
}

Engine::Engine(SDLScreen& screen)
    :m_screen(screen)
{
}

void Engine::Init(const std::string& filename)
{
    m_scene.LoadFromFile(filename);
}

void Engine::Calculate()
{
    const int max = Width * Height;
    const double cellWidth = 0.005;
    const double cellHeight = 0.005;
    const Vector3 origin(0.0,0.0,-5.0);

    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            Vector3 a;
            a.x = 1.0 * cellWidth * (i - Width/2);
            a.y = -1.0 * cellHeight * (j - Height/2);
            a.z = 0.0;

            a = a - origin;
            a.Normalize();

            Ray ray(origin, a);
            m_image[i][j] = trace(m_scene, ray, 0);
            m_progress++;

            int part = (m_progress*100/max);
            if (part*max == (m_progress*100))
            {
                if ((part/5)*5 == part)
                {
                    std::ostringstream caption;
                    caption << part << "%";
                    m_screen.SetCaption(caption.str());
                }
            }
        }
    }
}

void Engine::Draw()
{
    for (int i = 0; i < Width; i++)
        for (int j = 0; j < Height; j++)
        {
            m_screen.SetPixel(i,j,m_image[i][j]);
        }

    m_screen.Flip();
}


void Engine::WaitForQuit()
{
    bool quit = false;
    SDL_Event event;
    while (not quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }
}

Engine::~Engine()
{}

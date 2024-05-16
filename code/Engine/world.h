#pragma once
#include "Vector2D.h"
#include "actor.h"
#include "timer.h"
#include <unordered_set>
#include <vector>

class World final
{
public:
    Timer timer;
    friend class Engine;
    std::unordered_set< Actor * > GameActors;
    std::vector< Actor * > GameActors_to_add;
    std::unordered_set< Actor * > GameActors_to_delete;

    void Update();
    void Render();
    void Input();
};
extern World main_world;

class GameStatics final
{
public:
    template < typename T >
    static T *createActor(Vector2D pos = Vector2D(0, 0));
};

template < typename T > inline T *GameStatics::createActor(Vector2D pos)
{
    T *pActor = new T;
    if (pActor && static_cast< Actor * >(pActor))
    {
        main_world.GameActors_to_add.push_back(pActor);
        pActor->setLocalPosition(pos);
        // play
        return pActor;
    }
    return nullptr;
}
#include "Vector2D.h"
#include "actor.h"
#include "attack.h"
#include "collider.h"
#include "enemy.h"
#include "enemy_move.h"
#include "game_map.h"
#include "property.h"
#include "say.h"
#include "timer.h"
#include "tower.h"
#include "world.h"
#include <thread>
class Engine
{
public:
    static Enemy *enemy;

    static void Init();
    static void Update();
    static void End();
};

extern World main_world;

int main()
{
    Engine::Init();
    Engine::Update();
    Engine::End();
    return 0;
}

void Engine::Init()
{
    main_world.game_map = new GameMap(13, 5);

    Tower *tower = GameStatics::createActor< Tower >(Vector2D(0, 0));
    tower->getComponentByClass< Property >()->setType(0);
    tower->constructComponent< Say >();
    tower->constructComponent< Collider >()->init();
    tower->constructComponent< Attack >()->init();
    tower->getComponentByClass< Property >()->addAttackRange(
        {Vector2D(-PPU / 2, -PPU * 3 / 2),
         Vector2D(19 * PPU / 2, PPU * 3 / 2)});

    Enemy *enemy = GameStatics::createActor< Enemy >(Vector2D(6 * PPU, 0));
    EnemyMove *em = enemy->constructComponent< EnemyMove >();
    em->init();
    Property *ep = enemy->getComponentByClass< Property >();
    ep->addRoutePoint(Vector2D(-10 * PPU, 0));
    ep->setCurrentVelocity(ep->getVelocity());
    ep->addAttackRange(
        {Vector2D(-PPU / 2, -PPU / 2), Vector2D(PPU / 2, PPU / 2)});
    enemy->constructComponent< Say >();
    enemy->constructComponent< Collider >()->init();
    enemy->constructComponent< Attack >()->init();

    main_world.timer.start_timer();
}

void render()
{
    main_world.Render();
}

void update()
{
    main_world.Update();
}

void input()
{
    main_world.Input();
}

void add()
{
    if (!main_world.GameActors_to_add.empty())
    {
        for (auto &pActor : main_world.GameActors_to_add)
            main_world.GameActors.insert(pActor);
    }
    main_world.GameActors_to_add.clear();
}

void trash()
{
    if (!main_world.GameActors_to_delete.empty())
    {
        for (auto &pActor : main_world.GameActors_to_delete)
        {
            pActor->~Actor();
            for (auto &toremove : main_world.GameActors)
            {
                if (toremove == pActor)
                    main_world.GameActors.erase(toremove);
            }
        }
    }
    main_world.GameActors_to_delete.clear();
}

void Engine::Update()
{
    std::cout << "updating\n";
    std::thread ad(
        [](void) -> void
        {
            main_world.timer.fixedExecute(add);
        });
    std::thread rend(
        [](void) -> void
        {
            main_world.timer.fixedExecute(render);
        });
    std::thread upd(
        [](void) -> void
        {
            main_world.timer.fixedExecute(update);
        });
    std::thread inp(
        [](void) -> void
        {
            main_world.timer.fixedExecute(input);
        });
    std::thread tra(
        [](void) -> void
        {
            main_world.timer.fixedExecute(trash);
        });
    ad.join();
    rend.join();
    upd.join();
    inp.join();
    tra.join();
}

void Engine::End()
{
    for (auto pActor : main_world.GameActors)
        pActor->Destroy();
    main_world.GameActors.clear();
    if (!main_world.GameActors_to_delete.empty())
    {
        for (auto &pActor : main_world.GameActors_to_delete)
            delete pActor;  // ~Actor
    }
    main_world.GameActors_to_delete.clear();
    delete main_world.game_map;
}

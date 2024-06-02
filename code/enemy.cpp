#include "enemy.h"
#include "attack.h"
#include "buff_manager.h"
#include "collider.h"
#include "enemy_move.h"
#include "loader.h"
#include "property.h"
#include "say.h"

Enemy::Enemy()
{
    constructComponent< Property >();
}

void Enemy::Update()
{
    Actor::Update();
}

void Enemy::init(int i)
{
    Property *property = getComponentByClass< Property >();
    property->setID(i);
    Loader::getEnemy(i, property);
    constructComponent< EnemyMove >()->init();
    constructComponent< Collider >()->init();
    constructComponent< Attack >()->init();
    constructComponent< Say >();
    constructComponent< BuffManager >()->init();
}
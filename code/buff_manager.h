#pragma once
#include "actor.h"
#include "component.h"
#include "property.h"
#include "world.h"
#include <string>

extern World *main_world;

class BuffManager : public Component
{
private:
    Property *property;
public:
    void init()
    {
        property = pOwner->getComponentByClass< Property >();
    }
    void Update() {}
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }
    void addBuff()
    {
        if (get_random() <= 50)
        {
            int buff_type = get_random(1, 4);
            switch (buff_type)
            {
            case 1:
                property->setBuff(addHP);
                property->setMaxHP(property->getMaxHP() * 2);
                property->setCurHP(property->getMaxHP());
                break;
            case 2:
                property->setBuff(addDMG);
                property->setMaxDMG(property->getMaxDMG() * 2);
                property->setCurDMG(property->getMaxDMG());
                break;
            case 3:
                property->setBuff(addVelocity);
                property->setVelocity(property->getVelocity() * 2);
                property->setCurrentVelocity(property->getVelocity());
                break;
            case 4:
                property->setBuff(quickAttack);
                property->setAttackInterval(property->getAttackInterval() / 2);
                break;
            default: break;
            }
        }
    }
    static void setBuffforTower(Actor *pTower, int type)
    {
        if (pTower == nullptr)
            return;
        Property *property = pTower->getComponentByClass< Property >();
        if (property->getBuff() == Empty)
        {
            property->setBuff((BuffType)type);
            main_world->number_of_buff[type]--;
            switch (type)
            {
            case 1:
                property->setBuff(addHP);
                property->setMaxHP(property->getMaxHP() * 2);
                property->setCurHP(property->getMaxHP());
                break;
            case 2:
                property->setBuff(addDMG);
                property->setMaxDMG(property->getMaxDMG() * 2);
                property->setCurDMG(property->getMaxDMG());
                break;
            case 3:
                property->setBuff(addVelocity);
                property->setVelocity(property->getVelocity() * 2);
                property->setCurrentVelocity(property->getVelocity());
                break;
            case 4:
                property->setBuff(quickAttack);
                property->setAttackInterval(property->getAttackInterval() / 2);
                break;
            default: break;
            }
        }
    }
};
#pragma once
#include <string>
#include <typeinfo>

class Base  // 基类
{
    static long long tag;
protected:
    std::string name;
public:
    Base()
    {
        tag++;
        name = typeid(this).name() + std::string(" ") + std::to_string(tag);
    }
    virtual ~Base()
    {
        tag--;
    }
    std::string getName() const
    {
        return name;
    }
    void setName(const std::string &name)
    {
        this->name = name;
    }

    virtual void Update() = 0;
};
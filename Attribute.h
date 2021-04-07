#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "Goal.h"

template <typename enumType>
class Attribute : public Goal   {

private:
    int ruleNumber;

public:
    Attribute(int number = -1) : ruleNumber(number) {}

    int getNumber() override {
        return ruleNumber;
    }

    bool isActual() override    {
        return true;
    }

    std::string returnType() override    {
        std::string s = static_cast<std::string>("a ") + typeid (enumType).name();
        s.erase(std::remove_if(std::begin(s), std::end(s),
                                   [](auto ch) { return std::isdigit(ch);}));
        return s;

    }


    void setNumber(uint number) override {}

    void setActual() override   {}
};


#endif // ATTRIBUTE_H

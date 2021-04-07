#ifndef RULE_H
#define RULE_H
#include "Goal.h"

#include <iostream>
#include <boost/optional.hpp>
using boost::optional;
using boost::none;


template <typename enumType>
class Rule : public Goal    {

private:
     uint number;               // this rule's number
     enumType conclusion;
     race r;                    // these are attributes' values
     isAlive a;
     posNeg pN;
     status stat;
     realm rr;
     activity act;
     bool actualVector[6];          // actual components on the lefthand side
     bool isActualRule;

public:


     Rule(enumType conclusion, uint number, race r = race::undefinedRace,
          isAlive a = isAlive::undefinedIsAlive, posNeg p = posNeg::undefinedPosNeg, status stat = status::undefinedStatus,
          realm rr = realm::undefinedRealm, activity act = activity::undefinedActivity) :
         number(number) , conclusion(conclusion), r(r), a(a), pN(p), stat(stat), rr(rr), act(act), isActualRule(true)
     {

         for (int i =0; i<6; ++i)
             actualVector[i] = true;

         if (this->r == race::undefinedRace)
             actualVector[0] = false;
         if (this->a == isAlive::undefinedIsAlive)
             actualVector[1] = false;
         if (this->pN == posNeg::undefinedPosNeg)
             actualVector[2] = false;
         if (this->stat == status::undefinedStatus)
             actualVector[3] = false;
         if (this->rr == realm::undefinedRealm)
             actualVector[4] = false;
         if (this->act == activity::undefinedActivity)
             actualVector[5] = false;
     }

     void setNumber(uint number) override   {
         this->number = number;
     }

     int getNumber() override  {
         return number;
     }


     enumType getConclusion()   {
         return conclusion;
     }

     int checkRule(optional<race> r, optional<isAlive> a, optional<posNeg> curP, optional<status> curStat,
                   optional<realm> curRealm, optional<activity> curAct)   {              // values are passed






         bool checkTrueVal = true;
         // check if all these values are defined
         if (actualVector[0])
         {
             if (r == none)
                     return -1;
            checkTrueVal &= this->r == r;
          }

         if (!checkTrueVal)
             return 0;


         if (actualVector[1])   {
             if (a == none)
                return -2;
             checkTrueVal &= this->a == a;
         }

         if (!checkTrueVal)
             return 0;


         if (actualVector[2])   {
             if (curP == none)
                return -3;
             checkTrueVal &= this->pN == curP;
         }

         if (!checkTrueVal)
             return 0;


         if (actualVector[3])   {
             if (curStat == none)
                return -4;
             checkTrueVal &= this->stat == curStat;
         }

         if (!checkTrueVal)
             return 0;

         if (actualVector[4])   {
             if (curRealm == none)
                return -5;
             checkTrueVal &= this->rr == curRealm;
         }

         if (!checkTrueVal)
             return 0;


         if (actualVector[5])   {
             if (curAct == none)
                return -6;
             checkTrueVal &= this->act == curAct;
         }

         if (!checkTrueVal)
             return 0;


         return 1;

     }


     bool checkRuleUndefined(optional<race> r, optional<isAlive> a, optional<posNeg> curP, optional<status> curStat,
                   optional<realm> curRealm, optional<activity> curAct)   {

         bool checkTrue = true;
         if (r)
             checkTrue &= r == this->r;
         if (a)
             checkTrue &= a == this->a;
         if (curP)
             checkTrue &= curP == this->pN;
         if (curStat)
             checkTrue &= curStat == this->stat;
         if (curRealm)
             checkTrue &= curRealm == this->rr;
         else if (rr == realm::undefinedRealm)
             return false;
         if (curAct)
             checkTrue &= curAct == this->act;
         return checkTrue;
     }

     std::string returnType() override {
           std::string s = static_cast<std::string>("r ") + typeid(enumType).name();
           s.erase(std::remove_if(std::begin(s), std::end(s),
                                      [](auto ch) { return std::isdigit(ch);}));
           return s;
     }

     bool isActual() override    {
         return isActualRule;
     }

     void tossAway()    {
         isActualRule = false;
     }


     void setActual() override   {

         isActualRule = true;

     }



};





#endif // RULE_H

#ifndef ANSWERCHECK_H_INCLUDED
#define ANSWERCHECK_H_INCLUDED
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <algorithm>
#include "CreatDigraph.h"

class AnswerCheck
{
public:
    AnswerCheck(){ }
    ~AnswerCheck(){ }

    bool checkLink(CreatDigraph mycreatdigraph, string answerpath)
{
    string answer;
    ifstream inputAnswer(answerpath,ifstream::in);
    while(getline(inputAnswer,answer))
    {
        char filter;
        int car_ID;
        int car_speed;
        istringstream istringanswer(answer);
        istringanswer>>filter;
        istringanswer>>car_ID;
        istringanswer>>filter;
        istringanswer>>car_speed;
        int firstCross = mycreatdigraph.getCar(car_ID-mycreatdigraph.getCar(0).m_id).m_from;
        int lastCross = mycreatdigraph.getCar(car_ID-mycreatdigraph.getCar(0).m_id).m_to;
        int centreCross = firstCross;
        while(istringanswer>>filter)
        {
            if(centreCross==lastCross)
                break;
            if(filter==')')
                break;
            int road_ID;
            istringanswer>>road_ID;
            int cfirstCross = mycreatdigraph.getRoad(road_ID-mycreatdigraph.getRoad(0).m_id).m_from;
            int csecondCross = mycreatdigraph.getRoad(road_ID-mycreatdigraph.getRoad(0).m_id).m_to;
            if(cfirstCross==centreCross)
            {
                centreCross = csecondCross;
            }
            else if(csecondCross==centreCross)
            {
                centreCross = cfirstCross;
            }
            else
            {
                cout<<"------------"<<car_ID<<"------------"<<endl;
                cout<<"------------"<<road_ID<<"------------"<<endl;
                return false;
            }
        }
        if(centreCross!=lastCross)
        {
            cout<<"------------"<<car_ID<<"------------"<<endl;
            return false;
        }
    }
    return true;
}
};



#endif // ANSWERCHECK_H_INCLUDED

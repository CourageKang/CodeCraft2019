#include "lib/AnswerCheck.h"

//bool AnswerCheck::checkLink(CreatDigraph mycreatdigraph)
//{
//    string answer;
//    ifstream inputAnswer("../config/answer.txt",ifstream::in);
//    while(getline(inputAnswer,answer))
//    {
//        ofstream outerror("./error.txt",ofstream::out);
//        outerror<<"------------------------------------"<<endl;
//        char filter;
//        int car_ID;
//        int car_speed;
//        istringstream istringanswer(answer);
//        istringanswer>>filter;
//        istringanswer>>car_ID;
//        istringanswer>>filter;
//        istringanswer>>car_speed;
//        int firstCross = mycreatdigraph.getCar(car_ID-mycreatdigraph.getCar(0).m_id).m_from;
//        int lastCross = mycreatdigraph.getCar(car_ID-mycreatdigraph.getCar(0).m_id).m_to;
//        int centreCross = firstCross;
//        while(istringanswer>>filter)
//        {
//            if(centreCross==lastCross)
//                break;
//            if(filter==')')
//                break;
//            int road_ID;
//            istringanswer>>road_ID;
//            int cfirstCross = mycreatdigraph.getRoad(road_ID-mycreatdigraph.getRoad(0).m_id).m_from;
//            int csecondCross = mycreatdigraph.getRoad(road_ID-mycreatdigraph.getRoad(0).m_id).m_to;
//            outerror<<cfirstCross<<" "<<csecondCross<<" "<<centreCross<<endl;
//            if(cfirstCross==centreCross)
//            {
//                centreCross = csecondCross;
//            }
//            else if(csecondCross==centreCross)
//            {
//                centreCross = cfirstCross;
//            }
//            else
//            {
//                outerror<<"------------"<<car_ID<<"------------"<<endl;
//                outerror<<"------------"<<road_ID<<"------------"<<endl;
//                return false;
//            }
//            outerror<<cfirstCross<<" "<<csecondCross<<" "<<centreCross<<endl;
//        }
//        if(centreCross!=lastCross)
//        {
//            outerror<<"------------"<<car_ID<<"------------"<<endl;
//            return false;
//        }
//        outerror.close();
//    }
//    return true;
//}

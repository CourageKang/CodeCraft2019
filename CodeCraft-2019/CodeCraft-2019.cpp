#include "iostream"
#include <fstream>
#include <sstream>
#include "lib/Node.h"
#include "lib/cMap.h"
#include "lib/CreatDigraph.h"
#include "lib/Floyd.h"
#include "lib/AnswerCheck.h"

int main(int argc, char *argv[])
{
  std::cout << "Begin" << std::endl;

    if(argc < 5){
        std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
        exit(1);
    }

    std::string carPath(argv[1]);
    std::string roadPath(argv[2]);
    std::string crossPath(argv[3]);
    std::string answerPath(argv[4]);

    std::cout << "carPath is " << carPath << std::endl;
    std::cout << "roadPath is " << roadPath << std::endl;
    std::cout << "crossPath is " << crossPath << std::endl;
    std::cout << "answerPath is " << answerPath << std::endl;

//	string carPath = "../config/car.txt";
//	string roadPath = "../config/road.txt";
//	string crossPath = "../config/cross.txt";
//	string answerPath = "../config/answer.txt";


    CreatDigraph mycreatdigraph;
    //mycreatdigraph.test();

    //get VecCar
    string strCar;
    std::ifstream inputCar;
    inputCar.open(carPath,std::ifstream::in);
    std::getline(inputCar,strCar);
    while(std::getline(inputCar,strCar))
    {
        std::istringstream record(strCar);
        char c1,c2,c3,c4,c5,c6;
        int a,b,c,d,e;
        record>>c1>>a>>c2>>b>>c3>>c>>c4>>d>>c5>>e>>c6;
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
        mycreatdigraph.addCar(a,b,c,d,e);
        cout<<strCar<<endl;
    }

    //get VecCross
    string strCross;
    std::ifstream inputCross;
    inputCross.open(crossPath,std::ifstream::in);
    std::getline(inputCross,strCross);
    while(std::getline(inputCross,strCross))
    {
        std::istringstream record(strCross);
        char c1,c2,c3,c4,c5,c6;
        int a,b,c,d,e;
        record>>c1>>a>>c2>>b>>c3>>c>>c4>>d>>c5>>e>>c6;
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
        mycreatdigraph.addCross(a,b,c,d,e);
        cout<<strCross<<endl;
    }

    //get VecRoad
    string strRoad;
    std::ifstream inputRoad;
    inputRoad.open(roadPath,std::ifstream::in);
    std::getline(inputRoad,strRoad);
    while(std::getline(inputRoad,strRoad))
    {
        std::istringstream record(strRoad);
        char c1,c2,c3,c4,c5,c6,c7,c8;
        int a,b,c,d,e,f,g;
        record>>c1>>a>>c2>>b>>c3>>c>>c4>>d>>c5>>e>>c6>>f>>c7>>g>>c8;
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<g<<endl;
        mycreatdigraph.addRoad(a,b,c,d,e,f,g);
        cout<<strRoad<<endl;
    }

    //get the route corresponding to the speed
    cout<<"----get the route corresponding to the speed:begin----"<<endl;
    Floyd myfloyd;
    //myfloyd.test(mycreatdigraph);
    myfloyd.getNumPath(mycreatdigraph);
    cout<<"----get the route corresponding to the speed:end----"<<endl;

    //extract the speed and time slice of the vehicle set
    cout<<"----extract the speed and time slice of the vehicle set:begin----"<<endl;
    mycreatdigraph.classifySpeedCars();
    cout<<"----extract the speed and time slice of the vehicle set:end----"<<endl;

    //output answerPath
    cout<<"----output answerPath:begin----"<<endl;
    //mycreatdigraph.printPaths();
    mycreatdigraph.printNumAnswer(answerPath);
    cout<<"----output answerPath:end----"<<endl;

//    //优化重复
//    cout<<"----optimize path:begin----"<<endl;
//    mycreatdigraph.optiPath();
//    cout<<"----optimize path:end----"<<endl;

//    //output optimization answerPath
//    cout<<"----output optimization answerPath:begin----"<<endl;
//    mycreatdigraph.printOptiNumAnswer(answerPath);
//    cout<<"----output optimization answerPath:end----"<<endl;

    //验证路径
    cout<<"----check path:begin----"<<endl;
    AnswerCheck myanswercheck;
    bool IsRight = myanswercheck.checkLink(mycreatdigraph,answerPath);
    if(!IsRight)
    {
        cout<<"----Error Result----"<<endl;
    }
    else
    {
        cout<<"----Right Result----"<<endl;
    }
    cout<<"----check path:end----"<<endl;

    system("pause");
	return 0;
}

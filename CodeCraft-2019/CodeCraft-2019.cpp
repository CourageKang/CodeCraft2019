#include "iostream"
#include <fstream>
#include <sstream>
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

//    string carPath = "../config/car.txt";
//    string roadPath = "../config/road.txt";
//    string crossPath = "../config/cross.txt";
//    string answerPath = "../config/answer.txt";


    CreatDigraph mycreatdigraph;

    //get VecCar0
    string strCar;
    std::ifstream inputCar;

    inputCar.open(carPath,std::ifstream::in);
    std::getline(inputCar,strCar);
    int carid = 1;
    while(std::getline(inputCar,strCar))
    {
        std::istringstream record(strCar);
        char c1,c2,c3,c4,c5,c6;
        int a,b,c,d,e;
        record>>c1>>a>>c2>>b>>c3>>c>>c4>>d>>c5>>e>>c6;
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
        mycreatdigraph.MapCar1.insert(make_pair(carid,a));
        mycreatdigraph.MapCar2.insert(make_pair(a,carid));
        cout<<strCar<<endl;
        ++carid;
    }
    inputCar.close();

    //get VecCross0
    string strCross;
    std::ifstream inputCross;

    inputCross.open(crossPath,std::ifstream::in);
    std::getline(inputCross,strCross);
    int crossid = 1;
    while(std::getline(inputCross,strCross))
    {
        std::istringstream record(strCross);
        char c1,c2,c3,c4,c5,c6;
        int a,b,c,d,e;
        record>>c1>>a>>c2>>b>>c3>>c>>c4>>d>>c5>>e>>c6;
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
        mycreatdigraph.MapCross1.insert(make_pair(crossid,a));
        mycreatdigraph.MapCross2.insert(make_pair(a,crossid));
        cout<<strCross<<endl;
        ++crossid;
    }
    inputCross.close();

    //get VecRoad0
    string strRoad;
    std::ifstream inputRoad;


    inputRoad.open(roadPath,std::ifstream::in);
    std::getline(inputRoad,strRoad);
    int roadid = 1;
    while(std::getline(inputRoad,strRoad))
    {
        std::istringstream record(strRoad);
        char c1,c2,c3,c4,c5,c6,c7,c8;
        int a,b,c,d,e,f,g;
        record>>c1>>a>>c2>>b>>c3>>c>>c4>>d>>c5>>e>>c6>>f>>c7>>g>>c8;
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<g<<endl;
        mycreatdigraph.MapRoad1.insert(make_pair(roadid,a));
        mycreatdigraph.MapRoad2.insert(make_pair(a,roadid));
        cout<<strRoad<<endl;
        ++roadid;
    }
    inputRoad.close();

    //get VecCar
    inputCar.open(carPath,std::ifstream::in);
    std::getline(inputCar,strCar);
    carid = 1;
    while(std::getline(inputCar,strCar))
    {
        std::istringstream record(strCar);
        char c1,c2,c3,c4,c5,c6;
        int a,b,c,d,e;
        record>>c1>>a>>c2>>b>>c3>>c>>c4>>d>>c5>>e>>c6;
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
        mycreatdigraph.addCar(carid,a,mycreatdigraph.MapCross2[b],mycreatdigraph.MapCross2[c],d,e);
        cout<<strCar<<endl;
        ++carid;
    }
    inputCar.close();

    //get VecCross
    inputCross.open(crossPath,std::ifstream::in);
    std::getline(inputCross,strCross);
    crossid = 1;
    while(std::getline(inputCross,strCross))
    {
        std::istringstream record(strCross);
        char c1,c2,c3,c4,c5,c6;
        int a,b,c,d,e;
        record>>c1>>a>>c2>>b>>c3>>c>>c4>>d>>c5>>e>>c6;
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
        if(b!=-1)
        {
            b=mycreatdigraph.MapRoad2[b];
        }
        if(c!=-1)
        {
            c=mycreatdigraph.MapRoad2[c];
        }
        if(d!=-1)
        {
            d=mycreatdigraph.MapRoad2[d];
        }
        if(e!=-1)
        {
            e=mycreatdigraph.MapRoad2[e];
        }
        mycreatdigraph.addCross(crossid,a,b,c,d,e);
        cout<<strCross<<endl;
        ++crossid;
    }
    inputCross.close();

    //get VecRoad
    inputRoad.open(roadPath,std::ifstream::in);
    std::getline(inputRoad,strRoad);
    roadid = 1;
    while(std::getline(inputRoad,strRoad))
    {
        std::istringstream record(strRoad);
        char c1,c2,c3,c4,c5,c6,c7,c8;
        int a,b,c,d,e,f,g;
        record>>c1>>a>>c2>>b>>c3>>c>>c4>>d>>c5>>e>>c6>>f>>c7>>g>>c8;
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<g<<endl;
        mycreatdigraph.addRoad(roadid,a,b,c,d,mycreatdigraph.MapCross2[e],mycreatdigraph.MapCross2[f],g);
        cout<<strRoad<<endl;
        ++roadid;
    }
    inputRoad.close();

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

    //优化重复
    cout<<"----optimize path:begin----"<<endl;
    mycreatdigraph.optiPath();
    cout<<"----optimize path:end----"<<endl;

    //output optimization answerPath
    cout<<"----output optimization answerPath:begin----"<<endl;
    mycreatdigraph.printOptiNumAnswer(answerPath);
    cout<<"----output optimization answerPath:end----"<<endl;

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

    //output optimization answerPath
    cout<<"----output optimization answerPath:begin----"<<endl;
    mycreatdigraph.printOptiDisorderNumAnswer(answerPath);
    cout<<"----output optimization answerPath:end----"<<endl;

    system("pause");
	return 0;
}

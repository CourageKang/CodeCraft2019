#ifndef CREATDIGRAPH_H_INCLUDED
#define CREATDIGRAPH_H_INCLUDED
#include"Node.h"
#include"cMap.h"
#include<set>
#include<vector>
#include<algorithm>
#include<fstream>

struct RoadState
{
    vector<int> m_waitCars;
    vector<int> m_stopCars;
    vector<vector<int>> pathMatrix;
};

struct Road
{
    Road(){
        m_id = 0;
        m_length  = 0;
        m_speed = 0;
        m_channel = 0;
        m_from = 0;
        m_to = 0;
        m_isDuplex = false;
    }
    Road(int a, int b, int c, int d, int e, int f, int g){
        m_id = a;
        m_length  = b;
        m_speed = c;
        m_channel = d;
        m_from = e;
        m_to = f;
        m_isDuplex = bool(g);
        for(int i = 0; i < b; ++i)
        {
            vector<int> temM;
            for(int j = 0; j < d; ++j)
            {
                temM.push_back(0);
            }
            m_roadstate.pathMatrix.push_back(temM);
        }
    }
    int m_id;
    int m_length;
    int m_speed;
    int m_channel;
    int m_from;
    int m_to;
    bool m_isDuplex;
    RoadState m_roadstate;
};

struct CarState
{
    CarState()
    {
        Isspeed = 0;
        IsFrom = 0;
        IsTo = 0;
        distance = 0;
        roadTab = 0;
        Isstart = false;
        Isend = false;
    }
    CarState(Road myroad, int isspeed, int isfrom, int isto, int dis, int roadtab, bool isstart, bool isend)
    {
        IsRoad = myroad;
        Isspeed = isspeed;
        IsFrom = isfrom;
        IsTo = isto;
        distance = dis;
        roadTab = roadtab;
        Isstart = isstart;
        Isend = isend;
    }
    Road IsRoad;
    int Isspeed;
    int IsFrom;
    int IsTo;
    int distance;
    int roadTab;
    bool Isstart;
    bool Isend;
};

struct Car
{
    Car(){
        m_id = 0;
        m_from = 0;
        m_to = 0;
        m_speed = 0;
        m_planTime = 0;
    }
    Car(int a, int b, int c, int d, int e){
        m_id = a;
        m_from = b;
        m_to = c;
        m_speed = d;
        m_planTime = e;
    }
    int m_id;
    int m_from;
    int m_to;
    int m_speed;
    int m_planTime;
    vector<int> VecRoadID;
    CarState m_carstate;
};

struct Cross
{
    Cross(){
        m_id = 0;
        m_roadID1 = 0;
        m_roadID2 = 0;
        m_roadID3 = 0;
        m_roadID4 = 0;

    }
    Cross(int a, int b, int c, int d, int e){
        m_id = a;
        m_roadID1 = b;
        m_roadID2 = c;
        m_roadID3 = d;
        m_roadID4 = e;

    }
    int m_id;
    int m_roadID1;
    int m_roadID2;
    int m_roadID3;
    int m_roadID4;

};


class CreatDigraph
{
public:
    CreatDigraph();
    ~CreatDigraph();

    //测试创建有向图，深度遍历和广度遍历
    void test();

    //从外界添加汽车，路口，跑道信息
    void addCar(int a, int b, int c, int d, int e);
    void addCross(int a, int b, int c, int d, int e);
    void addRoad(int a, int b, int c, int d, int e, int f, int g);

    //从外界获取汽车，路口，跑道信息
    Car getCar(int i_car) const;
    Cross getCross(int i_cross) const;
    Road getRoad(int i_road) const;

    //外界获取汽车，路口，跑道总数
    int getCarSize() const;
    int getCrossSize() const;
    int getRoadSize() const;

    //按车速分类
    void classifySpeedCars();

    void printPaths();     //输出Floyd算法求出的恒权重路线图
    void printVecPaths();  //输出Floyd算法求出的根据车速的变权重路线图

    void printVecAnswer(); //输出根据固定车速变化的变权重路线图，路线为路口点
    void printNumAnswer(string answerpath); //输出根据固定车速变化的变权重路线图，路线为道路图
    void printOptiNumAnswer(string answerpath); //输出根据固定车速变化的变权重路线图，路线为道路图

    //转换交点和道路
    vector<int> crosstoroad(int speed, int firstcross, int endcross);

    //降低复杂度
    void optiPath();

    //路径仿真优化
    void pathSimuOpti();

public:
    typedef std::vector<std::vector<std::vector<int>>> VecPath;
    std::vector<std::vector<std::vector<int>>> m_paths;
    std::vector<VecPath> m_vecpaths;

private:
    std::vector<Car> VecCar;
    std::vector<Cross> VecCross;
    std::vector<Road> VecRoad;

    std::vector<std::set<int>> VecTimeCars;   //each timeslice cars
    std::vector<std::set<int>> VecSpeedCars;  //each speedslice cars
};

#endif // CREATDIGRAPH_H_INCLUDED

#ifndef CREATDIGRAPH_H_INCLUDED
#define CREATDIGRAPH_H_INCLUDED
#include"Node.h"
#include"cMap.h"
#include<vector>
#include<algorithm>
#include<fstream>
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
    }
    int m_id;
    int m_length;
    int m_speed;
    int m_channel;
    int m_from;
    int m_to;
    bool m_isDuplex;

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

    void printPaths();     //输出Floyd算法求出的恒权重路线图
    void printVecPaths();  //输出Floyd算法求出的根据车速的变权重路线图

    void printVecAnswer(); //输出根据固定车速变化的变权重路线图，路线为路口点
    void printNumAnswer(string answerpath); //输出根据固定车速变化的变权重路线图，路线为道路图

public:
    typedef std::vector<std::vector<std::vector<int>>> VecPath;
    std::vector<std::vector<std::vector<int>>> m_paths;
    std::vector<VecPath> m_vecpaths;

private:
    std::vector<Car> VecCar;
    std::vector<Cross> VecCross;
    std::vector<Road> VecRoad;


};

#endif // CREATDIGRAPH_H_INCLUDED

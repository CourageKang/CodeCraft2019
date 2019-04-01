#ifndef FLOYD_H_INCLUDED
#define FLOYD_H_INCLUDED

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include "CreatDigraph.h"

class Floyd{
public:
    Floyd();
    ~Floyd();

    //读取道路和路口信息，根据车速计算权重
    void ReadDate(const CreatDigraph &mycreatdigraph);
    void ReadDate(const CreatDigraph &mycreatdigraph,int myspeed);
    void ReadDate(const CreatDigraph &mycreatdigraph, Car mycar);
    //运行Floyd算法
    void runFloyd();

    //输出路口路线图
    void PrintResult(CreatDigraph &mycreatdigraph);
    //控制台测试流程
    void test(CreatDigraph &mycreatdigraph);

    void getPath(CreatDigraph &mycreatdigraph, Car mycar);   //流程计算 获取对应的每辆车的权重 Folyd地图 数据庞大
    void getVecPath(CreatDigraph &mycreatdigraph);

    void getPath(CreatDigraph &mycreatdigraph, int myspeed); //流程计算 获取对应车速的权重 Folyd地图
    void getNumPath(CreatDigraph &mycreatdigraph);
public:
    MGraph mGraph;
    int *iArrPath[MAX_VALUE];
};


#endif // FLOYD_H_INCLUDED

#include "lib/CreatDigraph.h"


CreatDigraph::CreatDigraph()
{

}

CreatDigraph::~CreatDigraph()
{

}

//cMap.h
//测试创建有向图，深度遍历和广度遍历
void CreatDigraph::test()
{
    cMap *pMap = new cMap(8);

	Node *pNodeA = new Node('A');
	Node *pNodeB = new Node('B');
	Node *pNodeC = new Node('C');
	Node *pNodeD = new Node('D');
	Node *pNodeE = new Node('E');
	Node *pNodeF = new Node('F');
	Node *pNodeG = new Node('G');
	Node *pNodeH = new Node('H');

	pMap->addNode(pNodeA);
	pMap->addNode(pNodeB);
	pMap->addNode(pNodeC);
	pMap->addNode(pNodeD);
	pMap->addNode(pNodeE);
	pMap->addNode(pNodeF);
	pMap->addNode(pNodeG);
	pMap->addNode(pNodeH);
	//
	pMap->setValueToMatrixForUndirectedGraph(0, 1);
	pMap->setValueToMatrixForUndirectedGraph(0, 3);
	pMap->setValueToMatrixForUndirectedGraph(1, 2);
	pMap->setValueToMatrixForUndirectedGraph(1, 5);
	pMap->setValueToMatrixForUndirectedGraph(3, 6);
	pMap->setValueToMatrixForUndirectedGraph(3, 7);
	pMap->setValueToMatrixForUndirectedGraph(6, 7);
	pMap->setValueToMatrixForUndirectedGraph(2, 4);
	pMap->setValueToMatrixForUndirectedGraph(4, 5);

    pMap->printMatrix();

	cout<<endl;
	pMap->depthFirstTraverse(0);

	pMap->resetNode();
	cout << endl;
	pMap->breadthFirstTraverse(0);
}

//从外界添加汽车，路口，跑道信息
void CreatDigraph::addCar(int a, int b, int c, int d, int e)
{
    Car mycar(a, b, c, d, e);
    VecCar.push_back(mycar);
}

void CreatDigraph::addCross(int a, int b, int c, int d, int e)
{
    Cross mycross(a, b, c, d, e);
    VecCross.push_back(mycross);
}

void CreatDigraph::addRoad(int a, int b, int c, int d, int e, int f, int g)
{
    Road myroad(a, b, c, d, e, f, g);
    VecRoad.push_back(myroad);
}

//从外界获取汽车，路口，跑道信息
Car CreatDigraph::getCar(int i_car) const
{
    if( i_car<VecCar.size() && i_car>=0 )
        return VecCar[i_car];
    else
        cout<<"invariale num"<<endl;
}

Cross CreatDigraph::getCross(int i_cross) const
{
    if( i_cross<VecCross.size() && i_cross>=0 )
        return VecCross[i_cross];
    else
        cout<<"invariale num"<<endl;
}

Road CreatDigraph::getRoad(int i_road) const
{
    if( i_road<VecRoad.size() && i_road>=0 )
        return VecRoad[i_road];
    else
        cout<<"invariale num"<<endl;

}

//外界获取汽车，路口，跑道总数
int CreatDigraph::getCarSize() const
{
    return VecCar.size();
}

int CreatDigraph::getCrossSize() const
{
    return VecCross.size();
}

int CreatDigraph::getRoadSize() const
{
    return VecRoad.size();
}

void CreatDigraph::classifySpeedCars()
{
    VecSpeedCars.reserve(11);
    for(int i = 0; i < 11; ++i)
    {
        std::set<int> temset;
        VecSpeedCars.push_back(temset);
    }
    cout<<"*********************"<<endl;
    for(int i_car = 0; i_car < VecCar.size(); ++i_car)
    {
        if(VecCar[i_car].m_speed<=10)
        {
            VecSpeedCars[VecCar[i_car].m_speed].insert(VecCar[i_car].m_id);
        }
        else
        {
            VecSpeedCars[10].insert(VecCar[i_car].m_id);
        }
    }
    cout<<"*********************"<<endl;
    int num = 0;
    int timeSlice = 1;
    int temSpeed[10] = {0};
    vector<set<int>> TimeCars;
    for(int i_TimeCars = 0; i_TimeCars < 10; ++i_TimeCars)
    {
        set<int> tem;
        TimeCars.push_back(tem);
    }
    set<int> timecars;
    for(int i_set = 10; i_set >= 0; --i_set)
    {
        std::set<int>::iterator iterset = VecSpeedCars[i_set].begin();
        for(; iterset != VecSpeedCars[i_set].end(); ++iterset)
        {
//            VecCar[*iterset-VecCar[0].m_id].m_planTime = max(timeSlice,VecCar[*iterset-VecCar[0].m_id].m_planTime);
//            timecars.insert(VecCar[*iterset-VecCar[0].m_id].m_id);
//            ++num;
//            if(i_set>6)
//            {
//                if(num == 14)
//                {
//                    num = 0;
//                    VecTimeCars.push_back(timecars);
//                    timecars.clear();
//                    ++timeSlice;
//                }
//            }
//            else if(i_set>=3)
//            {
//                if(num == 13)
//                {
//                    num = 0;
//                    VecTimeCars.push_back(timecars);
//                    timecars.clear();
//                    ++timeSlice;
//                }
//            }
//            else
//            {
//                if(num == 12)
//                {
//                    num = 0;
//                    VecTimeCars.push_back(timecars);
//                    timecars.clear();
//                    ++timeSlice;
//                }
//            }


            if(timeSlice >= VecCar[*iterset-VecCar[0].m_id].m_planTime)
            {
                VecCar[*iterset-VecCar[0].m_id].m_planTime = timeSlice;
                ++num;
                timecars.insert(VecCar[*iterset-VecCar[0].m_id].m_id);
            }
            else
            {
                VecCar[*iterset-VecCar[0].m_id].m_planTime = VecCar[*iterset-VecCar[0].m_id].m_planTime;
                ++temSpeed[VecCar[*iterset-VecCar[0].m_id].m_planTime-1];
                TimeCars[VecCar[*iterset-VecCar[0].m_id].m_planTime-1].insert(VecCar[*iterset-VecCar[0].m_id].m_id);
            }

            if(i_set>6)
            {
                if(num >= 20)
                {
                    num = 0;
                    if(timeSlice<11)
                    {
                        num = temSpeed[timeSlice-1];
                        VecTimeCars.push_back(timecars);
                        timecars.clear();
                        timecars = TimeCars[timeSlice];
                    }
                    else
                    {
                        num = 0;
                        VecTimeCars.push_back(timecars);
                        timecars.clear();
                    }
                    ++timeSlice;
                }
            }
            else if(i_set>=3)
            {
                if(num >= 20)
                {
                    num = 0;
                    if(timeSlice<11)
                    {
                        num = temSpeed[timeSlice-1];
                        VecTimeCars.push_back(timecars);
                        timecars.clear();
                        timecars = TimeCars[timeSlice-1];
                    }
                    else
                    {
                        num = 0;
                        VecTimeCars.push_back(timecars);
                        timecars.clear();
                    }
                    ++timeSlice;
                }
            }
            else
            {
                if(num >= 12)
                {
                    num = 0;
                    if(timeSlice<11)
                    {
                        num = temSpeed[timeSlice-1];
                        VecTimeCars.push_back(timecars);
                        timecars.clear();
                        timecars = TimeCars[timeSlice];
                    }
                    else
                    {
                        num = 0;
                        VecTimeCars.push_back(timecars);
                        timecars.clear();
                    }
                    ++timeSlice;
                }
            }

//            if(timeSlice >= VecCar[*iterset-VecCar[0].m_id].m_planTime)
//            {
//                VecCar[*iterset-VecCar[0].m_id].m_planTime = timeSlice;
//                ++num;
//            }
//            else
//            {
//                VecCar[*iterset-VecCar[0].m_id].m_planTime = VecCar[*iterset-VecCar[0].m_id].m_planTime;
//                ++temSpeed[VecCar[*iterset-VecCar[0].m_id].m_planTime-1];
//            }
//
//            if(num == 12)
//            {
//                ++timeSlice;
//                if(timeSlice<11)
//                    num = temSpeed[timeSlice-1];
//                else
//                    num = 0;
//            }
        }
    }
}


//输出Floyd算法求出的恒权重路线图
void CreatDigraph::printPaths()
{
    std::ofstream outputPaths("m_Paths.txt",std::ofstream::out);
    for(int i = 0; i < m_paths.size(); ++i)
    {
        for(int j = 0; j < m_paths[i].size(); ++j)
        {
            for(int k = 0; k < m_paths[i][j].size(); ++k)
            {
                outputPaths<<" "<<m_paths[i][j][k];
            }
            outputPaths<<endl;
        }
        outputPaths<<endl;
    }
    outputPaths.close();
}

//输出Floyd算法求出的根据车速的变权重路线图
void CreatDigraph::printVecPaths()
{
    std::ofstream outputPaths("m_VecPaths.txt",std::ofstream::out);
    for(int h = 0; h < m_vecpaths.size(); ++h)
    {
        outputPaths<<"------------the "<<h+1<<" car------------"<<endl;
        for(int i = 0; i < m_vecpaths[h].size(); ++i)
        {
            for(int j = 0; j < m_vecpaths[h][i].size(); ++j)
            {
                for(int k = 0; k < m_vecpaths[h][i][j].size(); ++k)
                {
                    outputPaths<<" "<<m_vecpaths[h][i][j][k];
                }
                outputPaths<<endl;
            }
            outputPaths<<endl;
        }
        outputPaths<<"------------the "<<h+1<<" car------------"<<endl;
    }
    outputPaths.close();
}

//输出根据固定车速变化的变权重路线图，路线为路口点
void CreatDigraph::printVecAnswer()
{
    std::ofstream outputanswer("../config/answer.txt",std::ifstream::out);
    for(int i_car = 0; i_car < VecCar.size(); ++i_car)
    {
        outputanswer<<"("<<VecCar[i_car].m_id<<", "<<1;
        for(int j = 0; j < m_vecpaths[i_car][VecCar[i_car].m_from-1][VecCar[i_car].m_to-1].size(); ++j)
        {
            outputanswer<<", "<<m_vecpaths[i_car][VecCar[i_car].m_from-1][VecCar[i_car].m_to-1][j];
        }
        outputanswer<<")"<<endl;
    }
    outputanswer.close();
}

//输出根据固定车速变化的变权重路线图，路线为道路图
void CreatDigraph::printNumAnswer(string answerpath)
{
    std::ofstream outputanswer(answerpath,std::ifstream::out);
    for(int i_car = 0; i_car < VecCar.size(); ++i_car)
    {
        outputanswer<<"("<<VecCar[i_car].m_id<<", "<<VecCar[i_car].m_planTime/*+i_car/11*/;
        for(int j = 0; j < m_vecpaths[VecCar[i_car].m_speed-1][VecCar[i_car].m_from-1][VecCar[i_car].m_to-1].size()-1; ++j)
        {
            int num_a = m_vecpaths[VecCar[i_car].m_speed-1][VecCar[i_car].m_from-1][VecCar[i_car].m_to-1][j];
            int num_b = m_vecpaths[VecCar[i_car].m_speed-1][VecCar[i_car].m_from-1][VecCar[i_car].m_to-1][j+1];

            if(VecCross[num_a-1].m_roadID1>=VecRoad[0].m_id)
            {
                if(VecRoad[VecCross[num_a-1].m_roadID1-VecRoad[0].m_id].m_from==num_b || VecRoad[VecCross[num_a-1].m_roadID1-VecRoad[0].m_id].m_to==num_b )
                {
                    outputanswer<<", "<<VecCross[num_a-1].m_roadID1;
                    VecCar[i_car].VecRoadID.push_back(VecCross[num_a-1].m_roadID1);
                    continue;
                }

            }
            if(VecCross[num_a-1].m_roadID2>=VecRoad[0].m_id)
            {
                if(VecRoad[VecCross[num_a-1].m_roadID2-VecRoad[0].m_id].m_from==num_b||VecRoad[VecCross[num_a-1].m_roadID2-VecRoad[0].m_id].m_to==num_b)
                {
                    outputanswer<<", "<<VecCross[num_a-1].m_roadID2;
                    VecCar[i_car].VecRoadID.push_back(VecCross[num_a-1].m_roadID2);
                    continue;
                }
            }
            if(VecCross[num_a-1].m_roadID3>=VecRoad[0].m_id)
            {
                if(VecRoad[VecCross[num_a-1].m_roadID3-VecRoad[0].m_id].m_from==num_b||VecRoad[VecCross[num_a-1].m_roadID3-VecRoad[0].m_id].m_to==num_b)
                {
                    outputanswer<<", "<<VecCross[num_a-1].m_roadID3;
                    VecCar[i_car].VecRoadID.push_back(VecCross[num_a-1].m_roadID3);
                    continue;
                }
            }
            if(VecCross[num_a-1].m_roadID4>=VecRoad[0].m_id)
            {
                if(VecRoad[VecCross[num_a-1].m_roadID4-VecRoad[0].m_id].m_from==num_b||VecRoad[VecCross[num_a-1].m_roadID4-VecRoad[0].m_id].m_to==num_b)
                {
                    outputanswer<<", "<<VecCross[num_a-1].m_roadID4;
                    VecCar[i_car].VecRoadID.push_back(VecCross[num_a-1].m_roadID4);
                    continue;
                }
            }
            outputanswer<<"error:----------------------------------------------------";
            //outputanswer<<", "<<m_vecpaths[VecCar[i_car].m_speed-1][VecCar[i_car].m_from-1][VecCar[i_car].m_to-1][j];
        }
        outputanswer<<")"<<endl;
    }
    outputanswer.close();
}

//输出根据固定车速变化的变权重路线图，路线为道路图
void CreatDigraph::printOptiNumAnswer(string answerpath)
{
    std::ofstream outputanswer(answerpath,std::ifstream::out);
    for(int i_car = 0; i_car < VecCar.size(); ++i_car)
    {
        outputanswer<<"("<<VecCar[i_car].m_id<<", "<<VecCar[i_car].m_planTime;
        for(int i_carroadid = 0; i_carroadid < VecCar[i_car].VecRoadID.size(); ++i_carroadid)
        {
            outputanswer<<", "<<VecCar[i_car].VecRoadID[i_carroadid];
        }
        outputanswer<<")"<<endl;
    }
    outputanswer.close();
}

vector<int> CreatDigraph::crosstoroad(int speed, int firstcross, int endcross)
{
    vector<int> vecroads;
    for(int j = 0; j < m_vecpaths[speed-1][firstcross-1][endcross-1].size()-1; ++j)
    {
            int num_a = m_vecpaths[speed-1][firstcross-1][endcross-1][j];
            int num_b = m_vecpaths[speed-1][firstcross-1][endcross-1][j+1];

            if(VecCross[num_a-1].m_roadID1>=VecRoad[0].m_id)
            {
                if(VecRoad[VecCross[num_a-1].m_roadID1-VecRoad[0].m_id].m_from==num_b || VecRoad[VecCross[num_a-1].m_roadID1-VecRoad[0].m_id].m_to==num_b )
                {
                    vecroads.push_back(VecCross[num_a-1].m_roadID1);
                    continue;
                }

            }
            if(VecCross[num_a-1].m_roadID2>=VecRoad[0].m_id)
            {
                if(VecRoad[VecCross[num_a-1].m_roadID2-VecRoad[0].m_id].m_from==num_b||VecRoad[VecCross[num_a-1].m_roadID2-VecRoad[0].m_id].m_to==num_b)
                {
                    vecroads.push_back(VecCross[num_a-1].m_roadID2);
                    continue;
                }
            }
            if(VecCross[num_a-1].m_roadID3>=VecRoad[0].m_id)
            {
                if(VecRoad[VecCross[num_a-1].m_roadID3-VecRoad[0].m_id].m_from==num_b||VecRoad[VecCross[num_a-1].m_roadID3-VecRoad[0].m_id].m_to==num_b)
                {
                    vecroads.push_back(VecCross[num_a-1].m_roadID3);
                    continue;
                }
            }
            if(VecCross[num_a-1].m_roadID4>=VecRoad[0].m_id)
            {
                if(VecRoad[VecCross[num_a-1].m_roadID4-VecRoad[0].m_id].m_from==num_b||VecRoad[VecCross[num_a-1].m_roadID4-VecRoad[0].m_id].m_to==num_b)
                {
                    vecroads.push_back(VecCross[num_a-1].m_roadID4);
                    continue;
                }
            }
    }
    return vecroads;
}

void CreatDigraph::optiPath()
{
    vector<int> VecNumRoads;
    for(int i_vecnumroad = 0; i_vecnumroad < VecRoad.size(); ++i_vecnumroad)
    {
        VecNumRoads.push_back(0);
    }
    vector<vector<int>> vecNumRoads;

    for(int i_time = 0; i_time < VecTimeCars.size(); ++i_time)
    {
        vector<int> NumRoads;
        for(int i_numroad = 0; i_numroad < VecRoad.size(); ++i_numroad)
        {
            NumRoads.push_back(0);
        }
        for(auto i_setcar = VecTimeCars[i_time].begin(); i_setcar != VecTimeCars[i_time].end(); ++i_setcar)
        {

            for(int i_carVecRoadID = 0; i_carVecRoadID < VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID.size(); ++i_carVecRoadID)
            {
                vector<int> vecroadid;
                int roadid = VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID];
                if(VecNumRoads[roadid-VecRoad[0].m_id]>1)
                {
                    vector<int> tempath = m_vecpaths[VecCar[(*i_setcar)-VecCar[0].m_id].m_speed-1][VecCar[(*i_setcar)-VecCar[0].m_id].m_from-1][VecCar[(*i_setcar)-VecCar[0].m_id].m_to-1];
                    for(int i_tempath = 0; i_tempath < tempath.size(); ++i_tempath)
                    {
                        if(tempath[i_tempath]==VecRoad[roadid-VecRoad[0].m_id].m_from || tempath[i_tempath]==VecRoad[roadid-VecRoad[0].m_id].m_to)
                        {
                            if(VecCross[tempath[i_tempath]-1].m_roadID1!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID1!=-1)
                            {
                                if(i_carVecRoadID>0)
                                {
                                    if(VecCross[tempath[i_tempath]-1].m_roadID1!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                    {
                                        if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        else{
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                //--i_carVecRoadID;
                                                break;
                                        }
                                    }
                                }
                                else{
                                        if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                break;
                                            }
                                        else{
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                break;
                                        }

                                }

                            }
                            if(VecCross[tempath[i_tempath]-1].m_roadID2!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID2!=-1)
                            {
                                if(i_carVecRoadID>0)
                                {
                                    if(VecCross[tempath[i_tempath]-1].m_roadID2!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                    {
                                        if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        else{
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                //--i_carVecRoadID;
                                                break;
                                        }
                                    }
                                }
                                else{
                                        if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                break;
                                            }
                                        else{
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                break;
                                        }

                                }
                            }
                            if(VecCross[tempath[i_tempath]-1].m_roadID3!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID3!=-1)
                            {
                                if(i_carVecRoadID>0)
                                {
                                    if(VecCross[tempath[i_tempath]-1].m_roadID3!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                    {
                                        if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        else{
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                //--i_carVecRoadID;
                                                break;
                                        }
                                    }
                                }
                                else{
                                        if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                break;
                                            }
                                        else{
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                break;
                                        }

                                }
                            }
                            if(VecCross[tempath[i_tempath]-1].m_roadID4!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID4!=-1)
                            {
                                if(i_carVecRoadID>0)
                                {
                                    if(VecCross[tempath[i_tempath]-1].m_roadID4!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                    {
                                        if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        else{
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                //--i_carVecRoadID;
                                                break;
                                        }
                                    }
                                }
                                else{
                                        if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                break;
                                            }
                                        else{
                                                vector<int> temroadid;
                                                temroadid = crosstoroad(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                vecroadid.insert(vecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = vecroadid;
                                                break;
                                        }

                                }
                            }
                        }
                    }
                }
                else{
                        ++NumRoads[roadid-VecRoad[0].m_id];
                        //++VecNumRoads[roadid-VecRoad[0].m_id];
                        vecroadid.push_back(roadid);
                }
            }
        }
        vecNumRoads.push_back(NumRoads);
        if(i_time>0)
        {
            auto iter = vecNumRoads.begin();
            vecNumRoads.erase(iter);
        }
        for(int i_num = 0; i_num < VecRoad.size(); ++i_num)
        {
            VecNumRoads[i_num] = 0;
            for(int j_num = 0; j_num < vecNumRoads.size(); ++j_num)
            {
                VecNumRoads[i_num] += vecNumRoads[j_num][i_num];
            }
        }
    }


}


void CreatDigraph::pathSimuOpti()
{
    int timeSlice = 0;
    int carNum = VecCar.size();
    vector<int> VecCarNum;
    for(int i = 0; i < carNum; ++i)
    {
        VecCarNum.push_back(i);
    }
    while(carNum)
    {
        ++timeSlice;
        //检查道路终止车辆
        for(int i_road = 0; i_road < VecRoad.size(); ++i_road)
        {
            int roadrow = VecRoad[i_road].m_channel;
            int roadcolumn = VecRoad[i_road].m_length;
            for(int i_roadrow = 0;;)
            {

            }
        }


        //检查道路路口交叉等待车辆、
        for(int i_cross = 0; i_cross < VecCross.size(); ++i_cross)
        {

        }



        //检查出库车辆
        for(int i_car = 0; i_car < VecCarNum.size(); ++i_car)
        {
            if((VecCar[i_car].m_planTime>=timeSlice)&&(VecCar[i_car].m_carstate.Isstart==false))
            {
                //判断道路车况
                int roadrow = VecRoad[VecCar[i_car].VecRoadID[0]-VecRoad[0].m_id].m_channel;
                int roadcolumn = VecRoad[VecCar[i_car].VecRoadID[0]-VecRoad[0].m_id].m_length;
                Car reCar;
                int reChannel=0;
                bool getcar = false;
                if(VecCar[i_car].m_carstate.IsFrom==VecRoad[VecCar[i_car].VecRoadID[0]-VecRoad[0].m_id].m_from)
                {
                    for(int i_roadrow = 0; i_roadrow < roadrow; ++i_roadrow)
                    {
                        if(VecRoad[VecCar[i_car].VecRoadID[0]-VecRoad[0].m_id].m_roadstate.pathMatrix[i_roadrow][roadcolumn-1] == 0)
                        {
                            reChannel = i_roadrow+1;
                            VecCar[i_car].m_carstate.IsRoad = VecRoad[VecCar[i_car].VecRoadID[0]-VecRoad[0].m_id];
                            VecCar[i_car].m_carstate.roadTab = reChannel;
                            VecCar[i_car].m_carstate.Isstart = true;
                            VecCar[i_car].m_carstate.IsFrom = VecCar[i_car].m_from;
                            if(VecCar[i_car].m_carstate.IsRoad.m_from==VecCar[i_car].m_carstate.IsFrom)
                                VecCar[i_car].m_carstate.IsTo = VecCar[i_car].m_carstate.IsRoad.m_to;
                            else
                                VecCar[i_car].m_carstate.IsTo = VecCar[i_car].m_carstate.IsRoad.m_from;

                            for(int i_roadcolumn = roadcolumn-1; i_roadcolumn >= 0 ; --i_roadcolumn)
                            {
                                if(VecRoad[VecCar[i_car].VecRoadID[0]-VecRoad[0].m_id].m_roadstate.pathMatrix[i_roadrow][i_roadcolumn] != 0)
                                {
                                    getcar = true;
                                    reCar = VecCar[(VecCar[i_car].m_carstate.IsRoad.m_roadstate.pathMatrix[i_roadrow][i_roadcolumn]-VecCar[0].m_id)];
                                    VecCar[i_car].m_carstate.Isspeed = min(VecCar[i_car].m_speed, VecCar[i_car].m_carstate.IsRoad.m_speed);
                                    if(VecCar[i_car].m_carstate.Isspeed>roadcolumn-1-i_roadcolumn)
                                        VecCar[i_car].m_carstate.Isspeed=roadcolumn-1-i_roadcolumn;
                                    VecCar[i_car].m_carstate.distance = VecCar[i_car].m_carstate.IsRoad.m_length-VecCar[i_car].m_carstate.Isspeed;
                                    break;
                                }
                            }
                            if(!getcar)
                            {
                                VecCar[i_car].m_carstate.Isspeed = min(VecCar[i_car].m_speed, VecCar[i_car].m_carstate.IsRoad.m_speed);
                                VecCar[i_car].m_carstate.distance = VecCar[i_car].m_carstate.IsRoad.m_length-VecCar[i_car].m_carstate.Isspeed;
                            }
                            VecRoad[VecCar[i_car].VecRoadID[0]-VecRoad[0].m_id].m_roadstate.pathMatrix[i_roadrow][VecCar[i_car].m_carstate.distance]=VecCar[i_car].m_id;
                            break;
                        }
                    }
                }
                else
                {
                    for(int i_roadrow = 0; i_roadrow < roadrow; ++i_roadrow)
                    {
                        if(VecRoad[VecCar[i_car].VecRoadID[0]-VecRoad[0].m_id].m_roadstate.pathMatrix[i_roadrow][roadcolumn-1] == 0)
                        {
                            reChannel = i_roadrow+1;
                            VecCar[i_car].m_carstate.IsRoad = VecRoad[VecCar[i_car].VecRoadID[0]-VecRoad[0].m_id];
                            VecCar[i_car].m_carstate.roadTab = reChannel;
                            VecCar[i_car].m_carstate.Isstart = true;
                            VecCar[i_car].m_carstate.IsFrom = VecCar[i_car].m_from;
                            if(VecCar[i_car].m_carstate.IsRoad.m_from==VecCar[i_car].m_carstate.IsFrom)
                                VecCar[i_car].m_carstate.IsTo = VecCar[i_car].m_carstate.IsRoad.m_to;
                            else
                                VecCar[i_car].m_carstate.IsTo = VecCar[i_car].m_carstate.IsRoad.m_from;

                            for(int i_roadcolumn = 0; i_roadcolumn < roadcolumn; ++i_roadcolumn)
                            {
                                if(VecRoad[VecCar[i_car].VecRoadID[0]-VecRoad[0].m_id].m_roadstate.pathMatrix[i_roadrow][i_roadcolumn] != 0)
                                {
                                    getcar = true;
                                    reCar = VecCar[(VecCar[i_car].m_carstate.IsRoad.m_roadstate.pathMatrix[i_roadrow][i_roadcolumn]-VecCar[0].m_id)];
                                    VecCar[i_car].m_carstate.Isspeed = min(VecCar[i_car].m_speed, VecCar[i_car].m_carstate.IsRoad.m_speed);
                                    if(VecCar[i_car].m_carstate.Isspeed>i_roadcolumn)
                                        VecCar[i_car].m_carstate.Isspeed=i_roadcolumn;
                                    VecCar[i_car].m_carstate.distance = VecCar[i_car].m_carstate.IsRoad.m_length-VecCar[i_car].m_carstate.Isspeed;
                                    break;
                                }
                            }
                            if(!getcar)
                            {
                                VecCar[i_car].m_carstate.Isspeed = min(VecCar[i_car].m_speed, VecCar[i_car].m_carstate.IsRoad.m_speed);
                                VecCar[i_car].m_carstate.distance = VecCar[i_car].m_carstate.IsRoad.m_length-VecCar[i_car].m_carstate.Isspeed;
                            }
                            VecRoad[VecCar[i_car].VecRoadID[0]-VecRoad[0].m_id].m_roadstate.pathMatrix[i_roadrow][roadcolumn-1-VecCar[i_car].m_carstate.distance]=VecCar[i_car].m_id;
                            break;
                        }
                    }
                }
            }
        }


    }
}






































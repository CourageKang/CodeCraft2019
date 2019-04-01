#include "lib/CreatDigraph.h"
using namespace std;

CreatDigraph::CreatDigraph()
{

}

CreatDigraph::~CreatDigraph()
{

}

//从外界添加汽车，路口，跑道信息
void CreatDigraph::addCar(int a, int b, int c, int d, int e, int f)
{
    Car mycar(a, b, c, d, e, f);
    VecCar.push_back(mycar);
}

void CreatDigraph::addCross(int a, int b, int c, int d, int e, int f)
{
    Cross mycross(a, b, c, d, e, f);
    VecCross.push_back(mycross);
}

void CreatDigraph::addRoad(int a, int b, int c, int d, int e, int f, int g, int h)
{
    Road myroad(a, b, c, d, e, f, g, h);
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

void CreatDigraph::ReadDate(int myspeed)
{
    //	cout << "请输入顶点数和边数" << endl;
    //	cin >> mGraph.iVertexCount >> mGraph.iEdageCount;
        mGraph.iVertexCount = getCrossSize();
        mGraph.iEdageCount = 2*getRoadSize();

        //MGraph mGraph;
        for (int i = 0; i <= mGraph.iVertexCount; i++){
            mGraph.edges[i] = new double[mGraph.iVertexCount+1];
        }

        for (int iRow = 1; iRow <= mGraph.iVertexCount; iRow++){
            for (int iCol = 1; iCol <= mGraph.iVertexCount; iCol++){
                mGraph.edges[iRow][iCol] = INF;
            }
        }

        //cout << "请输入邻接边及权重" << endl;

        int iRow, iCol;
        double iWeight;
        for (int i = 1; i <= mGraph.iEdageCount; i++){
            int num = i/2;
            if(i%2)
            {
                iRow = getRoad(num).m_from;
                iCol = getRoad(num).m_to;
                iWeight = double(getRoad(num).m_length) / double(min(myspeed,getRoad(num).m_speed));

            }
            else
            {
                if(getRoad(num-1).m_isDuplex==true)
                {
                    iRow = getRoad(num-1).m_to;
                    iCol = getRoad(num-1).m_from;
                    iWeight = double(getRoad(num-1).m_length) / double(min(myspeed,getRoad(num-1).m_speed));
                }
            }
            //cin >> iRow >> iCol >> iWeight;
            mGraph.edges[iRow][iCol] = iWeight;
        }

}

void CreatDigraph::runDijkstra(int roadid1, int roadid2,  int firstPnt, int endPnt, int myspeed, vector<int> &vecpathPnts)
{
    ReadDate(myspeed);

    MGraph myGraph = mGraph;
    myGraph.edges[VecRoad[roadid1-VecRoad[0].m_id].m_from][VecRoad[roadid1-VecRoad[0].m_id].m_to] = INF;
    myGraph.edges[VecRoad[roadid1-VecRoad[0].m_id].m_to][VecRoad[roadid1-VecRoad[0].m_id].m_from] = INF;
    myGraph.edges[VecRoad[roadid2-VecRoad[0].m_id].m_from][VecRoad[roadid2-VecRoad[0].m_id].m_to] = INF;
    myGraph.edges[VecRoad[roadid2-VecRoad[0].m_id].m_to][VecRoad[roadid2-VecRoad[0].m_id].m_from] = INF;
    const int n = myGraph.iVertexCount;
    //init Dis
    int pathDis[n] = {0};
    for(int i_endPnt = 0; i_endPnt < n; ++i_endPnt)
    {
        if(i_endPnt+1 != firstPnt)
            pathDis[i_endPnt] = myGraph.edges[firstPnt][i_endPnt+1];
    }
    //init path
//    vector<int> *dijkstrapath = new vector<int>[n];
    vector<vector<int>> dijkstrapath;
    for(int i_vecdijkstrapath = 0; i_vecdijkstrapath < n; ++i_vecdijkstrapath)
    {
        vector<int> temdijkstra;
        dijkstrapath.push_back(temdijkstra);
    }

    for(int i_dijkstrapath = 0; i_dijkstrapath < n; ++i_dijkstrapath)
    {
        dijkstrapath[i_dijkstrapath].push_back(firstPnt);
        if((i_dijkstrapath+1)!=firstPnt)
            dijkstrapath[i_dijkstrapath].push_back(i_dijkstrapath+1);
    }
    //classify Pnts
    set<int> Pnts;
    Pnts.insert(firstPnt-1);
    for(int i_test = 1; i_test < n; ++i_test)
    {
        int i_dis = INF;
        int i_numPnt = -1;
        for(int i_Pnt = 0; i_Pnt < n; ++i_Pnt)
        {
            if(Pnts.find(i_Pnt)==Pnts.end())
            {
                if(i_dis>pathDis[i_Pnt])
                {
                    i_dis = pathDis[i_Pnt];
                    i_numPnt = i_Pnt;
                }
            }

        }
        Pnts.insert(i_numPnt);
        for(int j_Pnt = 0; j_Pnt < n; ++j_Pnt)
        {
            if(Pnts.find(j_Pnt)==Pnts.end())
            {

                for(int j_path = 0; j_path < n; ++j_path)
                {
                    if(Pnts.find(j_path)!=Pnts.end())
                    {
                        if(pathDis[j_path]+myGraph.edges[j_path+1][j_Pnt+1]<pathDis[j_Pnt])
                        {
                            pathDis[j_Pnt] = pathDis[j_path]+myGraph.edges[j_path+1][j_Pnt+1];
                            dijkstrapath[j_Pnt] = dijkstrapath[j_path];
                            dijkstrapath[j_Pnt].push_back(j_Pnt+1);
                        }
                    }
                }
            }

        }
    }

    //get target
    if(pathDis[endPnt-1]<INF)
        vecpathPnts = dijkstrapath[endPnt-1];
}

void CreatDigraph::classifySpeedCars()
{
    VecSpeedCars.reserve(21);
    for(int i = 0; i < 21; ++i)
    {
        std::set<int> temset;
        VecSpeedCars.push_back(temset);
    }
    cout<<"*********************"<<endl;
    for(int i_car = 0; i_car < VecCar.size(); ++i_car)
    {
        if(VecCar[i_car].m_speed<=20)
        {
            VecSpeedCars[VecCar[i_car].m_speed].insert(VecCar[i_car].m_id);
        }
        else
        {
            VecSpeedCars[20].insert(VecCar[i_car].m_id);
        }
    }
    cout<<"*********************"<<endl;
    int num = 0;
    int timeSlice = 1;
    int temSpeed[50] = {0};
    vector<set<int>> TimeCars;
    for(int i_TimeCars = 0; i_TimeCars < 50; ++i_TimeCars)
    {
        set<int> tem;
        TimeCars.push_back(tem);
    }
    set<int> timecars;
    for(int i_set = 20; i_set >= 0; --i_set)
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
//                if(temSpeed[VecCar[*iterset-VecCar[0].m_id].m_planTime-1]>=22)
//                {

//                }
//                else
//                {
                    ++temSpeed[VecCar[*iterset-VecCar[0].m_id].m_planTime-1];
                    TimeCars[VecCar[*iterset-VecCar[0].m_id].m_planTime-1].insert(VecCar[*iterset-VecCar[0].m_id].m_id);
//                }
            }
            if(VecCar[0].m_idr>50000)
            {
                if(i_set>16)
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
                else if(i_set>12)
                {
                    if(num >= 18)
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
                else if(i_set>8)
                {
                    if(num >= 18)
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
                else if(i_set>4)
                {
                    if(num >= 16)
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
                    if(num >= 14)
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
            }
            else
            {
                if(i_set>16)
                {
                    if(num >= 24)
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
                else if(i_set>12)
                {
                    if(num >= 24)
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
                else if(i_set>8)
                {
                    if(num >= 24)
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
                else if(i_set>4)
                {
                    if(num >= 16)
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
                    if(num >= 16)
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
            }


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

//输出根据固定车速变化的变权重路线图，路线为道路图
void CreatDigraph::printOptiDisorderNumAnswer(string answerpath)
{
    std::ofstream outputanswer(answerpath,std::ifstream::out);
    for(int i_car = 0; i_car < VecCar.size(); ++i_car)
    {
        outputanswer<<"("<<VecCar[i_car].m_idr<<", "<<VecCar[i_car].m_planTime;
        for(int i_carroadid = 0; i_carroadid < VecCar[i_car].VecRoadID.size(); ++i_carroadid)
        {
            outputanswer<<", "<<VecRoad[VecCar[i_car].VecRoadID[i_carroadid]-VecRoad[0].m_id].m_idr;
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

vector<int> CreatDigraph::crosstoroadDijkstra(int roadid1, int roadid2, int speed, int firstcross, int endcross)
{
    vector<int> vecpathPnts;
    runDijkstra(roadid1, roadid2, firstcross,endcross,speed,vecpathPnts);
    vector<int> vecroads;
    if(vecpathPnts.size()==0)
        return vecroads;

    for(int j = 0; j < vecpathPnts.size()-1; ++j)
    {
            int num_a = vecpathPnts[j];
            int num_b = vecpathPnts[j+1];

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
    //every three time slices SUM
    vector<int> VecNumRoads;
    for(int i_vecnumroad = 0; i_vecnumroad < 2*VecRoad.size(); ++i_vecnumroad)
    {
        VecNumRoads.push_back(0);
    }
    //each time slice in three
    vector<vector<int>> vecNumRoads;

    for(int i_time = 0; i_time < VecTimeCars.size(); ++i_time)
    {
        //each time slice
        vector<int> NumRoads;
        for(int i_numroad = 0; i_numroad < 2*VecRoad.size(); ++i_numroad)
        {
            NumRoads.push_back(0);
        }
        //all cars in each time slice
        for(auto i_setcar = VecTimeCars[i_time].begin(); i_setcar != VecTimeCars[i_time].end(); ++i_setcar)
        {
            vector<int> vecroadid;
            set<int> setroadid;
            //all VecRoadID of each cars in one time slice
            for(int i_carVecRoadID = 0; i_carVecRoadID < VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID.size(); ++i_carVecRoadID)
            {
                int roadid = VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID];
                bool IsVary = false;
                bool IsForward = true;
                if(VecNumRoads[2*(roadid-VecRoad[0].m_id)]>(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[roadid-VecRoad[0].m_id].m_length-1) || VecNumRoads[2*(roadid-VecRoad[0].m_id)+1]>(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[roadid-VecRoad[0].m_id].m_length-1))
                {
                    vector<int> tempath = m_vecpaths[VecCar[(*i_setcar)-VecCar[0].m_id].m_speed-1][VecCar[(*i_setcar)-VecCar[0].m_id].m_from-1][VecCar[(*i_setcar)-VecCar[0].m_id].m_to-1];
                    int i_tempath = 0;
                    bool IsRoad = false;
                    for(; i_tempath < tempath.size(); ++i_tempath)
                    {
                        if(VecRoad[roadid-VecRoad[0].m_id].m_isDuplex)
                        {
                            if(tempath[i_tempath]==VecRoad[roadid-VecRoad[0].m_id].m_from)
                            {
                                IsForward = true;
                                if(VecNumRoads[2*(roadid-VecRoad[0].m_id)]>(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[roadid-VecRoad[0].m_id].m_length-1))
                                {
                                    IsRoad = true;
                                }
                                break;
                            }
                            else if( tempath[i_tempath]==VecRoad[roadid-VecRoad[0].m_id].m_to )
                            {
                                IsForward = false;
                                if(VecNumRoads[2*(roadid-VecRoad[0].m_id)+1]>(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[roadid-VecRoad[0].m_id].m_length-1))
                                {
                                    IsRoad = true;
                                }
                                break;
                            }
                        }
                        else
                        {
                            if(tempath[i_tempath]==VecRoad[roadid-VecRoad[0].m_id].m_from)
                            {
                                IsForward = true;
                                if(VecNumRoads[2*(roadid-VecRoad[0].m_id)]>(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[roadid-VecRoad[0].m_id].m_length-1))
                                {
                                    IsRoad = true;
                                }
                                break;
                            }
                        }

                    }
                    if(IsRoad)
                    {
                        if(setroadid.find(roadid)!=setroadid.end())
                        {
                            break;
                        }
                        if(VecCross[tempath[i_tempath]-1].m_roadID1!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID1!=-1)
                        {
                            bool IsDuplex = true;
                            if(!VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_isDuplex)
                            {
                                if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                    IsDuplex = false;
                            }
                            if(IsDuplex)
                            {
                                if(tempath[i_tempath]==VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from)
                                {
                                    if(VecNumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)]<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID1!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID1,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)];
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID1);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }
                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID1,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)];
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID1);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if(VecNumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1]<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID1!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID1,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1];
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID1);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }
                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID1,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1];
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID1);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }

                            }
                        }
                        if(VecCross[tempath[i_tempath]-1].m_roadID2!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID2!=-1)
                        {
                            bool IsDuplex = true;
                            if(!VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_isDuplex)
                            {
                                if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                    IsDuplex = false;
                            }
                            if(IsDuplex)
                            {
                                if(tempath[i_tempath]==VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from)
                                {
                                    if(VecNumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)]<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID2!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID2,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)];
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID2);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }

                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID2,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)];
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID2);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if(VecNumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)+1]<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID2!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID2,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)+1];
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID2);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }

                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID2,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)+1];
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID2);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }

                            }
                        }
                        if(VecCross[tempath[i_tempath]-1].m_roadID3!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID3!=-1)
                        {
                            bool IsDuplex = true;
                            if(!VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_isDuplex)
                            {
                                if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                    IsDuplex = false;
                            }
                            if(IsDuplex)
                            {
                                if(tempath[i_tempath]==VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from)
                                {
                                    if(VecNumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)]<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID3!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID3,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)];
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID3);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }

                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID3,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)];
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID3);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if(VecNumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)+1]<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID3!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID3,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)+1];
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID3);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }
                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID3,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)+1];
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID3);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }

                            }
                        }
                        if(VecCross[tempath[i_tempath]-1].m_roadID4!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID4!=-1)
                        {
                            bool IsDuplex = true;
                            if(!VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_isDuplex)
                            {
                                if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                    IsDuplex = false;
                            }
                            if(IsDuplex)
                            {
                                if(tempath[i_tempath]==VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from)
                                {
                                    if(VecNumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)]<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID4!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID4,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)];
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID4);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }

                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID4,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)];
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID4);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if(VecNumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)+1]<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID4!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID4,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)+1];
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID4);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }

                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID4,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)+1];
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID4);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
                if(!IsVary)
                {
                    if(IsForward)
                    {
                        ++NumRoads[2*(roadid-VecRoad[0].m_id)];
                        ++VecNumRoads[2*(roadid-VecRoad[0].m_id)];
                        vecroadid.push_back(roadid);
                    }
                    else
                    {
                        ++NumRoads[2*(roadid-VecRoad[0].m_id)+1];
                        ++VecNumRoads[2*(roadid-VecRoad[0].m_id)+1];
                        vecroadid.push_back(roadid);
                    }
                }
                else
                {
                    setroadid.insert(roadid);
                }
            }
            vecroadid.clear();
            setroadid.clear();
        }
        vecNumRoads.push_back(NumRoads);
//        if(i_time>0)
//        {
//            auto iter = vecNumRoads.begin();
//            vecNumRoads.erase(iter);
//        }
        for(int i_num = 0; i_num < 2*VecRoad.size(); ++i_num)
        {
            VecNumRoads[i_num] = 0;
//            for(int j_num = 0; j_num < vecNumRoads.size(); ++j_num)
//            {
//                VecNumRoads[i_num] += vecNumRoads[j_num][i_num];
//            }
        }
    }
}

void CreatDigraph::optiTimePath()
{
    //every three time slices SUM
    vector<int> VecTemNumRoads;
    for(int i_vecnumroad = 0; i_vecnumroad < 2*VecRoad.size(); ++i_vecnumroad)
    {
        VecTemNumRoads.push_back(0);
    }
    vector<vector<int>> VecTimeNumRoads;
    for(int i_vectimenumroad = 0; i_vectimenumroad < 50; ++i_vectimenumroad)
    {
        VecTimeNumRoads.push_back(VecTemNumRoads);
    }

    //each time slice in three
    for(int i_time = 0; i_time < VecTimeCars.size(); ++i_time)
    {
        //each time slice
        vector<int> NumRoads;
        for(int i_numroad = 0; i_numroad < 2*VecRoad.size(); ++i_numroad)
        {
            NumRoads.push_back(0);
        }
        //all cars in each time slice
        for(auto i_setcar = VecTimeCars[i_time].begin(); i_setcar != VecTimeCars[i_time].end(); ++i_setcar)
        {
            vector<int> vecroadid;
            set<int> setroadid;
            int TimeSUM = 0;
            int tempathRoadID;
            //all VecRoadID of each cars in one time slice
            for(int i_carVecRoadID = 0; i_carVecRoadID < VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID.size(); ++i_carVecRoadID)
            {
                int roadid = VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID];
                bool IsVary = false;
                bool IsForward = true;

                bool IsZero = true;
                if(i_time+TimeSUM>0)
                {
                    IsZero = false;
                }

                int IDNumber0 = 0;
                int IDNumber1 = 0;
                if(IsZero)
                {
                    IDNumber0 = VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)];
                    IDNumber1 = VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)+1];
                }
                else
                {
                    IDNumber0 = VecTimeNumRoads[i_time+TimeSUM-1][2*(roadid-VecRoad[0].m_id)]+VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)];
                    IDNumber1 = VecTimeNumRoads[i_time+TimeSUM-1][2*(roadid-VecRoad[0].m_id)+1]+VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)+1];
                }
                if(IDNumber0>(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[roadid-VecRoad[0].m_id].m_length-1) ||IDNumber1>(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[roadid-VecRoad[0].m_id].m_length-1))
                {
                    vector<int> tempath = m_vecpaths[VecCar[(*i_setcar)-VecCar[0].m_id].m_speed-1][VecCar[(*i_setcar)-VecCar[0].m_id].m_from-1][VecCar[(*i_setcar)-VecCar[0].m_id].m_to-1];
                    int i_tempath = 0;
                    bool IsRoad = false;
                    for(; i_tempath < tempath.size(); ++i_tempath)
                    {
                        if(VecRoad[roadid-VecRoad[0].m_id].m_isDuplex)
                        {
                            if(tempath[i_tempath]==VecRoad[roadid-VecRoad[0].m_id].m_from)
                            {
                                IsForward = true;
                                if(IDNumber0>(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[roadid-VecRoad[0].m_id].m_length-1))
                                {
                                    IsRoad = true;
                                }
                                break;
                            }
                            else if( tempath[i_tempath]==VecRoad[roadid-VecRoad[0].m_id].m_to )
                            {
                                IsForward = false;
                                if(IDNumber1>(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[roadid-VecRoad[0].m_id].m_length-1))
                                {
                                    IsRoad = true;
                                }
                                break;
                            }
                        }
                        else
                        {
                            if(tempath[i_tempath]==VecRoad[roadid-VecRoad[0].m_id].m_from)
                            {
                                IsForward = true;
                                if(IDNumber0>(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[roadid-VecRoad[0].m_id].m_length-1))
                                {
                                    IsRoad = true;
                                }
                                break;
                            }
                        }

                    }
                    if(IsRoad)
                    {
                        if(setroadid.find(roadid)!=setroadid.end())
                        {
                            break;
                        }
                        if(VecCross[tempath[i_tempath]-1].m_roadID1!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID1!=-1)
                        {
                            int IDNumber01 = 0;
                            int IDNumber11 = 0;
                            if(IsZero)
                            {
                                IDNumber01 = VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)];
                                IDNumber11 = VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1];
                            }
                            else
                            {
                                IDNumber01 = VecTimeNumRoads[i_time+TimeSUM-1][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)]+VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)];
                                IDNumber11 = VecTimeNumRoads[i_time+TimeSUM-1][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1]+VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)+1];
                            }

                            bool IsDuplex = true;
                            if(!VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_isDuplex)
                            {
                                if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                    IsDuplex = false;
                            }
                            if(IsDuplex)
                            {
                                if(tempath[i_tempath]==VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from)
                                {
                                    if(IDNumber01<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID1!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID1,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)];
                                                    ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)];
                                                    tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID1;
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID1);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }
                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID1,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)];
                                                ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)];
                                                tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID1;
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID1);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if(IDNumber11<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID1!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID1,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1];
                                                    ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1];
                                                    tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID1;
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID1);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }
                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID1,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1];
                                                ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1];
                                                tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID1;
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID1);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }

                            }
                        }
                        if(VecCross[tempath[i_tempath]-1].m_roadID2!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID2!=-1)
                        {
                            int IDNumber02 = 0;
                            int IDNumber12 = 0;
                            if(IsZero)
                            {
                                IDNumber02 = VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)];
                                IDNumber12 = VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1];
                            }
                            else
                            {
                                IDNumber02 = VecTimeNumRoads[i_time+TimeSUM-1][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)]+VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)];
                                IDNumber12 = VecTimeNumRoads[i_time+TimeSUM-1][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1]+VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)+1];
                            }
                            bool IsDuplex = true;
                            if(!VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_isDuplex)
                            {
                                if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                    IsDuplex = false;
                            }
                            if(IsDuplex)
                            {
                                if(tempath[i_tempath]==VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from)
                                {
                                    if(IDNumber02<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID2!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID2,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)];
                                                    ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)];
                                                    tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID2;
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID2);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }

                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID2,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)];
                                                ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)];
                                                tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID2;
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID2);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if(IDNumber12<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID2!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID2,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)+1];
                                                    ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)+1];
                                                    tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID2;
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID2);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }

                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID2,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)+1];
                                                ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID2-VecRoad[0].m_id)+1];
                                                tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID2;
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID2);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }

                            }
                        }
                        if(VecCross[tempath[i_tempath]-1].m_roadID3!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID3!=-1)
                        {
                            int IDNumber03 = 0;
                            int IDNumber13 = 0;
                            if(IsZero)
                            {
                                IDNumber03 = VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)];
                                IDNumber13 = VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1];
                            }
                            else
                            {
                                IDNumber03 = VecTimeNumRoads[i_time+TimeSUM-1][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)]+VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)];
                                IDNumber13 = VecTimeNumRoads[i_time+TimeSUM-1][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1]+VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)+1];
                            }
                            bool IsDuplex = true;
                            if(!VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_isDuplex)
                            {
                                if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                    IsDuplex = false;
                            }
                            if(IsDuplex)
                            {
                                if(tempath[i_tempath]==VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from)
                                {
                                    if(IDNumber03<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID3!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID3,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)];
                                                    ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)];
                                                    tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID3;
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID3);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }

                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID3,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)];
                                                ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)];
                                                tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID3;
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID3);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if(IDNumber13<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID3!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID3,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)+1];
                                                    ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)+1];
                                                    tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID3;
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID3);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }
                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID3,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)+1];
                                                ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID3-VecRoad[0].m_id)+1];
                                                tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID3;
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID3);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }

                            }
                        }
                        if(VecCross[tempath[i_tempath]-1].m_roadID4!=roadid&&VecCross[tempath[i_tempath]-1].m_roadID4!=-1)
                        {
                            int IDNumber04 = 0;
                            int IDNumber14 = 0;
                            if(IsZero)
                            {
                                IDNumber04 = VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)];
                                IDNumber14 = VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1];
                            }
                            else
                            {
                                IDNumber04 = VecTimeNumRoads[i_time+TimeSUM-1][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)]+VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)];
                                IDNumber14 = VecTimeNumRoads[i_time+TimeSUM-1][2*(VecCross[tempath[i_tempath]-1].m_roadID1-VecRoad[0].m_id)+1]+VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)+1];
                            }
                            bool IsDuplex = true;
                            if(!VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_isDuplex)
                            {
                                if(VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from!=tempath[i_tempath])
                                    IsDuplex = false;
                            }
                            if(IsDuplex)
                            {
                                if(tempath[i_tempath]==VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from)
                                {
                                    if(IDNumber04<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID4!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID4,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)];
                                                    ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)];
                                                    tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID4;
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID4);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }

                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID4,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_to,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)];
                                                ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)];
                                                tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID4;
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID4);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if(IDNumber14<(/*VecRoad[roadid-VecRoad[0].m_id].m_channel**/VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_length-1))
                                    {
                                        if(i_carVecRoadID>0)
                                        {
                                            if(VecCross[tempath[i_tempath]-1].m_roadID4!=VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID[i_carVecRoadID-1])
                                            {
                                                vector<int> temroadid;
                                                temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID4,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                                if(temroadid.size()!=0)
                                                {
                                                    ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)+1];
                                                    ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)+1];
                                                    tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID4;
                                                    vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID4);
                                                    vector<int> temvecroadid = vecroadid;
                                                    temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                    VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                    IsVary = true;
                                                    //--i_carVecRoadID;
                                                    break;
                                                }

                                            }
                                        }
                                        else{
                                            vector<int> temroadid;
                                            temroadid = crosstoroadDijkstra(roadid,VecCross[tempath[i_tempath]-1].m_roadID4,VecCar[(*i_setcar)-VecCar[0].m_id].m_speed,VecRoad[VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id].m_from,VecCar[(*i_setcar)-VecCar[0].m_id].m_to);
                                            if(temroadid.size()!=0)
                                            {
                                                ++NumRoads[2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)+1];
                                                ++VecTimeNumRoads[i_time+TimeSUM][2*(VecCross[tempath[i_tempath]-1].m_roadID4-VecRoad[0].m_id)+1];
                                                tempathRoadID = VecCross[tempath[i_tempath]-1].m_roadID4;
                                                vecroadid.push_back(VecCross[tempath[i_tempath]-1].m_roadID4);
                                                vector<int> temvecroadid = vecroadid;
                                                temvecroadid.insert(temvecroadid.end(),temroadid.begin(),temroadid.end());
                                                VecCar[(*i_setcar)-VecCar[0].m_id].VecRoadID = temvecroadid;
                                                IsVary = true;
                                                //--i_carVecRoadID;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }
                }


                if(!IsVary)
                {
                    if(IsForward)
                    {
                        ++VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)];
                        vecroadid.push_back(roadid);
                    }
                    else
                    {
                        ++VecTimeNumRoads[i_time+TimeSUM][2*(roadid-VecRoad[0].m_id)+1];
                        vecroadid.push_back(roadid);
                    }
                }
                else
                {
                    setroadid.insert(roadid);
                }

                if( min(VecCar[(*i_setcar)-VecCar[0].m_id].m_speed, VecRoad[roadid-VecRoad[0].m_id].m_speed) > 0.5*VecRoad[roadid-VecRoad[0].m_id].m_length )
                {
                    ++TimeSUM;
                }
                else
                {
                    ++TimeSUM;
                    ++TimeSUM;
                }
            }
            vecroadid.clear();
            setroadid.clear();
        }

        //increase capacity
        VecTimeNumRoads.push_back(VecTemNumRoads);
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






































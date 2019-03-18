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
    for(int i_set = 10; i_set >= 0; --i_set)
    {
        std::set<int>::iterator iterset = VecSpeedCars[i_set].begin();
        for(; iterset != VecSpeedCars[i_set].end(); ++iterset)
        {
            VecCar[*iterset-VecCar[0].m_id].m_planTime = max(timeSlice,VecCar[*iterset-VecCar[0].m_id].m_planTime);
            ++num;
            if(num == 13)
            {
                num = 0;
                ++timeSlice;
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
                    continue;
                }

            }
            if(VecCross[num_a-1].m_roadID2>=VecRoad[0].m_id)
            {
                if(VecRoad[VecCross[num_a-1].m_roadID2-VecRoad[0].m_id].m_from==num_b||VecRoad[VecCross[num_a-1].m_roadID2-VecRoad[0].m_id].m_to==num_b)
                {
                    outputanswer<<", "<<VecCross[num_a-1].m_roadID2;
                    continue;
                }
            }
            if(VecCross[num_a-1].m_roadID3>=VecRoad[0].m_id)
            {
                if(VecRoad[VecCross[num_a-1].m_roadID3-VecRoad[0].m_id].m_from==num_b||VecRoad[VecCross[num_a-1].m_roadID3-VecRoad[0].m_id].m_to==num_b)
                {
                    outputanswer<<", "<<VecCross[num_a-1].m_roadID3;
                    continue;
                }
            }
            if(VecCross[num_a-1].m_roadID4>=VecRoad[0].m_id)
            {
                if(VecRoad[VecCross[num_a-1].m_roadID4-VecRoad[0].m_id].m_from==num_b||VecRoad[VecCross[num_a-1].m_roadID4-VecRoad[0].m_id].m_to==num_b)
                {
                    outputanswer<<", "<<VecCross[num_a-1].m_roadID4;
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

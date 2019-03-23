#include "lib/Floyd.h"
using namespace std;

Floyd::Floyd()
{

}

Floyd::~Floyd()
{

}

void Floyd::ReadDate(const CreatDigraph &mycreatdigraph)
{
//	cout << "请输入顶点数和边数" << endl;
//	cin >> mGraph.iVertexCount >> mGraph.iEdageCount;
    mGraph.iVertexCount = mycreatdigraph.getCrossSize();
    mGraph.iEdageCount = 2*mycreatdigraph.getRoadSize();

    for (int i = 0; i <= mGraph.iVertexCount; i++){
		iArrPath[i] = new int[mGraph.iVertexCount+1];
	}
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
            iRow = mycreatdigraph.getRoad(num).m_from;
            iCol = mycreatdigraph.getRoad(num).m_to;
            iWeight = double(mycreatdigraph.getRoad(num).m_length);

        }
        else
        {
            if(mycreatdigraph.getRoad(num-1).m_isDuplex==true)
            {
                iRow = mycreatdigraph.getRoad(num-1).m_to;
                iCol = mycreatdigraph.getRoad(num-1).m_from;
                iWeight = double(mycreatdigraph.getRoad(num-1).m_length);
            }
        }
		//cin >> iRow >> iCol >> iWeight;
		mGraph.edges[iRow][iCol] = iWeight;
	}
}

void Floyd::ReadDate(const CreatDigraph &mycreatdigraph, Car mycar)
{
//	cout << "请输入顶点数和边数" << endl;
//	cin >> mGraph.iVertexCount >> mGraph.iEdageCount;
    mGraph.iVertexCount = mycreatdigraph.getCrossSize();
    mGraph.iEdageCount = 2*mycreatdigraph.getRoadSize();

    for (int i = 0; i <= mGraph.iVertexCount; i++){
		iArrPath[i] = new int[mGraph.iVertexCount+1];
	}
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
            iRow = mycreatdigraph.getRoad(num).m_from;
            iCol = mycreatdigraph.getRoad(num).m_to;
            iWeight = double(mycreatdigraph.getRoad(num).m_length) / double(min(mycar.m_speed,mycreatdigraph.getRoad(num).m_speed));

        }
        else
        {
            if(mycreatdigraph.getRoad(num-1).m_isDuplex==true)
            {
                iRow = mycreatdigraph.getRoad(num-1).m_to;
                iCol = mycreatdigraph.getRoad(num-1).m_from;
                iWeight = double(mycreatdigraph.getRoad(num-1).m_length) / double(min(mycar.m_speed,mycreatdigraph.getRoad(num-1).m_speed));
            }
        }
		//cin >> iRow >> iCol >> iWeight;
		mGraph.edges[iRow][iCol] = iWeight;
	}
}

void Floyd::ReadDate(const CreatDigraph &mycreatdigraph, int myspeed)
{
//	cout << "请输入顶点数和边数" << endl;
//	cin >> mGraph.iVertexCount >> mGraph.iEdageCount;
    mGraph.iVertexCount = mycreatdigraph.getCrossSize();
    mGraph.iEdageCount = 2*mycreatdigraph.getRoadSize();

    for (int i = 0; i <= mGraph.iVertexCount; i++){
		iArrPath[i] = new int[mGraph.iVertexCount+1];
	}
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
            iRow = mycreatdigraph.getRoad(num).m_from;
            iCol = mycreatdigraph.getRoad(num).m_to;
            iWeight = double(mycreatdigraph.getRoad(num).m_length) / double(min(myspeed,mycreatdigraph.getRoad(num).m_speed));

        }
        else
        {
            if(mycreatdigraph.getRoad(num-1).m_isDuplex==true)
            {
                iRow = mycreatdigraph.getRoad(num-1).m_to;
                iCol = mycreatdigraph.getRoad(num-1).m_from;
                iWeight = double(mycreatdigraph.getRoad(num-1).m_length) / double(min(myspeed,mycreatdigraph.getRoad(num-1).m_speed));
            }
        }
		//cin >> iRow >> iCol >> iWeight;
		mGraph.edges[iRow][iCol] = iWeight;
	}
}

void Floyd::runFloyd()
{

	for (int i = 1; i <= mGraph.iVertexCount; i++){
		for (int j = 1; j <= mGraph.iVertexCount; j++){
			iArrPath[i][j] = i;
		}
	}//初始化路径表

	for (int k = 1; k <= mGraph.iVertexCount; k++){
		for (int i = 1; i <= mGraph.iVertexCount; i++){
			for (int j = 1; j <= mGraph.iVertexCount; j++){
				if (mGraph.edges[i][k] + mGraph.edges[k][j] < mGraph.edges[i][j]){
					mGraph.edges[i][j] = mGraph.edges[i][k] + mGraph.edges[k][j];
					iArrPath[i][j] = iArrPath[k][j];
				}
			}
		}
	}

}

void Floyd::PrintResult(CreatDigraph &mycreatdigraph)
{

	cout << "Ori -> Des\tDistance\tPath" << endl;
	for (int i = 1; i <= mGraph.iVertexCount; i++){
        cout << i << "->" << i << endl;
        std::vector<std::vector<int>> vecvecpath;
		for (int j = 1; j <= mGraph.iVertexCount; j++){
            std::vector<int> vecpath;
			if (i != j){
				cout << i << "->" << j << "\t\t";
				if (mGraph.edges[i][j] == INF){
					cout << "无连通路径" << "\t\t" << endl;
					vecpath.push_back(-1);
					vecvecpath.push_back(vecpath);
				}
				else{
					cout << mGraph.edges[i][j] << "\t\t";
					std::stack<int> stackVertices;
					int k = j;
					do
					{
						k = iArrPath[i][k];
						stackVertices.push(k);
					} while (k != i);

					cout << stackVertices.top();
					vecpath.push_back(stackVertices.top());
					stackVertices.pop();

					unsigned int nLength = stackVertices.size();
					for (unsigned int nIndex = 0; nIndex < nLength; nIndex++)
					{
						cout << " -> " << stackVertices.top();
						vecpath.push_back(stackVertices.top());
						stackVertices.pop();
					}
					cout << " -> " << j << endl;
					vecpath.push_back(j);

					vecvecpath.push_back(vecpath);
				}
			}
			else{
                vecpath.push_back(-2);
                vecvecpath.push_back(vecpath);
			}
		}
		mycreatdigraph.m_paths.push_back(vecvecpath);
	}
	mycreatdigraph.m_vecpaths.push_back(mycreatdigraph.m_paths);
}

void Floyd::test(CreatDigraph &mycreatdigraph)
{
    Car mycar = mycreatdigraph.getCar(0);
	ReadDate(mycreatdigraph,mycar);
	runFloyd();
	PrintResult(mycreatdigraph);
}

void Floyd::getPath(CreatDigraph &mycreatdigraph, Car mycar)
{
	ReadDate(mycreatdigraph,mycar);
	runFloyd();
	PrintResult(mycreatdigraph);
}

void Floyd::getPath(CreatDigraph &mycreatdigraph, int myspeed)
{
	ReadDate(mycreatdigraph,myspeed);
	runFloyd();
	PrintResult(mycreatdigraph);
}

void Floyd::getVecPath(CreatDigraph &mycreatdigraph)
{
    int myCarNum = mycreatdigraph.getCarSize();
    for(int i_mycar = 0; i_mycar < myCarNum; ++i_mycar)
    {

        Car mycar = mycreatdigraph.getCar(i_mycar);
        getPath(mycreatdigraph,mycar);
    }
}

void Floyd::getNumPath(CreatDigraph &mycreatdigraph)
{
    for(int i_myspeed = 1; i_myspeed <= 10; ++i_myspeed)
    {
        getPath(mycreatdigraph,i_myspeed);
    }
}

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include<iostream>
using namespace std;

class Node
{
public:
	Node(char data = 0);
	char m_cData;
	bool m_IsVisited;
};

#endif // NODE_H_INCLUDED

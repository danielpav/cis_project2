//
// Created by grant on 7/22/19.
//

#ifndef FINDFRIENDS_GRAPH_H
#define FINDFRIENDS_GRAPH_H

#include <vector>
#include "vertex.h"
#include <map>
#include <queue>
#include <list>
#include<iterator>

using namespace std;

typedef std::map<const std::string, vertex*> vmap;
using rawLink= std::pair<std::string, std::string>;
using edge = std::pair<vertex*, vertex*>;

class graph
{
	int V; 
	list<int> *adj;
	public:

	graph(std::vector<rawLink> links)
	{
		for (auto & link : links)
		{
			addVertex(link.first);
			addVertex(link.second);
			addEdge(link.first, link.second);
		}
	}

	virtual ~graph()
	{
		for (auto iter : map)
		{
			delete iter.second;
		}
	}

	void addVertex(std::string& name)
	{
		if(keyExist((name)))
		{
			auto v = new vertex(name);
			map.insert({name, v});
			return;
		}
	}

	void addEdge(std::string key1, std::string key2)
	{
		map[key1]->getAdjList().push_back(map[key2]);
		map[key2]->getAdjList().push_back(map[key1]);

		edge edge;
		edge.first = map[key1];
		edge.second = map[key2];

		edgeList.push_back(edge);

	}

	bool keyExist(std::string name)
	{
		vmap::iterator iter = map.find(name);
		return iter == map.end();
	}

	vmap &getMap()
	{
		return map;
	}

	///commented out so i can debug generateMutualFriends
	//     bfs(int u) vector inputs  
	//    {
	//	    queue<int> q;
	//	    q.push(u);
	//	    V[u] = true;
	//	    while (!q.empty()) {
	//		    int f = q.front();
	//		    q.pop();
	//		    cout << f << "";
	//	    }
	//	for (auto i = AdjList(s).begin(); i !=AdjList(s).end();i++)
	//	{
	//		if(!visited[*i])
	//		{
	//			visited[*i] = true;
	//			queue.push_back(*i);
	//		}
	//		//add a function that increments a counter whenever an edge is added
	//	}
	//    }



	std::vector<vertex*> generateMutualFriends(const std::string& person)
	{

		std::vector<vertex*> friendsOfFriends;

		for (auto key : getMap()) //preps all nodes for the start of the bfs
			key.second->setVisited(false);

		getMap()[person]->setVisited(true);
		for (auto i: getMap()[person]->getAdjList())
		{
			for(auto j : i->getAdjList())
			{
				if (!j->isVisited() && !j->isAdj(getMap()[person]))
				{
					friendsOfFriends.push_back(j);
				}
				j->setVisited(true);
			}
			i->setVisited(true);
		}


		return friendsOfFriends;
	}


	//just testing code with namespace std graph



	//insert your graph after constructing in main
	//assign the two people you want to find as vertex v and vertex w
	//declare a vector of size of the number of nodes named found
	//
	//void backtrack(graph const &graph, int v, int w)
	/*vector<vector<int>> adjList;

	// Graph Constructor
	graph(vector<Edge> const &edges, int N)
	{
	// resize the vector to N elements of type vector<int>
	adjList.resize(N);

	// add edges to the undirected graph
	for (auto &edge: edges)
	{
	adjList[edge.src].push_back(edge.dest);
	adjList[edge.dest].push_back(edge.src);
	}
	}
	struct Edge {
	int src, dest;
	};
	void find_parent()
	{}
	void link_friends(graph const &graph, int v, int w, vector<bool> & found)
	{
	queue<int> q;

	found[V]= true;

	q.push(v);

	while(!q.empty())
	{
	v= q.front();
	q.pop();
	cout << v << " ";
	for( int W: graph.adjList[v])
	if(!found[W])
	{	
	found[w] = true;
	q.push[w];
	}
	}
	}
	*/

/*
	void friendpath(int a, int b, V) 
	{ 
		bool *visited = new bool[V]; 

		int *path = new int[V]; 
		int index = 0;

		for (int i = 0; i < V; i++) 
			visited[i] = false; 

		printPathsUtil(a, b, visited, path, index); 
	} 

	void printPathsUtil(int u, int d, bool visited[], 
			int path[], int &index) 
	{ 
		visited[u] = true; 
		path[index] = u; 
		index++; 
		list<int>::iterator i;
		if (u == d)
		{
			for (int i = 0; i<path_index; i++)
				cout << path[i] << " ";
			cout << endl;

		}
		else
		{
			for (i = adj[u].begin(); i != adj[u].end(); i++) 
				if (!visited[*i]) 
					printPathsUtil(*i, d, visited, path, index); 

		}
		index--; 
		visited[u] = false;


	}
*/

	int  bfs(const std::string& a, const std::string& b){
		for (auto key : getMap())
			key.second->setVisited(false);

		std::string origin = a;
		typedef std::vector<std::string> Path;
		Path p;
		p.push_back(a);
		std::queue<std::pair<vertex*,Path>> q;
		getMap()[a]->setVisited(true);
		std::pair<vertex*,Path> q_pair = std::make_pair(getMap()[a],p);
		q.push(q_pair);
		int level = 0;
		int j = 0;
		std::pair<std::string, int> path_pair;
		vector<std::pair<std::string,int>>v;

		while(!q.empty())
		{
			auto front = q.front().first;
			auto i_path = q.front().second;
			q.pop();
			for (auto i: front->getAdjList())
			{
				std::string name = i->getName();
				if (name == b)
				{
					for (auto &k :i_path)
					{
						cout << k << "--";
					}
					cout << b << "\n";

					return 0;
				}
				if (!i->isVisited())
				{
					i->setVisited(true);
					auto temp = i_path;
					temp.push_back(name);
					q_pair = std::make_pair(i,temp);
					q.push(q_pair);
					path_pair = std::make_pair(i->getName(),j);
					v.push_back(path_pair);
					j += 1;
				}
			}
		}
	}

	private:
	vmap map;
	std::vector<edge> edgeList;


};


#endif //FINDFRIENDS_GRAPH_H

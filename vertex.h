//
// Created by grant on 7/22/19.
//

#ifndef FINDFRIENDS_VERTEX_H
#define FINDFRIENDS_VERTEX_H

#include <string>
#include <list>
#include <iostream>

class vertex
{
public:

    std::vector<vertex*> &getAdjList() {
        return this->adjList;
    }


    vertex(std::string name):name(name){};

    //prints name of all vertices adjacent to this
    void printAdjList()
    {
        for (auto & iter : this->adjList)
        {
            std::cout << iter->name << " -> ";
        }
        std::cout << "null";

    }

    const std::string &getName() const
    {
        return name;
    }

    //gives access to visited tag in vertex
    void setVisited(bool visited)
    {
        this->visited = visited;
    }


    //returns true if person is directly linked to this*
    bool isAdj(vertex* person)
    {
        for(auto i : adjList)
        {
            if (i == person)
                return true;
        }
        return false;
    }

    bool isVisited()
    {
        return this->visited;
    }


private:
    std::vector<vertex*> adjList;
    std::string name;
    bool visited;
};


#endif //FINDFRIENDS_VERTEX_H

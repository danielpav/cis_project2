
#include <memory>
#include "graph.h"
#include <fstream>
#include <iostream>
//let argv[1] be the raw data of people and their friends
//let argv[2] be the people we are finding friends for

int main(int argc, char* argv[])
{
    if(argc != 3) //checks to see if file arguments are valid
    {
        std::cout << "check arguments";
        return 69;
    }


    //file streams to read in data
    ///remember to close filestreams later for dangling memory pointer
    std::fstream friends, findFriends;
    friends.open(argv[1]);
    findFriends.open(argv[2]);


    //generates a list for pairs for the graph class to construct a graph for
    int V= 0;
    std::vector<rawLink> rawFriends;
    while(friends.good())
    {
        rawLink link;

        friends >> link.first;
        friends >> link.second;
        friends >> std::ws;
	V++;
        rawFriends.push_back(link);
        if (friends.eof())
            break;
    }


    auto friendNetwork = graph(rawFriends);

//    while (findFriends.good())
//    {
//        std::string name;
//
//        findFriends >> name;
//        findFriends >> std::ws;
//
//        friendNetwork.generateMutualFriends(name);
//
//
//        if(findFriends.eof())
//            break;
//    }

    auto temp = friendNetwork.generateMutualFriends("Little");
    
	
    //for ( int i = 0; i< N ; i++)


    friendNetwork.bfs("Little", "Jackson");
	

    friends.close();
    findFriends.close();


    return 100;
}

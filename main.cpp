/*
	Gabriel Clark
	Terraria NPC Happiness
	May 2020
*/


#include "npc.hpp"
#include "group.hpp"
#include <iostream>
#include <vector>

using std::vector;
using std::string;

int main() 
{
	Group masterlist;
	masterlist.MakeListFromFile("npcs.tsv");
	
	return 0;
}


#ifndef GROUP_HPP
#define GROUP_HPP

#include "npc.hpp"
#include <vector>

using std::vector;

class Group
{
	private:
		vector<NPC> npcList;
	
	public:
		Group();
		Group(vector<NPC> npcVec);
		
		void AddNpc(NPC newNpc);
		bool MakeListFromFile(string filename);
};

#endif


#ifndef GROUP_HPP
#define GROUP_HPP

#include "npc.hpp"
#include <vector>
#include <string>

using std::vector;

const double lovesScore = 0.90;
const double likesScore = 0.95;
const double dislikesScore = 1.50;
const double hatesScore = 1.10;
const double nonCrowdingScore = 0.90;

class Group
{
	private:
		vector<NPC> npcList;
		double score;
		string biome;
		
		void CalculateNewScore();
	
	public:
		Group();
		Group(vector<NPC> npcVec);
		
		void MakeListFromFile(string filename);
		
		void AddNpc(NPC newNpc);
		void AddNpc(NPC npc, int position);
		void RemoveLastNpc();
		void RemoveNPC(int position);
		void RemoveAllNpcs();
		NPC* Find(string npcName);
		
		vector<NPC> GetNpcList();
		double GetScore();
		void SetBiome(string biome);
		string GetBiome();
		int GetNumberOfNpcs();
		NPC GetNpc(int position);
};

#endif


#ifndef NPC_HPP
#define NPC_HPP

#include <vector>
#include <string>

using std::string;
using std::vector;

class NPC
{
	private:
		string name;
		
		vector<NPC> npcLoves;
		vector<NPC> npcLikes;
		vector<NPC> npcDislikes;
		vector<NPC> npcHates;
		
		string npcLovesNames;
		string npcLikesNames;
		string npcDislikesNames;
		string npcHatesNames;
		
		string biomeLove;
		string biomeLike;
		string biomeDislike;
		string biomeHate;
		
		bool Find(NPC npc, vector<NPC> npcVec);
	
	public:
		NPC();
		NPC(string name);
		
		void SetName(string name);
		string GetName();
		
		void AddLove(NPC* npc);
		void AddLike(NPC* npc);
		void AddDislike(NPC* npc);
		void AddHate(NPC* npc);
		
		void SetNpcLovesNames(string names);
		string GetNpcLovesNames();
		
		void SetNpcLikesNames(string names);
		string GetNpcLikesNames();
		
		void SetNpcDislikesNames(string names);
		string GetNpcDislikesNames();
		
		void SetNpcHatesNames(string names);
		string GetNpcHatesNames();
		
		void SetBiomeLove(string);
		void SetBiomeLike(string);
		void SetBiomeDislike(string);
		void SetBiomeHates(string);
		
		bool DoesLove(NPC npc);
		bool DoesLike(NPC npc);
		bool DoesDislike(NPC npc);
		bool DoesHate(NPC npc);
		
		bool DoesBiomeLove(string biome);
		bool DoesBiomeLike(string biome);
		bool DoesBiomeDislike(string biome);
		bool DoesBiomeHate(string biome);
};

#endif

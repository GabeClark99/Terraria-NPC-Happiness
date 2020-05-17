
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
		
		vector<string> npcLoves;
		vector<string> npcLikes;
		vector<string> npcDislikes;
		vector<string> npcHates;
		
		string npcLovesNames;
		string npcLikesNames;
		string npcDislikesNames;
		string npcHatesNames;
		
		string biomeLike;
		string biomeDislike;
		
		bool Find(string);
	
	public:
		NPC();
		NPC(string name);
		
		void SetName(string name);
		string GetName();
		
		void AddLove(NPC npc);
		void AddLike(NPC npc);
		void AddDislike(NPC npc);
		void AddHate(NPC npc);
		
		void SetNpcLovesNames(string names);
		void SetNpcLikesNames(string names);
		void SetNpcDislikesNames(string names);
		void SetNpcHatesNames(string names);
		
		void SetBiomeLike(string);
		void SetBiomeDislike(string);
		
		bool DoesLove(string);
		bool DoesLike(string);
		bool DoesDislike(string);
		bool DoesHate(string);
};

#endif

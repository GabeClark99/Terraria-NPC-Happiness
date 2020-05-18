/*
	Gabriel Clark
	Terraria NPC Happiness
	May 2020
*/


#include "npc.hpp"
#include "group.hpp"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int CalculateTotalScore(vector<Group> groupVec);

int main() 
{
	Group mastergroup;
	mastergroup.MakeListFromFile("npcs2.tsv");
	
	vector<NPC> npcVec = mastergroup.GetNpcList();
	vector<Group> groupVec;
	vector<Group> bestVersion = groupVec;
	int bestTotalScore = 0;
	
	for(int i = 0; i < npcVec.size(); ++i)
	{
cout << endl << "i: " << i << endl;
		for(int j = 0; j < groupVec.size(); ++j)
		{
cout << endl << "\tj: " << j << endl;
			groupVec.at(j).AddNpc( npcVec.at(i) );
			
			int totalScore = CalculateTotalScore(groupVec);
//cout << "\ttotalScore: " << totalScore << endl;
//cout << "\tbestTotalScore: " << bestTotalScore << endl;
			if(totalScore >= bestTotalScore) // if current version's score is better than bestVersion's score...
			{
//cout << "\tupdating bestVersion..." << endl;
				bestVersion = groupVec;
				bestTotalScore = totalScore;
			}
			groupVec.at(j).RemoveLastNpc(); // undo what we just did to keep the same starting state (we have a copy in bestVersion if this version was better)
		}
		
		Group newGroup;
		newGroup.AddNpc( npcVec.at(i) );
		groupVec.push_back(newGroup);
		
		int totalScore = CalculateTotalScore(groupVec);
//cout << "totalScore: " << totalScore << endl;
//cout << "bestTotalScore: " << bestTotalScore << endl;
		if(totalScore >= bestTotalScore) // if current version's score is better than bestVersion's score...
		{
//cout << "updating bestVersion..." << endl;
			bestVersion = groupVec;
			bestTotalScore = totalScore;
		}
		groupVec.pop_back(); // undo what we just did to keep the same starting state (we have a copy in bestVersion if this version was better)
		
		groupVec = bestVersion; // set the current version to the best one to improve during the next run
	}
	
	cout << "Best Total Score: " << bestTotalScore << endl;
	cout << "Best Version: ";
	for(int i = 0; i < bestVersion.size(); ++i)
	{
		vector<NPC> groupList = bestVersion.at(i).GetNpcList();
		
		for(int j = 0; j < groupList.size(); ++j)
		{
			cout << groupList.at(j).GetName();
			
			if( j < groupList.size() - 1 )
			{
				cout << ",";
			}
		}
		
		if(i < groupVec.size() - 1)
		{
			cout << " - ";
		}
	}
	
	return 0;
}

int CalculateTotalScore(vector<Group> groupVec)
{
	int totalScore = 0;
	
	for(int i = 0; i < groupVec.size(); ++i)
	{
		totalScore += groupVec.at(i).GetScore();
	}
	
	return totalScore;
}






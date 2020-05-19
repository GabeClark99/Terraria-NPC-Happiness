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

void Initialize(vector<Group>* groupsVec);

void UpdateBestVersion(vector<Group>* groupVec, vector<Group>* bestVersion, double* bestScore);

double CalculateAverageScore(vector<Group> groupVec);

void DisplayVersion(vector<Group> currentVersion);

int main() 
{
	Group mastergroup;
	mastergroup.MakeListFromFile("npcs.tsv");
	
	vector<NPC> npcVec = mastergroup.GetNpcList();
	vector<Group> groupsVec;
	
	Initialize(&groupsVec);
	
	vector<Group> bestVersion = groupsVec;
	double bestScore = 1.0;
	
	for(int i = 0; i < npcVec.size(); ++i)
	{
		groupsVec = bestVersion;
		
		for(int j = 0; j < groupsVec.size(); ++j)
		{
			groupsVec.at(j).AddNpc( npcVec.at(i) ); // add current npc to current group
			
			UpdateBestVersion(&groupsVec, &bestVersion, &bestScore); // check if its better, and update if it is
			
			groupsVec.at(j).RemoveLastNpc(); // undo to try another method
		}
	}
	
	cout << "Best Average: " << CalculateAverageScore(bestVersion) << endl;
	cout << "Best Version: " << endl; DisplayVersion(bestVersion); cout << endl;
	
	
	
	return 0;
}

void Initialize(vector<Group>* groupsVec)
{
	// creating a group, setting the biome, and adding it to the groups vector
	Group forrest; forrest.SetBiome("Forest"); groupsVec->push_back(forrest);
	Group desert; desert.SetBiome("Desert"); groupsVec->push_back(desert);
	Group jungle; jungle.SetBiome("Jungle"); groupsVec->push_back(jungle);
	Group snow; snow.SetBiome("Snow"); groupsVec->push_back(snow);
	Group ocean; ocean.SetBiome("Ocean"); groupsVec->push_back(ocean);
	Group hallow; hallow.SetBiome("Hallow"); groupsVec->push_back(hallow);
	Group underground; underground.SetBiome("Underground"); groupsVec->push_back(underground);
	Group surfaceMushroom; surfaceMushroom.SetBiome("Surface Mushroom"); groupsVec->push_back(surfaceMushroom);
}

void UpdateBestVersion(vector<Group>* groupVec, vector<Group>* bestVersion, double* bestScore)
{
	//cout << "\tcurrent version:\n"; DisplayVersion(*groupVec); cout << endl;
	
	//cout << endl << "---CALCULATING CURRENT SCORE---" << endl;
	double currentScore = CalculateAverageScore(*groupVec);
	/*cout << "---CALCULATING BEST SCORE---" << endl;
	double bestScore = CalculateAverageScore(*bestVersion);*/
	
	//cout << endl;
	//cout << "\tcurrent score: " << currentScore << endl;
	//cout << "\tbest score: " << *bestScore << endl;
	
	int numNpcsCurrentVersion = 0;
	for(int i = 0; i < groupVec->size(); ++i)
	{
		numNpcsCurrentVersion += groupVec->at(i).GetNumberOfNpcs();
	}
	
	int numNpcsBestVersion = 0;
	for(int i = 0; i < bestVersion->size(); ++i)
	{
		numNpcsBestVersion += bestVersion->at(i).GetNumberOfNpcs();
	}
	
	if(currentScore <= *bestScore || numNpcsCurrentVersion > numNpcsBestVersion)
	{
		//cout << "\tupdating best score..." << endl;
		
		*bestVersion = *groupVec;
		*bestScore = currentScore;
	}
	else
	{
		//cout << endl;
	}
	
	return;
}

double CalculateAverageScore(vector<Group> groupsVec)
{
	double avg;
	double sum = 0.0;
	int totalNpcs = 0;
	
	for(int i = 0; i < groupsVec.size(); ++i)
	{
		if(groupsVec.at(i).GetNumberOfNpcs() > 0)
		{
			totalNpcs++;
			
			double score = groupsVec.at(i).GetScore();
			
			//cout << "score from npc " << i << ": " << score << endl; 
			
			sum += score;
			//cout << "\t\tsum: " << sum << endl << endl;
		}
		else
		{
			//cout << "skipping biome " << groupsVec.at(i).GetBiome() << endl << endl;
			// the group doesn't have any npcs, so its score is 1.0, which doesn't affect the average.
		}
	}
	
	avg = sum / totalNpcs;
	
	return avg;
}

void DisplayVersion(vector<Group> currentVersion)
{
	for(int i = 0; i < currentVersion.size(); ++i)
	{
		cout << "\t" << currentVersion.at(i).GetBiome() << ": ";
		
		vector<NPC> npcList = currentVersion.at(i).GetNpcList();
		
		for(int j = 0; j < npcList.size(); ++j)
		{
			cout << npcList.at(j).GetName();
			
			if( j < npcList.size() - 1 )
			{
				cout << ", ";
			}
		}
		
		if(i < currentVersion.size() - 1)
		{
			cout << /*" - "*/ endl;
		}
	}
}



/*
	Gabriel Clark
	Terraria NPC Happiness
	May 2020
*/


#include "npc.hpp"
#include "group.hpp"
#include <iostream>
#include <vector>
#include <time.h> // used to seed randomness

using std::cout;
using std::endl;
using std::vector;
using std::string;

void Initialize(vector<NPC>* npcVec, vector<Group>* groupsVec);

void Shuffle(vector<NPC>* npcVec);

void DisplayNpcs(vector<NPC> npcVec);

void FindNpcGrouping(vector<Group>* groupVec, vector<NPC>* npcVec);

void UpdateBestVersion(vector<Group>* groupVec, vector<Group>* bestVersion, double* bestScore);

double CalculateAverageScore(vector<Group> groupVec);

void DisplayVersion(vector<Group> currentVersion);

void EvictNpcs(vector<Group>* groupsVec);


int main() 
{
	
	vector<Group> groupsVec;
	vector<NPC> npcVec;
	
	Initialize(&npcVec, &groupsVec);
	
	for(int i = 0; i < 10; ++i)
	{
		Shuffle(&npcVec);
	
		DisplayNpcs(npcVec);
		
		FindNpcGrouping(&groupsVec, &npcVec);
		
		cout << "Best Average: " << CalculateAverageScore(groupsVec) << endl;
		cout << "Best Version: " << endl; DisplayVersion(groupsVec); cout << endl;
		
		EvictNpcs(&groupsVec);
	}
	
	
	
	
	
	
	return 0;
}

void Initialize(vector<NPC>* npcVec, vector<Group>* groupsVec)
{
	srand( time(NULL) );
	
	Group mastergroup;
	mastergroup.MakeListFromFile("npcs.tsv");
	*npcVec = mastergroup.GetNpcList();
	
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

void Shuffle(vector<NPC>* npcVec)
{
	vector<NPC> tempNpcVec = *npcVec;
	
	npcVec->clear(); // empties the vector
	
	while(tempNpcVec.size() > 0)
	{
		int randomNpcPos = rand() % tempNpcVec.size(); // picks a random position
		NPC randomNpc = tempNpcVec.at(randomNpcPos); // grabs the npc associated with that position
		
		npcVec->push_back( randomNpc ); // add the npc to the vector
		
		tempNpcVec.erase(tempNpcVec.begin() + randomNpcPos); // removes the npc from the options to choose from
	}
	
	return;
}

void DisplayNpcs(vector<NPC> npcVec)
{
	for(int i = 0; i < npcVec.size(); ++i)
	{
		cout << i << " " << npcVec.at(i).GetName() << endl;
	}
	
	cout << endl;
	
	return;
}

void FindNpcGrouping(vector<Group>* groupsVec, vector<NPC>* npcVec)
{
	vector<Group> bestVersion = *groupsVec;
	double bestScore = 1.0;
	
	for(int i = 0; i < npcVec->size(); ++i) // for every npc...
	{
		*groupsVec = bestVersion;
		
		for(int j = 0; j < groupsVec->size(); ++j) // for every group...
		{
			groupsVec->at(j).AddNpc( npcVec->at(i) ); // add current npc to current group
			
			UpdateBestVersion(groupsVec, &bestVersion, &bestScore); // check if its better, and update if it is
			
			groupsVec->at(j).RemoveLastNpc(); // undo to try another method
		}
	}
	
	*groupsVec = bestVersion;
	
	return;
}

void UpdateBestVersion(vector<Group>* groupVec, vector<Group>* bestVersion, double* bestScore)
{
	//cout << "\tcurrent version:\n"; DisplayVersion(*groupVec); cout << endl << endl;
	
	double currentScore = CalculateAverageScore(*groupVec);
	
	//cout << "\tcurrent average: " << currentScore << endl;
	//cout << "\tbest average: " << *bestScore << endl << endl;
	
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
		//cout << "\tupdating best average..." << endl << endl;
		
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
	
	for(int i = 0; i < groupsVec.size(); ++i) // for every group...
	{
		totalNpcs += groupsVec.at(i).GetNumberOfNpcs();
		
		if(groupsVec.at(i).GetNumberOfNpcs() > 0) // if it has any npcs in it...
		{
			//totalNpcs++;
			
			double score = groupsVec.at(i).GetScore();
			
			//cout << "score from npc " << i << ": " << score << endl; 
			
			sum += score;
			//cout << "sum: " << sum << endl << endl;
		}
		else
		{
			//cout << "skipping biome " << groupsVec.at(i).GetBiome() << endl << endl;
			// the group doesn't have any npcs, so its score is 1.0, which doesn't affect the average.
		}
	}
	
	//cout << "\tsum: " << sum << ", total number of npcs: " << totalNpcs << endl << endl;
	
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

void EvictNpcs(vector<Group>* groupsVec)
{
	for(int i = 0; i < groupsVec->size(); ++i)
	{
		groupsVec->at(i).RemoveAllNpcs();
	}
	
	return;
}






#include "group.hpp"
#include "npc.hpp"
#include <iostream>
#include <vector>
#include <fstream> // file input
#include <sstream> // extracting data from raw line data

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::istringstream;

Group::Group()
{
	
}

Group::Group(vector<NPC> npcVec) { this->npcList = npcVec; }

void Group::AddNpc(NPC newNpc) { this->npcList.push_back(newNpc); }


// Goes through each line of file, pulling in relevent data to create npc instance, minus
// the neighbor preferences because it needs the npc variables for that before I set them.
// For instance, Angler likes Demolitionist, but Demolitionist gets created after Angler.
// Therefore, I cannot add teh Demolitionist variable to Angler likes becuase it does not exist yet.
// Due to this, it only records the names on the first pass, then goes through every npc and adds
// the right variable after every npc variable is created.
bool Group::MakeListFromFile(string filename) // returns bool indicating the success of creating the list
{
	std::ifstream file;
	file.open(filename.c_str()); // converting to cstring to make function happy
	
	if( !file.is_open() ) // error checking for correct file name
	{
		return false;
	}
	
	string lineRaw;
	
	getline(file, lineRaw); // skipping first header line
	getline(file, lineRaw); // skipping second header line
	while( getline(file, lineRaw) ) // get each line, stop when no more lines
	{
		vector<string> tokens;
		
		istringstream lineRawStream(lineRaw);
cout << "\t lineRaw: " << lineRaw << endl;
		string token;
		while( getline(lineRawStream, token, '\t') ) // step through each token in lineRaw, splitting on tab character
		{
			tokens.push_back(token);
		}
		
cout << "tokens: ";
for(unsigned int i = 0; i < tokens.size(); ++i)
{
	cout << tokens.at(i) << " ";
}
cout << endl << endl;
		
		NPC* npc = new NPC();
		npc->SetName( tokens.at(0) );
		npc->SetBiomeLike( tokens.at(1) );
		npc->SetBiomeDislike( tokens.at(2) );
		npc->SetNpcLovesNames( tokens.at(3) );
		npc->SetNpcLikesNames( tokens.at(4) );
		npc->SetNpcDislikesNames( tokens.at(5) );
		npc->SetNpcHatesNames( tokens.at(6) );
		
		this->AddNpc(*npc);
	}
	
for(unsigned int i = 0; i < this->npcList.size(); ++i)
{
	cout << i << " " << this->npcList.at(i).GetName() << endl;
}
	
	// TODO: go through every npc's neighbor preference name string,
	//		 find a npc variable with that name, and add that npc variable 
	//		 to their preference vector.
	
	file.close();
	return true;
}


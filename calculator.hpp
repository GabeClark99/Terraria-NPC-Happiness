
#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "group.hpp"
#include <vector>

using std::vector;

class Calculator
{
	private:
		const int loveScore = 2;
		const int likeScore = 1;
		const int neutralScore = 0;
		const int dislikeScore = -1;
		const int hateScore = -2;
		
		vector<vector<Group>> universes;
		vector<Group> groups;
		
	public:
		Calculator();
		
		void AddGroup(Group group);
		
		void Run(Group npcs);
};

#endif


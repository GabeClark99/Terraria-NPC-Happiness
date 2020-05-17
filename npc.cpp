
#include "npc.hpp"

NPC::NPC() {}

NPC::NPC(string name) { this->name = name;}



void NPC::SetName(string name) { this->name = name; }
string NPC::GetName() { return this->name; }



void NPC::AddLove(NPC npc) {}

void NPC::AddLike(NPC npc) {}

void NPC::AddDislike(NPC npc) {}

void NPC::AddHate(NPC npc) {}



void NPC::SetNpcLovesNames(string names) { this->npcLovesNames = names; }

void NPC::SetNpcLikesNames(string names) { this->npcLikesNames = names; }

void NPC::SetNpcDislikesNames(string names) { this->npcDislikesNames = names; }

void NPC::SetNpcHatesNames(string names) {  this->npcHatesNames = names;  }



void NPC::SetBiomeLike(string biome) { this->biomeLike = biome; }

void NPC::SetBiomeDislike(string biome) { this->biomeDislike = biome; }



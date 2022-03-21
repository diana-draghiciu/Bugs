#pragma once
#include <string>
#include <vector>
#include "Bug.h"
class BugRepo
{
private:
	std::vector<Bug> buguri;
	std::string file;
public:
	BugRepo(const std::string& file) : file(file){ load();}
	const std::vector<Bug>& getElems() { return this->buguri; };

	void sortPriority();
	void load();

	//!! astea trebuia facute in service, si teste si specificatii la repo si serv!!
	void remove(int idx1, int idx2);
	void moveUp(int idx1, int idx2);
	void moveDown(int idx1, int idx2);
};


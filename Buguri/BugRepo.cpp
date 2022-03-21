#include "BugRepo.h"
#include <algorithm>
#include <sstream>
#include <fstream>

bool compare(const Bug& b1, const Bug& b2) {
	if (b1.getPriority() > b2.getPriority())
		return false;
	return true;
}
void BugRepo::sortPriority()
{
	std::sort(this->buguri.begin(), this->buguri.end(), &compare);
}

void BugRepo::load()
{
	std::ifstream fin;
	fin.open(this->file);
	if (!fin.is_open())
		return;
	Bug b;
	fin.get();
	while (!fin.eof()) {
		fin >> b;
		this->buguri.push_back(b);
	}
	fin.close();
}

void BugRepo::remove(int idx1, int idx2)
{
	this->buguri[idx1].getSteps().erase(this->buguri[idx1].getSteps().begin() + idx2);
}

void BugRepo::moveUp(int idx1,int idx2)
{
	std::swap(this->buguri[idx1].getSteps()[idx2], this->buguri[idx1].getSteps()[idx2-1]);
}

void BugRepo::moveDown(int idx1, int idx2)
{
	std::swap(this->buguri[idx1].getSteps()[idx2], this->buguri[idx1].getSteps()[idx2 + 1]);
}

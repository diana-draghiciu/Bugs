#include "Bug.h"
#include <sstream>

std::ostream& operator<<(std::ostream& out, const Bug& b)
{
	out << "\n" << b.getName() << " " << b.getPriority()<<" ";
	for (const auto& e : b.steps) {
		out << e<<",";
	}
	return out;
}

std::istream& operator>>(std::istream& in, Bug& b)
{
	in.clear(); in.sync();

	std::string name, priority, step, line;
	int pr;

	std::getline(in, line);
	std::stringstream attrib(line);

	std::getline(attrib, name, ' ');
	b.name = name;
	std::getline(attrib, priority, ' ');
	std::stringstream ax(priority);
	ax >> pr;
	b.priority = pr;

	while (std::getline(attrib, step, ',')) {
		b.steps.push_back(step);
	}

	return in;
}

Bug::Bug()
{
	this->name = "";
	this->priority = 0;
	this->steps.clear();
}

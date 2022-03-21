#pragma once
#include <string>
#include <vector>
class Bug
{
private:
	std::string name;
	int priority;
	std::vector<std::string> steps;
public:
	Bug();
	Bug(const std::string& name, int priority, std::vector<std::string>& steps) : name(name), priority(priority), steps(steps) {}

	//getters
	const std::string& getName() const { return this->name; };
	int getPriority() const { return this->priority; };
	std::vector<std::string>& getSteps() { return this->steps; };

	friend std::ostream& operator<<(std::ostream& out, const Bug& b);
	friend std::istream& operator>>(std::istream& in, Bug& b);
};


#include "BugGUI.h"
#include <QHBoxLayout>

void BugGUI::gui_init()
{
	QHBoxLayout* layout = new QHBoxLayout{ this };

	this->bugList = new QListWidget{};
	// set the selection model
	this->bugList->setSelectionMode(QAbstractItemView::SingleSelection);
	layout->addWidget(this->bugList);

	QWidget* rightSide = new QWidget{};
	QVBoxLayout* vLayout = new QVBoxLayout{ rightSide };

	//INFO Steps
	this->stepsList = new QListWidget{};
	// set the selection model
	this->stepsList->setSelectionMode(QAbstractItemView::SingleSelection);
	vLayout->addWidget(this->stepsList);

	//Buttons
	QWidget* buttonsWidget = new QWidget{};
	buttonsWidget->setStyleSheet("background-color: rgb(224,224,224)");
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	this->deleteButton = new QPushButton("Delete step");
	this->upButton= new QPushButton("Move up");
	this->downButton = new QPushButton("Move down");
	
	hLayout->addWidget(this->deleteButton);
	hLayout->addWidget(this->upButton);
	hLayout->addWidget(this->downButton);

	vLayout->addWidget(buttonsWidget);

	//Add rightside to general layout
	layout->addWidget(rightSide);

	//connections
	QObject::connect(this->bugList, &QListWidget::itemSelectionChanged, this, [this]() {this->selection(); });
	QObject::connect(this, &BugGUI::UpdatedSignal, this, &BugGUI::selection);
	// add button connections
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &BugGUI::delete_step);
	QObject::connect(this->upButton, &QPushButton::clicked, this, &BugGUI::move_up);
	QObject::connect(this->downButton, &QPushButton::clicked, this, &BugGUI::move_down);
	//sort priority
	this->repo->sortPriority();
}

void BugGUI::populate()
{
	// clear the list, if there are elements in it
	if (this->bugList->count() > 0)
		this->bugList->clear();

	for (const auto& e : this->repo->getElems()) {
		std::string aux = std::to_string(e.getPriority());
		QString itemInList = QString::fromStdString(e.getName()) + " " + QString::fromStdString(aux);
		QFont f{ "Verdana", 15, };
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		item->setFont(f);;
		this->bugList->addItem(item);
	}
}

void BugGUI::selection()
{
	int idx = get_bug_index();
	if (idx == -1)
		return;
	Bug b = this->repo->getElems()[idx];

	//remove items in stepslist
	this->stepsList->clear();

	QFont f{ "Verdana", 15, };
	for (const auto& elem : b.getSteps()) {
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(elem) };
		item->setFont(f);;
		this->stepsList->addItem(item);
	}
}

int BugGUI::get_bug_index()
{
	int idx;
	if (this->bugList->count() == 0)
		idx = -1;

	// get selected index
	QModelIndexList index = this->bugList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
		return -1;

	idx = index.at(0).row();

	if (idx >= this->repo->getElems().size())
		return -1;

	return idx;
}

int BugGUI::get_step_index()
{
	int idx;
	if (this->stepsList->count() == 0)
		idx = -1;

	// get selected index
	QModelIndexList index = this->stepsList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
		return -1;

	idx = index.at(0).row();

	return idx;
}


void BugGUI::delete_step()
{
	int idx = get_bug_index();
	if (idx == -1)
		return;

	Bug b = this->repo->getElems()[idx];

	if (b.getSteps().size() == 0)
		return;
	//------------------------------------------
	int idx1 = get_step_index();
	if (idx1 == -1)
		return;
	
	this->repo->remove(idx, idx1);

	emit UpdatedSignal();
}

void BugGUI::move_up()
{
	int idx = get_bug_index();
	if (idx == -1)
		return;

	Bug b = this->repo->getElems()[idx];

	if (b.getSteps().size() == 0)
		return;
	//------------------------------------------
	int idx1 = get_step_index();
	if (idx1 == -1 || idx1==0)
		return;

	this->repo->moveUp(idx, idx1);

	emit UpdatedSignal();
}

void BugGUI::move_down()
{
	int idx = get_bug_index();
	if (idx == -1)
		return;

	Bug b = this->repo->getElems()[idx];

	if (b.getSteps().size() == 0)
		return;
	//------------------------------------------
	int idx1 = get_step_index();
	if (idx1 == -1 || idx1 == b.getSteps().size()-1)
		return;

	this->repo->moveDown(idx, idx1);

	emit UpdatedSignal();
}

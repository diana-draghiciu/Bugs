#pragma once
#include <qwidget.h>
#include <QListWidget>
#include "BugRepo.h"
#include <QPushButton>
class BugGUI:public QWidget
{
	Q_OBJECT;
private:
	BugRepo* repo;
	QListWidget* bugList;
	QListWidget* stepsList;
	QPushButton* deleteButton;
	QPushButton* upButton;
	QPushButton* downButton;

public:
	BugGUI(QWidget* parent, BugRepo* bug) : QWidget{ parent }, repo(bug){gui_init(); populate(); }
	void gui_init();
	void populate();
	void selection();
	int get_bug_index();
	int get_step_index();

	void delete_step();
	void move_up();
	void move_down();

signals:
	void UpdatedSignal();
};


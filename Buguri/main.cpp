#include "Buguri.h"
#include <QtWidgets/QApplication>
#include "BugRepo.h"
#include "BugGUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BugRepo* repo=new BugRepo{ "buguri.txt" };
    BugGUI gui{ 0,repo };
    gui.show();
    return a.exec();
}

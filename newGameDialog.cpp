#include "newgamedialog.h"
#include <iostream>

newGameDialog::newGameDialog(QWidget *parent):QDialog(parent)
{
	setupUi(this);
	std::cout << "newGameDialog" << std::endl;
}

#include "newgamedialog.h"
#include <iostream>

newGameDialog::newGameDialog(QWidget *parent):QDialog(parent)
{
	setupUi(this);
	std::cout << "newGameDialog" << std::endl;
}

newGameDialog::~newGameDialog() {
	std::cout << "newGameDialog deleted" << std::endl;
}

void newGameDialog::on_buttonBox_accepted()
{
	std::cout << "on_buttonBox_accepted" << std::endl;
}

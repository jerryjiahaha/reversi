#ifndef NEW_GAME_H_
#define NEW_GAME_H_
#include <QDialog>

#include "ui_newgamedialog.h"

namespace Ui {
	class newGameDialog;
}

class newGameDialog : public QDialog, public Ui::newGameDialog
{
	Q_OBJECT
	public:
		newGameDialog(QWidget *parent=0);
		~newGameDialog();
	signals:
		void newGameStart(void *arg);
	private slots:
		void on_buttonBox_accepted();
};

#endif

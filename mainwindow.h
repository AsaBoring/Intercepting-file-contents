#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stdlib.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    string slotFetchKeyLine(string strFilePath , string strPara);
    string slotFetchStringForLable(string labelOne , string labelSec , string strSrc);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

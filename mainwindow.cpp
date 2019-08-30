#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <string>
#include <strstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    string ret = slotFetchKeyLine("05.jinshu.pdf_page16.inkml","context xml:id");
    int i = atoi(ret.c_str());
    qDebug()<<"ret----------------is : "<<ret.c_str();
    qDebug()<<"id is :"<<i;
}

MainWindow::~MainWindow()
{
    delete ui;
}

string MainWindow::slotFetchKeyLine(string strFilePath, string strPara)
{
    bool isLastLine = true;
    int lastIndex = 0;
    string strLabel = "contextRef";
    string strLineFeed = "\n";
    string strRet = "";
    FILE * fp = fopen(strFilePath.c_str(),"rb+");
    if(fp)
    {
        fseek(fp,0,SEEK_END);
        int nFileSize = ftell(fp);
        qDebug()<<"nFileSize is : "<<nFileSize;
        for(int var = nFileSize-1 ; var > 0 ; --var)
        {
            fseek(fp,var,SEEK_SET);
            char tmp[1];
            fread(tmp,1,1,fp);
            string strCompare(tmp);
            if(strCompare == strLineFeed)
            {

            }
            if(/*strcmp(strCompare.c_str(),strLineFeed.c_str()) == 0*/strCompare == strLineFeed)
            {
                if(isLastLine)
                {
                    isLastLine = false;
                    int lastLineLabelIndex = ftell(fp);
                    lastIndex = lastLineLabelIndex;
                }else{
                    int lastLineLabelIndex = ftell(fp);
                    int lineSize = lastIndex-lastLineLabelIndex-1;
                    char lineTmp[lineSize+1];
                    fread(lineTmp,lineSize,1,fp);
                    lastIndex = lastLineLabelIndex;
                    string strTmp(lineTmp);
                    if(strTmp.find(strPara.c_str()) != -1)
                    {
                        strRet = slotFetchStringForLable("\"","\"",strTmp);
                        fclose(fp);
                        return strRet;
                    }
                }
            }
        }

        if(lastIndex != 0)
        {
            fseek(fp,0,SEEK_SET);
            char lineTmp[lastIndex];
            fread(lineTmp,lastIndex-1,1,fp);
            string strTmp(lineTmp);
            if(strTmp.find(strPara.c_str()) != -1)
            {
                strRet = slotFetchStringForLable("\"","\"",strTmp);
                fclose(fp);
                return strRet;
            }
        }
        fclose(fp);
    }
}

string MainWindow::slotFetchStringForLable(string labelOne, string labelSec, string strSrc)
{
    int nPos1 = strSrc.find_last_of(labelOne);
    int nPos2 = strSrc.find_last_of(labelSec, nPos1 - 1);

    string strRet = strSrc.substr(nPos2 + 1, nPos1 - nPos2 - 1);
    strRet.erase(0,3);

    return strRet;
}


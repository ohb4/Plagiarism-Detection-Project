#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPixmap>
#include <QLabel>
#include <QDateTime>
#include<QTextCharFormat>
#include<QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    print();
    ui->tabWidget->hide();
    ui->Desktoploader->setEnabled(false);
    ui->line_2->hide();
    ui->ExitButton->hide();
    ui->MessageLabel->setText("You Have Not Uploaded a Document Yet!\nUpload the Document for Checking in the Upload Files Tab.");
    ui->submitFile->setEnabled(false);
    ui->tabWidget->setCurrentIndex(0);
    ui->MinimizeButton->hide();
}

QString filenames[] = {"document1.txt", "document2.txt", "document3.txt", "document4.txt"};

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print()
{
    QString filename = "C:/Users/obadw/Desktop/image.jpg";
    QPixmap pixmap(filename);
    ui->Wallpaper->setPixmap(pixmap);
    QString file = "C:/Users/obadw/Desktop/Detector.jpg";
    QPixmap det(file);
    ui->Detector_2->setPixmap(file);
    ui->Detector_2->setPixmap(det.scaled(ui->Detector_2->size(), Qt::KeepAspectRatio));
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDate = currentDateTime.toString("dd/MM/yyyy");
    QString formattedTime = currentDateTime.toString(" hh:mm:ss ");
    ui->date->setText(formattedDate);
    ui->time->setText(formattedTime);
}

int *pre_kmp(QString pattern)
{
    int size = pattern.size();
    int *pie=new int [size];
    pie[0] = 0;
    for(int i=1;i<size;i++)
    {
        int k=pie[i -1];

        while(k>0 && pattern[k] != pattern[i] )
        {
            k=pie[k-1];
        }
        if( pattern[k] == pattern[i] )
        {
            k=k+1;
        }
        pie[i]=k;
    }

    delete[] pie;
    return pie;

}

void kmp(QString text,QString pattern)
{
    int* pie=pre_kmp(pattern);
    int matched_pos=0;
    for(int current=0; current< text.length(); current++)
    {
        while (matched_pos > 0 && pattern[matched_pos] != text[current] )
            matched_pos = pie[matched_pos-1];

        if(pattern[matched_pos] == text[current])
            matched_pos = matched_pos+1;

        if( matched_pos == pattern.length())
        {
            matched_pos = pie[matched_pos-1];
        }
    }
}



void MainWindow::processFile(const QString& filename)
{
    QString corpus_dir = "C:/Users/Y/Desktop/test/";
    QString filec = "";
    QString corpusContents = "";

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Unable to open file");
        return;
    }

    QTextStream in(&file);
    QString fileContents = in.readAll();
    ui->textEdit->setText(fileContents);


    for (int i = 0; i < 4; i++)
    {
        QFile corpusFile(filenames[i]);





        QTextStream corpusIn(&corpusFile);
        corpusContents += corpusIn.readAll();

        corpusFile.close();
    }


    QVector<QString> v1;
    QVector<QString> v2;



    QStringList fileLines = fileContents.split('\n');
    QStringList corpusLines = corpusContents.split('\n');

    for(const QString& s1 : fileLines)
    {
        v1.append(s1);
    }

    for(const QString& s2 : corpusLines)
    {
        v2.append(s2);
    }


    int totalLines = fileLines.length();
    int plagLines = 0;
    for (int i = 0; i < totalLines; i++)
    {
        QString line = fileLines[i];
        for (int j = 0; j < corpusLines.length(); j++)
        {
            QString corpusLine = corpusLines[j];
            if (v1.at(i) == v2.at(j))
            {
                plagLines++;
                break;
            }
            else if (j == corpusLines.length() - 1)
            {
                QString pattern = line;
                QString text = corpusContents;
                int *pie = pre_kmp(pattern.toStdString().data());
                //rabinKarp(line,corpusLine,totalLines);
                int matched_pos = 0;
                for (int current = 0; current < text.length(); current++)
                {


                    while (matched_pos > 0 && pattern[matched_pos] != text[current])
                        matched_pos = pie[matched_pos-1];
                    if (pattern[matched_pos] == text[current])
                        matched_pos = matched_pos+1;
                    if (matched_pos == (pattern.length()))
                    {
                        plagLines++;
                        break;
                    }
                }
            }
        }
    }

    float plagPercentage = (plagLines * 100.0f) / totalLines;
    QString result = QString::number(plagPercentage, 'f', 2) + "%";
    ui->percentage->setText(result);
    ui->percentage->setAlignment(Qt::AlignCenter);


    QString c1 = "Little to No Plagarsim Detected ";
    QString c2 = "Adequate Plagarsim Detected ";
    QString c3 = "Severe Plagarsim Detected ";

    QTextEdit *TextEdit = ui->colorindicater;

    TextEdit->clear();
    TextEdit->selectAll();
    TextEdit->setFontWeight(QFont::Normal);
    TextEdit->setFontPointSize(15);
    TextEdit->setTextColor(Qt::black);
    TextEdit->setTextBackgroundColor(Qt::white);
    TextEdit->setAlignment(Qt::AlignHCenter);



    if(plagPercentage <=10.0)
    {
       TextEdit->setFontWeight(QFont::Bold);
       TextEdit->setTextColor(Qt::green);
       TextEdit->insertPlainText(c1);
       TextEdit->setAlignment(Qt::AlignCenter);
       TextEdit->setAlignment(Qt::AlignHCenter);
       TextEdit->setFontPointSize(15);


    }
    else if(plagPercentage<=40.0)
    {
        TextEdit->setFontWeight(QFont::Bold);
        TextEdit->setTextColor(Qt::darkYellow);
        TextEdit->insertPlainText(c2);
        TextEdit->setAlignment(Qt::AlignCenter);
        TextEdit->setAlignment(Qt::AlignHCenter);
        TextEdit->setFontPointSize(15);

    }
    else if(plagPercentage >= 50.0)
    {
        TextEdit->setFontWeight(QFont::Bold);
        TextEdit->setTextColor(Qt::red);
        TextEdit->insertPlainText(c3);
        TextEdit->setAlignment(Qt::AlignCenter);
        TextEdit->setAlignment(Qt::AlignHCenter);
        TextEdit->setFontPointSize(15);

    }

    file.close();


}





void MainWindow::f1(const QString& filename)
{
        QString corpus_dir = "C:/Users/Y/Desktop/test/";
        QString fileContents = "";
        QString corpusContents = "";

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, "Error", "Unable to open file");
            return;
        }

        QTextStream in(&file);
        fileContents = in.readAll();




    for (int i = 0; i < 4; i++)
    {
        QFile corpusFile(filenames[i]);





        QTextStream corpusIn(&corpusFile);
        corpusContents += corpusIn.readAll();

        corpusFile.close();
    }


    QVector<QString> v1;
    QVector<QString> v2;



    QStringList fileLines = fileContents.split('\n');
    QStringList corpusLines = corpusContents.split('\n');

    for(const QString& s1 : fileLines)
    {
        v1.append(s1);
    }

    for(const QString& s2 : corpusLines)
    {
        v2.append(s2);
    }

    int m = v1.length();
    int Totalines = fileContents.length();
    int possiblechar = 256;
    int n = v2.length();
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    int plagLines = 0;





    for (i = 0; i < m - 1; i++)
    {
        h = (h * possiblechar) % possiblechar;
    }
        QString pat = v1.at(i);
        QString txxt = v2.at(i);


    for (i = 0; i < m; i++) {
        p = (possiblechar * p + pat.toInt()) % possiblechar;
        t = (possiblechar * t + txxt.toInt()) % possiblechar;
    }

    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            plagLines++;
            for (j = 0; j < m; j++) {
                if (txxt[i + j] != pat[j]){
                    break;
            }

            if (j == m)
            {
            plagLines++;
            break;

             }

        if (i < n - m) {
           QString txt2 = v2.at(i+m);

           t = (possiblechar * (t - (txt2.toInt() * h) + txt2.toInt()) % possiblechar);

            if (t < 0){
              t = (t + possiblechar);
        }
    }

            float plagPercentage = (plagLines * 100.0f) / Totalines;
           QString result = QString::number(plagPercentage, 'f', 2) + "%";

            //ui->textEdit_2->setText(result);


    file.close();
}

}
    }

}



void MainWindow::on_openFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), "Text Files (*.txt)");
        if (!filename.isEmpty())
        {
           processFile(filename);
            //f1(filename);
        }
        ui->submitFile->setEnabled(true);
        ui->MessageLabel->setText("Statistics for the Document Uploaded: ");
}

int num=0;

void MainWindow::on_pushButton_clicked()
{
    if (num == 0)
    {
        ui->Desktoploader->setEnabled(true);
        ui->tabWidget->show();
        ui->Desktoploader->setEnabled(true);
        ui->line_2->show();
        ui->ExitButton->show();
        ui->MinimizeButton->show();
        num++;
    }
    else
    {
        ui->tabWidget->hide();
        ui->line_2->hide();
        ui->ExitButton->hide();
        ui->MinimizeButton->hide();
        num--;
    }
}


void MainWindow::on_Desktoploader_clicked()
{

    if (num == 0)
    {
        ui->tabWidget->hide();
        ui->line_2->hide();
        ui->ExitButton->hide();
        ui->MinimizeButton->hide();
        num++;
    }
    else
    {
        ui->tabWidget->show();
        ui->line_2->show();
        ui->ExitButton->show();
        ui->MinimizeButton->show();
        num--;
    }
}



void MainWindow::on_ExitButton_clicked()
{
    QTextEdit *TextEdit = ui->colorindicater;
    TextEdit->setText("");
    ui->percentage->setText("");
    ui->MinimizeButton->hide();
    ui->Desktoploader->setEnabled(false);
    ui->tabWidget->setCurrentIndex(0);
    ui->openFile->setEnabled(true);
    ui->submitFile->setEnabled(false);
    ui->tabWidget->hide();
    ui->label->lower();
    ui->line_2->hide();
    ui->ExitButton->hide();
    ui->textEdit->setFontPointSize(10);
    ui->textEdit->setText("Welcome to the uploader to the plagiarism website!!\n\n"
     "  This program was created to help doctors and students upload documents in \n\t\torder to check their plagiarism level.\n\n"
     "               Press 'Upload file' to upload the file you are going to use.\n\n"
     "After uploading the file, select a plagiarism detection method from the options.");
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->setAlignment(Qt::AlignHCenter);
    ui->MessageLabel->setText("You Have Not Uploaded a Document Yet!\nUpload the Document for Checking in the Upload Files Tab.");
    num--;

}

void MainWindow::on_submitFile_clicked()
{
    ui->openFile->setEnabled(false);
}

void MainWindow::on_MinimizeButton_clicked()
{
    ui->tabWidget->hide();
    ui->line_2->hide();
    ui->ExitButton->hide();
    ui->MinimizeButton->hide();
    num--;
}

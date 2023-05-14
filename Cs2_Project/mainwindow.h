#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFile_clicked();
    void processFile(const QString&);
    void f1(const QString&);

    void print();

    void on_pushButton_clicked();

    void on_Desktoploader_clicked();


    //void on_BoyerMooreMatcher_clicked();

    void on_ExitButton_clicked();

    void on_submitFile_clicked();

    void on_MinimizeButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

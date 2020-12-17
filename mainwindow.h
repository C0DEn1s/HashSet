#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include "HashSet.h"

typedef HashSet<std::string> Set;

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
    void on_remove_button_clicked();

    void on_add_button_clicked();

    void on_clear_button_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    void Update();

    Ui::MainWindow *ui;
    Set set;
};
#endif // MAINWINDOW_H

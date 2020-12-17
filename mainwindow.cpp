#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_remove_button_clicked() {
    set.erase(ui->lineEdit->text().toStdString());
    ui->lineEdit->clear();
    Update();
}

void MainWindow::on_add_button_clicked() {
    set << ui->lineEdit->text().toStdString();
    Update();
}

void MainWindow::on_clear_button_clicked() {
    set.clear();
    Update();
}

void MainWindow::on_actionOpen_triggered() {
    QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
    set.read(file_name.toStdString());
    Update();
}

void MainWindow::on_actionSave_triggered() {
    QString file_name = QFileDialog::getSaveFileName(this, "Save the file");
    set.print(file_name.toStdString());
}

void MainWindow::Update() {
    ui->listWidget->clear();
    if (set.empty()) {
        return;
    }
    for (const auto& bucket : set.buckets_) {
        if (!bucket.empty()) {
            for (const auto& elem : bucket) {
                QString item = QString::fromStdString(elem);
                ui->listWidget->addItem(item);
            }
        }
    }
}

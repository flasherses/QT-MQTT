#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QMqtt/qmqtt.h"
#include <QTime>
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
    void on_btn_connect_clicked();

    void on_btn_send_clicked();

    void on_btn_close_clicked();

    void connect_success_slot();

    void connect_error_slot(const QMQTT::ClientError error);

    void disconnect_slot();

    void received_slot(const QMQTT::Message& msg);

    void on_clear_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void ClickButton0();

    void ClickButton1();

    void ClickButton2();

    void ClickButton3();


//    void onTimeOut();



private:
    Ui::MainWindow *ui;
    QMQTT::Client *client;
    int flag0;
    int flag1;
    int flag2;
    int flag3;
    QTimer *tim;

};
#endif // MAINWINDOW_H

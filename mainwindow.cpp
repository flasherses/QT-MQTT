#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMqtt/qmqtt.h"
#include <QtNetwork>
#include <QHoverEvent>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //连接onenet云平台
    client = new QMQTT::Client(QHostAddress("183.230.40.39"),6002);
    client->setClientId("943137931");//设备ID
    client->setUsername("506581"); //产品ID
    client->setPassword("123456"); //鉴权信息ID
    client->setVersion(QMQTT::MQTTVersion::V3_1_1);

    connect(client,SIGNAL(connected()),this,SLOT(connect_success_slot()));
    connect(client,SIGNAL(received(const QMQTT::Message&)),this,SLOT(received_slot(const QMQTT::Message&)));
    connect(client,SIGNAL(error(const QMQTT::ClientError)),this,SLOT(connect_error_slot(const QMQTT::ClientError)));
    connect(client,SIGNAL(disconnected()),this,SLOT(disconnect_slot()));

    //
    connect(ui->btn_send, SIGNAL(clicked()), this, SLOT(ClickButton0()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ClickButton1()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(ClickButton2()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(ClickButton3()));


    flag0 = 0;
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;


    tim = new QTimer();
    tim->setInterval(5000);
    connect(tim,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    tim->start();    

}

MainWindow::~MainWindow()
{
    delete ui;

}

//连接onenet云
void MainWindow::on_btn_connect_clicked()
{
   client->connectToHost();

}

// 连接成功后输出“connect success”并订阅主题
void MainWindow::connect_success_slot(){
    qDebug() << "connect success";
    client->subscribe("Celsius",0);
    client->subscribe("Humidity",0);
    client->subscribe("Rain",0);
    client->subscribe("Smoke",0);
    client->subscribe("Light",0);
    client->subscribe("Far",0);
    client->subscribe("test",0);
    ui->output->setText("连接成功");

}

//连接出现错误时在控制台输出错误
void MainWindow::connect_error_slot(const QMQTT::ClientError error){
    qDebug() << "错误" << error;
}

// 断开连接输出disconnect___
void MainWindow::disconnect_slot(){
    qDebug() << "disconnect___";
    ui->output->setText("断开连接");
}

//断开onenet云
void MainWindow::on_btn_close_clicked()
{
    client->disconnectFromHost();
}

// 将对应主题的数据输出到对用的文本框中
void MainWindow::received_slot(const QMQTT::Message& msg){
    QString strPayload(msg.payload());
    if(msg.topic() == "Celsius")
        ui->le_receive->setText(strPayload);
    if(msg.topic() == "Humidity")
        ui->le_send->setText(strPayload);
    if(msg.topic() == "Rain")
        ui->rain->setText(strPayload);
    if(msg.topic() == "Smoke")
        ui->smoke->setText(strPayload);
    if(msg.topic() == "Light")
        ui->light->setText(strPayload);
    if(msg.topic() == "Far")
        ui->far->setText(strPayload);
    if(msg.topic() == "test")
     ui->lineEdit->setText(strPayload);

}

//清空文本框
void MainWindow::on_clear_clicked()
{
    ui->le_receive->setText("");
    ui->le_send->setText("");
    ui->far->setText("");
     ui->rain->setText("");
      ui->light->setText("");
       ui->smoke->setText("");
       ui->lineEdit->setText("");
}

//下发指令
void MainWindow::on_btn_send_clicked()
{
    if(ui->btn_send->text() == "打开水泵"){
        QString controal = "t";
        QMQTT::Message msg(110,"Controal",controal.toUtf8());
        client->publish(msg);


    }
    if(ui->btn_send->text() == "关闭水泵"){
        QString controal = "y";
        QMQTT::Message msg(110,"Controal",controal.toUtf8());
        client->publish(msg);


    }

}

void MainWindow::on_pushButton_clicked()
{


    if(ui->pushButton->text() == "开灯"){
            QString controal = "q";
            QMQTT::Message msg(110,"Controal",controal.toUtf8());
            client->publish(msg);
    }
    if(ui->pushButton->text() == "关灯"){

            QString controal = "w";
            QMQTT::Message msg(110,"Controal",controal.toUtf8());
            client->publish(msg);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text() == "开警报"){
        QString controal = "e";
        QMQTT::Message msg(110,"Controal",controal.toUtf8());
        client->publish(msg);


    }
    if(ui->pushButton_2->text() == "关警报"){
        QString controal = "r";
        QMQTT::Message msg(110,"Controal",controal.toUtf8());
        client->publish(msg);


    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->pushButton_3->text() == "打开风扇"){
        QString controal = "d";
        QMQTT::Message msg(110,"Controal",controal.toUtf8());
        client->publish(msg);


    }
    if(ui->pushButton_3->text() == "关闭风扇"){
        QString controal = "f";
        QMQTT::Message msg(110,"Controal",controal.toUtf8());
        client->publish(msg);



    }
}

void MainWindow::on_pushButton_4_clicked()
{
        QString controal = "z";
        QMQTT::Message msg(110,"Controal",controal.toUtf8());
        client->publish(msg);
}

void MainWindow::ClickButton0()
{
    if(!flag0){
    ui->btn_send->setText("关闭水泵");
    flag0 = 1;
    }
    else{
     ui->btn_send->setText("打开水泵");
     flag0 = 0;
    }

}

void MainWindow::ClickButton1()
{
    if(!flag1){
    ui->pushButton->setText("关灯");
    flag1 = 1;
    }
    else{
     ui->pushButton->setText("开灯");
     flag1 = 0;
    }

}

void MainWindow::ClickButton2()
{
    if(!flag2){
    ui->pushButton_2->setText("关警报");
    flag2 = 1;
    }
    else{
     ui->pushButton_2->setText("开警报");
     flag2 = 0;
    }

}

void MainWindow::ClickButton3()
{
    if(!flag3){
    ui->pushButton_3->setText("关闭风扇");
    flag3 = 1;
    }
    else{
     ui->pushButton_3->setText("打开风扇");
     flag3 = 0;
    }

}


//void MainWindow::onTimeOut()
//{
//    QString controal = "i";
//    QMQTT::Message msg(110,"Controal",controal.toUtf8());
//    client->publish(msg);
//}

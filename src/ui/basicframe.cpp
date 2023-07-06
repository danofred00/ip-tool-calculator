#include "basicframe.h"
#include "ui_basicframe.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "../ipcalculator.h"
#include "netip.h"
#include "utilities.h"


#include <iostream>


BasicFrame::BasicFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BasicFrame)
{
    ui->setupUi(this);
    connect(ui->calculateBtn, SIGNAL(clicked(bool)), this, SLOT(calculate()));
    connect(ui->saveBtn, SIGNAL(clicked(bool)), this, SLOT(save()));
}

BasicFrame::~BasicFrame()
{
    delete ui;
}

void BasicFrame::calculate()
{
   auto txt = encode(ui->ipEdit->text());

    if(validateIp(txt)) {

        auto _i = txt.toStdString();
        auto _ipstr = _i.c_str();

        if(ipv4_is_correct_str(_ipstr)) {

            // calculate everything
            netipv4 netip = netipv4_create_from_str(_ipstr);
            auto result = IpCalculator::basic(netip);
            auto doc = QJsonDocument(QJsonObject::fromVariantMap(result));

//            // set the buffer
//            auto str = QString("************** RESULT ****************\n\n"
//                               "TARGET IP    :   %1\n"
//                               "CLASS ADDR   :   %2\n"
//                               "TYPE         :   %3\n"
//                               "NET ADDR     :   %4\n"
//                               "SUBNET MASK  :   %5\n"
//                               "BROADCAST    :   %6\n"
//                               "BINARY       :   %7\n"
//                               "DECIMAL      :   %8\n"
//                               "HEX          :   0x%9\n"
//                               "\n").arg(result["ip"].toString()).arg(result["class"].toChar())
//                           .arg(result["type"].toString(), result["network"].toString(), result["netmask"].toString(), result["broadcast"].toString(), result["bin"].toString())
//                           .arg(result["decimal"].toUInt()).arg(result["hex"].toString());


            ui->result->setStyleSheet("color: #fff;");
            ui->result->setText( QString(doc.toJson()));

        } else {
            ui->result->setStyleSheet("color: #f00;");
            ui->result->setText("Error: Wrong Ip address.");
        }

    } else {
        ui->result->setStyleSheet("color: #f00;");
        ui->result->setText("Error: Something is wrong, please check your input.");
    }
}

void BasicFrame::save()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                                                tr("Text Files (*.txt);;All Files (*.*)"));
    if(!path.isEmpty())
        if(!saveFileContent(path, ui->result->text().toLatin1()))
        {
            auto ok = QMessageBox::critical(this, tr("ERROR"), tr("Couln'd save the file."));
            qDebug() << "Error during save the file";
        }
}

#include "basicframe.h"
#include "ui_basicframe.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include "ipv4.h"
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
    char *ip;
    char *bin;
    char *network;
    char *netmask;
    char *broadcast;
    char ipclass;
    char *type;

    auto txt = encode(ui->ipEdit->text());

    if(validateIp(txt)) {

        auto _i = txt.toStdString();
        auto _ipstr = _i.c_str();

        if(ipv4_is_correct_str(_ipstr)) {

            // calculate everything
            netipv4 netip = netipv4_create_from_str(_ipstr);
            netmask = ipv4_toString(ipv4_create_from_cidr(netip.cidr));
            network = ipv4_toString(netipv4_network(netip).ip);
            broadcast = ipv4_toString(netipv4_broadcast(netip).ip);
            ipclass = ipv4_class2char(ipv4_class(netip.ip));
            bin = ipv4_tobin(netip.ip);
            ip = ipv4_toString(netip.ip);
            type = ipv4_type2str(ipv4_type(netip.ip));
            QByteArray arr = QByteArray::number(netip.ip, 16).toUpper();

            // set the buffer
            auto str = QString("************** RESULT ****************\n\n"
                               "TARGET IP    :   %1\n"
                               "CLASS ADDR   :   %2\n"
                               "TYPE         :   %3\n"
                               "NET ADDR     :   %4\n"
                               "SUBNET MASK  :   %5\n"
                               "BROADCAST    :   %6\n"
                               "BINARY       :   %7\n"
                               "DECIMAL      :   %8\n"
                               "HEX          :   0x%9\n"
                               "\n").arg(ip).arg(ipclass)
                           .arg(type, network, netmask, broadcast, bin)
                           .arg(netip.ip).arg(arr);


            ui->result->setStyleSheet("color: #fff;");
            ui->result->setText(str);

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
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), "./", tr("Text Files (*.txt);;All Files (*.*)"));
    if(!path.isEmpty())
        if(!saveFileContent(path, ui->result->text().toLatin1()))
        {
            auto ok = QMessageBox::critical(this, tr("ERROR"), tr("Couln'd save the file."));
            qDebug() << "Error during save the file";
        }
}

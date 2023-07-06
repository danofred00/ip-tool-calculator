#include "advancedframe.h"
#include "ui_advancedframe.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

#include "ipv4.h"
#include "netip.h"
#include "utilities.h"

AdvancedFrame::AdvancedFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::AdvancedFrame)
{
    setup();
    // init the list
    list = QList<QHash<QString, QString>>(0);
    model = nullptr;
}

AdvancedFrame::~AdvancedFrame()
{
    delete ui;
    delete model;
}

void AdvancedFrame::calculate()
{
    char *bin;
    char *netmask;
    char ipclass;
    char *type;
    char *base;

    auto txt = encode(ui->ipEdit->text());

    if(validateIp(txt)) {

        auto _i = txt.toStdString();
        auto _ipstr = _i.c_str();

        if(ipv4_is_correct_str(_ipstr)) {

            netipv4 netip = netipv4_create_from_str(_ipstr);

            if(netipv4_is_network(netip))
            {
                subnetv4 subnet = subnetv4_create(netip);

                // calculate everything
                netmask = ipv4_toString(ipv4_create_from_cidr(netip.cidr));
                ipclass = ipv4_class2char(ipv4_class(netip.ip));
                bin = ipv4_tobin(netip.ip);
                type = ipv4_type2str(ipv4_type(netip.ip));
                base = ipv4_toString(subnetv4_base(netip));
                auto nets = subnetv4_net_maxcount(subnet);

                // update value
                ui->subnetMask->setText(netmask);
                ui->class_->setText(QChar(ipclass));
                ui->decimal->setText(QString::number(netip.ip));
                ui->type->setText(type);
                ui->hex->setText("0x" + QString::number(netip.ip, 16).toUpper());
                ui->subnets->setText(QString::number(nets));
                ui->hosts->setText(QString::number(subnetv4_host_maxcount(subnet)));
                ui->base->setText(base);
                // display the table
                list.clear();
                for(auto i=0; i<nets; i++) {
                    netip = subnetv4_subnet(subnet, i);

                    QHash<QString,QString> hash;
                    hash.insert("network", ipv4_toString(netip.ip));
                    hash.insert("netmask", ipv4_toString(ipv4_create_from_cidr(netip.cidr)));
                    hash.insert("broadcast", ipv4_toString(netipv4_broadcast(netip).ip));

                    list.append(hash);
                }

                if(model != nullptr) {
                    //model->removeRows(0, list)
                    delete model;
                }
                model = new IpTableModel(&list);
                ui->tableView->setModel(model);

                // clear entry
                ui->errorMessage->clear();
            } else
                ui->errorMessage->setText(tr("Error: Address entered is not a network address."));
        } else
            ui->errorMessage->setText(tr("Error: Wrong Ip address."));
    } else
        ui->errorMessage->setText(tr("Error: Something is wrong, please check your input."));
}

void AdvancedFrame::save()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                                                tr("Text Files (*.txt);;All Files (*.*)"));
    if(!path.isEmpty()) {
        QFile file {path};
        if(file.exists()) {
            if(file.open(QFile::WriteOnly)) {
                // write the first string to define datas
                file.write(tr("no   -   Net Address     -      Subnet Mask      -   Broadcast\n").toLatin1());
                for(auto i=0; i<list.size(); i++)
                {
                    auto index0 = model->index(i, 0);
                    auto index1 = model->index(i, 1);
                    auto index2 = model->index(i, 2);
                    auto index3 = model->index(i, 3);

                    auto str = QString("%1 - %2 - %3 - %4\n")
                                   .arg(model->data(index0).toUInt())
                                   .arg(model->data(index1).toString(), model->data(index2).toString(), model->data(index3).toString());

                    file.write(str.toLatin1());
                }
                file.close();
            }
        }
    }
}

void AdvancedFrame::setup()
{
    ui->setupUi(this);
    connect(ui->calculateBtn, SIGNAL(clicked(bool)), this, SLOT(calculate()));
    connect(ui->saveBtn, SIGNAL(clicked(bool)), this, SLOT(save()));
}

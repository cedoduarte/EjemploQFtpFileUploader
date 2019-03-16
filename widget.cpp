#include "widget.h"
#include "ui_widget.h"
#include "QFtpFileUploader.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->ftpPortLineEdit->setText("21");

    m_ftpUploader = new QFtpFileUploader(this);

    connect(m_ftpUploader, &QFtpFileUploader::uploadProgress, [&](int percentage)
    {
        ui->progressBar->setValue(percentage);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_selectFileButton_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Get Any File");
    ui->fileNameLineEdit->setText(filepath);
}

void Widget::on_uploadButton_clicked()
{
    m_ftpUploader->setFilePath(ui->fileNameLineEdit->text());
    m_ftpUploader->setFtpPassword(ui->ftpPasswordLineEdit->text());
    m_ftpUploader->setFtpPort(ui->ftpPortLineEdit->text().toInt());
    m_ftpUploader->setFtpServerUrl(ui->uploadUrlLineEdit->text());
    m_ftpUploader->setFtpUsername(ui->ftpUsernameLineEdit->text());
    m_ftpUploader->startUploading();
}

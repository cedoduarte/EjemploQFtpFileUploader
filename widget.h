#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QFtpFileUploader;

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_selectFileButton_clicked();
    void on_uploadButton_clicked();
private:
    Ui::Widget *ui;
    QFtpFileUploader *m_ftpUploader;
};

#endif // WIDGET_H

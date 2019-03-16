#ifndef QFTPFILEUPLOADER_H
#define QFTPFILEUPLOADER_H

#include <QObject>

class QFile;
class QNetworkAccessManager;

class QFtpFileUploader : public QObject
{
    Q_OBJECT
public:
    QFtpFileUploader(QObject *parent = nullptr);
    void setFtpPort(int port = 21);
    void setFtpServerUrl(const QString &ftpServerUrl);
    void setFilePath(const QString &filePath);
    void setFtpUsername(const QString &username);
    void setFtpPassword(const QString &password);
    int ftpPort() const;
    QString ftpServerUrl() const;
    QString filePath() const;
    QString ftpUsername() const;
    QString ftpPassword() const;
    void startUploading();
signals:
    void uploadProgress(int percentage);
private:
    QFile *m_file;
    int m_ftpPort;
    QString m_ftpServerUrl;
    QString m_filePath;
    QString m_ftpUsername;
    QString m_ftpPassword;
    QNetworkAccessManager *m_netManager;
};

#endif // QFTPFILEUPLOADER_H

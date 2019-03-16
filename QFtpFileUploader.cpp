#include "QFtpFileUploader.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

QFtpFileUploader::QFtpFileUploader(QObject *parent)
    : QObject { parent }
{
    m_file = nullptr;
    m_ftpPort = 21;
    m_ftpServerUrl = "";
    m_filePath = "";
    m_ftpUsername = "";
    m_ftpPassword = "";
    m_netManager = new QNetworkAccessManager(this);

    connect(m_netManager, &QNetworkAccessManager::finished, this, [&](QNetworkReply *reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            m_file->close();
            m_file->deleteLater();
            reply->deleteLater();
        }
    });
}

void QFtpFileUploader::setFtpPort(int port)
{
    m_ftpPort = port;
}

void QFtpFileUploader::setFtpServerUrl(const QString &ftpServerUrl)
{
    m_ftpServerUrl = ftpServerUrl;
}

void QFtpFileUploader::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}

void QFtpFileUploader::setFtpUsername(const QString &username)
{
    m_ftpUsername = username;
}

void QFtpFileUploader::setFtpPassword(const QString &password)
{
    m_ftpPassword = password;
}

int QFtpFileUploader::ftpPort() const
{
    return m_ftpPort;
}

QString QFtpFileUploader::ftpServerUrl() const
{
    return m_ftpServerUrl;
}

QString QFtpFileUploader::filePath() const
{
    return m_filePath;
}

QString QFtpFileUploader::ftpUsername() const
{
    return m_ftpUsername;
}

QString QFtpFileUploader::ftpPassword() const
{
    return m_ftpPassword;
}

void QFtpFileUploader::startUploading()
{
    m_file = new QFile(m_filePath);
    if (m_file->open(QIODevice::ReadOnly))
    {
        QUrl ftpUrl(m_ftpServerUrl);
        ftpUrl.setUserName(m_ftpUsername);
        ftpUrl.setPassword(m_ftpPassword);
        ftpUrl.setPort(m_ftpPort);
        QNetworkReply *reply = m_netManager->put(QNetworkRequest(ftpUrl), m_file);
        connect(reply, &QNetworkReply::uploadProgress, this, [&](qint64 bytesSent, qint64 bytesTotal)
        {
            if (bytesSent != 0 && bytesTotal != 0)
            {
                emit uploadProgress(100 * bytesSent / bytesTotal);
            }
        });
    }
}

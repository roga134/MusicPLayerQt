#include "encryption.h"
#include <QByteArray>

QString simpleXOREncryptDecrypt(const QString &input, char key)
{
    QByteArray bytes = input.toUtf8();
    for (int i = 0; i < bytes.size(); ++i)
        bytes[i] = static_cast<char>(bytes[i]) ^ key;
    return QString::fromUtf8(bytes);
}

#ifndef RARCHANDLER_H
#define RARCHANDLER_H

#include <QString>
#include <QByteArray>
#include <QVector>

struct VirtualFile {
    QString fileName;
    QByteArray data;
};

class RarcHandler
{
public:
    RarcHandler();
    // Chỉ nhận dữ liệu đã giải nén
    QVector<VirtualFile> parse(const QByteArray& rarcData);

private:
    quint16 readU16(const QByteArray& data, int offset);
    quint32 readU32(const QByteArray& data, int offset);
    QString readString(const QByteArray& data, int stringTableOffset, int stringOffset);
};

#endif // RARCHANDLER_H

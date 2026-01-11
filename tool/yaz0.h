#ifndef YAZ0_H
#define YAZ0_H

#include <QByteArray>

class Yaz0
{
public:
    // Kiểm tra xem có phải Yaz0 không
    static bool isYaz0(const QByteArray& data);

    // Giải nén
    static QByteArray decode(const QByteArray& src);

private:
    static quint32 readU32(const QByteArray& data, int offset);
};

#endif // YAZ0_H

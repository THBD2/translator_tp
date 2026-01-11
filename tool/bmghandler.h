#ifndef BMGHANDLER_H
#define BMGHANDLER_H

#include <QString>
#include <QByteArray>
#include <QVector>
#include <vector>
#include "translationmodel.h" // Để dùng struct TranslationEntry

class BmgHandler
{
public:
    BmgHandler();

    // 1. Đọc từ File (Dùng cho Import Folder BMG)
    std::vector<TranslationEntry> loadBmg(const QString& filePath);

    // 2. Đọc từ RAM (Dùng cho Import ARC)
    std::vector<TranslationEntry> loadBmgFromData(const QByteArray& data);

    // 3. Encode (Dùng khi Save - Để dành sau này)
    QByteArray encodeText(const QString& text);

private:
    // Hàm xử lý cốt lõi (được gọi bởi cả 2 hàm trên)
    std::vector<TranslationEntry> processBmgData(const QByteArray& data);

    // Các hàm giải mã
    QString decodeText(const QByteArray& rawData);

    // Các hàm đọc số Big Endian
    quint16 readU16(const QByteArray& data, int& offset);
    quint32 readU32(const QByteArray& data, int& offset);
};

#endif // BMGHANDLER_H

#include "bmghandler.h"
#include <QFile>
#include <QtEndian>
#include <QDebug>

BmgHandler::BmgHandler() {}

// =========================================================
// CÁC HÀM CÔNG KHAI
// =========================================================

std::vector<TranslationEntry> BmgHandler::loadBmg(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "❌ Lỗi: Không mở được file:" << filePath;
        return {};
    }
    return processBmgData(file.readAll());
}

std::vector<TranslationEntry> BmgHandler::loadBmgFromData(const QByteArray &data)
{
    return processBmgData(data);
}

// =========================================================
// HÀM ĐỌC SỐ AN TOÀN (CHỐNG CRASH)
// =========================================================
quint16 BmgHandler::readU16(const QByteArray &data, int &offset) {
    // Kiểm tra Offset âm hoặc vượt quá độ dài
    if (offset < 0 || offset + 2 > data.size()) return 0;

    quint16 val = qFromBigEndian<quint16>(reinterpret_cast<const uchar*>(data.mid(offset, 2).data()));
    offset += 2;
    return val;
}

quint32 BmgHandler::readU32(const QByteArray &data, int &offset) {
    if (offset < 0 || offset + 4 > data.size()) return 0;

    quint32 val = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(data.mid(offset, 4).data()));
    offset += 4;
    return val;
}

// =========================================================
// LOGIC PARSE FILE BMG
// =========================================================
std::vector<TranslationEntry> BmgHandler::processBmgData(const QByteArray &data)
{
    std::vector<TranslationEntry> entries;
    int cursor = 0;

    // 1. CHECK HEADER
    if (data.size() < 32 || data.mid(0, 8) != "MESGbmg1") {
        // qDebug() << "⚠️ Bỏ qua: Không phải định dạng MESGbmg1 hợp lệ.";
        return entries;
    }
    cursor += 8;

    quint32 fileSize = readU32(data, cursor);
    quint32 sectionCount = readU32(data, cursor);
    cursor = 0x20;

    int inf1Offset = -1;
    int dat1Offset = -1;

    // 2. TÌM INF1 VÀ DAT1
    for (quint32 i = 0; i < sectionCount; ++i) {
        if (cursor + 8 > data.size()) break;

        QByteArray secName = data.mid(cursor, 4);
        int secStart = cursor;

        cursor += 4;
        quint32 secSize = readU32(data, cursor);

        if (secName == "INF1") inf1Offset = secStart;
        else if (secName == "DAT1") dat1Offset = secStart;

        // Tính cursor tiếp theo an toàn
        cursor = secStart + (int)secSize;
        if (cursor < 0 || cursor > data.size()) break; // Chống tràn số
    }

    if (inf1Offset == -1 || dat1Offset == -1) return entries;

    // 3. ĐỌC INF1
    cursor = inf1Offset + 8;
    quint16 msgCount = readU16(data, cursor);
    quint16 entrySize = readU16(data, cursor);
    cursor += 4;

    // 4. ĐỌC DAT1
    int textBaseOffset = dat1Offset + 8;

    for (int i = 0; i < msgCount; ++i) {
        int entryOffset = inf1Offset + 0x10 + (i * entrySize);
        int tempCursor = entryOffset;

        quint32 textOffsetRelative = readU32(data, tempCursor);
        int absoluteTextPos = textBaseOffset + (int)textOffsetRelative;

        // Kiểm tra vị trí text có hợp lệ không
        if (absoluteTextPos < 0 || absoluteTextPos >= data.size()) continue;

        QByteArray rawText;
        int tPos = absoluteTextPos;
        while (tPos < data.size()) {
            char byte = data.at(tPos);
            if (byte == 0x00) break;
            rawText.append(byte);
            tPos++;
        }

        TranslationEntry entry;
        entry.id = QString("MSG_%1").arg(i, 4, 16, QChar('0')).toUpper();
        entry.original = decodeText(rawText);
        entry.translated = "";
        entry.isDone = false;
        entries.push_back(entry);
    }

    return entries;
}

QString BmgHandler::decodeText(const QByteArray &rawData)
{
    QString result = "";
    int i = 0;
    while (i < rawData.size()) {
        unsigned char byte = (unsigned char)rawData.at(i);

        if (byte >= 0x20 && byte != 0x7F) {
            result.append(QChar(byte));
            i++;
        }
        else if (byte == 0x1A) {
            if (i + 2 >= rawData.size()) break;
            unsigned char size = (unsigned char)rawData.at(i + 1);
            if (size == 0 || i + size > rawData.size()) { i++; continue; } // Fix lỗi lặp vô tận

            unsigned char type = (unsigned char)rawData.at(i + 2);
            QString tag = QString("<CMD:%1").arg(type, 2, 16, QChar('0')).toUpper();
            for (int k = 3; k < size; ++k) {
                unsigned char param = (unsigned char)rawData.at(i + k);
                tag += ":" + QString::number(param, 16).toUpper().rightJustified(2, '0');
            }
            tag += ">";
            result.append(tag);
            i += size;
        }
        else if (byte == 0x0A) {
            result.append("\n");
            i++;
        }
        else {
            result.append(QString("<0x%1>").arg(byte, 2, 16, QChar('0')).toUpper());
            i++;
        }
    }
    return result;
}

QByteArray BmgHandler::encodeText(const QString &text) { return QByteArray(); }

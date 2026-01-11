#include "rarchandler.h"
#include <QDebug>
#include <QtEndian>

RarcHandler::RarcHandler() {}

quint16 RarcHandler::readU16(const QByteArray &data, int offset) {
    if (offset < 0 || offset + 2 > data.size()) return 0;
    return qFromBigEndian<quint16>(reinterpret_cast<const uchar*>(data.mid(offset, 2).data()));
}

quint32 RarcHandler::readU32(const QByteArray &data, int offset) {
    if (offset < 0 || offset + 4 > data.size()) return 0;
    return qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(data.mid(offset, 4).data()));
}

QString RarcHandler::readString(const QByteArray &data, int stringTableOffset, int stringOffset) {
    int startPos = stringTableOffset + stringOffset;
    if (startPos < 0 || startPos >= data.size()) return "";
    int endPos = data.indexOf('\0', startPos);
    if (endPos == -1) return "";
    return QString::fromUtf8(data.mid(startPos, endPos - startPos));
}

QVector<VirtualFile> RarcHandler::parse(const QByteArray &data)
{
    QVector<VirtualFile> results;

    if (data.size() < 0x40 || data.mid(0, 4) != "RARC") {
        qDebug() << "❌ Lỗi: Không phải RARC";
        return results;
    }

    // Header RARC
    quint32 infoBlockOffset = readU32(data, 0x0C);
    quint32 dataRelativeOffset = readU32(data, 0x2C);
    quint32 fileDataStart = infoBlockOffset + dataRelativeOffset;

    // Info Block
    // Bỏ qua các biến không dùng để tránh warning
    // quint32 nodeTableOffset = infoBlockOffset + readU32(data, infoBlockOffset + 0x04);

    quint32 fileTableOffset = infoBlockOffset + readU32(data, infoBlockOffset + 0x0C);
    quint32 stringTableOffset = infoBlockOffset + readU32(data, infoBlockOffset + 0x14);
    quint16 totalFiles = readU16(data, infoBlockOffset + 0x1C);

    qDebug() << "🔹 RARC Info: Total Files =" << totalFiles;

    for (int i = 0; i < totalFiles; ++i) {
        int entryOffset = fileTableOffset + (i * 0x14);

        if (entryOffset + 20 > data.size()) break;

        quint16 id = readU16(data, entryOffset + 0x00);
        if (id == 0xFFFF) continue;

        // quint16 typeAndHash = readU16(data, entryOffset + 0x02); // Biến này không dùng -> xóa
        quint32 rawNameField = readU32(data, entryOffset + 0x04);

        quint8 type = (rawNameField >> 24) & 0xFF;
        int namePos = rawNameField & 0x00FFFFFF;

        if (type & 0x02) continue; // Folder

        QString name = readString(data, stringTableOffset, namePos);

        if (name.endsWith(".bmg", Qt::CaseInsensitive)) {
            quint32 fileOffset = readU32(data, entryOffset + 0x08);
            quint32 fileSize = readU32(data, entryOffset + 0x0C);
            quint32 absoluteOffset = fileDataStart + fileOffset;

            if (absoluteOffset + fileSize <= (quint32)data.size()) {
                QByteArray fileContent = data.mid(absoluteOffset, fileSize);
                results.append({name, fileContent});
                qDebug() << "   ✅ Trích xuất:" << name << "Size:" << fileSize;
            }
        }
    }
    return results;
}

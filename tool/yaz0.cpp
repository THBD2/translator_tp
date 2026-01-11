#include "yaz0.h"
#include <QtEndian>
#include <QDebug>

bool Yaz0::isYaz0(const QByteArray &data) {
    return data.startsWith("Yaz0");
}

quint32 Yaz0::readU32(const QByteArray& data, int offset) {
    return qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(data.mid(offset, 4).data()));
}

QByteArray Yaz0::decode(const QByteArray &src)
{
    if (!isYaz0(src)) return src;

    quint32 decodedSize = readU32(src, 4);
    QByteArray dst(decodedSize, 0);

    int srcPos = 16;
    int dstPos = 0;
    quint32 validBitCount = 0;
    unsigned char currCodeByte = 0;

    while (dstPos < decodedSize && srcPos < src.size()) {
        if (validBitCount == 0) {
            currCodeByte = (unsigned char)src[srcPos++];
            validBitCount = 8;
        }

        if ((currCodeByte & 0x80) != 0) {
            dst[dstPos++] = src[srcPos++];
        } else {
            unsigned char byte1 = (unsigned char)src[srcPos++];
            unsigned char byte2 = (unsigned char)src[srcPos++];
            quint32 dist = ((byte1 & 0x0F) << 8) | byte2;
            quint32 numBytes = (byte1 >> 4);
            if (numBytes == 0) numBytes = (unsigned char)src[srcPos++] + 0x12;
            else numBytes += 2;

            int copySrc = dstPos - (dist + 1);
            for (quint32 i = 0; i < numBytes; ++i) {
                if (dstPos >= decodedSize) break;
                dst[dstPos++] = dst[copySrc++];
            }
        }
        currCodeByte <<= 1;
        validBitCount--;
    }
    return dst;
}

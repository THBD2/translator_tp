#ifndef TRANSLATIONDATA_H
#define TRANSLATIONDATA_H

#include <QString>

struct TranslationEntry {
    QString id;          // ID (Ví dụ: MSG_001)
    QString original;    // Text tiếng Anh
    QString translation; // Text tiếng Việt
    QString status;      // Trạng thái: "New", "Done"
};

#endif // TRANSLATIONDATA_H

#ifndef TRANSLATIONMODEL_H
#define TRANSLATIONMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <QJsonArray>
#include <QJsonObject>

struct TranslationEntry {
    QString id;
    QString original;
    QString translated;
    bool isDone;
};

class TranslationModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TranslationModel(QObject *parent = nullptr);

    // Các hàm cơ bản của Qt
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // Các hàm xử lý dữ liệu
    void setEntries(const std::vector<TranslationEntry>& entries); // Xóa hết nạp mới
    void appendEntry(const TranslationEntry& entry); // Thêm 1 dòng vào cuối (Dùng cho Import)
    TranslationEntry getEntry(int row) const;
    void updateTranslation(int row, const QString& text);

    // Save/Load JSON
    QJsonArray toJson() const;
    void fromJson(const QJsonArray& json);

private:
    std::vector<TranslationEntry> m_data;
};

#endif // TRANSLATIONMODEL_H

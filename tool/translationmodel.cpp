#include "translationmodel.h"

TranslationModel::TranslationModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int TranslationModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return static_cast<int>(m_data.size());
}

int TranslationModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return 3; // ID, Original, Status
}

QVariant TranslationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto& item = m_data[index.row()];

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return item.id;
        case 1: return item.original;
        case 2: return item.isDone ? "✅ Done" : "Wait";
        }
    }
    return QVariant();
}

QVariant TranslationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section) {
    case 0: return "ID";
    case 1: return "Original Text";
    case 2: return "Status";
    }
    return QVariant();
}

void TranslationModel::setEntries(const std::vector<TranslationEntry> &entries)
{
    beginResetModel();
    m_data = entries;
    endResetModel();
}

void TranslationModel::appendEntry(const TranslationEntry &entry)
{
    // Báo cho Qt biết sắp chèn thêm 1 dòng vào cuối
    int newRow = m_data.size();
    beginInsertRows(QModelIndex(), newRow, newRow);
    m_data.push_back(entry);
    endInsertRows();
}

TranslationEntry TranslationModel::getEntry(int row) const
{
    if (row < 0 || row >= m_data.size()) return {};
    return m_data[row];
}

void TranslationModel::updateTranslation(int row, const QString &text)
{
    if (row < 0 || row >= m_data.size()) return;

    m_data[row].translated = text;
    if (!text.isEmpty()) m_data[row].isDone = true;

    emit dataChanged(index(row, 0), index(row, 2));
}

QJsonArray TranslationModel::toJson() const
{
    QJsonArray array;
    for (const auto& item : m_data) {
        QJsonObject obj;
        obj["id"] = item.id;
        obj["orig"] = item.original;
        obj["trans"] = item.translated;
        obj["done"] = item.isDone;
        array.append(obj);
    }
    return array;
}

void TranslationModel::fromJson(const QJsonArray& json)
{
    std::vector<TranslationEntry> newData;
    for (const auto& val : json) {
        QJsonObject obj = val.toObject();
        TranslationEntry item;
        item.id = obj["id"].toString();
        item.original = obj["orig"].toString();
        item.translated = obj["trans"].toString();
        item.isDone = obj["done"].toBool();
        newData.push_back(item);
    }
    setEntries(newData);
}

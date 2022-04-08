#include "transportmodel.h"
#include <iostream>
#include <ctime>
TransportModel::TransportModel( QObject* parent ) : QAbstractTableModel( parent ) {
}

int TransportModel::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return tableTransports.count();
}

int TransportModel::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return LAST;
}

QVariant TransportModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return section;
    }

    switch( section ) {
    case uniqueIdentificator:
        return  ("Уникальный идентификатор" );
    case typeTransport:
        return  ("Тип транспорта" );
    case yearManufacture:
        return ("Год выпуска" );
    case weight:
        return ("Вес" );
    case model:
        return("Модель");
    case brand:
        return("Марка");
    }

    return QVariant();
}
QVariant TransportModel::data( const QModelIndex& index, int role ) const {
    if(
        !index.isValid() ||
        tableTransports.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole )
    ) {
        return QVariant();
    }

    return tableTransports[ index.row() ][ Column( index.column() ) ];
}

Qt::ItemFlags TransportModel::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        if( index.column() == weight ) {
            flags |= Qt::ItemIsEditable;
        }
    }

    return flags;
}

void TransportModel::appendTransport(const QString& typeTrQ,const QString& weightQ, const QString& yearQ,const QString& brandQ,const QString& modelQ) {
    TransportData transport;
    srand(time(NULL ));
    transport[ uniqueIdentificator ] = rand() % 1000;
    transport[ typeTransport ] = typeTrQ;
    transport[ yearManufacture ] = yearQ;
    transport[ weight ] = weightQ;
    transport[ brand ] = brandQ;
    transport[ model ] = modelQ;

    int row = tableTransports.count();
    beginInsertRows( QModelIndex(), row, row );
    tableTransports.append( transport );
    endInsertRows();
}
bool TransportModel::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || tableTransports.count() <= index.row() ) {
        return false;
    }

    tableTransports[ index.row() ][ Column( index.column() ) ] = value;
    emit dataChanged( index, index );

    return true;
}
void TransportModel::removeSelected(const QString& deleteUniqueId) {
    int i = 0;
    Transports::iterator it = tableTransports.begin();
    while( it != tableTransports.end() ) {
        if( it->value( uniqueIdentificator, deleteUniqueId ).toBool() ) {
            beginRemoveRows( QModelIndex(), i, i );
            it = tableTransports.erase( it );
            endRemoveRows();
        } else {
            ++i;
            ++it;
        }
    }
}

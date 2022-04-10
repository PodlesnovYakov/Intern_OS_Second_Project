#include "transportmodel.h"
#include <iostream>
#include <ctime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include <QString>



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
        if( index.column() == weight || index.column() == typeTransport || index.column() == yearManufacture
                || index.column() == brand || index.column() == model) {
            flags |= Qt::ItemIsEditable;
        }
    }

    return flags;
}

void TransportModel::appendTransport(const QString& typeTrQ,const QString& yearQ, const QString& weightQ,const QString& brandQ,const QString& modelQ) {
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
    auto it = tableTransports.begin();
    while( it != tableTransports.end() ) {
        if( it->value( uniqueIdentificator) == deleteUniqueId ) {
            beginRemoveRows( QModelIndex(), i, i );
            it = tableTransports.erase( it );
            endRemoveRows();
        } else {
            ++i;
            ++it;
        }
    }
}
void TransportModel::printTransportTableInFile(){
    QFile fileOut("myfile.txt");
        if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            int i = 1;
            QTextStream inOut(&fileOut);
            inOut << trUtf8("\t\t\t\tТаблица записей") << "\n";
            for(auto item:tableTransports){
                inOut << trUtf8("Номер записи:")<< i << "\n";
                inOut << trUtf8("Уникальный идентификатор транспорта:")<<item.value(uniqueIdentificator).toString()<< "\n" ;
                inOut << trUtf8("Тип транспорта:")<<item.value(typeTransport).toString()<< "\n";
                inOut << trUtf8("Год выпуска транспорта:")<<item.value(yearManufacture).toString()<< "\n";
                inOut << trUtf8("Вес транспорта:")<< item.value(weight).toString()<< "\n";
                inOut << trUtf8("Марка транспорта:")<<item.value(brand).toString()<< "\n";
                inOut << trUtf8("Модель транспорта:")<<item.value(model).toString()<< "\n";
                inOut << "\n";
                i++;
            }



        }
    fileOut.close();
}
void TransportModel::fileappendTransport(const QString& idQ,const QString& typeTrQ,const QString& yearQ, const QString& weightQ,const QString& brandQ,const QString& modelQ) {
    TransportData transport;
    transport[ uniqueIdentificator ] = idQ;
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
void TransportModel::printTranportTableOutFile(){
    QFile fileOut("myfile.txt");
    QVector<QString> vec(10);
    QString str;
    int found;
    int count = 8;
    int j = 0;
    if(fileOut.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream inOut(&fileOut);
        str = inOut.readLine();
        while (!inOut.atEnd()) {
            //qDebug() << str;
            count--;
            while(count){
                str = inOut.readLine();
                if (count <= 6 && str.length()) {
                    found = str.indexOf(':');
                    vec[j] = str.mid(found + 1);
                    j++;
                }
                count--;
             }
            count = 8;
            j = 0;
            str = inOut.readLine();
            fileappendTransport(vec[0],vec[1],vec[2],vec[3],vec[4],vec[5]);
    }

  }


  fileOut.close();
}



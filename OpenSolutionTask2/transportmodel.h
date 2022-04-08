#ifndef TRANSPORTMODEL_H
#define TRANSPORTMODEL_H

#include <QAbstractTableModel>

class TransportModel : public QAbstractTableModel {
    Q_OBJECT
public:
    TransportModel( QObject* parent = 0 );

    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;

    void appendTransport(const QString& typeTrQ,const QString& weightQ, const QString& yearQ,const QString& brandQ,const QString& modelQ);
    void removeSelected(const QString& deleteUniqueId);

private:
    enum Column {
        uniqueIdentificator = 0,
        typeTransport,
        yearManufacture,
        weight,
        brand,
        model,
        LAST
    };

    typedef QHash< Column, QVariant > TransportData;
    typedef QList<TransportData > Transports;
    Transports tableTransports;

};
#endif // TRANSPORTMODEL_H

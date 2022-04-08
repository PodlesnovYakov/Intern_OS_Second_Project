#ifndef TRANSPORTWIDGET_H
#define TRANSPORTWIDGET_H
#include "transportmodel.h"
#include <QWidget>
#include <QTableView>
#include <QLineEdit>



class TransportWidget : public QWidget {
    Q_OBJECT

public:
    TransportWidget( QWidget* parent = 0 );
    ~TransportWidget();

private slots:
    void onAppend();
    void deleteTransport();
private:
    QTableView* TransportView;
    TransportModel* ModelTransport;

    QLineEdit* typeTransportEdit;
    QLineEdit* yearManufactureEdit;
    QLineEdit* brandEdit;
    QLineEdit* modelEdit;
    QLineEdit* weightEdit;
    QLineEdit* deleteTransportEdit;
};

#endif // TRANSPORTWIDGET_H

#include "TransportWidget.h"
#include "ui_widget.h"
#include <QTableView>
#include <QHeaderView>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

TransportWidget::TransportWidget( QWidget* parent ) : QWidget( parent ) {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    TransportView = new QTableView;
    TransportView->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    TransportView->setModel( ModelTransport = new TransportModel );
    mainLayout->addWidget( TransportView );

    QGridLayout* panelLayout = new QGridLayout;
    mainLayout->addLayout( panelLayout );

    QPushButton* removeButton = new QPushButton("Удалить");
    connect( removeButton, SIGNAL( clicked()), SLOT( deleteTransport()));
    panelLayout->addWidget( removeButton, 0, 2 );

    QLabel* lbDeleteTransport = new QLabel("Введите уникальный идентификатор транспорта, который хотите удалить");
    panelLayout->addWidget( lbDeleteTransport, 0, 0 );
    deleteTransportEdit = new QLineEdit;
    panelLayout->addWidget( deleteTransportEdit, 0, 1 );

    QLabel* lbTypeTransport = new QLabel("Тип транспорта");
    panelLayout->addWidget( lbTypeTransport, 1, 0 );
    typeTransportEdit = new QLineEdit;
    panelLayout->addWidget( typeTransportEdit, 1, 1 );

    QLabel* lbYearManufacture = new QLabel("Год выпуска");
    panelLayout->addWidget( lbYearManufacture, 1, 2 );
    yearManufactureEdit = new QLineEdit;
    panelLayout->addWidget( yearManufactureEdit, 1, 3 );

    QLabel* lbWeight = new QLabel("Вес");
    panelLayout->addWidget( lbWeight, 1, 4 );
    weightEdit = new QLineEdit;
    panelLayout->addWidget( weightEdit, 1, 5 );

    QLabel* lbModel = new QLabel("Модель");
    panelLayout->addWidget( lbModel, 1, 6 );
    modelEdit = new QLineEdit;
    panelLayout->addWidget( modelEdit, 1, 7 );

    QLabel* lbBrand = new QLabel("Марка");
    panelLayout->addWidget( lbBrand, 1, 8 );
    brandEdit = new QLineEdit;
    panelLayout->addWidget( brandEdit, 1, 9 );

    QPushButton* createButton = new QPushButton("Добавить");
    connect( createButton, SIGNAL( clicked() ), SLOT( onAppend() ) );
    panelLayout->addWidget( createButton, 1, 10 );

    resize( 1600, 1000 );
}

TransportWidget::~TransportWidget() {
}
void TransportWidget::deleteTransport(){
    ModelTransport->removeSelected(deleteTransportEdit->text());
}
void TransportWidget::onAppend() {
    ModelTransport->appendTransport(
        typeTransportEdit->text(),
        weightEdit->text(),
        yearManufactureEdit->text(),
        brandEdit->text(),
        modelEdit->text()
    );
}


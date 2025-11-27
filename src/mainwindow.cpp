#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mainwindow.h"
#include "calc_widget.h"

MainWindow::MainWindow():
    m_historyWidget(new QListWidget(this)),
    m_currentExpression(new QLineEdit(this)),
    m_calcWidget(new CalcWidget())
{
    QHBoxLayout* mainHLay = new QHBoxLayout(this);
    QVBoxLayout* rightVLay = new QVBoxLayout(this);

    this->setLayout(mainHLay);

    m_currentExpression->setReadOnly(true);

    rightVLay->addWidget(m_currentExpression);
    rightVLay->addWidget(m_calcWidget);

    mainHLay->addWidget(m_historyWidget);
    mainHLay->addLayout(rightVLay);

    const QSize calcSize = m_calcWidget->size();
}

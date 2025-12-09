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
    QHBoxLayout* mainHLay = new QHBoxLayout();
    QVBoxLayout* rightVLay = new QVBoxLayout();

    setLayout(mainHLay);

    m_currentExpression->setReadOnly(true);
    m_currentExpression->setText("0");

    rightVLay->addWidget(m_currentExpression);
    rightVLay->addWidget(m_calcWidget);

    mainHLay->addWidget(m_historyWidget);
    mainHLay->addLayout(rightVLay);

    connect(m_calcWidget, &CalcWidget::numberUpdated, this, &MainWindow::onNumberUpdated);
    connect(m_calcWidget, &CalcWidget::equalClicked, this, &MainWindow::onEqualClicked);
}

void MainWindow::onNumberUpdated(const QString& number)
{
    m_currentExpression->setText(number);
}

void MainWindow::onEqualClicked(const QString& firstNum, const QString& operation, const QString& secondNum, const QString& result)
{
    QString historyEntry = firstNum + " " + operation + " " + secondNum + " = " + result;
    m_historyWidget->addItem(historyEntry);

    m_currentExpression->setText(result);
}

#include "calc_widget.h"
#include "math_core.h"
#include <QGridLayout>
#include <QPushButton>
#include <QVector>

CalcWidget::CalcWidget():
    m_core(new MathCore()),
    m_currNum(QString())
{
    const QSize widgetSize(400, 300);
    const QSize buttonSize(50,50);

    QVector<QChar> signs{'+', '-', '*', '/', '.', '='};
    QGridLayout* mainLay = new QGridLayout(this);

    setLayout(mainLay);
    setFixedSize(widgetSize);

    for(int i = 0; i < 5; i++)
    {
        QPushButton* button = new QPushButton(QString(signs.takeFirst()), this);
        button->setFixedSize(buttonSize);
        mainLay->addWidget(button, 0, i);
        connect(button, &QPushButton::clicked, [this, button = button]()
                {
                    m_core->setFirstNum(m_currNum.toInt());
                    m_core->setOperation(button->text().at(0));
                    m_currNum.clear();
                });
    }

    int number = 1;
    for (int row = 1; row <= 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton* btnNum = new QPushButton(QString::number(number++), this);
            btnNum->setFixedSize(buttonSize);
            mainLay->addWidget(btnNum, row, col);
            connect(btnNum, &QPushButton::clicked, [this, btnNum = btnNum]() {m_currNum.append(btnNum->text());});
        }
    }

    QPushButton* btnZero = new QPushButton("0", this);
    btnZero->setFixedSize(buttonSize.width() * 2 + mainLay->horizontalSpacing(), buttonSize.height());
    mainLay->addWidget(btnZero, 4, 0, 1, 2);
    connect(btnZero, &QPushButton::clicked,
            [this, btnZero = btnZero] ()
            {
                m_currNum.append(btnZero->text());
            });

    QPushButton* eq = new QPushButton(QString(signs.takeFirst()), this);
    eq->setFixedSize(QSize(buttonSize.width(), 90));
    mainLay->addWidget(eq, 1, 3, 2, 1);
    connect(eq, &QPushButton::clicked, [this, eq = eq]() {m_currNum.append(eq->text());});
    show();
}

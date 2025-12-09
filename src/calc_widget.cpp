#include "calc_widget.h"
#include "math_core.h"
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QMessageBox>

CalcWidget::CalcWidget():
    m_core(new MathCore()),
    m_currNum(""),
    m_firstNum(""),
    m_operation(""),
    m_operationPending(false)
{
    const QSize widgetSize(400, 300);
    const QSize buttonSize(50,50);

    QVector<QString> signs{"+", "-", "*", "/", ".", "C"};
    QGridLayout* mainLay = new QGridLayout(this);
    setLayout(mainLay);
    setFixedSize(widgetSize);

    for(int i = 0; i < 5; i++)
    {
        QPushButton* button = new QPushButton(signs[i], this);
        button->setFixedSize(buttonSize);
        mainLay->addWidget(button, 0, i);

        connect(button, &QPushButton::clicked, [this, button]()
                {
                    QString buttonText = button->text();

                    if (buttonText == ".") {
                        if (m_currNum.isEmpty()) {
                            m_currNum = "0.";
                        }
                        else if (m_currNum.contains('.')) {
                            return;
                        }
                        else if (m_currNum == "-") {
                            m_currNum = "-0.";
                        }
                        else {
                            m_currNum.append(".");
                        }
                        emit numberUpdated(m_currNum);
                        return;
                    }

                    if (m_currNum.isEmpty() && buttonText != "-") {
                        QMessageBox::warning(this, "Ошибка", "Сначала введите число!");
                        return;
                    }

                    if (buttonText == "-" && m_currNum.isEmpty()) {
                        m_currNum = "-";
                        emit numberUpdated(m_currNum);
                        return;
                    }

                    if (buttonText == "-" && m_currNum.startsWith("-")) {
                        return;
                    }

                    if (!m_currNum.isEmpty() && m_currNum != "-") {
                        m_firstNum = m_currNum;
                        m_operation = buttonText;
                        m_core->setFirstNum(m_currNum.toFloat());
                        m_core->setOperation(buttonText.at(0));
                        m_operationPending = true;

                        emit numberUpdated(m_firstNum + " " + m_operation);
                    }
                });
    }

    QPushButton* btnClear = new QPushButton(signs[5], this);
    btnClear->setFixedSize(buttonSize);
    mainLay->addWidget(btnClear, 0, 5);
    connect(btnClear, &QPushButton::clicked, [this]() {
        m_currNum.clear();
        m_firstNum.clear();
        m_operation.clear();
        m_operationPending = false;
        emit numberUpdated("0");
    });

    int number = 1;
    for (int row = 1; row <= 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton* btnNum = new QPushButton(QString::number(number++), this);
            btnNum->setFixedSize(buttonSize);
            mainLay->addWidget(btnNum, row, col);

            connect(btnNum, &QPushButton::clicked, [this, btnNum]()
                    {
                        if (m_operationPending && !m_currNum.startsWith("-")) {
                            m_currNum.clear();
                            m_operationPending = false;
                        }

                        if (m_currNum == "0") {
                            m_currNum = btnNum->text();
                        } else if (m_currNum == "-0") {
                            m_currNum = "-" + btnNum->text();
                        } else {
                            m_currNum.append(btnNum->text());
                        }
                        emit numberUpdated(m_currNum);
                    });
        }
    }

    QPushButton* btnZero = new QPushButton("0", this);
    btnZero->setFixedSize(buttonSize.width() * 2 + mainLay->horizontalSpacing(), buttonSize.height());
    mainLay->addWidget(btnZero, 4, 0, 1, 2);

    connect(btnZero, &QPushButton::clicked, [this]()
            {
                if (m_operationPending) {
                    m_currNum.clear();
                    m_operationPending = false;
                }

                if (m_currNum.isEmpty() || m_currNum == "-") {
                    m_currNum.append("0");
                } else if (m_currNum != "0") {
                    m_currNum.append("0");
                }
                emit numberUpdated(m_currNum);
            });

    QPushButton* eq = new QPushButton("=", this);
    eq->setFixedSize(QSize(buttonSize.width(), buttonSize.height() * 3 + mainLay->verticalSpacing() * 2));
    mainLay->addWidget(eq, 1, 3, 3, 1);

    connect(eq, &QPushButton::clicked, [this]()
            {
                if (m_currNum.isEmpty() || m_currNum == "-") {
                    QMessageBox::warning(this, "Ошибка", "Нет числа для вычисления!");
                    return;
                }

                if (m_currNum.endsWith('.')) {
                    m_currNum.append('0');
                }

                if (m_operation.isEmpty()) {
                    emit numberUpdated(m_currNum);
                    return;
                }

                float secondNum = m_currNum.toFloat();
                m_core->calculate(secondNum);

                QString result = QString::number(m_core->getResult());

                emit equalClicked(m_firstNum, m_operation, m_currNum, result);

                m_currNum = result;
                m_firstNum = result;
                m_operationPending = false;

                emit numberUpdated(m_currNum);
            });

    show();
}

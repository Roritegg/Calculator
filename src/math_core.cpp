#include <iostream>
#include "math_core.h"

MathCore::MathCore():
    m_firstNum(0),
    m_secondNum(0),
    m_result(0),
    m_operation(MathOperation::UNKNOWN),
    m_operationChar(' ')
{}

void MathCore::setFirstNum(float num)
{
    m_firstNum = num;
}

void MathCore::setOperation(QChar ch)
{
    m_operationChar = ch;
    switch (ch.toLatin1())
    {
    case '+':
        m_operation = MathOperation::PLUS;
        break;
    case '-':
        m_operation = MathOperation::MINUS;
        break;
    case '*':
        m_operation = MathOperation::MULT;
        break;
    case '/':
        m_operation = MathOperation::DIV;
        break;
    default:
        m_operation = MathOperation::UNKNOWN;
    }
}

void MathCore::calculate(float num)
{
    m_secondNum = num;

    switch(m_operation)
    {
    case PLUS:
        m_result = m_firstNum + m_secondNum;
        break;
    case MINUS:
        m_result = m_firstNum - m_secondNum;
        break;
    case MULT:
        m_result = m_firstNum * m_secondNum;
        break;
    case DIV:
        if (m_secondNum != 0.0f)
        {
            m_result = m_firstNum / m_secondNum;
        }
        else
        {
            std::cout << "Error: Division by zero!" << std::endl;
            m_result = 0;
        }
        break;
    default:
        m_result = m_secondNum;
    }

    m_operation = UNKNOWN;
}

QString MathCore::getLastOperation() const
{
    return QString(m_operationChar);
}

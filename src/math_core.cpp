#include <iostream>
#include "mainwindow.h"
#include "math_core.h"

MathCore::MathCore(): m_firstNum(0),
    m_secondNum(0),
    m_result(0),
    m_operation(MathOperation::UNKOWN)
{}

void MathCore::setFirstNum(float num)
{
    m_firstNum = num;
}

void MathCore::setOperation(QChar ch)
{
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
        m_operation = MathOperation::UNKOWN;
    }
}

void MathCore::calculate(float num)
{
    m_secondNum = num;

    std::cout << m_firstNum << " " << m_secondNum << std::endl;

    switch(m_operation)
    {
    case PLUS:
        m_result = m_firstNum + m_secondNum;
        std::cout << m_result << std::endl;
        break;
    case MINUS:
        m_result = m_firstNum - m_secondNum;
        std::cout << m_result << std::endl;
        break;
    case MULT:
        m_result = m_firstNum * m_secondNum;
        std::cout << m_result << std::endl;
        break;
    case DIV:
        if (m_secondNum != 0)
        {
            m_result = m_firstNum / m_secondNum;
            std::cout << m_result << std::endl;
            break;
        }
        else
        {
            std::cout << "U can't divide by zero! ERORR!!!" << std::endl;
            break;
        }
    default:
        m_result = 0;
        std::cout << m_result << std::endl;
    }



    m_firstNum = 0;
    m_secondNum = 0;
}

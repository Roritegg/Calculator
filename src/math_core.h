#include <QObject>

class MathCore : public QObject
{
    Q_OBJECT
public:
    MathCore();
public slots:
    void setFirstNum(float);
    void setOperation(QChar);
    void calculate(float);

private:
    enum MathOperation
    {
        UNKOWN = 0,
        PLUS,
        MINUS,
        MULT,
        DIV
    };
    float m_firstNum;
    float m_secondNum;
    float m_result;
    MathOperation m_operation;
};

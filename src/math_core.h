#include <QObject>

class MathCore : public QObject
{
    Q_OBJECT

public:
    MathCore();
    float getResult() const { return m_result; }
    QString getLastOperation() const;

public slots:
    void setFirstNum(float);
    void setOperation(QChar);
    void calculate(float);

private:
    enum MathOperation
    {
        UNKNOWN = 0,
        PLUS,
        MINUS,
        MULT,
        DIV
    };

    float m_firstNum;
    float m_secondNum;
    float m_result;
    MathOperation m_operation;
    QChar m_operationChar;
};

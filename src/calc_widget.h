#include <QWidget>

class MathCore;

class CalcWidget : public QWidget
{
    Q_OBJECT

public:
    CalcWidget();
    QString getCurrentNumber() const { return m_currNum; }

signals:
    void equalClicked(const QString& firstNum, const QString& operation, const QString& secondNum, const QString& result);
    void numberUpdated(const QString& number);

private:
    MathCore* m_core;
    QString m_currNum;
    QString m_firstNum;
    QString m_operation;
    bool m_operationPending;
};

#include <QWidget>

class MathCore;

class CalcWidget : public QWidget
{
    Q_OBJECT

public:
    CalcWidget();
    QString getResult();
signals:
    void equalClicked(QChar);
    void buttonClicked();
private:
    MathCore* m_core;
    QString m_currNum;
};

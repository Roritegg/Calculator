#include <QWidget>

class QListWidget;
class QLineEdit;
class CalcWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void onNumberUpdated(const QString& number);
    void onEqualClicked(const QString& firstNum, const QString& operation, const QString& secondNum, const QString& result);

private:
    QListWidget* m_historyWidget;
    QLineEdit* m_currentExpression;
    CalcWidget* m_calcWidget;
};

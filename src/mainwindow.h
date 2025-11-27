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
    void onButtonClicked(QChar){};
    void onEqualClicked(){};
private:
    QListWidget* m_historyWidget;
    QLineEdit* m_currentExpression;
    CalcWidget* m_calcWidget;
};

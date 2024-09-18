#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QTimer *timer;
    QString getHostInfo();          /* 获取本机的网络的信息，返回类型是 QString */

private slots:
    void timerTimerout();   /* 定时器槽函数，点击按钮后定时触发 */
    void showHostInfo();    /* 显示本机信息 */
    void timerStart();      /* 启动定时器 */
    void clearHostInfo();   /* 清空 textBrowser 的信息 */
};
#endif // WIDGET_H

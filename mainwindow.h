#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 声明重写“窗口大小改变”事件
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_AC_clicked();//清空

    void on_Del_clicked();//删除

    void on_input_button_clicked();//输入槽函数

    void on_equals_clicked();//等于

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

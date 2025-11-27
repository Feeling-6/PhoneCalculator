#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJSEngine>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //数字槽
    connect(ui->one,   &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->two,   &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->three, &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->four,  &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->five,  &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->six,   &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->seven, &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->eight, &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->nine,  &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->zero,  &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->point, &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    //加减乘除
    connect(ui->add,      &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->subtract, &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->multiply, &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    connect(ui->divided,  &QPushButton::clicked, this, &MainWindow::on_input_button_clicked);
    //初始显示为空
    ui->displayLineEdit->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // 1. 调用父类处理，保证布局正常计算
    QMainWindow::resizeEvent(event);

    // 2. 根据窗口当前高度动态计算字号
    // 系数 0.05 意味着字体大小占窗口高度的 5%，你可以根据实际效果调整这个数字(比如 0.04 或 0.06)
    int h = this->height();
    int newFontSize = h * 0.05;

    // 限制最小字号为 12px，防止缩得太小看不见
    if (newFontSize < 12) newFontSize = 12;

    // 3. 自动查找界面上所有的按钮并设置新字体
    const QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
    for (QPushButton *btn : buttons) {
        QFont f = btn->font();
        f.setPixelSize(newFontSize); // 使用像素大小设置
        btn->setFont(f);
    }

    // 4. 单独设置显示屏的字体 (通常比按钮大一点)
    if (ui->displayLineEdit) {
        QFont f = ui->displayLineEdit->font();
        f.setPixelSize(newFontSize + 18); // 比按钮大 18px
        ui->displayLineEdit->setFont(f);
    }
}

//公共槽函数
void MainWindow::on_input_button_clicked()
{
    //获取信号
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;
    //获取按钮文本
    QString buttonText = clickedButton->text();
    if (buttonText.isEmpty()) return;
    //获取显示框当前内容
    QString currentText = ui->displayLineEdit->text();

    // 当前显示为空（""）、"Error"直接替换
    if (currentText.isEmpty() || currentText == "Error") {
        //如果按钮是小数点，前面加 "0"
        if (buttonText == ".") {
            ui->displayLineEdit->setText("0.");
        } else {
            ui->displayLineEdit->setText(buttonText);
        }
        return;
    }
    //安全获取最后一个字符
    QString lastString = currentText.right(1);
    //如果最后一个字符是运算符，再输入运算符的时候就替换掉
    if ((lastString == "+" || lastString == "-" || lastString == "x" || lastString == "÷")
        && (buttonText == "+" || buttonText == "-" || buttonText == "x" || buttonText == "÷")) {
        ui->displayLineEdit->setText(currentText.chopped(1) + buttonText);
        return;
    }
    //其他情况，直接输入
    ui->displayLineEdit->setText(currentText + buttonText);
}

//清空按钮
void MainWindow::on_AC_clicked()
{
    ui->displayLineEdit->setText("");
}

//删除按钮
void MainWindow::on_Del_clicked()
{
    //获取显示框当前内容
    QString currentText = ui->displayLineEdit->text();
    if(currentText == "Error"){
        ui->displayLineEdit->setText("");
    }
    ui->displayLineEdit->backspace();
}

//这个函数是ai写的
void MainWindow::on_equals_clicked()
{
    // 1. 获取完整的表达式
    QString expression = ui->displayLineEdit->text();
    //如果表达式是空的直接结束
    if(expression.isEmpty()){
        return;
    }

    // 2.替换UI符号为 JavaScript 认识的符号
    expression.replace("x", "*");
    expression.replace("÷", "/");

    // 3. 创建 JavaScript 引擎
    QJSEngine engine;

    // 4. 计算！
    QJSValue result = engine.evaluate(expression);

    // 5. 显示结果
    if (result.isError()) {
        // 如果表达式有错，显示 Error
        ui->displayLineEdit->setText("Error");
    } else {
        // 否则，把计算结果 (QJSValue) 转成字符串并显示
        ui->displayLineEdit->setText(result.toString());
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJSEngine>

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

//公共槽函数
void MainWindow::on_input_button_clicked()
{
    //获取信号
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton)
        return;
    //获取按钮文本
    QString buttonText = clickedButton->text();
    //获取显示框当前内容
    QString currentText = ui->displayLineEdit->text();

    // 如果当前显示的是 "" 或 "Error"
    // 我们就用新按键替换它
    if (currentText == "" && buttonText != ".") {
        ui->displayLineEdit->setText(buttonText);
    } else if (currentText == "Error" || currentText == "undefined") {
        ui->displayLineEdit->setText(buttonText);
    }
    // 否则，直接在末尾追加
    else {
        ui->displayLineEdit->setText(currentText + buttonText);
    }
}

//清空按钮
void MainWindow::on_AC_clicked()
{
    ui->displayLineEdit->setText("");
}

//删除按钮
void MainWindow::on_Del_clicked()
{
    ui->displayLineEdit->backspace();
}


void MainWindow::on_equals_clicked()
{
    // 1. 获取完整的表达式
    QString expression = ui->displayLineEdit->text();

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


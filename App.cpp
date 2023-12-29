#pragma once
#include <QMainWindow>
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QFont>
#include <QFontDatabase>
#include "solve.h"
#include "App.h"

App::App(int width, int height) {
    number_ = "";

    window_ = new QMainWindow();
    window_->setFixedSize(width, height);
    window_->setStyleSheet("QMainWindow {"
                           "background: #000 }");

    num_edit_ = new QLineEdit(window_);
    num_edit_->resize(550, 30);
    num_edit_->move(25, 15);
    num_edit_->setStyleSheet("QLineEdit { background: #858493;"
                             "color: #000;"
                             "border-radius: 8px;"
                             "opacity: 1; }");
    num_edit_->setPlaceholderText("исходное число");

    converted_num_ = new QLabel(window_);
    converted_num_->resize(550, 30);
    converted_num_->move(25, 65);
    converted_num_->setStyleSheet("QLabel { background: #858493;"
                                  "color: #000;"
                                  "border-radius: 8px;"
                                  "padding-left: 0.5px; }");
    converted_num_->setText("конвертированное число");

    base_edit_ = new QLineEdit(window_);
    base_edit_->resize(200, 30);
    base_edit_->move(600, 15);
    base_edit_->setStyleSheet("QLineEdit { background: #a7a6b5;"
                              "color: #000;"
                              "border-radius: 5px; }");
    base_edit_->setPlaceholderText("исходная система счисления");

    target_base_edit_ = new QLineEdit(window_);
    target_base_edit_->resize(200, 30);
    target_base_edit_->move(600, 65);
    target_base_edit_->setStyleSheet("QLineEdit { background: #a7a6b5;"
                                     "color: #000;"
                                     "border-radius: 5px; }");
    target_base_edit_->setPlaceholderText("новая система счисления");

    convert_ = new QPushButton(window_);
    convert_->resize(200, 40);
    convert_->move(600, 110);
    convert_->setStyleSheet("QPushButton { ""background: #aaa;"
                            "color: #000;"
                            "border-radius: 5px; }");
    convert_->setText("конвертировать");
    connect(convert_, SIGNAL (released()), this, SLOT (convertNumber()));

    save_button_ = new QPushButton(window_);
    save_button_->resize(100, 40);
    save_button_->move(25, 110);
    save_button_->setStyleSheet("QPushButton { background: #aaa;"
                                "color: #000;"
                                "border-radius: 5px; }");
    save_button_->setText("сохранить");
    connect(save_button_, SIGNAL (released()), this, SLOT (saveToFile()));

    load_button_ = new QPushButton(window_);
    load_button_->resize(100, 40);
    load_button_->move(140, 110);
    load_button_->setStyleSheet("QPushButton { background: #aaa;"
                                "color: #000;"
                                "border-radius: 5px; }");
    load_button_->setText("импортировать");
    connect(load_button_, SIGNAL (released()), this, SLOT (loadFromFile()));
}

App::~App() {
    delete load_button_;
    delete save_button_;
    delete window_;
    delete base_edit_;
    delete target_base_edit_;
    delete num_edit_;
    delete convert_;
    delete header_container_;
}

void App::convertNumber() {
    std::string number = num_edit_->text().toStdString();
    int base = base_edit_->text().toInt();
    int target = target_base_edit_->text().toInt();
    std::string a, b, c;
//    for (int i = 0; i < number.size(); ++i) {
//        if (number[i] >= 'a' && number[i] <= 'z') {
//            number[i] ^= 1<<5;
//        }
//        int tmp = 0;
//        if (number[i] == '[') {
//            ++i;
//            while (number[i] != ']') {
//                if (nu)
//            }
//        }
//    }
    int i = 0;
    for (; i < number.size(); ++i) {
        if (number[i] == '.' || number[i] == ',') {
            break;
        }
        a.push_back(number[i]);
    }
    ++i;
    for (; i < number.size(); ++i) {
        if (number[i] == '(') {
            break;
        }
        b.push_back(number[i]);
    }
    ++i;
    for (; i < number.size(); ++i) {
        if (number[i] == ')') {
            break;
        }
        c.push_back(number[i]);
    }
    number_ = solve(a, b, c, base, target);
    converted_num_->setText(QString::fromStdString(number_));
}

void App::saveToFile() {
    QString file = QFileDialog::getSaveFileName(nullptr, "Save to", "", "*.txt");
    QFile outFile(file);
    if (!outFile.open(QIODevice::WriteOnly)) return;
    QTextStream ostream(&outFile);
    ostream << QString::fromStdString(number_);
    outFile.close();
}

void App::loadFromFile() {
    num_edit_->clear();
    QString file = QFileDialog::getOpenFileName(nullptr, "Choose txt file", "", "*.txt");
    QFile in(file);
    if (!in.open(QIODevice::ReadOnly)) return;
    QString data = in.readLine();
    in.close();
    if (data.isEmpty()) return;
    num_edit_->setText(data);
}
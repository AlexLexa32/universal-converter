#pragma once
#include <QApplication>
#include "App.h"

int32_t main(int32_t argc, char *argv[]) {
    QApplication a(argc, argv);

    App convertor(825, 160);
    convertor.render();

    return QApplication::exec();
}

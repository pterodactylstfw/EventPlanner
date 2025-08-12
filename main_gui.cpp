#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("EventPlanner GUI - Hello Qt!");
    window.resize(500, 300);
    window.show();

    return app.exec();
}
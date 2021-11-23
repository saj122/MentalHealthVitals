#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

namespace Ui { class MainWindow; }

namespace MHV
{
    class ImageViewer;
    class Hashing;
    class Database;
}

namespace MHV
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            explicit MainWindow(QWidget *parent = nullptr);
            ~MainWindow() override;

        private slots:
            void on_actionExit_triggered();
            void setToPage();
            void registerUser();
            void loginUser();

        private:
            Ui::MainWindow *ui;

            std::unique_ptr<ImageViewer> _rgbViewer;

            std::unique_ptr<Database> _database;
            std::unique_ptr<Hashing> _hashing;
    };
}

#endif // MAINWINDOW_H

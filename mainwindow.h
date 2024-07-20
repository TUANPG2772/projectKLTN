#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_btnClear_clicked();
    void on_btnLoad_clicked();
    void on_btnSave_clicked();

    void on_btn_temp_clicked();

    void on_pushButton_4_clicked();

   // void on_btn_state_clicked();

   // void on_btn_getTemp_clicked();
    
   // void on_btn_getState_clicked();
    
    void on_btnLoad2_clicked();

    void on_result_temp_clicked();

    void on_result_state_clicked();

    void on_btnsave1_clicked();

private:
    Ui::MainWindow *ui;
    struct LongestSubstringResult {
        int length;
        QString substring;
    };
    LongestSubstringResult LengthOfLongestString(const QString &s); // Khai báo hàm LengthOfLongestString
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDebug>
#include <QHash>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "Open Directory");
    if (!dirPath.isEmpty())
        ui->lblDirectory->setText(dirPath);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                "Open File",
                "",
                "Text File(*.txt);; All File(*.*)");
    ui->lblOpenFile->setText(path);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString path = QFileDialog::getSaveFileName(
                this,
                "Save File",
                "",
                "Text File(*.txt);; All File(*.*)");
    ui->lblSaveFile->setText(path);
}

void MainWindow::on_btnClear_clicked()
{
    ui->txtEdit->clear();
}

void MainWindow::on_btnLoad_clicked()
{
    QFile file("/home/debian/testQT/outputMores.txt");
    QTextStream textStream(&file);
    if (file.open(QIODevice::ReadOnly))
    {
        QString str = textStream.readAll();
        ui->txtEdit->setPlainText(str);
        LongestSubstringResult result = LengthOfLongestString(str);
        ui->txtEditout->setPlainText(QString("Longest Substring: %1\nLength: %2").arg(result.substring).arg(result.length));
        file.close();
    }
    else {
        QMessageBox::critical(this, "Error", "Can not open file. Please check again.");
    }
}

void MainWindow::on_btnSave_clicked()
{
    QFile file("/home/debian/outputTest.txt");
    QTextStream textStream(&file);
    if (file.open(QIODevice::WriteOnly))
    {
        QString str = ui->txtEdit->toPlainText();
        textStream << str;
        file.close();
    }
    else {
        QMessageBox::critical(this, "Error", "Can not open file. Please check again.");
    }
}


MainWindow::LongestSubstringResult MainWindow::LengthOfLongestString(const QString &s)
{
    int n = s.length();
    QHash<QChar, int> index;
    int maxLength = 0;
    int start = 0;
    int maxStart = 0;
    int currentLength = 0;

    QHash<QString, int> substringCount;
    QString mostRepeatedSubstring;
    int mostRepeatedCount = 0;

    for (int end = 0; end < n; end++) {
        QChar currentChar = s[end];

        // Nếu gặp khoảng trắng, reset lại các giá trị
        if (currentChar.isSpace()) {
            // Kiểm tra và cập nhật chuỗi dài nhất
            if (currentLength > maxLength) {
                maxLength = currentLength;
                maxStart = start;
            }

            // Kiểm tra và cập nhật chuỗi lặp lại nhiều nhất
            QString currentSubstring = s.mid(start, currentLength);
            if (!currentSubstring.isEmpty()) {
                substringCount[currentSubstring]++;
                if (substringCount[currentSubstring] > mostRepeatedCount) {
                    mostRepeatedCount = substringCount[currentSubstring];
                    mostRepeatedSubstring = currentSubstring;
                }
            }

            // Reset lại các giá trị cho chuỗi tiếp theo
            index.clear();
            start = end + 1;
            currentLength = 0;
            continue;
        }

        // Nếu ký tự hiện tại đã xuất hiện trước đó và nằm trong khoảng của cửa sổ hiện tại
        if (index.contains(currentChar) && index[currentChar] >= start) {
            start = index[currentChar] + 1;
            currentLength = end - start;  // Cập nhật lại độ dài chuỗi con thực tế
        }

        // Cập nhật vị trí xuất hiện cuối cùng của ký tự hiện tại
        index[currentChar] = end;

        // Tính độ dài chuỗi con hiện tại (bỏ qua khoảng trắng)
        currentLength++;
    }

    // Kiểm tra lần cuối cùng sau khi kết thúc vòng lặp
    if (currentLength > maxLength) {
        maxLength = currentLength;
        maxStart = start;
    }

    QString currentSubstring = s.mid(start, currentLength);
    if (!currentSubstring.isEmpty()) {
        substringCount[currentSubstring]++;
        if (substringCount[currentSubstring] > mostRepeatedCount) {
            mostRepeatedCount = substringCount[currentSubstring];
            mostRepeatedSubstring = currentSubstring;
        }
    }

    QString longestSubstring;

    // Tạo chuỗi con dài nhất trong khi bỏ qua các ký tự khoảng trắng
    for (int i = maxStart; i < maxStart + maxLength; i++) {
        if (!s[i].isSpace()) {
            longestSubstring.append(s[i]);
        }
    }

    return {longestSubstring.length(), longestSubstring + "\nMost Repeated Substring: " + mostRepeatedSubstring + "\nCount: " + QString::number(mostRepeatedCount)};
}
void MainWindow::on_btn_temp_clicked()
{
    QProcess *process = new QProcess(this);
    QString program = "python3";

    QStringList arguments;

    arguments << "/home/debian/testQT/receiver.py";

    process->start(program, arguments);

    if(!process->waitForStarted()) {
        qDebug() << "Failed to start process";
        return;
    }

    if (!process->waitForFinished()) {
        qDebug() << "Failed to finish process";
        return;
    }

    QString output(process->readAllStandardOutput());
    QString error(process->readAllStandardError());

    qDebug() << "Output: " << output;
    qDebug() << "Error: " << error;

}

void MainWindow::on_pushButton_4_clicked()
{
    QProcess *process = new QProcess(this);
    QString program = "python3";

    QStringList arguments;

    arguments << "/home/debian/testQT/receiver1.py";

    process->start(program, arguments);

    if(!process->waitForStarted()) {
        qDebug() << "Failed to start process";
        return;
    }

    if (!process->waitForFinished()) {
        qDebug() << "Failed to finish process";
        return;
    }

    QString output(process->readAllStandardOutput());
    QString error(process->readAllStandardError());

    qDebug() << "Output: " << output;
    qDebug() << "Error: " << error;

}
//void MainWindow::on_btn_getTemp_clicked()
//{
//    QFile file("/home/debian/testQT/outputMores.txt");
//    QTextStream textStream(&file);
//    if (file.open(QIODevice::ReadOnly))
//    {
//        QString str = textStream.readAll();
//        ui->txtEdit->setPlainText(str);
//        LongestSubstringResult result = LengthOfLongestString(str);
//        ui->txtEditout_2->setPlainText(QString("Longest Substring: %1\nLength: %2").arg(result.substring).arg(result.length));
//        file.close();
//    }
//    else {
//        QMessageBox::critical(this, "Error", "Can not open file. Please check again.");
//    }
//}

//void MainWindow::on_btn_getState_clicked()
//{
//    QFile file("/home/tuan2772/testQT/outputMores1.txt");
//    QTextStream textStream(&file);
//    if (file.open(QIODevice::ReadOnly))
//    {
//        QString str = textStream.readAll();
//        ui->txtEdit->setPlainText(str);
//        LongestSubstringResult result = LengthOfLongestString(str);
//        ui->txtEditout_3->setPlainText(QString("Longest Substring: %1\nLength: %2").arg(result.substring).arg(result.length));
//        file.close();
//    }
//    else {
//        QMessageBox::critical(this, "Error", "Can not open file. Please check again.");
//    }
//}

void MainWindow::on_btnLoad2_clicked()
{
    QFile file("/home/debian/testQT/outputMores1.txt");
    QTextStream textStream(&file);
    if (file.open(QIODevice::ReadOnly))
    {
        QString str = textStream.readAll();
        ui->txtEdit->setPlainText(str);
        LongestSubstringResult result = LengthOfLongestString(str);
        ui->txtEditout->setPlainText(QString("Longest Substring: %1\nLength: %2").arg(result.substring).arg(result.length));
        file.close();
    }
    else {
        QMessageBox::critical(this, "Error", "Can not open file. Please check again.");
    }
}

void MainWindow::on_result_temp_clicked()
{
        QFile file("/home/debian/testQT/outputMores.txt");
        QTextStream textStream(&file);
        if (file.open(QIODevice::ReadOnly))
        {
            QString str = textStream.readAll();
            ui->txtEdit->setPlainText(str);
            LongestSubstringResult result = LengthOfLongestString(str);
            ui->txtEditout_2->setPlainText(QString("Longest Substring: %1\nLength: %2").arg(result.substring).arg(result.length));
            file.close();
        }
        else {
            QMessageBox::critical(this, "Error", "Can not open file. Please check again.");
        }
}

void MainWindow::on_result_state_clicked()
{
        QFile file("/home/debian/testQT/outputMores1.txt");
        QTextStream textStream(&file);
        if (file.open(QIODevice::ReadOnly))
        {
            QString str = textStream.readAll();
            ui->txtEdit->setPlainText(str);
            LongestSubstringResult result = LengthOfLongestString(str);
            ui->txtEditout_3->setPlainText(QString("Longest Substring: %1\nLength: %2").arg(result.substring).arg(result.length));
            file.close();
        }
        else {
            QMessageBox::critical(this, "Error", "Can not open file. Please check again.");
        }
}

void MainWindow::on_btnsave1_clicked()
{
    QFile file("/home/debian/outputTest1.txt");
    QTextStream textStream(&file);
    if (file.open(QIODevice::WriteOnly))
    {
        QString str = ui->txtEdit->toPlainText();
        textStream << str;
        file.close();
    }
    else {
        QMessageBox::critical(this, "Error", "Can not open file. Please check again.");
    }
}

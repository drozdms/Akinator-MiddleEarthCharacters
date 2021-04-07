#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Questions.h"
#include "Rule.h"
#include "Database.h"
#include "Attribute.h"
#include <qstack.h>
#include "ui_mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void exec();

private slots:


    void on_buttonNextRace_clicked();

    void on_tryAgainButton_clicked();

    void on_actionexit_triggered();

    void on_nextAlive_clicked();

    void on_nextPosNeg_clicked();

    void on_activityNext_clicked();

    void on_nextStatus_clicked();

    void on_nextRealm_clicked();

    void closeEvent(QCloseEvent*) override;


private:
    QStack<Goal*> goalStack;
    QList<Goal*> ruleList;

    void generateRaceActivities(race);
    void generateRaceRealms(race);
};
#endif // MAINWINDOW_H

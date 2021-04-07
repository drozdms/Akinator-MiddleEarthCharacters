#include "mainwindow.h"

#include <iostream>
#include <boost/optional.hpp>
#include <QApplication>
#include <QThread>
#include <QTimer>

using namespace std;
static boost::optional<race> currentRace = none;
static boost::optional<isAlive> currentAlive = none;
static boost::optional<character> currentCharacter = none;
static boost::optional<posNeg> currentPosNeg = none;
static boost::optional<status> curStatus = none;
static boost::optional<realm> curRealm = none;
static boost::optional<activity> curActivity = none;
static bool algoStop = false;
static bool waitForUser = false;
static bool triggerRestart = false;
template <typename T>
bool analyzeRule(Rule<T>* rule, QStack<Goal*> * goalStack)    {


    switch (rule->checkRule(currentRace, currentAlive, currentPosNeg, curStatus, curRealm, curActivity)) {

        case 1:

            if (typeid (T) == typeid(race))
                currentRace = static_cast<race>(rule->getConclusion());
            else if (typeid (T) == typeid(isAlive))
                currentAlive = static_cast<isAlive>(rule->getConclusion());
            else if (typeid(T) == typeid(character))
                currentCharacter = static_cast<character>(rule->getConclusion());
            else if (typeid(T) == typeid(realm))
                curRealm = static_cast<realm>(rule->getConclusion());
            else if (typeid(T) == typeid(posNeg))
                currentPosNeg = static_cast<posNeg>(rule->getConclusion());
            else if (typeid(T) == typeid(status))
                curStatus = static_cast<status>(rule->getConclusion());
            else if (typeid(T) == typeid(activity))
                curActivity = static_cast<activity>(rule->getConclusion());

            goalStack->pop();

            rule->tossAway();       // we don't need this rule anymore ???

            if (goalStack->empty())
                algoStop = true;
            else return true;
        break;



        case 0:         // rule is  false
            rule->tossAway();
        break;

        case -1:
            goalStack->push(new Attribute<race>(rule->getNumber()));     // push into stack with this rule's number

        break;

        case -2:
            goalStack->push(new Attribute<isAlive>(rule->getNumber()));
        break;

        case -3:
            goalStack->push(new Attribute<posNeg>(rule->getNumber()));
        break;

        case -4:
            goalStack->push(new Attribute<status>(rule->getNumber()));
        break;

        case -5:
            goalStack->push(new Attribute<realm>(rule->getNumber()));
        break;

        case -6:
            goalStack->push(new Attribute<activity>(rule->getNumber()));
        break;


    }

    return false;




}

bool preProcAnalyzeRule(int i, QList<Goal*> * ruleList, QStack<Goal*> * goalStack)   {

    bool anRetType;
    if (ruleList->at(i)->returnType() == "r race")
        anRetType = analyzeRule(static_cast<Rule<race>*>(ruleList->at(i)), goalStack);
    else if (ruleList->at(i)->returnType() == "r isAlive")
        anRetType = analyzeRule(static_cast<Rule<isAlive>*>(ruleList->at(i)), goalStack);
    else if (ruleList->at(i)->returnType() == "r character")
        anRetType = analyzeRule(static_cast<Rule<character>*>(ruleList->at(i)), goalStack);
    else if (ruleList->at(i)->returnType() == "r status")
        anRetType = analyzeRule(static_cast<Rule<status>*>(ruleList->at(i)), goalStack);
    else if (ruleList->at(i)->returnType() == "r posNeg")
        anRetType = analyzeRule(static_cast<Rule<posNeg>*>(ruleList->at(i)), goalStack);
    else if (ruleList->at(i)->returnType() == "r realm")
        anRetType = analyzeRule(static_cast<Rule<realm>*>(ruleList->at(i)), goalStack);
    else if (ruleList->at(i)->returnType() == "r activity")
        anRetType = analyzeRule(static_cast<Rule<activity>*>(ruleList->at(i)), goalStack);
    return anRetType;

}

int searchRule(Goal* goal, QList<Goal*> * ruleList)  {

    // there are only rules on the ruleList

    string goalName = goal ->returnType();



    for (int i = 0; i<ruleList->size(); ++i)    {

        if (ruleList->at(i)->isActual())    {
            string ruleReturnType = ruleList->at(i)->returnType();

            int compareStrings = goalName.compare(2, string::npos, ruleReturnType, 2, string::npos);

            if (compareStrings == 0)
                return i;
        }
    }

    return -1;



}




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setupUi(this);

    this->setWindowIcon(QIcon("images/LotrIcon.png"));

    uint quant = ruleList.size();
    ruleList.append(new Rule<isAlive>(isAlive::alive, quant++, race::Valar));
    ruleList.append(new Rule<character>(character::Gimli, quant++, race::Dwarf, isAlive::alive));
    ruleList.append(new Rule<character>(character::Thorin, quant++, race::Dwarf, isAlive::dead, posNeg::positive,
                                        status::king, realm::LonelyM));
    ruleList.append(new Rule<character>(character::Balin, quant++, race::Dwarf, isAlive::dead, posNeg::positive,
                                        status::king, realm::Moria));
    ruleList.append(new Rule<character>(character::Frodo, quant++, race::Hobbit, isAlive::alive, posNeg::positive,
                                        status::undefinedStatus, realm::Shire, activity::woreTheRing));
    ruleList.append(new Rule<character>(character::Bilbo, quant++, race::Hobbit, isAlive::alive, posNeg::positive,
                                        status::undefinedStatus, realm::Shire, activity::helpedTheDwarves));
    ruleList.append(new Rule<character>(character::Gollum, quant++, race::Hobbit, isAlive::dead, posNeg::negative,
                                        status::undefinedStatus, realm::Shire, activity::woreTheRing));
    ruleList.append(new Rule<status>(status::regular, quant++, race::Hobbit, isAlive::undefinedIsAlive, posNeg::undefinedPosNeg,
                                        status::undefinedStatus, realm::undefinedRealm));

    ruleList.append(new Rule<character>(character::Sam, quant++, race::Hobbit, isAlive::alive, posNeg::positive,
                                        status::undefinedStatus, realm::Shire, activity::helpedHisMaster));
    ruleList.append(new Rule<character>(character::Merry, quant++, race::Hobbit, isAlive::alive, posNeg::positive,
                                        status::undefinedStatus, realm::Rohan, activity::undefinedActivity));
    ruleList.append(new Rule<character>(character::Pippin, quant++, race::Hobbit, isAlive::alive, posNeg::positive,
                                        status::undefinedStatus, realm::Gondor, activity::undefinedActivity));
    ruleList.append(new Rule<character>(character::Elrond, quant++, race::Elf, isAlive::alive, posNeg::positive,
                                        status::king, realm::Rivendell, activity::undefinedActivity));

    ruleList.append(new Rule<character>(character::Galadriel, quant++, race::Elf, isAlive::alive, posNeg::positive,
                                        status::king, realm::Lorien, activity::undefinedActivity));
    ruleList.append(new Rule<character>(character::Thranduil, quant++, race::Elf, isAlive::alive, posNeg::positive,
                                        status::king, realm::Mirkwood, activity::undefinedActivity));
    ruleList.append(new Rule<character>(character::Legolas, quant++, race::Elf, isAlive::alive, posNeg::positive,
                                        status::greatWarrior, realm::Mirkwood, activity::undefinedActivity));
    ruleList.append(new Rule<character>(character::Glorfindel, quant++, race::Elf, isAlive::alive, posNeg::positive,
                                        status::greatWarrior, realm::Gondolin));
    ruleList.append(new Rule<character>(character::Fingolfin, quant++, race::Elf, isAlive::dead, posNeg::positive,
                                        status::king, realm::undefinedRealm, activity::fougthMorgoth));
    ruleList.append(new Rule<character>(character::GilGalad, quant++, race::Elf, isAlive::dead, posNeg::positive,
                                        status::king, realm::undefinedRealm, activity::diedFightingSauron));
    ruleList.append(new Rule<character>(character::Turgon, quant++, race::Elf, isAlive::dead, posNeg::positive,
                                        status::king, realm::Gondolin));
    ruleList.append(new Rule<character>(character::Echtelion, quant++, race::Elf, isAlive::dead, posNeg::positive,
                                        status::greatWarrior, realm::Gondolin));
    ruleList.append(new Rule<character>(character::Feanor, quant++, race::Elf, isAlive::dead, posNeg::negative,
                                        status::undefinedStatus, realm::undefinedRealm, activity::madeSilmarils));
    ruleList.append(new Rule<character>(character::Ingwe, quant++, race::Elf, isAlive::alive, posNeg::positive,
                                        status::king, realm::Valinor));
    ruleList.append(new Rule<character>(character::Aragorn, quant++, race::Man, isAlive::alive, posNeg::positive,
                                        status::king, realm::Gondor));
    ruleList.append(new Rule<character>(character::Eomer, quant++, race::Man, isAlive::alive, posNeg::positive,
                                        status::king, realm::Rohan));
    ruleList.append(new Rule<character>(character::Theoden, quant++, race::Man, isAlive::dead, posNeg::positive,
                                        status::king, realm::Rohan));
    ruleList.append(new Rule<character>(character::Tuor, quant++, race::Man, isAlive::dead, posNeg::positive,
                                        status::greatWarrior, realm::Gondolin));
    ruleList.append(new Rule<character>(character::Thurin, quant++, race::Man, isAlive::dead, posNeg::positive,
                                        status::greatWarrior, realm::DorLomin));
    ruleList.append(new Rule<character>(character::Boromir, quant++, race::Man, isAlive::dead, posNeg::positive,
                                        status::greatWarrior, realm::Gondor));
    ruleList.append(new Rule<character>(character::Sauron, quant++, race::Maiar, isAlive::dead, posNeg::negative,
                                        status::undefinedStatus, realm::Mordor));
    ruleList.append(new Rule<character>(character::Saruman, quant++, race::Maiar, isAlive::dead, posNeg::negative,
                                        status::undefinedStatus, realm::Orthanc));
    ruleList.append(new Rule<character>(character::Gandalf, quant++, race::Maiar, isAlive::alive, posNeg::positive,
                                        status::undefinedStatus, realm::undefinedRealm, activity::helpedPeoplesOfMiddleEarth));
    ruleList.append(new Rule<character>(character::Radagast, quant++, race::Maiar, isAlive::alive, posNeg::positive,
                                        status::undefinedStatus, realm::undefinedRealm, activity::TakesCareAboutAnimals));
    ruleList.append(new Rule<character>(character::Manwe, quant++, race::Valar, isAlive::undefinedIsAlive, posNeg::positive,
                                        status::undefinedStatus, realm::air));
    ruleList.append(new Rule<character>(character::Aule, quant++, race::Valar, isAlive::undefinedIsAlive, posNeg::positive,
                                        status::undefinedStatus, realm::earth));
    ruleList.append(new Rule<character>(character::Varda, quant++, race::Valar, isAlive::undefinedIsAlive, posNeg::positive,
                                        status::undefinedStatus, realm::stars));
    ruleList.append(new Rule<character>(character::Ulmo, quant++, race::Valar, isAlive::undefinedIsAlive, posNeg::positive,
                                        status::undefinedStatus, realm::water));
    ruleList.append(new Rule<character>(character::Melkor, quant++, race::Valar, isAlive::undefinedIsAlive, posNeg::negative));
    ruleList.append(new Rule<status>(status::king, quant++, race::Man, isAlive::alive));
    ruleList.append(new Rule<posNeg>(posNeg::positive, quant++, race::Man));
    ruleList.append(new Rule<character>(character::DurinsBane, quant++, race::Maiar, isAlive::dead, posNeg::negative,
                                        status::undefinedStatus, realm::Moria));
    ruleList.append(new Rule<character>(character::Glorfindel, quant++, race::Elf, isAlive::alive, posNeg::positive,
                                        status::greatWarrior, realm::Rivendell));

/*
    int quant = ruleList.size();
    int prepquant = 0;
    for (int al = isAlive::undefinedIsAlive; al<= isAlive::alive; al++)
    {
        for (int st = status::undefinedStatus; st<= status::regular; st++)
        {
            for (int pN = posNeg::undefinedPosNeg; pN<= posNeg::negative; pN++)
            {
                for (int act = activity::undefinedActivity; act<= activity::inTheQuestForLonelyMountaint; act++)
                {
                    int q = 0;
                    int ind = -1;
                    for (int i = prepquant; i<quant + prepquant; ++i)
                    {
                        if (ruleList.at(i)->returnType() == "r enum character")
                            if (((Rule<character>*)ruleList.at(i))->
                                    checkRuleUndefined(Elf, (isAlive)al, (posNeg)pN, (status)st, none,(activity)act))
                            {
                                q++;
                                ind = i;
                            }
                    }
                    if (q == 1)
                    {
                        ruleList.prepend(new Rule<character>(((Rule<character>*)ruleList.at(ind))->getConclusion(), 0,
                                                            Elf, (isAlive)al, (posNeg)pN, (status)st, realm::undefinedRealm, (activity)act));
                        for (int j = 1; j < ruleList.size(); ++j)
                            ruleList.at(j)->setNumber(ruleList.at(j)->getNumber()+1);
                        prepquant++;

                    }
                }
            }
        }
    }*/

    QAction *restart = new QAction("Restart");
    QAction *exit  = new QAction("Exit");
    this->menubar->addAction(restart);
    this->menubar->addAction(exit);
    this->stackedWidget->setCurrentWidget(startWidget);
    connect(restart, SIGNAL(triggered()), this, SLOT(on_tryAgainButton_clicked()));
    connect(exit, SIGNAL(triggered()), this, SLOT(on_actionexit_triggered()));
    connect(this, SIGNAL(destroyed()), this, SLOT(on_actionexit_triggered()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(on_tryAgainButton_clicked()));

}


void MainWindow::exec()  {

    goalStack.push(new Attribute<character>());
    algoStop = false;
    while (!algoStop)   {

        int i = searchRule(goalStack.top(), &ruleList);

        if (i >= 0)
        {

            if (preProcAnalyzeRule(i, &ruleList, &goalStack))
                continue;              // go to the next goal

        }

        else    {
            // if there is a question, ask a question
            if (questionIndices.find(goalStack.top()->returnType()) != questionIndices.end())
            {
                if (goalStack.size() <= 1){
                    algoStop = true;
                    continue;
                }
                stackedWidget->setCurrentIndex(questionIndices.value(goalStack.top()->returnType()));
                waitForUser = true;
                QTimer *timer = new QTimer(this);
                while (waitForUser)  {
                    QEventLoop loop;
                    timer->start(5);
                    connect(timer, SIGNAL(timeout()), &loop, SLOT(quit()));
                    loop.exec();
                }
                // assign required value to global var
                if (algoStop)
                    return;
                // delete attribute from stack
                int ruleNumber = goalStack.pop()->getNumber();
                if (ruleNumber >= 0)
                {
                    if (preProcAnalyzeRule(ruleNumber, &ruleList, &goalStack))
                        continue;              // go to the next goal

                }

            }   else    algoStop = true;
        }
    }
    stackedWidget->setCurrentIndex(questionIndices.value("success"));
    if (currentCharacter)  {

        QPixmap pic(QString::fromStdString(pathsAndNames.value(currentCharacter.value()).second));
        finalImage->setPixmap(pic.scaled(finalImage->width() < pic.width() ? finalImage->width() : pic.width(), finalImage->height(), Qt::KeepAspectRatio));
        string name = pathsAndNames.value(currentCharacter.value()).first;
        finalMessage->setText(QString::fromStdString("Congratulations! It's " + name + "!\nWanna try again?"));

    }
    else
    {
        finalImage->setPixmap(QPixmap("images/gollum_sad").scaled(finalImage->width(), finalImage->height(), Qt::KeepAspectRatio));
        finalMessage->setText(QString::fromStdString("Oh no... I cannot guess. Try again!"));
    }





}

MainWindow::~MainWindow()
{

}


void MainWindow::on_buttonNextRace_clicked()
{

    QString rac = comboBoxRace->currentText();
    if (rac == "Elf")   {
        currentRace = race::Elf;
        generateRaceActivities(race::Elf);
        generateRaceRealms(race::Elf);
    }
    else if (rac == "Valar")    {
        currentRace = race::Valar;
        generateRaceActivities(race::Valar);
        generateRaceRealms(race::Valar);
    }
    else if (rac == "Maiar")    {
        currentRace = race::Maiar;
        generateRaceActivities(race::Maiar);
        generateRaceRealms(race::Maiar);
    }
    else if (rac == "Man")  {
        currentRace = race::Man;
        generateRaceActivities(race::Man);
        generateRaceRealms(race::Man);
    }
    else if (rac == "Dwarf")    {
        currentRace = race::Dwarf;
        generateRaceActivities(race::Dwarf);
        generateRaceRealms(race::Dwarf);
    }
    else if (rac == "Hobbit")   {
        currentRace = race::Hobbit;
        generateRaceActivities(race::Hobbit);
        generateRaceRealms(race::Hobbit);
    }
    waitForUser = false;
}

void MainWindow::on_tryAgainButton_clicked()
{
    algoStop = false;
    currentRace = none;
    currentAlive = none;
    currentCharacter = none;
    currentPosNeg = none;
    curStatus = none;
    curRealm = none;
    curActivity = none;
    activityComboBox->clear();
    realmComboBox->clear();
    waitForUser = false;
    for (int i =0; i<ruleList.size(); ++i)
        ruleList[i]->setActual();
    goalStack.clear();

   // while(true)
        this->exec();
}

void MainWindow::on_nextAlive_clicked()
{
    if (this->yesNoButtonGroupAlive->checkedId()==-1)
        return;
//    else if (yesNoButtonGroupAlive->checkedButton() == undefinedAlive)
  //      currentAlive = isAlive::undefinedIsAlive;
    else if (yesNoButtonGroupAlive->checkedButton() == yesAlive)
        currentAlive = isAlive::alive;
    else if (yesNoButtonGroupAlive->checkedButton() == this->noNotAlive)
        currentAlive = isAlive::dead;
    else return;
    waitForUser = false;
}

void MainWindow::on_nextPosNeg_clicked()
{
    if (this->posNegButtonGroup->checkedId()==-1)
        return;
    else if (posNegButtonGroup->checkedButton() == posRadButton)
        currentPosNeg = posNeg::positive;
    else    if (posNegButtonGroup->checkedButton() == negRadButton)
         currentPosNeg = posNeg::negative;
    else return;
    waitForUser = false;
}

void MainWindow::on_activityNext_clicked()
{
    QString acti = activityComboBox->currentText();
    curActivity = activity::undefinedActivity;
    if (activities.find(acti) != activities.end())
        curActivity = activities.value(acti);
    waitForUser = false;

}

void MainWindow::on_nextStatus_clicked()
{
    if (this->statusButtonGroup->checkedId()==-1)
        return;
    if (this->statusButtonGroup->checkedButton() == this->kingButton)
        curStatus = status::king;
    else  if (this->statusButtonGroup->checkedButton() == this->regularButton)
        curStatus = status::regular;
    else  if (this->statusButtonGroup->checkedButton() == this->gwarriorButton)
        curStatus = status::greatWarrior;
    waitForUser = false;
}

void MainWindow::on_nextRealm_clicked()
{
    QString realmm = realmComboBox->currentText();
    curRealm = realm::undefinedRealm;
    if (realms.find(realmm) != realms.end())
        curRealm = realms.value(realmm);
    waitForUser = false;
}

void MainWindow::on_actionexit_triggered() {

    waitForUser = false;
    algoStop = true;

    this->close();
    qApp->quit();
}


void MainWindow::generateRaceActivities(race r) {



    activityComboBox->addItem("");
    switch (r)  {

       case Elf:
            activityComboBox->addItems(elvesActivities);
       break;
       case Hobbit:
            activityComboBox->addItems(hobbitsActivities);
       break;
       case Valar:
            activityComboBox->addItems(valarsActivities);
       break;

        case Maiar:
              activityComboBox->addItems(maiarsActivities);
        break;

        case Dwarf:
              activityComboBox->addItems(dwarvesActivities);
        break;

    case Man:
          activityComboBox->addItems(menActivities);
    break;

    default:
        break;


    }



}

void MainWindow::generateRaceRealms(race r) {



    realmComboBox->addItem("");
    switch (r)  {

       case Elf:
            realmComboBox->addItems(elfRealms);
       break;
       case Hobbit:
            realmComboBox->addItems(hobbitRealms);
       break;
       case Valar:
            realmComboBox->addItems(valarRealms);
       break;

        case Maiar:
              realmComboBox->addItems(maiarRealms);
        break;

        case Dwarf:
              realmComboBox->addItems(dwarfRealms);
        break;

    case Man:
          realmComboBox->addItems(manRealms);
    break;

    default:
        break;


    }



}

void MainWindow::closeEvent(QCloseEvent* e) {

    this->on_actionexit_triggered();

}

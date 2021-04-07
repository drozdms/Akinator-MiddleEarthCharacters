#ifndef QUESTIONS_H
#define QUESTIONS_H

#include "Attribute.h"
#include <QMap>
#include "Database.h"

static QMap<std::string, int> questionIndices
({{"a race",0}, {"a isAlive",1}, {"a status", 2}, {"a posNeg", 3},
  {"a realm", 4}, {"a activity", 5},
  {"a character",6}, {"success",7}});  // questions depend on type of the goal which we pass as key

static const QStringList elvesActivities{"Fought Morgoth Himself",
                                         "Died Fighting Sauron",
                                         "Made The Silmarils",
                                        "Died Protecting Gondolin"};

static const QStringList hobbitsActivities{"Wore The Ring",
                                         "Helped his Master in his Quest",
                                         "Followed Frodo and Sam from the Shire",
                                        "Helped the Dwarves"};

static const QStringList maiarsActivities{"Helped peoples of Middle-Earth",
                                         "Took care about animals"};

static const QStringList valarsActivities{""};


static const QStringList menActivities{""};

static const QStringList dwarvesActivities{"Was in the Quest for the Lonely Mountain"};

static const QStringList valarRealms{"water", "earth", "air", "stars"};
static const QStringList hobbitRealms{"Shire", "Gondor", "Rohan"};
static const QStringList elfRealms{"Gondolin", "Rivendell", "Lorien", "Mirkwood", "Valinor"};
static const QStringList manRealms{"Gondor", "Rohan", "Gondolin", "Dor-Lomin"};
static const QStringList maiarRealms{"Moria", "Mordor", "Orthanc"};
static const QStringList dwarfRealms{"Moria", "Lonely Mountain"};




static const QMap<QString, activity> activities{{elvesActivities[0], activity::fougthMorgoth},
                                                {elvesActivities[1], activity::diedFightingSauron},
                                               {elvesActivities[2], activity::madeSilmarils},
                                               {elvesActivities[3], activity::diedProtectingGondolin},
                                                {hobbitsActivities[0], activity::woreTheRing},
                                                {hobbitsActivities[1], activity::helpedHisMaster},
                                                {hobbitsActivities[2], activity::followedFrodoAndSam},
                                                {hobbitsActivities[3], activity::helpedTheDwarves},
                                                {maiarsActivities[0], activity::helpedPeoplesOfMiddleEarth},
                                               {maiarsActivities[1], activity::TakesCareAboutAnimals},
                                                {dwarvesActivities[0], activity::inTheQuestForLonelyMountain}};


static const QMap<QString, realm> realms{{valarRealms[0], realm::water},
                                        {valarRealms[1], realm::earth},
                                        {valarRealms[2], realm::air},
                                        {valarRealms[3], realm::stars},
                                        {hobbitRealms[0], realm::Shire},
                                        {hobbitRealms[1], realm::Gondor},
                                        {hobbitRealms[2], realm::Rohan},
                                        {elfRealms[0], realm::Gondolin},
                                        {elfRealms[1], realm::Rivendell},
                                        {elfRealms[2], realm::Lorien},
                                        {elfRealms[3], realm::Mirkwood},
                                        {elfRealms[4], realm::Valinor},
                                        {manRealms[0], realm::Gondor},
                                        {manRealms[1], realm::Rohan},
                                        {manRealms[2], realm::Gondolin},
                                        {manRealms[3], realm::DorLomin},
                                        {maiarRealms[0], realm::Moria},
                                        {maiarRealms[1], realm::Mordor},
                                        {maiarRealms[2], realm::Orthanc},
                                        {dwarfRealms[0], realm::Moria},
                                        {dwarfRealms[1], realm::LonelyM}};

#endif // QUESTIONS_H

#ifndef DATABASE_H
#define DATABASE_H

#include <QMap>

enum race { undefinedRace, Valar,  Maiar, Elf, Man, Dwarf, Hobbit };
enum isAlive {undefinedIsAlive, dead, alive};                 // at the end of the Third Age


enum posNeg {undefinedPosNeg, positive, negative};

enum realm {undefinedRealm, water, earth, air, stars, Gondor, Rohan, Gondolin, DorLomin,
            Rivendell, Lorien, Mirkwood, Valinor, LonelyM, Moria, Shire, Mordor, Orthanc};

enum status {undefinedStatus, king, greatWarrior, regular};

enum activity { undefinedActivity, helpedPeoplesOfMiddleEarth, TakesCareAboutAnimals, fougthMorgoth,
                diedFightingSauron, madeSilmarils, diedProtectingGondolin, woreTheRing, helpedHisMaster, followedFrodoAndSam,
                helpedTheDwarves, inTheQuestForLonelyMountain};



enum character { undefinedCharacter, Gandalf, Frodo, Sam, Merry, Pippin, Elrond, Aragorn, Legolas,
                 Gimli, Balin, Saruman, Sauron, Boromir, Radagast, Thorin, Thranduil,
                 Galadriel, GilGalad, Fingolfin, Manwe, Melkor, Aule, Ulmo, Gollum, Theoden, Eomer,
               Feanor, Echtelion, Turgon, Glorfindel, Ingwe, Thurin, Tuor, DurinsBane, Bilbo, Varda};

static QMap<character, std::pair<std::string, std::string>> pathsAndNames
({{character::Gandalf, {"Gandalf", "images/Gandalf.jpg"}},
  {character::Frodo, {"Frodo","images/Frodo.jpg"}},
  {character::Gimli, {"Gimli","images/Gimli.jpg"}},
  {character::Bilbo, {"Bilbo", "images/Bilbo.jpg"}},
  {character::Gollum, {"Gollum","images/Gollum.jpg"}},
 {character::Sam, {"Sam","images/Sam.jpg"}},
 {character::Merry, {"Merry","images/Merry.jpg"}},
 {character::Pippin, {"Pippin","images/Pippin.jpg"}},
 {character::Echtelion, {"Echtelion","images/Echtelion.jpg"}},
 {character::Feanor, {"Feanor","images/Feanor.jpg"}},
 {character::Turgon, {"Turgon","images/Turgon.jpg"}},
 {character::GilGalad, {"Gil-Galad","images/Gil-Galad.jpg"}},
 {character::Fingolfin, {"Fingolfin","images/Fingolfin.jpg"}},
 {character::Glorfindel, {"Glorfindel","images/Glorfindel.jpg"}},
 {character::Legolas, {"Legolas","images/Legolas.jpg"}},
 {character::Ingwe, {"Ingwe","images/Ingwe.jpg"}},
 {character::Thranduil, {"Thranduil","images/Thranduil.jpg"}},
 {character::Galadriel, {"Galadriel","images/Galadriel.jpg"}},
 {character::Elrond, {"Elrond","images/Elrond.jpg"}},
 {character::Boromir, {"Boromir","images/Boromir.jpg"}},
 {character::Thurin, {"Turin","images/Turin.jpg"}},
 {character::Tuor, {"Tuor","images/Tuor.jpg"}},
 {character::Theoden, {"Theoden","images/Theoden.jpg"}},
 {character::Eomer, {"Eomer","images/Eomer.jpg"}},
 {character::Aragorn, {"Aragorn","images/Aragorn.jpg"}},
 {character::Saruman, {"Saruman","images/Saruman.jpg"}},
 {character::Sauron, {"Sauron","images/Sauron.jpg"}},
 {character::DurinsBane, {"Balrog/Durin's Bane","images/Balrog.jpg"}},
 {character::Radagast, {"Radagast","images/Radagast.jpg"}},
 {character::Manwe, {"Manwe","images/Manwe.jpg"}},
 {character::Aule, {"Aule","images/Aule.jpg"}},
 {character::Ulmo, {"Ulmo","images/Ulmo.jpg"}},
 {character::Melkor, {"Melkor/Morgoth","images/Melkor.jpg"}},
 {character::Varda, {"Varda","images/Varda.jpg"}},
  {character::Balin, {"Balin","images/Balin.jpg"}},
 {character::Thorin, {"Thorin Oeakenshield","images/Thorin.jpg"}}});










#endif // DATABASE_H

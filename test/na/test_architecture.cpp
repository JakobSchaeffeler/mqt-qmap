//
// This file is part of the MQT QMAP library released under the MIT license.
// See README.md or go to https://github.com/cda-tum/qmap for more information.
//

#include "Architecture.hpp"
#include "operations/OpType.hpp"

#include "gtest/gtest.h"
#include <fstream>
#include <random>
#include <sstream>
#include <string>

constexpr const char* ARCH_FN = "arch.json";
constexpr const char* GRID_FN = "grid.csv";

class TestNAArchitecture : public testing::Test {
protected:
  void SetUp() override {
    // write content to a file
    std::ofstream archF(ARCH_FN);
    archF << "{\n"
             "    \"name\": \"Nature\",\n"
             "    \"initialZones\": [\n"
             "        \"storage\"\n"
             "    ],\n"
             "    \"zones\": [\n"
             "        {\n"
             "            \"name\": \"entangling\",\n"
             "            \"xmin\": -300,\n"
             "            \"xmax\": 656,\n"
             "            \"ymin\": -10,\n"
             "            \"ymax\": 46,\n"
             "            \"fidelity\": 0.9959\n"
             "        },\n"
             "        {\n"
             "            \"name\": \"storage\",\n"
             "            \"xmin\": -300,\n"
             "            \"xmax\": 656,\n"
             "            \"ymin\": 47,\n"
             "            \"ymax\": 121,\n"
             "            \"fidelity\": 1\n"
             "        },\n"
             "        {\n"
             "            \"name\": \"readout\",\n"
             "            \"xmin\": -300,\n"
             "            \"xmax\": 656,\n"
             "            \"ymin\": 122,\n"
             "            \"ymax\": 156,\n"
             "            \"fidelity\": 0.99\n"
             "        }\n"
             "    ],\n"
             "    \"operations\": [\n"
             "        {\n"
             "            \"name\": \"rz\",\n"
             "            \"type\": \"local\",\n"
             "            \"zones\": [\n"
             "                \"entangling\",\n"
             "                \"storage\",\n"
             "                \"readout\"\n"
             "            ],\n"
             "            \"time\": 0.5,\n"
             "            \"fidelity\": 0.999\n"
             "        },\n"
             "        {\n"
             "            \"name\": \"ry\",\n"
             "            \"type\": \"global\",\n"
             "            \"zones\": [\n"
             "                \"entangling\",\n"
             "                \"storage\",\n"
             "                \"readout\"\n"
             "            ],\n"
             "            \"time\": 0.5,\n"
             "            \"fidelity\": 0.999\n"
             "        },\n"
             "        {\n"
             "            \"name\": \"cz\",\n"
             "            \"type\": \"global\",\n"
             "            \"zones\": [\n"
             "                \"entangling\"\n"
             "            ],\n"
             "            \"time\": 0.2,\n"
             "            \"fidelity\": 0.9959\n"
             "        },\n"
             "        {\n"
             "            \"name\": \"measure\",\n"
             "            \"type\": \"global\",\n"
             "            \"zones\": [\n"
             "                \"readout\"\n"
             "            ],\n"
             "            \"time\": 0.2,\n"
             "            \"fidelity\": 0.95\n"
             "        }\n"
             "    ],\n"
             "    \"decoherence\": {\n"
             "        \"t1\": 100000000,\n"
             "        \"t2\": 1500000\n"
             "    },\n"
             "    \"interactionRadius\": 2,\n"
             "    \"noInteractionRadius\": 5,\n"
             "    \"minAtomDistance\": 1,\n"
             "    \"shuttling\": [\n"
             "        {\n"
             "            \"rows\": 5,\n"
             "            \"columns\": 5,\n"
             "            \"xmin\": -2.5,\n"
             "            \"xmax\": 2.5,\n"
             "            \"ymin\": -2.5,\n"
             "            \"ymax\": 2.5,\n"
             "            \"move\": {\n"
             "                \"speed\": 0.55,\n"
             "                \"fidelity\": 1\n"
             "            },\n"
             "            \"load\": {\n"
             "                \"time\": 20,\n"
             "                \"fidelity\": 1\n"
             "            },\n"
             "            \"store\": {\n"
             "                \"time\": 20,\n"
             "                \"fidelity\": 1\n"
             "            }\n"
             "        }\n"
             "    ]\n"
             "}\n";
    archF.close();
    std::ofstream gridF(GRID_FN);
    gridF << "x,y\n"
             "3,0\n"
             "13,0\n"
             "23,0\n"
             "33,0\n"
             "43,0\n"
             "53,0\n"
             "63,0\n"
             "73,0\n"
             "83,0\n"
             "93,0\n"
             "103,0\n"
             "113,0\n"
             "123,0\n"
             "133,0\n"
             "143,0\n"
             "153,0\n"
             "163,0\n"
             "173,0\n"
             "183,0\n"
             "193,0\n"
             "203,0\n"
             "213,0\n"
             "223,0\n"
             "233,0\n"
             "243,0\n"
             "253,0\n"
             "263,0\n"
             "273,0\n"
             "283,0\n"
             "293,0\n"
             "303,0\n"
             "313,0\n"
             "323,0\n"
             "333,0\n"
             "343,0\n"
             "353,0\n"
             "3,12\n"
             "13,12\n"
             "23,12\n"
             "33,12\n"
             "43,12\n"
             "53,12\n"
             "63,12\n"
             "73,12\n"
             "83,12\n"
             "93,12\n"
             "103,12\n"
             "113,12\n"
             "123,12\n"
             "133,12\n"
             "143,12\n"
             "153,12\n"
             "163,12\n"
             "173,12\n"
             "183,12\n"
             "193,12\n"
             "203,12\n"
             "213,12\n"
             "223,12\n"
             "233,12\n"
             "243,12\n"
             "253,12\n"
             "263,12\n"
             "273,12\n"
             "283,12\n"
             "293,12\n"
             "303,12\n"
             "313,12\n"
             "323,12\n"
             "333,12\n"
             "343,12\n"
             "353,12\n"
             "3,24\n"
             "13,24\n"
             "23,24\n"
             "33,24\n"
             "43,24\n"
             "53,24\n"
             "63,24\n"
             "73,24\n"
             "83,24\n"
             "93,24\n"
             "103,24\n"
             "113,24\n"
             "123,24\n"
             "133,24\n"
             "143,24\n"
             "153,24\n"
             "163,24\n"
             "173,24\n"
             "183,24\n"
             "193,24\n"
             "203,24\n"
             "213,24\n"
             "223,24\n"
             "233,24\n"
             "243,24\n"
             "253,24\n"
             "263,24\n"
             "273,24\n"
             "283,24\n"
             "293,24\n"
             "303,24\n"
             "313,24\n"
             "323,24\n"
             "333,24\n"
             "343,24\n"
             "353,24\n"
             "3,36\n"
             "13,36\n"
             "23,36\n"
             "33,36\n"
             "43,36\n"
             "53,36\n"
             "63,36\n"
             "73,36\n"
             "83,36\n"
             "93,36\n"
             "103,36\n"
             "113,36\n"
             "123,36\n"
             "133,36\n"
             "143,36\n"
             "153,36\n"
             "163,36\n"
             "173,36\n"
             "183,36\n"
             "193,36\n"
             "203,36\n"
             "213,36\n"
             "223,36\n"
             "233,36\n"
             "243,36\n"
             "253,36\n"
             "263,36\n"
             "273,36\n"
             "283,36\n"
             "293,36\n"
             "303,36\n"
             "313,36\n"
             "323,36\n"
             "333,36\n"
             "343,36\n"
             "353,36\n"
             "0,56\n"
             "5,56\n"
             "10,56\n"
             "15,56\n"
             "20,56\n"
             "25,56\n"
             "30,56\n"
             "35,56\n"
             "40,56\n"
             "45,56\n"
             "50,56\n"
             "55,56\n"
             "60,56\n"
             "65,56\n"
             "70,56\n"
             "75,56\n"
             "80,56\n"
             "85,56\n"
             "90,56\n"
             "95,56\n"
             "100,56\n"
             "105,56\n"
             "110,56\n"
             "115,56\n"
             "120,56\n"
             "125,56\n"
             "130,56\n"
             "135,56\n"
             "140,56\n"
             "145,56\n"
             "150,56\n"
             "155,56\n"
             "160,56\n"
             "165,56\n"
             "170,56\n"
             "175,56\n"
             "180,56\n"
             "185,56\n"
             "190,56\n"
             "195,56\n"
             "200,56\n"
             "205,56\n"
             "210,56\n"
             "215,56\n"
             "220,56\n"
             "225,56\n"
             "230,56\n"
             "235,56\n"
             "240,56\n"
             "245,56\n"
             "250,56\n"
             "255,56\n"
             "260,56\n"
             "265,56\n"
             "270,56\n"
             "275,56\n"
             "280,56\n"
             "285,56\n"
             "290,56\n"
             "295,56\n"
             "300,56\n"
             "305,56\n"
             "310,56\n"
             "315,56\n"
             "320,56\n"
             "325,56\n"
             "330,56\n"
             "335,56\n"
             "340,56\n"
             "345,56\n"
             "350,56\n"
             "355,56\n"
             "0,61\n"
             "5,61\n"
             "10,61\n"
             "15,61\n"
             "20,61\n"
             "25,61\n"
             "30,61\n"
             "35,61\n"
             "40,61\n"
             "45,61\n"
             "50,61\n"
             "55,61\n"
             "60,61\n"
             "65,61\n"
             "70,61\n"
             "75,61\n"
             "80,61\n"
             "85,61\n"
             "90,61\n"
             "95,61\n"
             "100,61\n"
             "105,61\n"
             "110,61\n"
             "115,61\n"
             "120,61\n"
             "125,61\n"
             "130,61\n"
             "135,61\n"
             "140,61\n"
             "145,61\n"
             "150,61\n"
             "155,61\n"
             "160,61\n"
             "165,61\n"
             "170,61\n"
             "175,61\n"
             "180,61\n"
             "185,61\n"
             "190,61\n"
             "195,61\n"
             "200,61\n"
             "205,61\n"
             "210,61\n"
             "215,61\n"
             "220,61\n"
             "225,61\n"
             "230,61\n"
             "235,61\n"
             "240,61\n"
             "245,61\n"
             "250,61\n"
             "255,61\n"
             "260,61\n"
             "265,61\n"
             "270,61\n"
             "275,61\n"
             "280,61\n"
             "285,61\n"
             "290,61\n"
             "295,61\n"
             "300,61\n"
             "305,61\n"
             "310,61\n"
             "315,61\n"
             "320,61\n"
             "325,61\n"
             "330,61\n"
             "335,61\n"
             "340,61\n"
             "345,61\n"
             "350,61\n"
             "355,61\n"
             "0,66\n"
             "5,66\n"
             "10,66\n"
             "15,66\n"
             "20,66\n"
             "25,66\n"
             "30,66\n"
             "35,66\n"
             "40,66\n"
             "45,66\n"
             "50,66\n"
             "55,66\n"
             "60,66\n"
             "65,66\n"
             "70,66\n"
             "75,66\n"
             "80,66\n"
             "85,66\n"
             "90,66\n"
             "95,66\n"
             "100,66\n"
             "105,66\n"
             "110,66\n"
             "115,66\n"
             "120,66\n"
             "125,66\n"
             "130,66\n"
             "135,66\n"
             "140,66\n"
             "145,66\n"
             "150,66\n"
             "155,66\n"
             "160,66\n"
             "165,66\n"
             "170,66\n"
             "175,66\n"
             "180,66\n"
             "185,66\n"
             "190,66\n"
             "195,66\n"
             "200,66\n"
             "205,66\n"
             "210,66\n"
             "215,66\n"
             "220,66\n"
             "225,66\n"
             "230,66\n"
             "235,66\n"
             "240,66\n"
             "245,66\n"
             "250,66\n"
             "255,66\n"
             "260,66\n"
             "265,66\n"
             "270,66\n"
             "275,66\n"
             "280,66\n"
             "285,66\n"
             "290,66\n"
             "295,66\n"
             "300,66\n"
             "305,66\n"
             "310,66\n"
             "315,66\n"
             "320,66\n"
             "325,66\n"
             "330,66\n"
             "335,66\n"
             "340,66\n"
             "345,66\n"
             "350,66\n"
             "355,66\n"
             "0,71\n"
             "5,71\n"
             "10,71\n"
             "15,71\n"
             "20,71\n"
             "25,71\n"
             "30,71\n"
             "35,71\n"
             "40,71\n"
             "45,71\n"
             "50,71\n"
             "55,71\n"
             "60,71\n"
             "65,71\n"
             "70,71\n"
             "75,71\n"
             "80,71\n"
             "85,71\n"
             "90,71\n"
             "95,71\n"
             "100,71\n"
             "105,71\n"
             "110,71\n"
             "115,71\n"
             "120,71\n"
             "125,71\n"
             "130,71\n"
             "135,71\n"
             "140,71\n"
             "145,71\n"
             "150,71\n"
             "155,71\n"
             "160,71\n"
             "165,71\n"
             "170,71\n"
             "175,71\n"
             "180,71\n"
             "185,71\n"
             "190,71\n"
             "195,71\n"
             "200,71\n"
             "205,71\n"
             "210,71\n"
             "215,71\n"
             "220,71\n"
             "225,71\n"
             "230,71\n"
             "235,71\n"
             "240,71\n"
             "245,71\n"
             "250,71\n"
             "255,71\n"
             "260,71\n"
             "265,71\n"
             "270,71\n"
             "275,71\n"
             "280,71\n"
             "285,71\n"
             "290,71\n"
             "295,71\n"
             "300,71\n"
             "305,71\n"
             "310,71\n"
             "315,71\n"
             "320,71\n"
             "325,71\n"
             "330,71\n"
             "335,71\n"
             "340,71\n"
             "345,71\n"
             "350,71\n"
             "355,71\n"
             "0,76\n"
             "5,76\n"
             "10,76\n"
             "15,76\n"
             "20,76\n"
             "25,76\n"
             "30,76\n"
             "35,76\n"
             "40,76\n"
             "45,76\n"
             "50,76\n"
             "55,76\n"
             "60,76\n"
             "65,76\n"
             "70,76\n"
             "75,76\n"
             "80,76\n"
             "85,76\n"
             "90,76\n"
             "95,76\n"
             "100,76\n"
             "105,76\n"
             "110,76\n"
             "115,76\n"
             "120,76\n"
             "125,76\n"
             "130,76\n"
             "135,76\n"
             "140,76\n"
             "145,76\n"
             "150,76\n"
             "155,76\n"
             "160,76\n"
             "165,76\n"
             "170,76\n"
             "175,76\n"
             "180,76\n"
             "185,76\n"
             "190,76\n"
             "195,76\n"
             "200,76\n"
             "205,76\n"
             "210,76\n"
             "215,76\n"
             "220,76\n"
             "225,76\n"
             "230,76\n"
             "235,76\n"
             "240,76\n"
             "245,76\n"
             "250,76\n"
             "255,76\n"
             "260,76\n"
             "265,76\n"
             "270,76\n"
             "275,76\n"
             "280,76\n"
             "285,76\n"
             "290,76\n"
             "295,76\n"
             "300,76\n"
             "305,76\n"
             "310,76\n"
             "315,76\n"
             "320,76\n"
             "325,76\n"
             "330,76\n"
             "335,76\n"
             "340,76\n"
             "345,76\n"
             "350,76\n"
             "355,76\n"
             "0,81\n"
             "5,81\n"
             "10,81\n"
             "15,81\n"
             "20,81\n"
             "25,81\n"
             "30,81\n"
             "35,81\n"
             "40,81\n"
             "45,81\n"
             "50,81\n"
             "55,81\n"
             "60,81\n"
             "65,81\n"
             "70,81\n"
             "75,81\n"
             "80,81\n"
             "85,81\n"
             "90,81\n"
             "95,81\n"
             "100,81\n"
             "105,81\n"
             "110,81\n"
             "115,81\n"
             "120,81\n"
             "125,81\n"
             "130,81\n"
             "135,81\n"
             "140,81\n"
             "145,81\n"
             "150,81\n"
             "155,81\n"
             "160,81\n"
             "165,81\n"
             "170,81\n"
             "175,81\n"
             "180,81\n"
             "185,81\n"
             "190,81\n"
             "195,81\n"
             "200,81\n"
             "205,81\n"
             "210,81\n"
             "215,81\n"
             "220,81\n"
             "225,81\n"
             "230,81\n"
             "235,81\n"
             "240,81\n"
             "245,81\n"
             "250,81\n"
             "255,81\n"
             "260,81\n"
             "265,81\n"
             "270,81\n"
             "275,81\n"
             "280,81\n"
             "285,81\n"
             "290,81\n"
             "295,81\n"
             "300,81\n"
             "305,81\n"
             "310,81\n"
             "315,81\n"
             "320,81\n"
             "325,81\n"
             "330,81\n"
             "335,81\n"
             "340,81\n"
             "345,81\n"
             "350,81\n"
             "355,81\n"
             "0,86\n"
             "5,86\n"
             "10,86\n"
             "15,86\n"
             "20,86\n"
             "25,86\n"
             "30,86\n"
             "35,86\n"
             "40,86\n"
             "45,86\n"
             "50,86\n"
             "55,86\n"
             "60,86\n"
             "65,86\n"
             "70,86\n"
             "75,86\n"
             "80,86\n"
             "85,86\n"
             "90,86\n"
             "95,86\n"
             "100,86\n"
             "105,86\n"
             "110,86\n"
             "115,86\n"
             "120,86\n"
             "125,86\n"
             "130,86\n"
             "135,86\n"
             "140,86\n"
             "145,86\n"
             "150,86\n"
             "155,86\n"
             "160,86\n"
             "165,86\n"
             "170,86\n"
             "175,86\n"
             "180,86\n"
             "185,86\n"
             "190,86\n"
             "195,86\n"
             "200,86\n"
             "205,86\n"
             "210,86\n"
             "215,86\n"
             "220,86\n"
             "225,86\n"
             "230,86\n"
             "235,86\n"
             "240,86\n"
             "245,86\n"
             "250,86\n"
             "255,86\n"
             "260,86\n"
             "265,86\n"
             "270,86\n"
             "275,86\n"
             "280,86\n"
             "285,86\n"
             "290,86\n"
             "295,86\n"
             "300,86\n"
             "305,86\n"
             "310,86\n"
             "315,86\n"
             "320,86\n"
             "325,86\n"
             "330,86\n"
             "335,86\n"
             "340,86\n"
             "345,86\n"
             "350,86\n"
             "355,86\n"
             "0,91\n"
             "5,91\n"
             "10,91\n"
             "15,91\n"
             "20,91\n"
             "25,91\n"
             "30,91\n"
             "35,91\n"
             "40,91\n"
             "45,91\n"
             "50,91\n"
             "55,91\n"
             "60,91\n"
             "65,91\n"
             "70,91\n"
             "75,91\n"
             "80,91\n"
             "85,91\n"
             "90,91\n"
             "95,91\n"
             "100,91\n"
             "105,91\n"
             "110,91\n"
             "115,91\n"
             "120,91\n"
             "125,91\n"
             "130,91\n"
             "135,91\n"
             "140,91\n"
             "145,91\n"
             "150,91\n"
             "155,91\n"
             "160,91\n"
             "165,91\n"
             "170,91\n"
             "175,91\n"
             "180,91\n"
             "185,91\n"
             "190,91\n"
             "195,91\n"
             "200,91\n"
             "205,91\n"
             "210,91\n"
             "215,91\n"
             "220,91\n"
             "225,91\n"
             "230,91\n"
             "235,91\n"
             "240,91\n"
             "245,91\n"
             "250,91\n"
             "255,91\n"
             "260,91\n"
             "265,91\n"
             "270,91\n"
             "275,91\n"
             "280,91\n"
             "285,91\n"
             "290,91\n"
             "295,91\n"
             "300,91\n"
             "305,91\n"
             "310,91\n"
             "315,91\n"
             "320,91\n"
             "325,91\n"
             "330,91\n"
             "335,91\n"
             "340,91\n"
             "345,91\n"
             "350,91\n"
             "355,91\n"
             "0,96\n"
             "5,96\n"
             "10,96\n"
             "15,96\n"
             "20,96\n"
             "25,96\n"
             "30,96\n"
             "35,96\n"
             "40,96\n"
             "45,96\n"
             "50,96\n"
             "55,96\n"
             "60,96\n"
             "65,96\n"
             "70,96\n"
             "75,96\n"
             "80,96\n"
             "85,96\n"
             "90,96\n"
             "95,96\n"
             "100,96\n"
             "105,96\n"
             "110,96\n"
             "115,96\n"
             "120,96\n"
             "125,96\n"
             "130,96\n"
             "135,96\n"
             "140,96\n"
             "145,96\n"
             "150,96\n"
             "155,96\n"
             "160,96\n"
             "165,96\n"
             "170,96\n"
             "175,96\n"
             "180,96\n"
             "185,96\n"
             "190,96\n"
             "195,96\n"
             "200,96\n"
             "205,96\n"
             "210,96\n"
             "215,96\n"
             "220,96\n"
             "225,96\n"
             "230,96\n"
             "235,96\n"
             "240,96\n"
             "245,96\n"
             "250,96\n"
             "255,96\n"
             "260,96\n"
             "265,96\n"
             "270,96\n"
             "275,96\n"
             "280,96\n"
             "285,96\n"
             "290,96\n"
             "295,96\n"
             "300,96\n"
             "305,96\n"
             "310,96\n"
             "315,96\n"
             "320,96\n"
             "325,96\n"
             "330,96\n"
             "335,96\n"
             "340,96\n"
             "345,96\n"
             "350,96\n"
             "355,96\n"
             "0,101\n"
             "5,101\n"
             "10,101\n"
             "15,101\n"
             "20,101\n"
             "25,101\n"
             "30,101\n"
             "35,101\n"
             "40,101\n"
             "45,101\n"
             "50,101\n"
             "55,101\n"
             "60,101\n"
             "65,101\n"
             "70,101\n"
             "75,101\n"
             "80,101\n"
             "85,101\n"
             "90,101\n"
             "95,101\n"
             "100,101\n"
             "105,101\n"
             "110,101\n"
             "115,101\n"
             "120,101\n"
             "125,101\n"
             "130,101\n"
             "135,101\n"
             "140,101\n"
             "145,101\n"
             "150,101\n"
             "155,101\n"
             "160,101\n"
             "165,101\n"
             "170,101\n"
             "175,101\n"
             "180,101\n"
             "185,101\n"
             "190,101\n"
             "195,101\n"
             "200,101\n"
             "205,101\n"
             "210,101\n"
             "215,101\n"
             "220,101\n"
             "225,101\n"
             "230,101\n"
             "235,101\n"
             "240,101\n"
             "245,101\n"
             "250,101\n"
             "255,101\n"
             "260,101\n"
             "265,101\n"
             "270,101\n"
             "275,101\n"
             "280,101\n"
             "285,101\n"
             "290,101\n"
             "295,101\n"
             "300,101\n"
             "305,101\n"
             "310,101\n"
             "315,101\n"
             "320,101\n"
             "325,101\n"
             "330,101\n"
             "335,101\n"
             "340,101\n"
             "345,101\n"
             "350,101\n"
             "355,101\n"
             "0,106\n"
             "5,106\n"
             "10,106\n"
             "15,106\n"
             "20,106\n"
             "25,106\n"
             "30,106\n"
             "35,106\n"
             "40,106\n"
             "45,106\n"
             "50,106\n"
             "55,106\n"
             "60,106\n"
             "65,106\n"
             "70,106\n"
             "75,106\n"
             "80,106\n"
             "85,106\n"
             "90,106\n"
             "95,106\n"
             "100,106\n"
             "105,106\n"
             "110,106\n"
             "115,106\n"
             "120,106\n"
             "125,106\n"
             "130,106\n"
             "135,106\n"
             "140,106\n"
             "145,106\n"
             "150,106\n"
             "155,106\n"
             "160,106\n"
             "165,106\n"
             "170,106\n"
             "175,106\n"
             "180,106\n"
             "185,106\n"
             "190,106\n"
             "195,106\n"
             "200,106\n"
             "205,106\n"
             "210,106\n"
             "215,106\n"
             "220,106\n"
             "225,106\n"
             "230,106\n"
             "235,106\n"
             "240,106\n"
             "245,106\n"
             "250,106\n"
             "255,106\n"
             "260,106\n"
             "265,106\n"
             "270,106\n"
             "275,106\n"
             "280,106\n"
             "285,106\n"
             "290,106\n"
             "295,106\n"
             "300,106\n"
             "305,106\n"
             "310,106\n"
             "315,106\n"
             "320,106\n"
             "325,106\n"
             "330,106\n"
             "335,106\n"
             "340,106\n"
             "345,106\n"
             "350,106\n"
             "355,106\n"
             "0,111\n"
             "5,111\n"
             "10,111\n"
             "15,111\n"
             "20,111\n"
             "25,111\n"
             "30,111\n"
             "35,111\n"
             "40,111\n"
             "45,111\n"
             "50,111\n"
             "55,111\n"
             "60,111\n"
             "65,111\n"
             "70,111\n"
             "75,111\n"
             "80,111\n"
             "85,111\n"
             "90,111\n"
             "95,111\n"
             "100,111\n"
             "105,111\n"
             "110,111\n"
             "115,111\n"
             "120,111\n"
             "125,111\n"
             "130,111\n"
             "135,111\n"
             "140,111\n"
             "145,111\n"
             "150,111\n"
             "155,111\n"
             "160,111\n"
             "165,111\n"
             "170,111\n"
             "175,111\n"
             "180,111\n"
             "185,111\n"
             "190,111\n"
             "195,111\n"
             "200,111\n"
             "205,111\n"
             "210,111\n"
             "215,111\n"
             "220,111\n"
             "225,111\n"
             "230,111\n"
             "235,111\n"
             "240,111\n"
             "245,111\n"
             "250,111\n"
             "255,111\n"
             "260,111\n"
             "265,111\n"
             "270,111\n"
             "275,111\n"
             "280,111\n"
             "285,111\n"
             "290,111\n"
             "295,111\n"
             "300,111\n"
             "305,111\n"
             "310,111\n"
             "315,111\n"
             "320,111\n"
             "325,111\n"
             "330,111\n"
             "335,111\n"
             "340,111\n"
             "345,111\n"
             "350,111\n"
             "355,111\n"
             "0,131\n"
             "5,131\n"
             "10,131\n"
             "15,131\n"
             "20,131\n"
             "25,131\n"
             "30,131\n"
             "35,131\n"
             "40,131\n"
             "45,131\n"
             "50,131\n"
             "55,131\n"
             "60,131\n"
             "65,131\n"
             "70,131\n"
             "75,131\n"
             "80,131\n"
             "85,131\n"
             "90,131\n"
             "95,131\n"
             "100,131\n"
             "105,131\n"
             "110,131\n"
             "115,131\n"
             "120,131\n"
             "125,131\n"
             "130,131\n"
             "135,131\n"
             "140,131\n"
             "145,131\n"
             "150,131\n"
             "155,131\n"
             "160,131\n"
             "165,131\n"
             "170,131\n"
             "175,131\n"
             "180,131\n"
             "185,131\n"
             "190,131\n"
             "195,131\n"
             "200,131\n"
             "205,131\n"
             "210,131\n"
             "215,131\n"
             "220,131\n"
             "225,131\n"
             "230,131\n"
             "235,131\n"
             "240,131\n"
             "245,131\n"
             "250,131\n"
             "255,131\n"
             "260,131\n"
             "265,131\n"
             "270,131\n"
             "275,131\n"
             "280,131\n"
             "285,131\n"
             "290,131\n"
             "295,131\n"
             "300,131\n"
             "305,131\n"
             "310,131\n"
             "315,131\n"
             "320,131\n"
             "325,131\n"
             "330,131\n"
             "335,131\n"
             "340,131\n"
             "345,131\n"
             "350,131\n"
             "355,131\n"
             "0,136\n"
             "5,136\n"
             "10,136\n"
             "15,136\n"
             "20,136\n"
             "25,136\n"
             "30,136\n"
             "35,136\n"
             "40,136\n"
             "45,136\n"
             "50,136\n"
             "55,136\n"
             "60,136\n"
             "65,136\n"
             "70,136\n"
             "75,136\n"
             "80,136\n"
             "85,136\n"
             "90,136\n"
             "95,136\n"
             "100,136\n"
             "105,136\n"
             "110,136\n"
             "115,136\n"
             "120,136\n"
             "125,136\n"
             "130,136\n"
             "135,136\n"
             "140,136\n"
             "145,136\n"
             "150,136\n"
             "155,136\n"
             "160,136\n"
             "165,136\n"
             "170,136\n"
             "175,136\n"
             "180,136\n"
             "185,136\n"
             "190,136\n"
             "195,136\n"
             "200,136\n"
             "205,136\n"
             "210,136\n"
             "215,136\n"
             "220,136\n"
             "225,136\n"
             "230,136\n"
             "235,136\n"
             "240,136\n"
             "245,136\n"
             "250,136\n"
             "255,136\n"
             "260,136\n"
             "265,136\n"
             "270,136\n"
             "275,136\n"
             "280,136\n"
             "285,136\n"
             "290,136\n"
             "295,136\n"
             "300,136\n"
             "305,136\n"
             "310,136\n"
             "315,136\n"
             "320,136\n"
             "325,136\n"
             "330,136\n"
             "335,136\n"
             "340,136\n"
             "345,136\n"
             "350,136\n"
             "355,136\n"
             "0,141\n"
             "5,141\n"
             "10,141\n"
             "15,141\n"
             "20,141\n"
             "25,141\n"
             "30,141\n"
             "35,141\n"
             "40,141\n"
             "45,141\n"
             "50,141\n"
             "55,141\n"
             "60,141\n"
             "65,141\n"
             "70,141\n"
             "75,141\n"
             "80,141\n"
             "85,141\n"
             "90,141\n"
             "95,141\n"
             "100,141\n"
             "105,141\n"
             "110,141\n"
             "115,141\n"
             "120,141\n"
             "125,141\n"
             "130,141\n"
             "135,141\n"
             "140,141\n"
             "145,141\n"
             "150,141\n"
             "155,141\n"
             "160,141\n"
             "165,141\n"
             "170,141\n"
             "175,141\n"
             "180,141\n"
             "185,141\n"
             "190,141\n"
             "195,141\n"
             "200,141\n"
             "205,141\n"
             "210,141\n"
             "215,141\n"
             "220,141\n"
             "225,141\n"
             "230,141\n"
             "235,141\n"
             "240,141\n"
             "245,141\n"
             "250,141\n"
             "255,141\n"
             "260,141\n"
             "265,141\n"
             "270,141\n"
             "275,141\n"
             "280,141\n"
             "285,141\n"
             "290,141\n"
             "295,141\n"
             "300,141\n"
             "305,141\n"
             "310,141\n"
             "315,141\n"
             "320,141\n"
             "325,141\n"
             "330,141\n"
             "335,141\n"
             "340,141\n"
             "345,141\n"
             "350,141\n"
             "355,141\n"
             "0,146\n"
             "5,146\n"
             "10,146\n"
             "15,146\n"
             "20,146\n"
             "25,146\n"
             "30,146\n"
             "35,146\n"
             "40,146\n"
             "45,146\n"
             "50,146\n"
             "55,146\n"
             "60,146\n"
             "65,146\n"
             "70,146\n"
             "75,146\n"
             "80,146\n"
             "85,146\n"
             "90,146\n"
             "95,146\n"
             "100,146\n"
             "105,146\n"
             "110,146\n"
             "115,146\n"
             "120,146\n"
             "125,146\n"
             "130,146\n"
             "135,146\n"
             "140,146\n"
             "145,146\n"
             "150,146\n"
             "155,146\n"
             "160,146\n"
             "165,146\n"
             "170,146\n"
             "175,146\n"
             "180,146\n"
             "185,146\n"
             "190,146\n"
             "195,146\n"
             "200,146\n"
             "205,146\n"
             "210,146\n"
             "215,146\n"
             "220,146\n"
             "225,146\n"
             "230,146\n"
             "235,146\n"
             "240,146\n"
             "245,146\n"
             "250,146\n"
             "255,146\n"
             "260,146\n"
             "265,146\n"
             "270,146\n"
             "275,146\n"
             "280,146\n"
             "285,146\n"
             "290,146\n"
             "295,146\n"
             "300,146\n"
             "305,146\n"
             "310,146\n"
             "315,146\n"
             "320,146\n"
             "325,146\n"
             "330,146\n"
             "335,146\n"
             "340,146\n"
             "345,146\n"
             "350,146\n"
             "355,146\n";
    gridF.close();
  }
  void TearDown() override {
    std::remove(ARCH_FN);
    std::remove(GRID_FN);
  }
};

TEST_F(TestNAArchitecture, Import) {
  na::Architecture const arch(ARCH_FN, GRID_FN);

  EXPECT_EQ(arch.getNZones(), 3);
  EXPECT_EQ(arch.getNSites(), 360);
  EXPECT_EQ(arch.getName(), "Nature");
  EXPECT_EQ(arch.getZoneLabel(arch.getZoneOfSite(0)), "entangling");
}

TEST_F(TestNAArchitecture, GateApplicability) {
  na::Architecture const arch(ARCH_FN, GRID_FN);

  EXPECT_TRUE(arch.isAllowedGlobally({qc::OpType::RY, 0}, 1));
  EXPECT_TRUE(arch.isAllowedGlobally({qc::OpType::Z, 1}, 0));
  EXPECT_TRUE(arch.isAllowedLocally({qc::OpType::RZ, 0}, 1));
}

TEST_F(TestNAArchitecture, WithConfiguration) {
  na::Architecture const  arch(ARCH_FN, GRID_FN);
  na::Configuration const config(2, 3);
  const auto              modArch = arch.withConfig(config);
  EXPECT_EQ(modArch.getNSites(), 54);
}

TEST_F(TestNAArchitecture, SiteUp) {
  const na::Architecture arch(ARCH_FN, GRID_FN);
  EXPECT_TRUE(arch.hasSiteUp({3, 3}, false, true));
  EXPECT_FALSE(arch.hasSiteUp({3, 0}, true, true));
  EXPECT_EQ(arch.getPositionOfSite(arch.getNearestSiteUp({3, 3}, true, true)),
            (na::Point{3, 0}));
  EXPECT_ANY_THROW(std::ignore = arch.getNearestSiteUp({3, 0}, true, true));
}

TEST_F(TestNAArchitecture, SiteDown) {
  const na::Architecture arch(ARCH_FN, GRID_FN);
  EXPECT_FALSE(arch.hasSiteDown({0, 3}, false, true));
  EXPECT_TRUE(arch.hasSiteDown({3, 0}, true, true));
  EXPECT_ANY_THROW(std::ignore = arch.getNearestSiteDown({0, 3}, false, true));
  EXPECT_EQ(arch.getPositionOfSite(arch.getNearestSiteDown({3, 0}, true, true)),
            (na::Point{3, 12}));
}

TEST_F(TestNAArchitecture, SiteLeft) {
  const na::Architecture arch(ARCH_FN, GRID_FN);
  EXPECT_TRUE(arch.hasSiteLeft({3, 0}, false, true));
  EXPECT_FALSE(arch.hasSiteLeft({3, 0}, true, true));
  EXPECT_EQ(arch.getPositionOfSite(arch.getNearestSiteLeft({3, 0}, false, true)),
            (na::Point{3, 0}));
  EXPECT_ANY_THROW(std::ignore = arch.getNearestSiteLeft({3, 0}, true, true));
}

TEST_F(TestNAArchitecture, SiteRight) {
  const na::Architecture arch(ARCH_FN, GRID_FN);
  EXPECT_TRUE(arch.hasSiteRight({3, 0}, false, true));
  EXPECT_FALSE(arch.hasSiteRight({3, 3}, true, true));
  EXPECT_EQ(
      arch.getPositionOfSite(arch.getNearestSiteRight({3, 0}, true, true)),
      (na::Point{13, 0}));
  EXPECT_ANY_THROW(std::ignore = arch.getNearestSiteRight({3, 3}, true, true));
}
// gameboard.cpp
// implementation for gameboard.h file
#include "gameboard.h"

Gameboard::Gameboard(){

}

Gameboard::Gameboard(bool fromNewGame)
{
    setHexLayer();
    setVertLayer();
    setEdgeLayer();
    int i;
    for(i=0;i<3;i++)
        unassTerrain.push_back(HILLS);
    for(i=0;i<4;i++)
        unassTerrain.push_back(FIELD);
    for(i=0;i<4;i++)
        unassTerrain.push_back(FOREST);
    for(i=0;i<3;i++)
        unassTerrain.push_back(MOUNTAINS);
    for(i=0;i<4;i++)
        unassTerrain.push_back(PASTURE);
    unassTerrain.push_back(DESERT);
    for (int i=0;i<6;i++){
            if (i==5){
                for (int j=0;j<4;j++){
                    unassPorts.push_back(i);}
            }
            else
                unassPorts.push_back(i);
    }

    if(fromNewGame){
        assTerrain();
        setBandit();
    }

        setYield();
        setPorts();
}

HEXAGON::HEXAGON(int hexNum){
    hexId=hexNum;
    hasBandit=false;
    if (hexNum == 0){
        assVert.push_back(0);
        assVert.push_back(1);
        assVert.push_back(2);
        assVert.push_back(10);
        assVert.push_back(9);
        assVert.push_back(8);
    }
    else if (hexNum == 1){
        assVert.push_back(2);
        assVert.push_back(3);
        assVert.push_back(4);
        assVert.push_back(12);
        assVert.push_back(11);
        assVert.push_back(10);
    }
    else if (hexNum == 2){
        assVert.push_back(4);
        assVert.push_back(5);
        assVert.push_back(6);
        assVert.push_back(14);
        assVert.push_back(13);
        assVert.push_back(12);
    }
    else if (hexNum == 3){
        assVert.push_back(7);
        assVert.push_back(8);
        assVert.push_back(9);
        assVert.push_back(19);
        assVert.push_back(18);
        assVert.push_back(17);
    }
    else if (hexNum == 4){
        assVert.push_back(9);
        assVert.push_back(10);
        assVert.push_back(11);
        assVert.push_back(21);
        assVert.push_back(20);
        assVert.push_back(19);
    }
    else if (hexNum == 5){
        assVert.push_back(11);
        assVert.push_back(12);
        assVert.push_back(13);
        assVert.push_back(23);
        assVert.push_back(22);
        assVert.push_back(21);
    }
    else if (hexNum == 6){
        assVert.push_back(13);
        assVert.push_back(14);
        assVert.push_back(15);
        assVert.push_back(25);
        assVert.push_back(24);
        assVert.push_back(23);
    }
    else if (hexNum == 7){
        assVert.push_back(16);
        assVert.push_back(17);
        assVert.push_back(18);
        assVert.push_back(29);
        assVert.push_back(28);
        assVert.push_back(27);
    }
    else if (hexNum == 8){
        assVert.push_back(18);
        assVert.push_back(19);
        assVert.push_back(20);
        assVert.push_back(31);
        assVert.push_back(30);
        assVert.push_back(29);
    }
    else if (hexNum == 9){
        assVert.push_back(20);
        assVert.push_back(21);
        assVert.push_back(22);
        assVert.push_back(33);
        assVert.push_back(32);
        assVert.push_back(31);
    }
    else if (hexNum == 10){
        assVert.push_back(22);
        assVert.push_back(23);
        assVert.push_back(24);
        assVert.push_back(35);
        assVert.push_back(34);
        assVert.push_back(33);
    }
    else if (hexNum == 11){
        assVert.push_back(24);
        assVert.push_back(25);
        assVert.push_back(26);
        assVert.push_back(37);
        assVert.push_back(36);
        assVert.push_back(35);
    }
    else if (hexNum == 12){
        assVert.push_back(28);
        assVert.push_back(29);
        assVert.push_back(30);
        assVert.push_back(40);
        assVert.push_back(39);
        assVert.push_back(38);
    }
    else if (hexNum == 13){
        assVert.push_back(30);
        assVert.push_back(31);
        assVert.push_back(32);
        assVert.push_back(42);
        assVert.push_back(41);
        assVert.push_back(40);
    }
    else if (hexNum == 14){
        assVert.push_back(32);
        assVert.push_back(33);
        assVert.push_back(34);
        assVert.push_back(44);
        assVert.push_back(43);
        assVert.push_back(42);
    }
    else if (hexNum == 15){
        assVert.push_back(34);
        assVert.push_back(35);
        assVert.push_back(36);
        assVert.push_back(46);
        assVert.push_back(45);
        assVert.push_back(44);
    }
    else if (hexNum == 16){
        assVert.push_back(39);
        assVert.push_back(40);
        assVert.push_back(41);
        assVert.push_back(49);
        assVert.push_back(48);
        assVert.push_back(47);
    }
    else if (hexNum == 17){
        assVert.push_back(41);
        assVert.push_back(42);
        assVert.push_back(43);
        assVert.push_back(51);
        assVert.push_back(50);
        assVert.push_back(49);
    }
    else if (hexNum == 18){
        assVert.push_back(43);
        assVert.push_back(44);
        assVert.push_back(45);
        assVert.push_back(53);
        assVert.push_back(52);
        assVert.push_back(51);
    }
}

VERTEX::VERTEX(int vertNum) {
    vertId=vertNum;
    occupiedBy = NOONE;
    occByType=0;
    if(vertNum == 0){
        adjEdge.push_back(0);
        adjEdge.push_back(6);
    }
    else if(vertNum == 1){
        adjEdge.push_back(1);
        adjEdge.push_back(0);
    }
    else if(vertNum == 2){
        adjEdge.push_back(1);
        adjEdge.push_back(2);
        adjEdge.push_back(7);
    }
    else if(vertNum == 3){
        adjEdge.push_back(3);
        adjEdge.push_back(2);
    }
    else if(vertNum == 4){
        adjEdge.push_back(3);
        adjEdge.push_back(4);
        adjEdge.push_back(8);
    }
    else if(vertNum == 5){
        adjEdge.push_back(5);
        adjEdge.push_back(4);
    }
    else if(vertNum == 6){
        adjEdge.push_back(5);
        adjEdge.push_back(9);
    }
    else if(vertNum == 7){
        adjEdge.push_back(10);
        adjEdge.push_back(18);
    }
    else if(vertNum == 8){
        adjEdge.push_back(6);
        adjEdge.push_back(11);
        adjEdge.push_back(10);
    }
    else if(vertNum == 9){
        adjEdge.push_back(11);
        adjEdge.push_back(12);
        adjEdge.push_back(19);
    }
    else if(vertNum == 10){
        adjEdge.push_back(7);
        adjEdge.push_back(13);
        adjEdge.push_back(12);
    }
    else if(vertNum == 11){
        adjEdge.push_back(13);
        adjEdge.push_back(14);
        adjEdge.push_back(20);
    }
    else if(vertNum == 12){
        adjEdge.push_back(8);
        adjEdge.push_back(15);
        adjEdge.push_back(14);
    }
    else if(vertNum == 13){
        adjEdge.push_back(15);
        adjEdge.push_back(16);
        adjEdge.push_back(21);
    }
    else if(vertNum == 14){
        adjEdge.push_back(9);
        adjEdge.push_back(17);
        adjEdge.push_back(16);
    }
    else if(vertNum == 15){
        adjEdge.push_back(17);
        adjEdge.push_back(22);
    }
    else if(vertNum == 16){
        adjEdge.push_back(23);
        adjEdge.push_back(33);
    }
    else if(vertNum == 17){
        adjEdge.push_back(18);
        adjEdge.push_back(24);
        adjEdge.push_back(23);
    }
    else if(vertNum == 18){
        adjEdge.push_back(24);
        adjEdge.push_back(25);
        adjEdge.push_back(34);
    }
    else if(vertNum == 19){
        adjEdge.push_back(19);
        adjEdge.push_back(26);
        adjEdge.push_back(25);
    }
    else if(vertNum == 20){
        adjEdge.push_back(26);
        adjEdge.push_back(27);
        adjEdge.push_back(35);
    }
    else if(vertNum == 21){
        adjEdge.push_back(20);
        adjEdge.push_back(28);
        adjEdge.push_back(27);
    }
    else if(vertNum == 22){
        adjEdge.push_back(28);
        adjEdge.push_back(29);
        adjEdge.push_back(36);
    }
    else if(vertNum == 23){
        adjEdge.push_back(21);
        adjEdge.push_back(30);
        adjEdge.push_back(29);
    }
    else if(vertNum == 24){
        adjEdge.push_back(30);
        adjEdge.push_back(31);
        adjEdge.push_back(37);
    }
    else if(vertNum == 25){
        adjEdge.push_back(22);
        adjEdge.push_back(32);
        adjEdge.push_back(31);
    }
    else if(vertNum == 26){
        adjEdge.push_back(32);
        adjEdge.push_back(38);
    }
    else if(vertNum == 27){
        adjEdge.push_back(33);
        adjEdge.push_back(39);
    }
    else if(vertNum == 28){
        adjEdge.push_back(39);
        adjEdge.push_back(40);
        adjEdge.push_back(49);
    }
    else if(vertNum == 29){
        adjEdge.push_back(34);
        adjEdge.push_back(41);
        adjEdge.push_back(40);
    }
    else if(vertNum == 30){
        adjEdge.push_back(41);
        adjEdge.push_back(42);
        adjEdge.push_back(50);
    }
    else if(vertNum == 31){
        adjEdge.push_back(35);
        adjEdge.push_back(43);
        adjEdge.push_back(42);
    }
    else if(vertNum == 32){
        adjEdge.push_back(43);
        adjEdge.push_back(44);
        adjEdge.push_back(51);
    }
    else if(vertNum == 33){
        adjEdge.push_back(36);
        adjEdge.push_back(45);
        adjEdge.push_back(44);
    }
    else if(vertNum == 34){
        adjEdge.push_back(45);
        adjEdge.push_back(46);
        adjEdge.push_back(52);
    }
    else if(vertNum == 35){
        adjEdge.push_back(37);
        adjEdge.push_back(47);
        adjEdge.push_back(46);
    }
    else if(vertNum == 36){
        adjEdge.push_back(47);
        adjEdge.push_back(48);
        adjEdge.push_back(53);
    }
    else if(vertNum == 37){
        adjEdge.push_back(38);
        adjEdge.push_back(48);
    }
    else if(vertNum == 38){
        adjEdge.push_back(49);
        adjEdge.push_back(54);
    }
    else if(vertNum == 39){
        adjEdge.push_back(54);
        adjEdge.push_back(55);
        adjEdge.push_back(62);
    }
    else if(vertNum == 40){
        adjEdge.push_back(50);
        adjEdge.push_back(56);
        adjEdge.push_back(55);
    }
    else if(vertNum == 41){
        adjEdge.push_back(56);
        adjEdge.push_back(57);
        adjEdge.push_back(63);
    }
    else if(vertNum == 42){
        adjEdge.push_back(51);
        adjEdge.push_back(58);
        adjEdge.push_back(57);
    }
    else if(vertNum == 43){
        adjEdge.push_back(58);
        adjEdge.push_back(59);
        adjEdge.push_back(64);
    }
    else if(vertNum == 44){
        adjEdge.push_back(52);
        adjEdge.push_back(60);
        adjEdge.push_back(59);
    }
    else if(vertNum == 45){
        adjEdge.push_back(60);
        adjEdge.push_back(61);
        adjEdge.push_back(65);
    }
    else if(vertNum == 46){
        adjEdge.push_back(53);
        adjEdge.push_back(61);
    }
    else if(vertNum == 47){
        adjEdge.push_back(62);
        adjEdge.push_back(66);
    }
    else if(vertNum == 48){
        adjEdge.push_back(66);
        adjEdge.push_back(67);
    }
    else if(vertNum == 49){
        adjEdge.push_back(63);
        adjEdge.push_back(68);
        adjEdge.push_back(67);
    }
    else if(vertNum == 50){
        adjEdge.push_back(68);
        adjEdge.push_back(69);
    }
    else if(vertNum == 51){
        adjEdge.push_back(64);
        adjEdge.push_back(70);
        adjEdge.push_back(69);
    }
    else if(vertNum == 52){
        adjEdge.push_back(70);
        adjEdge.push_back(71);
    }
    else if(vertNum == 53){
        adjEdge.push_back(65);
        adjEdge.push_back(71);
    }
    //vertLayer.push_back(this);
}

EDGE::EDGE(int edgeNum){
    edgeId=edgeNum;
    occupiedBy=NOONE;
    if(edgeNum==0){
        adjVert.push_back(0);
        adjVert.push_back(1);
    }
    else if(edgeNum==1){
        adjVert.push_back(1);
        adjVert.push_back(2);
    }
    else if(edgeNum==2){
        adjVert.push_back(2);
        adjVert.push_back(3);
    }
    else if(edgeNum==3){
        adjVert.push_back(3);
        adjVert.push_back(4);
    }
    else if(edgeNum==4){
        adjVert.push_back(4);
        adjVert.push_back(5);
    }
    else if(edgeNum==5){
        adjVert.push_back(5);
        adjVert.push_back(6);
    }
    else if(edgeNum==6){
        adjVert.push_back(0);
        adjVert.push_back(8);
    }
    else if(edgeNum==7){
        adjVert.push_back(2);
        adjVert.push_back(10);
    }
    else if(edgeNum==8){
        adjVert.push_back(4);
        adjVert.push_back(12);
    }
    else if(edgeNum==9){
        adjVert.push_back(6);
        adjVert.push_back(16);
    }
    else if(edgeNum==10){
        adjVert.push_back(7);
        adjVert.push_back(8);
    }
    else if(edgeNum==11){
        adjVert.push_back(8);
        adjVert.push_back(9);
    }
    else if(edgeNum==12){
        adjVert.push_back(9);
        adjVert.push_back(10);
    }
    else if(edgeNum==13){
        adjVert.push_back(10);
        adjVert.push_back(11);
    }
    else if(edgeNum==14){
        adjVert.push_back(11);
        adjVert.push_back(12);
    }
    else if(edgeNum==15){
        adjVert.push_back(12);
        adjVert.push_back(13);
    }
    else if(edgeNum==16){
        adjVert.push_back(13);
        adjVert.push_back(14);
    }
    else if(edgeNum==17){
        adjVert.push_back(14);
        adjVert.push_back(15);
    }
    else if(edgeNum==18){
        adjVert.push_back(7);
        adjVert.push_back(17);
    }
    else if(edgeNum==19){
        adjVert.push_back(9);
        adjVert.push_back(19);
    }
    else if(edgeNum==20){
        adjVert.push_back(11);
        adjVert.push_back(21);
    }
    else if(edgeNum==21){
        adjVert.push_back(13);
        adjVert.push_back(23);
    }
    else if(edgeNum==22){
        adjVert.push_back(15);
        adjVert.push_back(25);
    }
    else if(edgeNum==23){
        adjVert.push_back(16);
        adjVert.push_back(17);
    }
    else if(edgeNum==24){
        adjVert.push_back(17);
        adjVert.push_back(18);
    }
    else if(edgeNum==25){
        adjVert.push_back(18);
        adjVert.push_back(19);
    }
    else if(edgeNum==26){
        adjVert.push_back(19);
        adjVert.push_back(20);
    }
    else if(edgeNum==27){
        adjVert.push_back(20);
        adjVert.push_back(21);
    }
    else if(edgeNum==28){
        adjVert.push_back(21);
        adjVert.push_back(22);
    }
    else if(edgeNum==29){
        adjVert.push_back(22);
        adjVert.push_back(23);
    }
    else if(edgeNum==30){
        adjVert.push_back(23);
        adjVert.push_back(24);
    }
    else if(edgeNum==31){
        adjVert.push_back(24);
        adjVert.push_back(25);
    }
    else if(edgeNum==32){
        adjVert.push_back(25);
        adjVert.push_back(26);
    }
    else if(edgeNum==33){
        adjVert.push_back(16);
        adjVert.push_back(27);
    }
    else if(edgeNum==34){
        adjVert.push_back(18);
        adjVert.push_back(29);
    }
    else if(edgeNum==35){
        adjVert.push_back(20);
        adjVert.push_back(31);
    }
    else if(edgeNum==36){
        adjVert.push_back(22);
        adjVert.push_back(33);
    }
    else if(edgeNum==37){
        adjVert.push_back(24);
        adjVert.push_back(35);
    }
    else if(edgeNum==38){
        adjVert.push_back(26);
        adjVert.push_back(37);
    }
    else if(edgeNum==39){
        adjVert.push_back(27);
        adjVert.push_back(28);
    }
    else if(edgeNum==40){
        adjVert.push_back(28);
        adjVert.push_back(29);
    }
    else if(edgeNum==41){
        adjVert.push_back(29);
        adjVert.push_back(30);
    }
    else if(edgeNum==42){
        adjVert.push_back(30);
        adjVert.push_back(31);
    }
    else if(edgeNum==43){
        adjVert.push_back(31);
        adjVert.push_back(32);
    }
    else if(edgeNum==44){
        adjVert.push_back(32);
        adjVert.push_back(33);
    }
    else if(edgeNum==45){
        adjVert.push_back(33);
        adjVert.push_back(34);
    }
    else if(edgeNum==46){
        adjVert.push_back(34);
        adjVert.push_back(35);
    }
    else if(edgeNum==47){
        adjVert.push_back(35);
        adjVert.push_back(36);
    }
    else if(edgeNum==48){
        adjVert.push_back(36);
        adjVert.push_back(37);
    }
    else if(edgeNum==49){
        adjVert.push_back(28);
        adjVert.push_back(38);
    }
    else if(edgeNum==50){
        adjVert.push_back(30);
        adjVert.push_back(40);
    }
    else if(edgeNum==51){
        adjVert.push_back(32);
        adjVert.push_back(42);
    }
    else if(edgeNum==52){
        adjVert.push_back(34);
        adjVert.push_back(44);
    }
    else if(edgeNum==53){
        adjVert.push_back(36);
        adjVert.push_back(46);
    }
    else if(edgeNum==54){
        adjVert.push_back(38);
        adjVert.push_back(39);
    }
    else if(edgeNum==55){
        adjVert.push_back(39);
        adjVert.push_back(40);
    }
    else if(edgeNum==56){
        adjVert.push_back(40);
        adjVert.push_back(41);
    }
    else if(edgeNum==57){
        adjVert.push_back(41);
        adjVert.push_back(42);
    }
    else if(edgeNum==58){
        adjVert.push_back(42);
        adjVert.push_back(43);
    }
    else if(edgeNum==59){
        adjVert.push_back(43);
        adjVert.push_back(44);
    }
    else if(edgeNum==60){
        adjVert.push_back(44);
        adjVert.push_back(45);
    }
    else if(edgeNum==61){
        adjVert.push_back(45);
        adjVert.push_back(46);
    }
    else if(edgeNum==62){
        adjVert.push_back(39);
        adjVert.push_back(47);
    }
    else if(edgeNum==63){
        adjVert.push_back(41);
        adjVert.push_back(49);
    }
    else if(edgeNum==64){
        adjVert.push_back(43);
        adjVert.push_back(51);
    }
    else if(edgeNum==65){
        adjVert.push_back(45);
        adjVert.push_back(53);
    }
    else if(edgeNum==66){
        adjVert.push_back(47);
        adjVert.push_back(48);
    }
    else if(edgeNum==67){
        adjVert.push_back(48);
        adjVert.push_back(49);
    }
    else if(edgeNum==68){
        adjVert.push_back(49);
        adjVert.push_back(50);
    }
    else if(edgeNum==69){
        adjVert.push_back(50);
        adjVert.push_back(51);
    }
    else if(edgeNum==70){
        adjVert.push_back(51);
        adjVert.push_back(52);
    }
    else if(edgeNum==71){
        adjVert.push_back(52);
        adjVert.push_back(53);
    }
//    edgeLayer.push_back(this);
}

YIELDNUM::YIELDNUM(int id, int num1, int num2) {
    this->num = id;
    hex1=num1;
    hex2=num2;
}

YIELDNUM::YIELDNUM(int id, int num1) {
    this->num = id;
    hex1=num1;
}

PORT::PORT(int terr, int num){
    player=NOONE;
    type=terr;
    if (num==0){
        loc1=0;
        loc2=1;
    }
    else if (num==1){
        loc1=3;
        loc2=4;
    }
    else if (num==2){
        loc1=14;
        loc2=15;
    }
    else if (num==3){
        loc1=26;
        loc2=37;
    }
    else if (num==4){
        loc1=46;
        loc2=45;
    }
    else if (num==5){
        loc1=51;
        loc2=50;
    }
    else if (num==6){
        loc1=48;
        loc2=47;
    }
    else if (num==7){
        loc1=38;
        loc2=28;
    }
    else if (num==8){
        loc1=17;
        loc2=7;
    }
}

void Gameboard::setHexLayer()
{

    for (int i = 0; i<19; i++){
        HEXAGON hex(i);
        hexLayer.push_back(hex);
    }

    /*HEXAGON hex0(0);
    HEXAGON hex1(1);
    HEXAGON hex2(2);
    HEXAGON hex3(3);
    HEXAGON hex4(4);
    HEXAGON hex5(5);
    HEXAGON hex6(6);
    HEXAGON hex7(7);
    HEXAGON hex8(8);
    HEXAGON hex9(9);
    HEXAGON hex10(10);
    HEXAGON hex11(11);
    HEXAGON hex12(12);
    HEXAGON hex13(13);
    HEXAGON hex14(14);
    HEXAGON hex15(15);
    HEXAGON hex16(16);
    HEXAGON hex17(17);
    HEXAGON hex18(18)*/
    ;
}

void Gameboard::setVertLayer()
{
    for (int i = 0; i<54; i++){
        VERTEX vert(i);
        vertLayer.push_back(vert);
    }
//    VERTEX vert0(0);
//    VERTEX vert1(1);
//    VERTEX vert2(2);
//    VERTEX vert3(3);
//    VERTEX vert4(4);
//    VERTEX vert5(5);
//    VERTEX vert6(6);
//    VERTEX vert7(7);
//    VERTEX vert8(8);
//    VERTEX vert9(9);
//    VERTEX vert10(10);
//    VERTEX vert11(11);
//    VERTEX vert12(12);
//    VERTEX vert13(13);
//    VERTEX vert14(14);
//    VERTEX vert15(15);
//    VERTEX vert16(16);
//    VERTEX vert17(17);
//    VERTEX vert18(18);
//    VERTEX vert19(19);
//    VERTEX vert20(20);
//    VERTEX vert21(21);
//    VERTEX vert22(22);
//    VERTEX vert23(23);
//    VERTEX vert24(24);
//    VERTEX vert25(25);
//    VERTEX vert26(26);
//    VERTEX vert27(27);
//    VERTEX vert28(28);
//    VERTEX vert29(29);
//    VERTEX vert30(30);
//    VERTEX vert31(31);
//    VERTEX vert32(32);
//    VERTEX vert33(33);
//    VERTEX vert34(34);
//    VERTEX vert35(35);
//    VERTEX vert36(36);
//    VERTEX vert37(37);
//    VERTEX vert38(38);
//    VERTEX vert39(39);
//    VERTEX vert40(40);
//    VERTEX vert41(41);
//    VERTEX vert42(42);
//    VERTEX vert43(43);
//    VERTEX vert44(44);
//    VERTEX vert45(45);
//    VERTEX vert46(46);
//    VERTEX vert47(47);
//    VERTEX vert48(48);
//    VERTEX vert49(49);
//    VERTEX vert50(50);
//    VERTEX vert51(51);
//    VERTEX vert52(52);
//    VERTEX vert53(53);
}

void Gameboard::setEdgeLayer()
{
    for (int i = 0; i<72; i++){
        EDGE edge(i);
        edgeLayer.push_back(edge);
    }
//    EDGE edge0(0);
//    EDGE edge1(1);
//    EDGE edge2(2);
//    EDGE edge3(3);
//    EDGE edge4(4);
//    EDGE edge5(5);
//    EDGE edge6(6);
//    EDGE edge7(7);
//    EDGE edge8(8);
//    EDGE edge9(9);
//    EDGE edge10(10);
//    EDGE edge11(11);
//    EDGE edge12(12);
//    EDGE edge13(13);
//    EDGE edge14(14);
//    EDGE edge15(15);
//    EDGE edge16(16);
//    EDGE edge17(17);
//    EDGE edge18(18);
//    EDGE edge19(19);
//    EDGE edge20(20);
//    EDGE edge21(21);
//    EDGE edge22(22);
//    EDGE edge23(23);
//    EDGE edge24(24);
//    EDGE edge25(25);
//    EDGE edge26(26);
//    EDGE edge27(27);
//    EDGE edge28(28);
//    EDGE edge29(29);
//    EDGE edge30(30);
//    EDGE edge31(31);
//    EDGE edge32(32);
//    EDGE edge33(33);
//    EDGE edge34(34);
//    EDGE edge35(35);
//    EDGE edge36(36);
//    EDGE edge37(37);
//    EDGE edge38(38);
//    EDGE edge38(39);
//    EDGE edge40(40);
//    EDGE edge41(41);
//    EDGE edge42(42);
//    EDGE edge43(43);
//    EDGE edge44(44);
//    EDGE edge45(45);
//    EDGE edge46(46);
//    EDGE edge47(47);
//    EDGE edge48(48);
//    EDGE edge49(49);
//    EDGE edge50(50);
//    EDGE edge51(51);
//    EDGE edge52(52);
//    EDGE edge53(53);
//    EDGE edge54(54);
//    EDGE edge55(55);
//    EDGE edge56(56);
//    EDGE edge57(57);
//    EDGE edge58(58);
//    EDGE edge59(59);
//    EDGE edge60(60);
//    EDGE edge61(61);
//    EDGE edge62(62);
//    EDGE edge63(63);
//    EDGE edge64(64);
//    EDGE edge65(65);
//    EDGE edge66(66);
//    EDGE edge67(67);
//    EDGE edge68(68);
//    EDGE edge69(69);
//    EDGE edge70(70);
//    EDGE edge71(71);
}

void Gameboard::assTerrain()
{
    int terrAss; //index for unassTerrain
    for(int i=0;i<19;i++){
            srand(time(NULL));
            terrAss=rand()%(int)unassTerrain.size();
//            cout << "terrAss selected to be " << terrAss << endl;
            hexLayer[i].terrType=unassTerrain[terrAss];
//            cout << "hexagon should be set to " << unassTerrain[terrAss] << endl;
//            cout << "hexagon " << i << " is set to " << hexLayer[i].terrType << endl;
            if(unassTerrain[terrAss] == DESERT)
                desHex=i;
                hexLayer[i].yieldNum=7;
            if((terrAss==(int)unassTerrain.size()) and desHex!=unassTerrain[terrAss]){
                cout << "something broke, terrAss is " << terrAss << endl;
                cout << "desHex is "  << desHex;
                cout << "and hexagon 0 is " << hexLayer[0].terrType << endl;
                cout << "length of unassTerrain is " << unassTerrain.size() << endl;

            }
            unassTerrain.erase(unassTerrain.begin()+terrAss);
    }
//    cout << "desert hexagon is " << desHex <<endl;
//    cout << "hexagon " << desHex << "is " << hexLayer[desHex].terrType << endl;

}

void Gameboard::setYield()
{
    int i;
    int hexAss; //index of availHex
    int hexAss1; //index of availHex
    int hexAss2; //index of availHex
    vector<int> availHex; //list of available hexagon IDs
    for(i=0;i<19;i++){
        if(i!=desHex)
            availHex.push_back(i);
    }

     int holdAss1; //holds number of assigned hex
     int holdAss2; //holds number of second assigned hex
     //cout << "making yieldNum 2\n";
     srand(time(NULL));
     hexAss1=rand()%availHex.size();
     holdAss1=availHex[hexAss1];
     hexLayer[holdAss1].yieldNum=2;
     availHex.erase(availHex.begin()+hexAss1);
     YIELDNUM ynum(2,holdAss1);
     yieldNums.push_back(ynum);
     i=3;
     //cout << "made yieldNum 2\n";
     while((availHex.size()!=1)){
         if(i!=7){
            hexAss1=rand()%availHex.size();
            holdAss1=availHex[hexAss1];
            hexLayer[holdAss1].yieldNum=i;
            availHex.erase(availHex.begin()+hexAss1);
            hexAss2=rand()%availHex.size();
            holdAss2=availHex[hexAss2];
            hexLayer[holdAss2].yieldNum=i;
            availHex.erase(availHex.begin()+hexAss2);
            YIELDNUM znum(i,holdAss1,holdAss2);
            yieldNums.push_back(znum);
            hexLayer[holdAss1].yieldNum=i;
            hexLayer[holdAss2].yieldNum=i;
        }
        i++;
     }
     //cout << "made yieldNums 3-11\n";
     //cout << "there are " << availHex.size() << " hexagons left.\n";
     holdAss1=availHex[0];
     hexLayer[holdAss1].yieldNum=12;
     availHex.erase(availHex.begin());
     YIELDNUM dbznum(12,holdAss1);
     yieldNums.push_back(dbznum);
//     if(availHex.empty())
//         cout << "list of available hexagons is empty\n";
//     else
//         cout << "something went wrong, list of hexagons is not empty\n";
}

void Gameboard::setBandit()
{
    hexLayer[desHex].hasBandit=true;
    banditLoc=desHex;
}

void Gameboard::setPorts()
{
    int assDex;
    for (int i=0;i<9;i++){
        timeval Time;
        gettimeofday(&Time, NULL);
        long timeseed=Time.tv_usec ;
        srand(timeseed);
        assDex=rand()%unassPorts.size();
        PORT make(unassPorts[assDex],i);
        ports.push_back(make);
        unassPorts.erase(unassPorts.begin()+assDex);
    }
}

int Gameboard::moveBandit(int hexNum)
{
    if(banditLoc==hexNum)
        return 1;
    hexLayer[banditLoc].hasBandit=false;
    hexLayer[hexNum].hasBandit=true;
    banditLoc=hexNum;
    return 0;
}

terr Gameboard::getTerrain(int hexId)
{
    return hexLayer[hexId].terrType;
}

int Gameboard::getBanditLoc()
{
    return banditLoc;
}

void Gameboard::setBanditLoc(int val){
    banditLoc = val;
}

int Gameboard::validSettle(playerNum currPlayer, int vertNum)
{
    //cout << "checking if occupied vertex\n";
    if (vertLayer[vertNum].occupiedBy!= NOONE)
            return 1; //vertex is occupied, cout accordingly
    //cout<< "checking nearby vertices\n";
    for (int i=0;i<(int)(vertLayer[vertNum].adjEdge.size());i++){ //loop through adjacent edges
        for (int j=0;j<2;j++){ //loop through adjacent vertices
            if ((vertLayer[edgeLayer[vertLayer[vertNum].adjEdge[i]].adjVert[j]].occupiedBy)!= NOONE)
                return 2; //one of the surrounding vertices is occupied, cout accordingly
        }
    }
    //cout << "checking for nearby roads\n";
    for (int i=0;i<(int)(vertLayer[vertNum].adjEdge.size());i++){
        if ((edgeLayer[vertLayer[vertNum].adjEdge[i]].occupiedBy)==currPlayer) //whatever represents the current player
            break;
        if(i==((int)(vertLayer[vertNum].adjEdge.size())-1)){
            return 3; //the player's road does not lead to this vertex, cout accordingly
        }
    }
    //cout << "all clear, valid local\n";
    return 0; //vertex is a valid settlement site
}

int Gameboard::validRoad(playerNum currPlayer, int edgeNum)
{
    if (edgeLayer[edgeNum].occupiedBy!= NOONE)
            return 1; //edge is occupied, cout accordingly

    //just used for checking first road placement
    for (int i=0;i<2;i++)
        if (vertLayer[edgeLayer[edgeNum].adjVert[i]].occupiedBy==currPlayer)
            return 2; //first road placement or subsequent ones is valid

    for (int i=0;i<2;i++){
        //cout << "stepping through adjacent vertices.\n";
        for (unsigned int j=0;j< (vertLayer[edgeLayer[edgeNum].adjVert[i]].adjEdge.size());j++){ //it was here
            //cout << "stepping through adjacent vertices' adjacent edges.\n";
            if (((edgeLayer[vertLayer[edgeLayer[edgeNum].adjVert[i]].adjEdge[j]].occupiedBy)== currPlayer))
                return 0; //valid settlement location
        }
    }
    return 3; //there are none of the player's roads adjacent to any of these edges
}

vector<int> Gameboard::getAssVert(int hexNum)
{
    return hexLayer[hexNum].assVert;
}

vector<int> Gameboard::getAssEdge(int vertNum){
    return vertLayer[vertNum].adjEdge;
}

void Gameboard::setSettle(playerNum currPlayer,int vertNum)
{
    vertLayer[vertNum].occupiedBy=currPlayer;
    vertLayer[vertNum].occByType=1;
}

void Gameboard::setRoad(playerNum currPlayer, int edgeNum)
{
    edgeLayer[edgeNum].occupiedBy=currPlayer;
}

void Gameboard::setCity(playerNum currPlayer, int vertNum)
{
    vertLayer[vertNum].occByType=2;
}

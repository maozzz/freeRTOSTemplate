//
// Created by Alexey Matukhin on 2019-04-02.
//
#include "main.h"
#include <Pin.h>
#include "LcdKs0108.h"
#include <task.h>


const uint8_t CHARS[60][5] = {
        {0x00, 0x00, 0x00, 0x00, 0x00},  // Code for char
        {0x00, 0x00, 0x5E, 0x00, 0x00},  // Code for char !
        {0x00, 0x06, 0x00, 0x06, 0x00},  // Code for char "
        {0x14, 0x74, 0x7E, 0x1E, 0x14},  // Code for char #
        {0x00, 0x4C, 0xEA, 0x5F, 0x72},  // Code for char $
        {0x4E, 0x2A, 0x7E, 0x54, 0x72},  // Code for char %
        {0x7E, 0x5A, 0x66, 0x50, 0x00},  // Code for char &
        {0x00, 0x00, 0x06, 0x00, 0x00},  // Code for char '
        {0x00, 0x7C, 0x82, 0x01, 0x00},  // Code for char (
        {0x00, 0x01, 0x82, 0x7C, 0x00},  // Code for char )
        {0x00, 0x0C, 0x1E, 0x0C, 0x00},  // Code for char *
        {0x10, 0x10, 0x7C, 0x10, 0x10},  // Code for char +
        {0x00, 0x00, 0xC0, 0x00, 0x00},  // Code for char ,
        {0x00, 0x10, 0x10, 0x10, 0x00},  // Code for char -
        {0x00, 0x00, 0x40, 0x00, 0x00},  // Code for char .
        {0x00, 0x80, 0x70, 0x0C, 0x02},  // Code for char /
        {0x3C, 0x52, 0x4A, 0x3C, 0x00},  // Code for char 0
        {0x00, 0x44, 0x7E, 0x40, 0x00},  // Code for char 1
        {0x00, 0x44, 0x62, 0x52, 0x4E},  // Code for char 2
        {0x00, 0x42, 0x4A, 0x4A, 0x36},  // Code for char 3
        {0x30, 0x28, 0x26, 0x7E, 0x20},  // Code for char 4
        {0x00, 0x4E, 0x4A, 0x4A, 0x32},  // Code for char 5
        {0x00, 0x3C, 0x4E, 0x4A, 0x3A},  // Code for char 6
        {0x00, 0x02, 0x62, 0x1A, 0x06},  // Code for char 7
        {0x00, 0x76, 0x4A, 0x4A, 0x36},  // Code for char 8
        {0x5C, 0x52, 0x52, 0x3C, 0x00},  // Code for char 9
        {0x00, 0x00, 0x48, 0x00, 0x00},  // Code for char :
        {0x00, 0x10, 0x28, 0x44, 0x00},  // Code for char <
        {0x00, 0x28, 0x28, 0x28, 0x28},  // Code for char =
        {0x00, 0x44, 0x28, 0x10, 0x00},  // Code for char >
        {0x00, 0x52, 0x12, 0x1C, 0x00},  // Code for char ?
        {0xF8, 0x04, 0x7A, 0x3A, 0x7C},  // Code for char @
        {0x00, 0x7C, 0x22, 0x7C, 0x00},  // Code for char A
        {0x00, 0x7E, 0x4A, 0x4A, 0x36},  // Code for char B
        {0x3C, 0x42, 0x42, 0x42, 0x00},  // Code for char C
        {0x7E, 0x42, 0x42, 0x3C, 0x00},  // Code for char D
        {0x00, 0x7E, 0x4A, 0x4A, 0x00},  // Code for char E
        {0x00, 0x7E, 0x0A, 0x0A, 0x00},  // Code for char F
        {0x3C, 0x42, 0x4A, 0x7A, 0x00},  // Code for char G
        {0x7E, 0x08, 0x08, 0x7E, 0x00},  // Code for char H
        {0x00, 0x42, 0x7E, 0x42, 0x00},  // Code for char I
        {0x00, 0x42, 0x42, 0x7E, 0x00},  // Code for char J
        {0x00, 0x7E, 0x18, 0x24, 0x42},  // Code for char K
        {0x00, 0x7E, 0x40, 0x40, 0x00},  // Code for char L
        {0x7E, 0x0C, 0x10, 0x0C, 0x7E},  // Code for char M
        {0x00, 0x7E, 0x18, 0x7E, 0x00},  // Code for char N
        {0x3C, 0x42, 0x42, 0x42, 0x3C},  // Code for char O
        {0x00, 0x7E, 0x12, 0x12, 0x0C},  // Code for char P
        {0x3C, 0x42, 0xC2, 0x42, 0x3C},  // Code for char Q
        {0x00, 0x7E, 0x12, 0x12, 0x6C},  // Code for char R
        {0x00, 0x4C, 0x4A, 0x52, 0x32},  // Code for char S
        {0x02, 0x02, 0x7E, 0x02, 0x02},  // Code for char T
        {0x3E, 0x40, 0x40, 0x3E, 0x00},  // Code for char U
        {0x00, 0x3E, 0x40, 0x3E, 0x00},  // Code for char V
        {0x00, 0x7E, 0x08, 0x7E, 0x00},  // Code for char W
        {0x42, 0x24, 0x18, 0x24, 0x42},  // Code for char X
        {0x02, 0x0C, 0x70, 0x0C, 0x02},  // Code for char Y
        {0x42, 0x72, 0x4E, 0x42, 0x40},  // Code for char Z
        {0x00, 0x00, 0xFF, 0x00, 0x00},  // Code for char |
        {0x30, 0x10, 0x30, 0x20, 0x30},  // Code for char ~
};

static uint8_t CHARS_RU[160][5] = {
        {0x00, 0x00, 0x00, 0x00, 0x00},// (space) 0x20
        {0x00, 0x00, 0x5F, 0x00, 0x00},// !	0x21
        {0x00, 0x07, 0x00, 0x07, 0x00},// "	0x22
        {0x14, 0x7F, 0x14, 0x7F, 0x14},// #	0x23
        {0x24, 0x2A, 0x7F, 0x2A, 0x12},// $	0x24
        {0x23, 0x13, 0x08, 0x64, 0x62},// %	0x25
        {0x36, 0x49, 0x55, 0x22, 0x50},// &	0x26
        {0x00, 0x05, 0x03, 0x00, 0x00},// '	0x27
        {0x00, 0x1C, 0x22, 0x41, 0x00},// (	0x28
        {0x00, 0x41, 0x22, 0x1C, 0x00},// )	0x29
        {0x08, 0x2A, 0x1C, 0x2A, 0x08},// *	0x2A
        {0x08, 0x08, 0x3E, 0x08, 0x08},// +	0x2B
        {0x00, 0x50, 0x30, 0x00, 0x00},// ,	0x2C
        {0x08, 0x08, 0x08, 0x08, 0x08},// -	0x2D
        {0x00, 0x60, 0x60, 0x00, 0x00},// .	0x2E
        {0x20, 0x10, 0x08, 0x04, 0x02},// /	0x2F
        {0x3E, 0x51, 0x49, 0x45, 0x3E},// 	0x30
        {0x00, 0x42, 0x7F, 0x40, 0x00},// 1	0x31
        {0x42, 0x61, 0x51, 0x49, 0x46},// 2	0x32
        {0x21, 0x41, 0x45, 0x4B, 0x31},// 3	0x33
        {0x18, 0x14, 0x12, 0x7F, 0x10},// 4	0x34
        {0x27, 0x45, 0x45, 0x45, 0x39},// 5	0x35
        {0x3C, 0x4A, 0x49, 0x49, 0x30},// 6	0x36
        {0x01, 0x71, 0x09, 0x05, 0x03},// 7	0x37
        {0x36, 0x49, 0x49, 0x49, 0x36},// 8	0x38
        {0x06, 0x49, 0x49, 0x29, 0x1E},// 9	0x39
        {0x00, 0x36, 0x36, 0x00, 0x00},// :	0x3A
        {0x00, 0x56, 0x36, 0x00, 0x00},// ;	0x3B
        {0x00, 0x08, 0x14, 0x22, 0x41},// <	0x3C
        {0x14, 0x14, 0x14, 0x14, 0x14},// =	0x3D
        {0x41, 0x22, 0x14, 0x08, 0x00},// >	0x3E
        {0x02, 0x01, 0x51, 0x09, 0x06},// ?	0x3F
        {0x32, 0x49, 0x79, 0x41, 0x3E},// @	0x40
        {0x7E, 0x11, 0x11, 0x11, 0x7E},// A	0x41
        {0x7F, 0x49, 0x49, 0x49, 0x36},// B	0x42
        {0x3E, 0x41, 0x41, 0x41, 0x22},// C	0x43
        {0x7F, 0x41, 0x41, 0x22, 0x1C},// D	0x44
        {0x7F, 0x49, 0x49, 0x49, 0x41},// E	0x45
        {0x7F, 0x09, 0x09, 0x01, 0x01},// F	0x46
        {0x3E, 0x41, 0x41, 0x51, 0x32},// G	0x47
        {0x7F, 0x08, 0x08, 0x08, 0x7F},// H	0x48
        {0x00, 0x41, 0x7F, 0x41, 0x00},// I	0x49
        {0x20, 0x40, 0x41, 0x3F, 0x01},// J	0x4A
        {0x7F, 0x08, 0x14, 0x22, 0x41},// K	0x4B
        {0x7F, 0x40, 0x40, 0x40, 0x40},// L	0x4C
        {0x7F, 0x02, 0x04, 0x02, 0x7F},// M	0x4D
        {0x7F, 0x04, 0x08, 0x10, 0x7F},// N	0x4E
        {0x3E, 0x41, 0x41, 0x41, 0x3E},// O	0x4F
        {0x7F, 0x09, 0x09, 0x09, 0x06},// P	0x50
        {0x3E, 0x41, 0x51, 0x21, 0x5E},// Q	0x51
        {0x7F, 0x09, 0x19, 0x29, 0x46},// R	0x52
        {0x46, 0x49, 0x49, 0x49, 0x31},// S	0x53
        {0x01, 0x01, 0x7F, 0x01, 0x01},// T	0x54
        {0x3F, 0x40, 0x40, 0x40, 0x3F},// U	0x55
        {0x1F, 0x20, 0x40, 0x20, 0x1F},// V	0x56
        {0x7F, 0x20, 0x18, 0x20, 0x7F},// W	0x57
        {0x63, 0x14, 0x08, 0x14, 0x63},// X	0x58
        {0x03, 0x04, 0x78, 0x04, 0x03},// Y	0x59
        {0x61, 0x51, 0x49, 0x45, 0x43},// Z	0x5A
        {0x00, 0x00, 0x7F, 0x41, 0x41},// [	0x5B
        {0x02, 0x04, 0x08, 0x10, 0x20},// "\"	0x5C
        {0x41, 0x41, 0x7F, 0x00, 0x00},// ]	0x5D
        {0x04, 0x02, 0x01, 0x02, 0x04},// ^	0x5E
        {0x40, 0x40, 0x40, 0x40, 0x40},// _	0x5F
        {0x00, 0x01, 0x02, 0x04, 0x00},// `	0x60
        {0x20, 0x54, 0x54, 0x54, 0x78},// a	0x61
        {0x7F, 0x48, 0x44, 0x44, 0x38},// b	0x62
        {0x38, 0x44, 0x44, 0x44, 0x20},// c	0x63
        {0x38, 0x44, 0x44, 0x48, 0x7F},// d	0x64
        {0x38, 0x54, 0x54, 0x54, 0x18},// e	0x65
        {0x08, 0x7E, 0x09, 0x01, 0x02},// f	0x66
        {0x08, 0x14, 0x54, 0x54, 0x3C},// g	0x67
        {0x7F, 0x08, 0x04, 0x04, 0x78},// h	0x68
        {0x00, 0x44, 0x7D, 0x40, 0x00},// i	0x69
        {0x20, 0x40, 0x44, 0x3D, 0x00},// j	0x6A
        {0x00, 0x7F, 0x10, 0x28, 0x44},// k	0x6B
        {0x00, 0x41, 0x7F, 0x40, 0x00},// l	0x6C
        {0x7C, 0x04, 0x18, 0x04, 0x78},// m	0x6D
        {0x7C, 0x08, 0x04, 0x04, 0x78},// n	0x6E
        {0x38, 0x44, 0x44, 0x44, 0x38},// o	0x6F
        {0x7C, 0x14, 0x14, 0x14, 0x08},// p	0x70
        {0x08, 0x14, 0x14, 0x18, 0x7C},// q	0x71
        {0x7C, 0x08, 0x04, 0x04, 0x08},// r	0x72
        {0x48, 0x54, 0x54, 0x54, 0x20},// s	0x73
        {0x04, 0x3F, 0x44, 0x40, 0x20},// t	0x74
        {0x3C, 0x40, 0x40, 0x20, 0x7C},// u	0x75
        {0x1C, 0x20, 0x40, 0x20, 0x1C},// v	0x76
        {0x3C, 0x40, 0x30, 0x40, 0x3C},// w	0x77
        {0x44, 0x28, 0x10, 0x28, 0x44},// x	0x78
        {0x0C, 0x50, 0x50, 0x50, 0x3C},// y	0x79
        {0x44, 0x64, 0x54, 0x4C, 0x44},// z	0x7A
        {0x00, 0x08, 0x36, 0x41, 0x00},// {	0x7B
        {0x00, 0x00, 0x7F, 0x00, 0x00},// |	0x7C
        {0x00, 0x41, 0x36, 0x08, 0x00},// }	0x7D
        {0x08, 0x08, 0x2A, 0x1C, 0x08},// ->	0x7E
        {0x08, 0x1C, 0x2A, 0x08, 0x08}, // <-	0x7F
        {0x7C, 0x14, 0x14, 0x14, 0x08},//p 	0x80
        {0x38, 0x44, 0x44, 0x44, 0x20},//c	0x81
        {0x04, 0x04, 0x7c, 0x04, 0x04},//т	0x82
        {0x0C, 0x50, 0x50, 0x50, 0x3C},//у	0x83
        {0x30, 0x48, 0xfc, 0x48, 0x30},//ф	0x84
        {0x44, 0x28, 0x10, 0x28, 0x44},//x	0x85
        {0x7c, 0x40, 0x40, 0x40, 0xfc},//ц	0x86
        {0x0c, 0x10, 0x10, 0x10, 0x7c},//ч	0x87
        {0x7c, 0x40, 0x7c, 0x40, 0x7c},//ш	0x88
        {0x7c, 0x40, 0x7c, 0x40, 0xfc},//щ	0x89
        {0x04, 0x7c, 0x50, 0x50, 0x20},//ъ	0x8A
        {0x7c, 0x50, 0x50, 0x20, 0x7c},//ы	0x8B
        {0x7c, 0x50, 0x50, 0x20, 0x00},//ь	0x8C
        {0x28, 0x44, 0x54, 0x54, 0x38},//э	0x8D
        {0x7c, 0x10, 0x38, 0x44, 0x38},//ю	0x8E
        {0x08, 0x54, 0x34, 0x14, 0x7c},//я	0x8F
        {0x7e, 0x11, 0x11, 0x11, 0x7e},//A	0x90
        {0x7f, 0x49, 0x49, 0x49, 0x33},//Б	0x91
        {0x7f, 0x49, 0x49, 0x49, 0x36},//В	0x92
        {0x7f, 0x01, 0x01, 0x01, 0x03},//Г	0x93
        {0xe0, 0x51, 0x4f, 0x41, 0xff},//Д	0x94
        {0x7f, 0x49, 0x49, 0x49, 0x41},//E	0x95
        {0x77, 0x08, 0x7f, 0x08, 0x77},//Ж	0x96
        {0x41, 0x49, 0x49, 0x49, 0x36},//З	0x97
        {0x7f, 0x10, 0x08, 0x04, 0x7f},//И	0x98
        {0x7c, 0x21, 0x12, 0x09, 0x7c},//Й	0x99
        {0x7f, 0x08, 0x14, 0x22, 0x41},//K	0x9A
        {0x20, 0x41, 0x3f, 0x01, 0x7f},//Л	0x9B
        {0x7f, 0x02, 0x0c, 0x02, 0x7f},//M	0x9C
        {0x7f, 0x08, 0x08, 0x08, 0x7f},//H	0x9D
        {0x3e, 0x41, 0x41, 0x41, 0x3e},//O	0x9E
        {0x7f, 0x01, 0x01, 0x01, 0x7f},//П	0x9F
        {0x7f, 0x09, 0x09, 0x09, 0x06},//P	0xA0
        {0x3e, 0x41, 0x41, 0x41, 0x22},//C	0xA1
        {0x01, 0x01, 0x7f, 0x01, 0x01},//T	0xA2
        {0x47, 0x28, 0x10, 0x08, 0x07},//У	0xA3
        {0x1c, 0x22, 0x7f, 0x22, 0x1c},//Ф	0xA4
        {0x63, 0x14, 0x08, 0x14, 0x63},//X	0xA5
        {0x7f, 0x40, 0x40, 0x40, 0xff},//Ц	0xA6
        {0x07, 0x08, 0x08, 0x08, 0x7f},//Ч	0xA7
        {0x7f, 0x40, 0x7f, 0x40, 0x7f},//Ш	0xA8
        {0x7f, 0x40, 0x7f, 0x40, 0xff},//Щ	0xA9
        {0x01, 0x7f, 0x48, 0x48, 0x30},//Ъ	0xAA
        {0x7f, 0x48, 0x30, 0x00, 0x7f},//Ы	0xAB
        {0x00, 0x7f, 0x48, 0x48, 0x30},//Э	0xAC
        {0x22, 0x41, 0x49, 0x49, 0x3e},//Ь	0xAD
        {0x7f, 0x08, 0x3e, 0x41, 0x3e},//Ю	0xAE
        {0x46, 0x29, 0x19, 0x09, 0x7f},//Я	0xAF
        {0x20, 0x54, 0x54, 0x54, 0x78},//a	0xB0
        {0x3c, 0x4a, 0x4a, 0x49, 0x31},//б	0xB1
        {0x7c, 0x54, 0x54, 0x28, 0x00},//в	0xB2
        {0x7c, 0x04, 0x04, 0x04, 0x0c},//г	0xB3
        {0xe0, 0x54, 0x4c, 0x44, 0xfc},//д	0xB4
        {0x38, 0x54, 0x54, 0x54, 0x18},//e	0xB5
        {0x6c, 0x10, 0x7c, 0x10, 0x6c},//ж	0xB6
        {0x44, 0x44, 0x54, 0x54, 0x28},//з	0xB7
        {0x7c, 0x20, 0x10, 0x08, 0x7c},//и	0xB8
        {0x7c, 0x41, 0x22, 0x11, 0x7c},//й	0xB9
        {0x7c, 0x10, 0x28, 0x44, 0x00},//к	0xBA
        {0x20, 0x44, 0x3c, 0x04, 0x7c},//л	0xBB
        {0x7c, 0x08, 0x10, 0x08, 0x7c},//м	0xBC
        {0x7c, 0x10, 0x10, 0x10, 0x7c},//н	0xBD
        {0x38, 0x44, 0x44, 0x44, 0x38},//o	0xBE
        {0x7c, 0x04, 0x04, 0x04, 0x7c},//п	0xBF
};

void LcdKs0108::waitForLcdReady(uint8_t state) {
    //Линия RW = 1 - мы читаем с индикатора
    RW->switchOn();

    //Читаем команду
    A0->switchOff();

    //Включаем необходимый чип
    (state && CHIP1) ? E1->switchOn() : E2->switchOn();

    //Необходимая задержка


    //Выставляем строб
    E->switchOn();
    //Необходимая задержка
    asm("nop");

    //Седьмой пин данных делаем входом
    dataPins[7]->oe(PORT_OE_IN);

    //Необходимая задержка
    asm("nop");

    //Дожидаемся сброса сигнала занятости
    while (dataPins[7]->read()) {
        portYIELD();
    }

    //Сбрасываем строб
    E->switchOff();

    //Вновь пин - на выход
    dataPins[7]->oe(PORT_OE_OUT);
    //Необходимая задержка
    asm("nop");

    //Сбрасываем сигналы управления чипами
    E1->switchOff();
    E2->switchOff();
}

uint8_t LcdKs0108::readByte(uint8_t state) {
    //Все пины - вход
    for (int i = 0; i < 8; ++i) {
        dataPins[i]->oe(PORT_OE_IN);
    }

    //Ждем готовности
    waitForLcdReady(state);

    //Будем считывать
    RW->switchOn();
    A0->switchOn();

    //Выбираем чип
    (state & CHIP1) ? E1->switchOn() : E2->switchOn();  //digitalWrite(E1, 1) : digitalWrite(E2, 1);

    //Необходимая задержка
    vTaskDelay(1);

    //Устанавливаем строб
    E->switchOn();
    //Ждем
    vTaskDelay(1);

    uint8_t readedByte = 0;

    //Считываем данные с шины
    for (int i = 0; i < 8; ++i) {
        readedByte |= (dataPins[i]->read() << i);
    }

    //Убираем строб
    E->switchOff();
    //Ждем
    vTaskDelay(1);

    //Восстанавливаем направление шины
    for (int i = 0; i < 8; ++i) {
        dataPins[i]->oe(PORT_OE_OUT);
    }
    return readedByte;
}

void LcdKs0108::writeByte(uint8_t data, uint8_t state) {


    //Ждем готовности
//    waitForLcdReady(state);

    taskENTER_CRITICAL();
    //На RW=0 - мы будем писАть в индикатор
    RW->switchOff();
    //Команду или данный
    (state & DATA) ? A0->switchOn() : A0->switchOff();

    //Выбираем необходимый чип
    if (state & CHIP1) E1->switchOn();
    else E1->switchOff(); //digitalWrite(E1, 1) : digitalWrite(E2, 1);
    if (state & CHIP2) E2->switchOn();
    else E2->switchOff(); //digitalWrite(E1, 1) : digitalWrite(E2, 1);

    //Выставляем данные на шину
    for (int i = 0; i < 8; ++i) {
        (data & (1 << i)) ? dataPins[i]->switchOn() : dataPins[i]->switchOff();
    }

    //Устанавливаем строб
    E->switchOn();

    //Ждем
//    asm("nop");

    //Сбрасываем строб
    E->switchOff();

    //Сбрасываем сигналы управления чипами
    E1->switchOff();
    E2->switchOff();
    taskEXIT_CRITICAL();
    portYIELD();
}

void LcdKs0108::init(Pin *_DB0, Pin *_DB1, Pin *_DB2, Pin *_DB3,
                     Pin *_DB4, Pin *_DB5, Pin *_DB6, Pin *_DB7,
                     Pin *_E1, Pin *_E2, Pin *_RES, Pin *_RW,
                     Pin *_CD, Pin *_E) {

    //Заполняем массив пинами с линиями данных
    dataPins[0] = _DB0;
    dataPins[1] = _DB1;
    dataPins[2] = _DB2;
    dataPins[3] = _DB3;
    dataPins[4] = _DB4;
    dataPins[5] = _DB5;
    dataPins[6] = _DB6;
    dataPins[7] = _DB7;

    //Все пины - выход
    for (int i = 0; i < 8; ++i) {
        //Serial.println(dataPins[i], DEC);
        dataPins[i]->oe(PORT_OE_OUT);
    }
    A0 = _CD;
    E = _E;
    E1 = _E1;
    E2 = _E2;
    RES = _RES;
    RW = _RW;

    //Сбрасываем модуль
    E->switchOff();
    RES->switchOff();
    vTaskDelay(2);
    RES->switchOn();
    vTaskDelay(2);


    writeByte(~0xC0, CHIP1);
    //Верхняя строчка отображения - 0
    writeByte(0xC0, CHIP1);
    writeByte(0xC0, CHIP2);

    //Включить контроллер!
    writeByte(0x3F, CHIP1);
    writeByte(0x3F, CHIP2);
}

/**
 * Тест GLCD - двигает кубики.
 */
void LcdKs0108::test() {
    uint8_t startLine = 0;
    while (1) {
        vTaskDelay(1);
        startLine++;
        if (startLine == 64) startLine = 0;
        uint8_t startL = startLine;
        this->writeByte(0xC0 | startL, CHIP1 | CHIP2);
        bool t;
        for (uint8_t i = 0; i < 8; i++) {
            this->setPage(i); // выбор страницы
            t = i > 3 ? 1 : 0;
            this->writeByte(0x40, CHIP1 | CHIP2); // 0 строка
            for (uint8_t k = 0; k < 32; k++) {
                if (t) {
                    this->writeByte(0xFF, DATA | CHIP1);
                    this->writeByte(0xFF, DATA | CHIP1);
                    this->writeByte(0x00, DATA | CHIP2);
                    this->writeByte(0x00, DATA | CHIP2);
                } else {
                    this->writeByte(0xFF, DATA | CHIP2);
                    this->writeByte(0xFF, DATA | CHIP2);
                    this->writeByte(0x00, DATA | CHIP1);
                    this->writeByte(0x00, DATA | CHIP1);
                }
            }
        }
    }
}

void LcdKs0108::test2() {
    while (1) {
        clear();
        uint8_t len = sizeof(CHARS_RU) / 6 - 1;
        uint8_t charNum = 80;
        for (int i = 0; i < 8; i++) {
            setPage(i);
            for (int k = 0; k < 10; k++) {
                if (charNum >= len) charNum = 0;
                for (int j = 0; j < 5; j++) {
                    writeByte(CHARS_RU[charNum][j], DATA | 0x01);
                }
                writeByte(0x00, DATA | 0x01);
                vTaskDelay(1000);
                charNum++;
            }
        }
        vTaskDelay(1000);
    }
}

void LcdKs0108::clear() {
    for (int i = 0; i < 8; i++) {
        setPage(i);
        for (int k = 0; k < 64; k++) {
            writeByte(0x00, DATA | 0x02);
            writeByte(0x00, DATA | 0x01);
        }
    }
}

void LcdKs0108::setPage(uint8_t page) {
    // 0xBF & (0xB8 | page) 10111xxx
    writeByte(0xB8 | page, CHIP1 | CHIP2);
    writeByte(0x40, CHIP1 | CHIP2); // сброс адреса в 0
}

#include "gsession.h"


QString GSession::uname = "";

QString GSession::getTimeName()
{

    //凌晨 1 - 5
    //早上 6 - 8
    //上午 9 - 11
    //中午 12
    //下午 13 - 18
    //晚上 19 - 23
    //午夜 0

    static QString timeName;
    switch( QTime::currentTime().hour() ) {
    case 0:
        timeName = "午夜";
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        timeName = "凌晨";
        break;
    case 6:
    case 7:
    case 8:
        timeName = "早上";
        break;
    case 9:
    case 10:
    case 11:
        timeName = "上午";
        break;
    case 12:
        timeName = "正午";
        break;

    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        timeName = "下午";
        break;

    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
        timeName = "晚上";
        break;
    default:
        timeName = "";
        break;
    }

    return timeName;
}

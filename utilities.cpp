#include "utilities.h"

QString getCurrentTime(){
    char out[15];
    std::time_t t=std::time(NULL);
    std::strftime(out, sizeof(out), "%Y%m%d%H%M%S", std::localtime(&t));
    QString str(out);
    return str;
}

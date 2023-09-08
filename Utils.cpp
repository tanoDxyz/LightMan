#include "QDateTime"
#include "quuid.h"
#include "Utils.h"
QString currentTimeMilliseconds() {
    return QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz");
}

QString newUUIDFromCurrentDateTime() {
    return QUuid().fromString(currentTimeMilliseconds()).toString();
}


int Counter::get() const {
    return counter;
}

void Counter::setCounter(int value) {
    this->counter = value;
}

Counter::Counter() {}
int Counter::getAndIncrement() {
    auto counterVallue =  get();
    ++counter;
    return counterVallue;
}


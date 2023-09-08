#ifndef UTILS_H
#define UTILS_H
#include "QString"
QString currentTimeMilliseconds();
QString newUUIDFromCurrentDateTime();

class Counter {
private:
    int counter = 1;
public:
    Counter();
    Counter(int start = 1):counter{start}{}
    int get() const;
    void setCounter(int value);
    int getAndIncrement();
};
#endif // UTILS_H

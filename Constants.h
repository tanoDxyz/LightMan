#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Utils.h"

#include <QPair>

namespace Constants {
constexpr inline int NEW_REQUEST_URL_INPUT_TEXT_EDIT_MAX_HEIGHT = 120;
constexpr inline int PARAMS = 121;
constexpr inline int HEADERS = 122;

    namespace HttpMethods {
    inline const QString GET = QString(("GET"));
    inline const QString HEAD = QString(("HEAD"));
    inline const QString POST = QString(("POST"));
    inline const QString PUT = QString(("PUT"));
    inline const QString DELETE = QString(("DELETE"));
    inline const QString NONE = QString(("NONE"));
    }

}
#endif // CONSTANTS_H

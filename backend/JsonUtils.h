//
// Created by Raul-Nicolae Constantin on 08.09.2025.
//

#ifndef JSONUTILS_H
#define JSONUTILS_H

#include "Event.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

json serialize(const Event & ev);

Event deserialize (const json & j_ev);




#endif //JSONUTILS_H

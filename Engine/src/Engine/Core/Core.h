#pragma once

#include <functional>

#define EN_BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)
#pragma once

#define BIND_EVENT(type, x) std::bind(&type::x, this, std::placeholders::_1)
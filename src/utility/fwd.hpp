#pragma once
#ifndef FWD
#define FWD(arg) static_cast<decltype(arg)&&>(arg)
#endif
#pragma once

#include "../../build/furredengine_export.h"
#if __cplusplus
    #define FE_EXPORT extern "C" FURREDENGINE_EXPORT
#else
    #define FE_EXPORT FURREDENGINE_EXPORT
#endif /* __cplusplus */

#define FE_STRUCT(x) typedef struct x x; struct x
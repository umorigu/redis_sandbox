// gcc -O2 -shared -fPIC emptymod.c -o emptymod.so

#include "../include/redismodule.h"

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  if (RedisModule_Init(ctx, "emptymod", 1, REDISMODULE_APIVER_1)
      == REDISMODULE_ERR) return REDISMODULE_ERR;
  return REDISMODULE_OK;
}

// gcc -O2 -shared -fPIC hellomod.c -o hellomod.so

#include "redismodule.h"
//#include <stdlib.h>
#include <string.h>

int HelloMod_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  if (argc != 2) return RedisModule_WrongArity(ctx);

  const char* str = "hello";
  if (RedisModule_ReplyWithStringBuffer(ctx, str, strlen(str)) == REDISMODULE_ERR)
    return REDISMODULE_ERR;

  return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  if (RedisModule_Init(ctx, "hellomod", 1, REDISMODULE_APIVER_1)
      == REDISMODULE_ERR) return REDISMODULE_ERR;

  if (RedisModule_CreateCommand(ctx,"hellomod",
                                HelloMod_RedisCommand, "readonly", 1, 1, 1) == REDISMODULE_ERR)
    return REDISMODULE_ERR;
  return REDISMODULE_OK;
}

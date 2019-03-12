// gcc -O2 -shared -fPIC helloworld.c -o helloworld.so

#include "redismodule.h"
#include <stdlib.h>
#include <string.h>

int HelloWorld_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  /* 引数の数をチェック */
  if (argc != 2) return RedisModule_WrongArity(ctx);


  /* 引数の値をkeyにしてLPUSH */
  const char *hello = "Hello, World!";
  RedisModuleKey *key =RedisModule_OpenKey(ctx, argv[1], REDISMODULE_WRITE);
  RedisModuleString *str = RedisModule_CreateString(ctx, hello, strlen(hello));
  if (RedisModule_ListPush(key, REDISMODULE_LIST_TAIL, str) == REDISMODULE_ERR)
    return REDISMODULE_ERR;
  RedisModule_CloseKey(key);

  /* クライアントに値を返却 */
  if (RedisModule_ReplyWithString(ctx, str) == REDISMODULE_ERR)
    return REDISMODULE_ERR;

  return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  if (RedisModule_Init(ctx, "helloworld", 1, REDISMODULE_APIVER_1)
      == REDISMODULE_ERR) return REDISMODULE_ERR;

  if (RedisModule_CreateCommand(ctx,"helloworld",
                                HelloWorld_RedisCommand, "write", 1, 1, 1) == REDISMODULE_ERR)
    return REDISMODULE_ERR;

  return REDISMODULE_OK;
}

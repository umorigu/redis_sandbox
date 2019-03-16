// gcc -O2 -shared -fPIC hellohscan.c -o hellohscan.so

#include "../include/redismodule.h"
#include <stdlib.h>
#include <string.h>

int HelloHscan_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  /* Check arg count */
  if (argc != 2) return RedisModule_WrongArity(ctx);

  const char *hello = "Hello, World!";
  RedisModuleString* keyStr = argv[1];

  RedisModule_Log(ctx, "notice", "Before call()");
  RedisModule_ReplyWithArray(ctx, REDISMODULE_POSTPONED_ARRAY_LEN);
  RedisModule_ReplyWithStringBuffer(ctx, "[start]", 7);
  RedisModuleCallReply *reply = RedisModule_Call(ctx, "HSCAN", "sc", keyStr, "0");
  if (RedisModule_CallReplyType(reply) != REDISMODULE_REPLY_ARRAY) {
    RedisModule_Log(ctx, "warning", "not array");
    return REDISMODULE_ERR;
  }
  RedisModule_Log(ctx, "notice", "After call()");
  size_t length0 = RedisModule_CallReplyLength(reply);
  if (length0 != 2) {
    RedisModule_Log(ctx, "warning", "length0 is NOT 2");
    return REDISMODULE_ERR;
  }
  RedisModuleCallReply *r0 = RedisModule_CallReplyArrayElement(reply, 0);
  if (RedisModule_CallReplyType(r0) == REDISMODULE_REPLY_STRING) {
    size_t len = 0;
    const char *s = RedisModule_CallReplyStringPtr(r0, &len);
    RedisModule_ReplyWithStringBuffer(ctx, s, len);
  } else {
    RedisModule_ReplyWithStringBuffer(ctx, "ERR", strlen("ERR"));
  }
  RedisModuleCallReply *r1 = RedisModule_CallReplyArrayElement(reply, 1);
  size_t length = RedisModule_CallReplyLength(r1);

  for (size_t i = 0; i < length; i++) {
    RedisModuleCallReply *r = RedisModule_CallReplyArrayElement(r1, i);
    if (RedisModule_CallReplyType(r) == REDISMODULE_REPLY_STRING) {
      size_t len = 0;
      const char *s = RedisModule_CallReplyStringPtr(r, &len);
      RedisModule_ReplyWithStringBuffer(ctx, s, len);
    } else {
      RedisModule_ReplyWithStringBuffer(ctx, "[non str]", strlen("[non str]"));
    }
  }
  RedisModule_FreeCallReply(reply);
  RedisModule_Log(ctx, "notice", "NOTICE!");
  RedisModule_ReplyWithLongLong(ctx, length);
  RedisModule_ReplyWithStringBuffer(ctx, "[end]", strlen("[end]"));
  RedisModule_ReplySetArrayLength(ctx, length + 4);
  return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  if (RedisModule_Init(ctx, "hellohscan", 1, REDISMODULE_APIVER_1)
    == REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  if (RedisModule_CreateCommand(ctx,"hellohscan",
    HelloHscan_RedisCommand, "readonly", 1, 1, 1) == REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }
  return REDISMODULE_OK;
}

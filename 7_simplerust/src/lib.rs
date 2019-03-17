extern crate libc;
use libc::c_int;

const MODULE_NAME: &'static str = "emptyrust2";

pub enum RedisModuleCtx {}
pub enum RedisModuleString {}

#[allow(improper_ctypes)]
#[link(name = "redismodule", kind = "static")]
extern "C" {
    pub fn Export_RedisModule_Init(
        ctx: *mut RedisModuleCtx,
        modulename: *const u8,
        module_version: c_int,
        api_version: c_int,
    ) -> c_int;
}

pub fn SimpleRust_RedisCommand(
    ctx: *mut RedisModuleCtx,
    argv: *mut *mut RedisModuleString,
    argc: c_int,
) -> c_int {
    if (argc != 2) {
        return 1;
    }
    return 0;
}

extern "C" {
    // int RedisModule_CreateCommand(RedisModuleCtx *ctx, const char *name,
    //   RedisModuleCmdFunc cmdfunc, const char *strflags, int firstkey,
    //   int lastkey, int keystep);
    fn RedisModule_CreateCommand(
        ctx: *mut RedisModuleCtx,
        name: *const u8,
        fmdfunc: extern "C" fn(*mut RedisModuleCtx, *mut *mut RedisModuleString, c_int) -> c_int,
        strflags: *const u8,
        firstkey: c_int,
        lastkey: c_int,
        keystep: c_int,
    );
}

/*
enum Status {
    Ok = 0,
    Err = 1,
}
*/

#[no_mangle]
pub extern "C" fn RedisModule_OnLoad(
    ctx: *mut RedisModuleCtx,
    argv: *mut *mut RedisModuleString,
    argc: c_int,
) -> c_int {
    unsafe {
        Export_RedisModule_Init(ctx, format!("{}\0", MODULE_NAME).as_ptr(), 1, 1);
    }
    return 0;
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}

extern crate libc;
use libc::c_int;

const MODULE_NAME: &'static str = "emptyrust2";

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

pub enum RedisModuleCtx {}
pub enum RedisModuleString {}

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

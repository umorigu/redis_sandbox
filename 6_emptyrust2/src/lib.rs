extern crate libc;
use libc::c_int;

pub enum RedisModuleCtx {}
pub enum RedisModuleString {}

#[no_mangle]
pub extern "C" fn RedisModule_OnLoad(
    ctx: *mut RedisModuleCtx,
    argv: *mut *mut RedisModuleString,
    argc: c_int,
) -> c_int {
    return 0;
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}

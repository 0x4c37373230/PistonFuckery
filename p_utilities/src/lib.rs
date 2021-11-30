use simple_config_parser::Config;

#[cfg(test)]
mod tests {
    #[test]
    fn arm_logging_true() {
        assert!(crate::log_arm_updates())
    }
}

#[no_mangle]
pub extern fn delete_blocks() -> bool {
    let cfg = Config::new().file("./config.cfg").unwrap();
    let deletion: i32 = cfg.get("deleteBlocksOnExtension").unwrap();

    deletion != 0
}

#[no_mangle]
pub extern fn log_updates() -> bool {
    let cfg = Config::new().file("./config.cfg").unwrap();
    let log: i32 = cfg.get("updateLogging").unwrap();

    log != 0
}

#[no_mangle]
pub extern fn log_arm_updates() -> bool {
    let cfg = Config::new().file("./config.cfg").unwrap();
    let log: i32 = cfg.get("armLogging").unwrap();

    log != 0
}

#[no_mangle]
pub extern fn change_push_limit() -> bool {
    let cfg = Config::new().file("./config.cfg").unwrap();
    let log: i32 = cfg.get("customPushLimit").unwrap();

    log != 0
}

#[no_mangle]
pub extern fn new_push_limit() -> i32 {
    let cfg = Config::new().file("./config.cfg").unwrap();
    let log: i32 = cfg.get("newPushLimit").unwrap();

    log
}

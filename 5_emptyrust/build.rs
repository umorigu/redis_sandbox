extern crate gcc;

fn main() {
    gcc::Config::new()
        .file("src/redismodule.c")
        .include("include/")
        .compile("libredismodule.a");
}


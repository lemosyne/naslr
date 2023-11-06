use std::{env, path::PathBuf};

const SOURCE: &str = "./src/lib.c";
const HEADER: &str = "./src/lib.h";
const TARGETS: &[&str] = &[SOURCE, HEADER];

fn main() {
    for file in TARGETS {
        println!("cargo:rerun-if-changed={file}");
    }

    let outdir = PathBuf::from(env::var("OUT_DIR").unwrap());
    let outfile = outdir.join("bindings.rs");

    cc::Build::new().file(SOURCE).compile("naslr");

    println!("cargo:rustc-link-lib=naslr");

    let bindings = bindgen::Builder::default()
        .header(HEADER)
        .derive_default(true)
        .generate()
        .expect("failed to generate bindings");

    bindings.write_to_file(&outfile).unwrap();
}

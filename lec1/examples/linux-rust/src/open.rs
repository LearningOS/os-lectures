use std::fs::File;
use std::io::Write;
fn main() {
    let mut file = File::create("output.txt").unwrap();
    file.write(b"ooo\n").unwrap();
}
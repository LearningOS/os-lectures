use exec::Command;

fn main() {
    let args: Vec<_> = std::env::args_os().skip(1).collect();
    let err = Command::new("ls")
        .args(&args)
        .exec();
    println!("Error: {}", err);
}
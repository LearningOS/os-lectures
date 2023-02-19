use std::process::Command;
use std::os::unix::process::ExitStatusExt;

fn main() {
    let mut child = Command::new("echo")
        .arg("THIS")
        .arg("IS")
        .arg("ECHO")
        .spawn()
        .expect("failed to execute child process");
    
    println!("parent waiting");
    let status = child.wait().expect("failed to wait on child");

    if let Some(exit_code) = status.code() {
        println!("the child exited with status {}", exit_code);
    } else if let Some(signal) = status.signal() {
        println!("the child was terminated by signal {}", signal);
    }
}
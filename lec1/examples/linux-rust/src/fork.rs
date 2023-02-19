use fork::{fork, Fork};
fn main() {
    // keeps the same arguments of course
    match fork() {
       Ok(Fork::Parent(child)) => println!("Continuing execution in parent process, new child has pid: {}", child),
       Ok(Fork::Child) => println!("I'm a new child process"),
       Err(_) => println!("Fork failed"),
    }
}
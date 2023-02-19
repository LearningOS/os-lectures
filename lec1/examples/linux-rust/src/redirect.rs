use fork::{fork, Fork};
use exec::Command;
fn main() {
    let pid = fork();
    if pid == 0 {
        close(1);
        open("output.txt", O_WRONLY | O_CREAT);
        let argv = [ "echo", "this", "is", "redirected", "echo", 0 ];
        exec("echo", argv);
        println!("exec failed!\n");
        exit(1);
    } else {
        wait(0);
    }
}
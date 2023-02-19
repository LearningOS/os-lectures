use std::env;
use std::io::{stdout, Write};

fn main() {
    let args: Vec<String> = env::args().skip(1).collect();

    for (i, arg) in args.iter().enumerate() {
        stdout().write_all(arg.as_bytes()).unwrap();
        if i + 1 < args.len() {
            stdout().write_all(b" ").unwrap();
        } else {
            stdout().write_all(b"\n").unwrap();
        }
    }
}

// - 首先，我们需要导入需要使用的 Rust 库，包括 std::env 和 std::io。std::env 库提供了一个函数 args()，该函数返回一个迭代器，用于访问命令行参数。std::io 库用于进行输入和输出操作。
// - 我们使用 env::args() 获取命令行参数，并使用 skip(1) 跳过第一个参数（程序名称）。然后，我们将所有剩余的参数存储在一个 Vec<String> 类型的向量中。
// - 接下来，我们使用 for 循环迭代向量中的所有参数，并使用 stdout() 函数来输出它们。write_all() 函数用于将参数的字节表示写入标准输出流。如果当前参数不是最后一个参数，则还需要输出一个空格。否则，需要输出一个换行符，以便下一行输出从新的一行开始。
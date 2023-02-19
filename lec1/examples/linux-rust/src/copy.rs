// using read/write to copy input to output.
use std::env;
use std::fs::File;
use std::io::{BufReader, BufWriter, Result, Write, Read};

const BUFSIZE: usize = 512;

fn main() -> Result<()> {
    let args: Vec<String> = env::args().collect();
    if args.len() != 3 {
        eprintln!("usage: copy file1 file2");
        std::process::exit(1);
    }

    // open file1 for reading
    let file1 = File::open(&args[1])?;
    let mut reader = BufReader::new(file1);

    // open/create file2 for writing
    let file2 = File::create(&args[2])?;
    let mut writer = BufWriter::new(file2);

    // copy file1 to file2
    let mut buf = [0u8; BUFSIZE];
    loop {
        let n = reader.read(&mut buf)?;
        if n == 0 {
            break;
        }
        writer.write_all(&buf[..n])?;
    }

    Ok(())
}

// 以下是相应的Rust代码实现，使用了标准库中的File和BufReader/BufWriter来进行文件读写操作：
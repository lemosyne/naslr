use anyhow::{anyhow, Result};
use clap::Parser;
use std::process::Command;

#[derive(Parser)]
struct Args {
    /// Command to run with ASLR disabled
    #[arg(num_args = 0..)]
    command: Vec<String>,
}

fn main() -> Result<()> {
    let args = Args::parse();

    if args.command.len() < 1 {
        return Err(anyhow!("invalid command length"));
    }

    naslr::disable_aslr()?;

    let mut cmd = Command::new(&args.command[0]);
    for arg in args.command.iter().skip(1) {
        cmd.arg(arg);
    }

    let mut child = cmd.spawn()?;
    child.wait()?;

    Ok(())
}

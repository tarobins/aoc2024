use clap::{Arg, Command};

fn main() {
    let matches = Command::new("1_rust")
        .version("1.0")
        .about("A simple program that processes a filename flag")
        .arg(
            Arg::new("filename")
                .long("filename")
                .short('f')
                .value_name("FILE")
                .help("Sets the filename to use")
                .required(false)
        )
        .get_matches();

    if let Some(filename) = matches.get_one::<String>("filename") {
        println!("Filename provided: {}", filename);
    } else {
        println!("No filename provided. Use --filename or -f to specify a file.");
    }
}

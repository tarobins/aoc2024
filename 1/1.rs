use clap::{Arg, Command};
use std::fs;

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
        
        // Construct the file path as <cwd>/1/<filename>
        if let Ok(current_dir) = std::env::current_dir() {
            let file_path = current_dir.join("1").join(filename);
            println!("Attempting to read file: {}", file_path.display());
            
            // Try to read and print the file contents
            match fs::read_to_string(&file_path) {
                Ok(contents) => {
                    println!("File contents:");
                    println!("{}", contents);
                }
                Err(err) => {
                    eprintln!("Error reading file '{}': {}", file_path.display(), err);
                }
            }
        } else {
            eprintln!("Failed to get the current working directory.");
        }
    } else {
        println!("No filename provided. Use --filename or -f to specify a file.");
    }

    // Print the current working directory
    if let Ok(current_dir) = std::env::current_dir() {
        println!("Current working directory: {}", current_dir.display());
    } else {
        eprintln!("Failed to get the current working directory.");
    }
}

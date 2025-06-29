use clap::{Arg, Command};
use std::fs;

// Import the table library
use table_rust::{Table, from_string_with};

fn process(table: &Table<i32>) {
    // Example processing function that could be used later
    // This is just a placeholder for any future logic
    println!("Processing table with {} rows and {} columns", 
             table.row_count(), 
             table.column_count());

    let mut column1: Vec<i32> = vec![];
    let mut column2: Vec<i32> = vec![];
    for row in table {
        if let Some(value) = row.get(0) {
            column1.push(*value);
        }
        if let Some(value) = row.get(1) {
            column2.push(*value);
        }
    }

    let sum: i32 = column1.iter()
        .map(|val| {
            let sim = column2.iter()
                .map(|v| if *v == *val { 1 } else { 0 })
                .sum::<i32>();
            *val * sim
        })
        .sum();
    
    println!("Similarity: {}", sum);   
}

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
                    let table: Table<i32> = from_string_with(&contents, |s| {
                        s.parse().unwrap_or_else(|_| {
                            eprintln!("Warning: Failed to parse '{}' as integer, using 0", s);
                            0
                        })
                    });

                    process(&table);
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
}

use std::fs::File;
use std::io::{BufRead, BufReader};

fn main() {
    let file = File::open("5/test_data.txt").expect("Unable to open the file");
    let reader = BufReader::new(file);

    let mut tuples: Vec<(i32, i32)> = Vec::new();
    let mut vectors: Vec<Vec<i32>> = Vec::new();

    let mut lines = reader.lines();
    let mut processing_tuples = true;

    for line in &mut lines {
        let line = line.expect("Unable to read line");
        if line.is_empty() {
            processing_tuples = false;
            continue;
        }

        if processing_tuples {
            let parts: Vec<&str> = line.split('|').collect();
            let tuple = (
                parts[0].parse().expect("Failed to parse"),
                parts[1].parse().expect("Failed to parse"),
            );
            tuples.push(tuple);
        } else {
            let parts: Vec<i32> = line
                .split(',')
                .map(|s| s.parse().expect("Failed to parse"))
                .collect();
            vectors.push(parts);
        }
    }

    println!("Tuples: {:?}", tuples);
    println!("Vectors: {:?}", vectors);
}
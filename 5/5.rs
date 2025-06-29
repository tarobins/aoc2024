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

    let mut valid_vectors: Vec<Vec<i32>> = Vec::new();
    for vector in &vectors {
        let mut is_vector_valid = true;
        if vector.len() < 2 {
            is_vector_valid = false;
        } else {
            'pair_loop: for i in 0..vector.len() - 1 {
                let current_pair = (vector[i], vector[i + 1]);
                let mut pair_found_in_tuples = false;
                for &tuple in &tuples {
                    if tuple == current_pair {
                        pair_found_in_tuples = true;
                        break;
                    }
                }

                if !pair_found_in_tuples {
                    is_vector_valid = false;
                    break 'pair_loop;
                }
            }
        }

        if is_vector_valid {
            valid_vectors.push(vector.clone());
        }
    }

    println!("Valid Vectors: {:?}", valid_vectors);

    let mut total_sum = 0;
    println!("\nCalculating sum of center elements:");
    for vector in &valid_vectors {
        if !vector.is_empty() {
            let center_index = vector.len() / 2;
            let center_element = vector[center_index];
            println!("  - For vector {:?}, center element is {}, adding to sum.", vector, center_element);
            total_sum += center_element;
        }
    }

    println!("\nTotal sum of center elements: {}", total_sum);
}
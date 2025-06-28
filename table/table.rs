/// A simple table processing library for Advent of Code
/// 
/// This module provides utilities for working with table-like data structures.

/// Represents a simple table row as a vector of strings
pub type TableRow = Vec<String>;

/// Represents a table as a vector of rows
pub type Table = Vec<TableRow>;

/// Creates a new empty table
pub fn new_table() -> Table {
    Vec::new()
}

/// Adds a row to the table
pub fn add_row(table: &mut Table, row: TableRow) {
    table.push(row);
}

/// Gets the number of rows in the table
pub fn row_count(table: &Table) -> usize {
    table.len()
}

/// Gets the number of columns in the first row (assumes rectangular table)
pub fn column_count(table: &Table) -> usize {
    table.first().map_or(0, |row| row.len())
}

/// Parses a line of text into a table row, splitting by whitespace
pub fn parse_line(line: &str) -> TableRow {
    line.split_whitespace().map(|s| s.to_string()).collect()
}

/// Creates a table from a multi-line string
pub fn from_string(input: &str) -> Table {
    input
        .lines()
        .filter(|line| !line.trim().is_empty())
        .map(parse_line)
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_new_table() {
        let table = new_table();
        assert_eq!(table.len(), 0);
    }

    #[test]
    fn test_add_row() {
        let mut table = new_table();
        let row = vec!["hello".to_string(), "world".to_string()];
        add_row(&mut table, row);
        assert_eq!(table.len(), 1);
        assert_eq!(table[0].len(), 2);
    }

    #[test]
    fn test_row_count() {
        let mut table = new_table();
        assert_eq!(row_count(&table), 0);
        
        add_row(&mut table, vec!["a".to_string(), "b".to_string()]);
        assert_eq!(row_count(&table), 1);
        
        add_row(&mut table, vec!["c".to_string(), "d".to_string()]);
        assert_eq!(row_count(&table), 2);
    }

    #[test]
    fn test_column_count() {
        let table = new_table();
        assert_eq!(column_count(&table), 0);
        
        let mut table = new_table();
        add_row(&mut table, vec!["a".to_string(), "b".to_string(), "c".to_string()]);
        assert_eq!(column_count(&table), 3);
    }

    #[test]
    fn test_parse_line() {
        let line = "hello world rust";
        let row = parse_line(line);
        assert_eq!(row, vec!["hello", "world", "rust"]);
        
        let line = "  a   b   c  ";
        let row = parse_line(line);
        assert_eq!(row, vec!["a", "b", "c"]);
    }

    #[test]
    fn test_from_string() {
        let input = "1 2 3\n4 5 6\n\n7 8 9";
        let table = from_string(input);
        assert_eq!(table.len(), 3);
        assert_eq!(table[0], vec!["1", "2", "3"]);
        assert_eq!(table[1], vec!["4", "5", "6"]);
        assert_eq!(table[2], vec!["7", "8", "9"]);
    }

    #[test]
    fn test_empty_input() {
        let table = from_string("");
        assert_eq!(table.len(), 0);
        
        let table = from_string("   \n  \n  ");
        assert_eq!(table.len(), 0);
    }
}

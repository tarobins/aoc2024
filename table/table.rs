/// A simple table processing library for Advent of Code
/// 
/// This module provides utilities for working with table-like data structures.

/// Represents a simple table row as a struct containing a vector of any type
#[derive(Debug, Clone, PartialEq)]
pub struct TableRow<T> {
    pub data: Vec<T>,
}

impl<T> TableRow<T> {
    /// Creates a new empty table row
    pub fn new() -> Self {
        TableRow { data: Vec::new() }
    }

    /// Creates a table row from a vector
    pub fn from_vec(data: Vec<T>) -> Self {
        TableRow { data }
    }

    /// Gets the length of the row
    pub fn len(&self) -> usize {
        self.data.len()
    }

    /// Checks if the row is empty
    pub fn is_empty(&self) -> bool {
        self.data.is_empty()
    }

    /// Adds an element to the row
    pub fn push(&mut self, item: T) {
        self.data.push(item);
    }

    /// Gets an element by index
    pub fn get(&self, index: usize) -> Option<&T> {
        self.data.get(index)
    }

    /// Gets a mutable reference to an element by index
    pub fn get_mut(&mut self, index: usize) -> Option<&mut T> {
        self.data.get_mut(index)
    }

    /// Returns an iterator over the row elements
    pub fn iter(&self) -> std::slice::Iter<T> {
        self.data.iter()
    }

    /// Returns a mutable iterator over the row elements
    pub fn iter_mut(&mut self) -> std::slice::IterMut<T> {
        self.data.iter_mut()
    }

    /// Converts the row into its underlying vector
    pub fn into_vec(self) -> Vec<T> {
        self.data
    }
}

impl<T> std::ops::Index<usize> for TableRow<T> {
    type Output = T;

    fn index(&self, index: usize) -> &Self::Output {
        &self.data[index]
    }
}

impl<T> std::ops::IndexMut<usize> for TableRow<T> {
    fn index_mut(&mut self, index: usize) -> &mut Self::Output {
        &mut self.data[index]
    }
}

impl<T> Default for TableRow<T> {
    fn default() -> Self {
        Self::new()
    }
}

impl<T> From<Vec<T>> for TableRow<T> {
    fn from(data: Vec<T>) -> Self {
        TableRow::from_vec(data)
    }
}

impl<T> Into<Vec<T>> for TableRow<T> {
    fn into(self) -> Vec<T> {
        self.data
    }
}

impl<T> IntoIterator for TableRow<T> {
    type Item = T;
    type IntoIter = std::vec::IntoIter<T>;

    fn into_iter(self) -> Self::IntoIter {
        self.data.into_iter()
    }
}

impl<'a, T> IntoIterator for &'a TableRow<T> {
    type Item = &'a T;
    type IntoIter = std::slice::Iter<'a, T>;

    fn into_iter(self) -> Self::IntoIter {
        self.data.iter()
    }
}

impl<'a, T> IntoIterator for &'a mut TableRow<T> {
    type Item = &'a mut T;
    type IntoIter = std::slice::IterMut<'a, T>;

    fn into_iter(self) -> Self::IntoIter {
        self.data.iter_mut()
    }
}

impl<T> FromIterator<T> for TableRow<T> {
    fn from_iter<I: IntoIterator<Item = T>>(iter: I) -> Self {
        TableRow::from_vec(iter.into_iter().collect())
    }
}

/// Represents a table as a vector of rows
pub type Table<T> = Vec<TableRow<T>>;

/// Creates a new empty table
pub fn new_table<T>() -> Table<T> {
    Vec::new()
}

/// Adds a row to the table
pub fn add_row<T>(table: &mut Table<T>, row: TableRow<T>) {
    table.push(row);
}

/// Gets the number of rows in the table
pub fn row_count<T>(table: &Table<T>) -> usize {
    table.len()
}

/// Gets the number of columns in the first row (assumes rectangular table)
pub fn column_count<T>(table: &Table<T>) -> usize {
    table.first().map_or(0, |row| row.len())
}

/// Parses a line of text into a table row, splitting by whitespace
pub fn parse_line(line: &str) -> TableRow<String> {
    let data = line.split_whitespace().map(|s| s.to_string()).collect();
    TableRow::from_vec(data)
}

/// Creates a table from a multi-line string
pub fn from_string(input: &str) -> Table<String> {
    input
        .lines()
        .filter(|line| !line.trim().is_empty())
        .map(parse_line)
        .collect()
}

/// Parses a line of text into a table row with a custom parser function
pub fn parse_line_with<T, F>(line: &str, parser: F) -> TableRow<T>
where
    F: Fn(&str) -> T,
{
    let data = line.split_whitespace().map(parser).collect();
    TableRow::from_vec(data)
}

/// Creates a table from a multi-line string with a custom parser function
pub fn from_string_with<T, F>(input: &str, parser: F) -> Table<T>
where
    F: Fn(&str) -> T + Copy,
{
    input
        .lines()
        .filter(|line| !line.trim().is_empty())
        .map(|line| parse_line_with(line, parser))
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_new_table() {
        let table: Table<String> = new_table();
        assert_eq!(table.len(), 0);
    }

    #[test]
    fn test_add_row() {
        let mut table: Table<String> = new_table();
        let row = TableRow::from_vec(vec!["hello".to_string(), "world".to_string()]);
        add_row(&mut table, row);
        assert_eq!(table.len(), 1);
        assert_eq!(table[0].len(), 2);
    }

    #[test]
    fn test_row_count() {
        let mut table: Table<String> = new_table();
        assert_eq!(row_count(&table), 0);
        
        add_row(&mut table, TableRow::from_vec(vec!["a".to_string(), "b".to_string()]));
        assert_eq!(row_count(&table), 1);
        
        add_row(&mut table, TableRow::from_vec(vec!["c".to_string(), "d".to_string()]));
        assert_eq!(row_count(&table), 2);
    }

    #[test]
    fn test_column_count() {
        let table: Table<String> = new_table();
        assert_eq!(column_count(&table), 0);
        
        let mut table: Table<String> = new_table();
        add_row(&mut table, TableRow::from_vec(vec!["a".to_string(), "b".to_string(), "c".to_string()]));
        assert_eq!(column_count(&table), 3);
    }

    #[test]
    fn test_parse_line() {
        let line = "hello world rust";
        let row = parse_line(line);
        assert_eq!(row.data, vec!["hello", "world", "rust"]);
        
        let line = "  a   b   c  ";
        let row = parse_line(line);
        assert_eq!(row.data, vec!["a", "b", "c"]);
    }

    #[test]
    fn test_from_string() {
        let input = "1 2 3\n4 5 6\n\n7 8 9";
        let table = from_string(input);
        assert_eq!(table.len(), 3);
        assert_eq!(table[0].data, vec!["1", "2", "3"]);
        assert_eq!(table[1].data, vec!["4", "5", "6"]);
        assert_eq!(table[2].data, vec!["7", "8", "9"]);
    }

    #[test]
    fn test_empty_input() {
        let table = from_string("");
        assert_eq!(table.len(), 0);
        
        let table = from_string("   \n  \n  ");
        assert_eq!(table.len(), 0);
    }

    #[test]
    fn test_generic_table_with_integers() {
        let mut table: Table<i32> = new_table();
        add_row(&mut table, TableRow::from_vec(vec![1, 2, 3]));
        add_row(&mut table, TableRow::from_vec(vec![4, 5, 6]));
        
        assert_eq!(row_count(&table), 2);
        assert_eq!(column_count(&table), 3);
        assert_eq!(table[0].data, vec![1, 2, 3]);
        assert_eq!(table[1].data, vec![4, 5, 6]);
    }

    #[test]
    fn test_parse_line_with_integers() {
        let input = "1 2 3\n4 5 6";
        let table: Table<i32> = from_string_with(input, |s| s.parse().unwrap());
        
        assert_eq!(table.len(), 2);
        assert_eq!(table[0].data, vec![1, 2, 3]);
        assert_eq!(table[1].data, vec![4, 5, 6]);
    }

    #[test]
    fn test_parse_line_with_floats() {
        let input = "1.5 2.7 3.14\n4.0 5.5 6.28";
        let table: Table<f64> = from_string_with(input, |s| s.parse().unwrap());
        
        assert_eq!(table.len(), 2);
        assert_eq!(table[0].data, vec![1.5, 2.7, 3.14]);
        assert_eq!(table[1].data, vec![4.0, 5.5, 6.28]);
    }

    #[test]
    fn test_table_row_methods() {
        let mut row: TableRow<i32> = TableRow::new();
        assert!(row.is_empty());
        assert_eq!(row.len(), 0);
        
        row.push(1);
        row.push(2);
        row.push(3);
        
        assert!(!row.is_empty());
        assert_eq!(row.len(), 3);
        assert_eq!(row.get(0), Some(&1));
        assert_eq!(row.get(1), Some(&2));
        assert_eq!(row.get(2), Some(&3));
        assert_eq!(row.get(3), None);
        
        // Test indexing
        assert_eq!(row[0], 1);
        assert_eq!(row[1], 2);
        assert_eq!(row[2], 3);
        
        // Test mutable access
        *row.get_mut(1).unwrap() = 42;
        assert_eq!(row[1], 42);
        
        row[2] = 100;
        assert_eq!(row[2], 100);
    }

    #[test]
    fn test_table_row_conversions() {
        // Test From/Into Vec
        let vec = vec![1, 2, 3, 4];
        let row: TableRow<i32> = vec.clone().into();
        assert_eq!(row.data, vec);
        
        let back_to_vec: Vec<i32> = row.into();
        assert_eq!(back_to_vec, vec);
        
        // Test from_iter/collect
        let row: TableRow<i32> = (1..=5).collect();
        assert_eq!(row.data, vec![1, 2, 3, 4, 5]);
    }

    #[test]
    fn test_table_row_iterators() {
        let row = TableRow::from_vec(vec![1, 2, 3, 4, 5]);
        
        // Test iter()
        let mut sum = 0;
        for value in row.iter() {
            sum += value;
        }
        assert_eq!(sum, 15);
        
        // Test into_iter() by reference
        let mut sum = 0;
        for value in &row {
            sum += value;
        }
        assert_eq!(sum, 15);
        
        // Test into_iter() consuming
        let sum: i32 = row.into_iter().sum();
        assert_eq!(sum, 15);
    }

    #[test]
    fn test_table_row_mutable_iteration() {
        let mut row = TableRow::from_vec(vec![1, 2, 3]);
        
        // Test iter_mut()
        for value in row.iter_mut() {
            *value *= 2;
        }
        assert_eq!(row.data, vec![2, 4, 6]);
        
        // Test into_iter() mutable
        for value in &mut row {
            *value += 1;
        }
        assert_eq!(row.data, vec![3, 5, 7]);
    }
}

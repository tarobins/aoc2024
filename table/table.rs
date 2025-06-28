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

/// Represents a table as a struct containing a vector of rows
#[derive(Debug, Clone, PartialEq)]
pub struct Table<T> {
    pub rows: Vec<TableRow<T>>,
}

impl<T> Table<T> {
    /// Creates a new empty table
    pub fn new() -> Self {
        Table { rows: Vec::new() }
    }

    /// Creates a table from a vector of rows
    pub fn from_rows(rows: Vec<TableRow<T>>) -> Self {
        Table { rows }
    }

    /// Adds a row to the table
    pub fn add_row(&mut self, row: TableRow<T>) {
        self.rows.push(row);
    }

    /// Gets the number of rows in the table
    pub fn row_count(&self) -> usize {
        self.rows.len()
    }

    /// Gets the number of columns in the first row (assumes rectangular table)
    pub fn column_count(&self) -> usize {
        self.rows.first().map_or(0, |row| row.len())
    }

    /// Gets the number of rows (alias for row_count for consistency with Vec)
    pub fn len(&self) -> usize {
        self.rows.len()
    }

    /// Checks if the table is empty
    pub fn is_empty(&self) -> bool {
        self.rows.is_empty()
    }

    /// Gets a row by index
    pub fn get_row(&self, index: usize) -> Option<&TableRow<T>> {
        self.rows.get(index)
    }

    /// Gets a mutable reference to a row by index
    pub fn get_row_mut(&mut self, index: usize) -> Option<&mut TableRow<T>> {
        self.rows.get_mut(index)
    }

    /// Gets an element at the specified row and column
    pub fn get(&self, row: usize, col: usize) -> Option<&T> {
        self.rows.get(row)?.get(col)
    }

    /// Gets a mutable reference to an element at the specified row and column
    pub fn get_mut(&mut self, row: usize, col: usize) -> Option<&mut T> {
        self.rows.get_mut(row)?.get_mut(col)
    }

    /// Returns an iterator over the rows
    pub fn iter(&self) -> std::slice::Iter<TableRow<T>> {
        self.rows.iter()
    }

    /// Returns a mutable iterator over the rows
    pub fn iter_mut(&mut self) -> std::slice::IterMut<TableRow<T>> {
        self.rows.iter_mut()
    }

    /// Converts the table into its underlying vector of rows
    pub fn into_rows(self) -> Vec<TableRow<T>> {
        self.rows
    }

    /// Removes and returns the last row, or None if empty
    pub fn pop_row(&mut self) -> Option<TableRow<T>> {
        self.rows.pop()
    }

    /// Inserts a row at the specified index
    pub fn insert_row(&mut self, index: usize, row: TableRow<T>) {
        self.rows.insert(index, row);
    }

    /// Removes and returns the row at the specified index
    pub fn remove_row(&mut self, index: usize) -> TableRow<T> {
        self.rows.remove(index)
    }

    /// Clears all rows from the table
    pub fn clear(&mut self) {
        self.rows.clear();
    }
}

impl<T> std::ops::Index<usize> for Table<T> {
    type Output = TableRow<T>;

    fn index(&self, index: usize) -> &Self::Output {
        &self.rows[index]
    }
}

impl<T> std::ops::IndexMut<usize> for Table<T> {
    fn index_mut(&mut self, index: usize) -> &mut Self::Output {
        &mut self.rows[index]
    }
}

impl<T> Default for Table<T> {
    fn default() -> Self {
        Self::new()
    }
}

impl<T> From<Vec<TableRow<T>>> for Table<T> {
    fn from(rows: Vec<TableRow<T>>) -> Self {
        Table::from_rows(rows)
    }
}

impl<T> Into<Vec<TableRow<T>>> for Table<T> {
    fn into(self) -> Vec<TableRow<T>> {
        self.rows
    }
}

impl<T> IntoIterator for Table<T> {
    type Item = TableRow<T>;
    type IntoIter = std::vec::IntoIter<TableRow<T>>;

    fn into_iter(self) -> Self::IntoIter {
        self.rows.into_iter()
    }
}

impl<'a, T> IntoIterator for &'a Table<T> {
    type Item = &'a TableRow<T>;
    type IntoIter = std::slice::Iter<'a, TableRow<T>>;

    fn into_iter(self) -> Self::IntoIter {
        self.rows.iter()
    }
}

impl<'a, T> IntoIterator for &'a mut Table<T> {
    type Item = &'a mut TableRow<T>;
    type IntoIter = std::slice::IterMut<'a, TableRow<T>>;

    fn into_iter(self) -> Self::IntoIter {
        self.rows.iter_mut()
    }
}

impl<T> FromIterator<TableRow<T>> for Table<T> {
    fn from_iter<I: IntoIterator<Item = TableRow<T>>>(iter: I) -> Self {
        Table::from_rows(iter.into_iter().collect())
    }
}

/// Creates a new empty table (deprecated - use Table::new() instead)
pub fn new_table<T>() -> Table<T> {
    Table::new()
}

/// Adds a row to the table (deprecated - use table.add_row() instead)
pub fn add_row<T>(table: &mut Table<T>, row: TableRow<T>) {
    table.add_row(row);
}

/// Gets the number of rows in the table (deprecated - use table.row_count() instead)
pub fn row_count<T>(table: &Table<T>) -> usize {
    table.row_count()
}

/// Gets the number of columns in the first row (deprecated - use table.column_count() instead)
pub fn column_count<T>(table: &Table<T>) -> usize {
    table.column_count()
}

/// Parses a line of text into a table row, splitting by whitespace
pub fn parse_line(line: &str) -> TableRow<String> {
    let data = line.split_whitespace().map(|s| s.to_string()).collect();
    TableRow::from_vec(data)
}

/// Creates a table from a multi-line string
pub fn from_string(input: &str) -> Table<String> {
    let rows: Vec<TableRow<String>> = input
        .lines()
        .filter(|line| !line.trim().is_empty())
        .map(parse_line)
        .collect();
    Table::from_rows(rows)
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
    let rows: Vec<TableRow<T>> = input
        .lines()
        .filter(|line| !line.trim().is_empty())
        .map(|line| parse_line_with(line, parser))
        .collect();
    Table::from_rows(rows)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_new_table() {
        let table: Table<String> = new_table();
        assert_eq!(table.len(), 0);
        
        let table: Table<String> = Table::new();
        assert_eq!(table.len(), 0);
        assert!(table.is_empty());
    }

    #[test]
    fn test_add_row() {
        let mut table: Table<String> = new_table();
        let row = TableRow::from_vec(vec!["hello".to_string(), "world".to_string()]);
        add_row(&mut table, row);
        assert_eq!(table.len(), 1);
        assert_eq!(table[0].len(), 2);
        
        // Test new method
        let mut table: Table<String> = Table::new();
        let row = TableRow::from_vec(vec!["hello".to_string(), "world".to_string()]);
        table.add_row(row);
        assert_eq!(table.len(), 1);
        assert_eq!(table[0].len(), 2);
    }

    #[test]
    fn test_row_count() {
        let mut table: Table<String> = new_table();
        assert_eq!(row_count(&table), 0);
        assert_eq!(table.row_count(), 0);
        
        add_row(&mut table, TableRow::from_vec(vec!["a".to_string(), "b".to_string()]));
        assert_eq!(row_count(&table), 1);
        assert_eq!(table.row_count(), 1);
        
        table.add_row(TableRow::from_vec(vec!["c".to_string(), "d".to_string()]));
        assert_eq!(table.row_count(), 2);
    }

    #[test]
    fn test_column_count() {
        let table: Table<String> = new_table();
        assert_eq!(column_count(&table), 0);
        assert_eq!(table.column_count(), 0);
        
        let mut table: Table<String> = Table::new();
        table.add_row(TableRow::from_vec(vec!["a".to_string(), "b".to_string(), "c".to_string()]));
        assert_eq!(table.column_count(), 3);
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
        let mut table: Table<i32> = Table::new();
        table.add_row(TableRow::from_vec(vec![1, 2, 3]));
        table.add_row(TableRow::from_vec(vec![4, 5, 6]));
        
        assert_eq!(table.row_count(), 2);
        assert_eq!(table.column_count(), 3);
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

    #[test]
    fn test_table_methods() {
        let mut table: Table<i32> = Table::new();
        assert!(table.is_empty());
        assert_eq!(table.len(), 0);
        assert_eq!(table.row_count(), 0);
        assert_eq!(table.column_count(), 0);
        
        // Add some rows
        table.add_row(TableRow::from_vec(vec![1, 2, 3]));
        table.add_row(TableRow::from_vec(vec![4, 5, 6]));
        table.add_row(TableRow::from_vec(vec![7, 8, 9]));
        
        assert!(!table.is_empty());
        assert_eq!(table.len(), 3);
        assert_eq!(table.row_count(), 3);
        assert_eq!(table.column_count(), 3);
        
        // Test element access
        assert_eq!(table.get(0, 0), Some(&1));
        assert_eq!(table.get(1, 2), Some(&6));
        assert_eq!(table.get(2, 1), Some(&8));
        assert_eq!(table.get(3, 0), None); // Out of bounds
        assert_eq!(table.get(0, 3), None); // Out of bounds
        
        // Test row access
        assert_eq!(table.get_row(0).unwrap().data, vec![1, 2, 3]);
        assert_eq!(table.get_row(2).unwrap().data, vec![7, 8, 9]);
        assert!(table.get_row(3).is_none());
        
        // Test indexing
        assert_eq!(table[0].data, vec![1, 2, 3]);
        assert_eq!(table[1].data, vec![4, 5, 6]);
    }

    #[test]
    fn test_table_conversions() {
        // Test From/Into Vec<TableRow<T>>
        let rows = vec![
            TableRow::from_vec(vec![1, 2]),
            TableRow::from_vec(vec![3, 4]),
        ];
        let table: Table<i32> = rows.clone().into();
        assert_eq!(table.rows, rows);
        
        let back_to_rows: Vec<TableRow<i32>> = table.into();
        assert_eq!(back_to_rows, rows);
        
        // Test from_iter/collect
        let table: Table<i32> = (0..3)
            .map(|i| TableRow::from_vec(vec![i, i + 1, i + 2]))
            .collect();
        assert_eq!(table.len(), 3);
        assert_eq!(table[0].data, vec![0, 1, 2]);
        assert_eq!(table[2].data, vec![2, 3, 4]);
    }

    #[test]
    fn test_table_iterators() {
        let table = Table::from_rows(vec![
            TableRow::from_vec(vec![1, 2]),
            TableRow::from_vec(vec![3, 4]),
            TableRow::from_vec(vec![5, 6]),
        ]);
        
        // Test iter()
        let mut sum = 0;
        for row in table.iter() {
            for value in row.iter() {
                sum += value;
            }
        }
        assert_eq!(sum, 21); // 1+2+3+4+5+6
        
        // Test into_iter() by reference
        let mut sum = 0;
        for row in &table {
            for value in row {
                sum += value;
            }
        }
        assert_eq!(sum, 21);
        
        // Test into_iter() consuming
        let sum: i32 = table.into_iter()
            .flat_map(|row| row.into_iter())
            .sum();
        assert_eq!(sum, 21);
    }

    #[test]
    fn test_table_mutable_operations() {
        let mut table = Table::from_rows(vec![
            TableRow::from_vec(vec![1, 2]),
            TableRow::from_vec(vec![3, 4]),
        ]);
        
        // Test mutable element access
        *table.get_mut(0, 1).unwrap() = 42;
        assert_eq!(table.get(0, 1), Some(&42));
        
        // Test mutable row access
        table.get_row_mut(1).unwrap().push(5);
        assert_eq!(table[1].data, vec![3, 4, 5]);
        
        // Test mutable indexing
        table[0][0] = 100;
        assert_eq!(table[0][0], 100);
        
        // Test mutable iteration
        for row in &mut table {
            for value in row {
                *value *= 2;
            }
        }
        assert_eq!(table[0].data, vec![200, 84]); // 100*2, 42*2
        assert_eq!(table[1].data, vec![6, 8, 10]); // 3*2, 4*2, 5*2
    }

    #[test]
    fn test_table_modification_methods() {
        let mut table: Table<i32> = Table::new();
        
        // Test add_row and pop_row
        table.add_row(TableRow::from_vec(vec![1, 2]));
        table.add_row(TableRow::from_vec(vec![3, 4]));
        assert_eq!(table.len(), 2);
        
        let popped = table.pop_row().unwrap();
        assert_eq!(popped.data, vec![3, 4]);
        assert_eq!(table.len(), 1);
        
        // Test insert_row and remove_row
        table.insert_row(0, TableRow::from_vec(vec![10, 11]));
        assert_eq!(table.len(), 2);
        assert_eq!(table[0].data, vec![10, 11]);
        assert_eq!(table[1].data, vec![1, 2]);
        
        let removed = table.remove_row(0);
        assert_eq!(removed.data, vec![10, 11]);
        assert_eq!(table.len(), 1);
        assert_eq!(table[0].data, vec![1, 2]);
        
        // Test clear
        table.clear();
        assert_eq!(table.len(), 0);
        assert!(table.is_empty());
    }
}

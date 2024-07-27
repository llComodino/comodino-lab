use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines (filename: &str) -> Vec<String> {
    let mut lines = Vec::new();
    let file = File::open(filename).expect("file not found");
    let buf = BufReader::new(file);
    for line in buf.lines() {
        lines.push(line.expect("could not parse line"));
    }
    lines
}

fn main () {

    let lines = read_lines("short_input.txt");

    let mut i = 0;
    for line in &lines {

        if line.len() != 5 {
            continue;
        }
        
        let mut j = 0;
        for line2 in &lines {
            
            if line2.len() != 5 {
                continue;
            }
        
            if i == j {
                j += 1;
                continue;
            }
            
            let mut diff = 0;
            let mut k = 0;
            
            for c in line.chars() {
                if c != line2.chars().nth(k).unwrap() {
                    diff += 1;
                }
                k += 1;
            }
            
            if diff == 1 {
                println!("{} {}", line, line2);
            }
            
            j += 1;
        
        }
        
        i += 1;

    }
}

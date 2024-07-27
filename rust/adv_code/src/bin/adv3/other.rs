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

    let lines = read_lines("input.txt");

    let mut vec0 = vec![0_u32; 12];
    let mut vec1 = vec![0_u32; 12];
    let mut vec2 = vec![0_u32; 12];

    for line in &lines {

        if line.len() != 12 {
            continue;
        }

        for (i, c) in line.chars().enumerate() {
            match c { 
                '0' => vec1[i] += 1,
                '1' => vec2[i] += 1,
                _ => (),
            }
        }
    }

    // Find the most common digit in each position
    for x in 0..12 {
        if vec1[x] > vec2[x] {
            vec0[x] = 0;
        } else if vec1[x] < vec2[x] {
            vec0[x] = 1;
        } else {
            vec0[x] = 2;
        }
    }

    for i in 0..12 {
        
        match vec0[i] {
            
            0 => {
                vec1[i] = 0;
                vec2[i] = 1;
            },

            1 => {
                vec1[i] = 1;
                vec2[i] = 0;
            },

            2 => {
                vec1[i] = 1;
                vec2[i] = 0;
            },

            _ => (),
        }
    }


    // Find line with most corresponding digits to vec1
    let mut max = 0;
    let mut max_line = 0;

    for (i, line) in lines.iter().enumerate() {

        let mut count = 0;

        for (j, c) in line.chars().enumerate() {
            
            if c.to_digit(10).unwrap() == vec1[j] {
                count += 1;
            } else {
                break;
            }
            println!("{} {}", line, count);
        }

        if count > max {
            max = count;
            max_line = i;
        }
    }

    println!("Line: {}", lines[max_line]);

    // Convert line to decimal
    let mut line1_dec : u32 = 0;

    for (i, c) in lines[max_line].chars().enumerate() {
        line1_dec += c.to_digit(10).unwrap() * 2_u32.pow(11 - i as u32);
    }

    // Find line with most corresponding digits to vec2
    max = 0;
    max_line = 0;

    for (i, line) in lines.iter().enumerate() {

        let mut count = 0;

        for (j, c) in line.chars().enumerate() {
            
            if c.to_digit(10).unwrap() == vec2[j] {
                count += 1;
            } else {
                break;
            }
            println!("{} {}", line, count);
        }

        if count > max {
            max = count;
            max_line = i;
        }
    }

    println!("Line: {}", lines[max_line]);
 
    // Convert line to decimal
    let mut line2_dec : u32 = 0;

    for (i, c) in lines[max_line].chars().enumerate() {
        line2_dec += c.to_digit(10).unwrap() * 2_u32.pow(11 - i as u32);
    }

    println!("vec1: {:?}", vec1);
    println!("vec2: {:?}", vec2);
    
    println!("Consupion: {}", line1_dec * line2_dec);
}

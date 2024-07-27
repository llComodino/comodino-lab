use std::fs::File;
use std::io::*;

fn read_lines<P>(filename: P) -> std::io::Result<std::io::Lines<BufReader<File>>>
where
    P: AsRef<std::path::Path>,
{
    let file = File::open(filename)?;
    Ok(BufReader::new(file).lines())
}

fn main() {
    let contents = read_lines("input.txt").expect("Error reading file");

    let mut x: i32 = 0;
    let mut depth: i32 = 0;
    let mut aim: i32 = 0;

    for line in contents {
        if let Ok(data) = line {
            let values: Vec<&str> = data.split(' ').collect();

            match values.len() {
                2 => {
                    let strdata = values[0];
                    let intdata = values[1].parse::<i32>().expect("Not an integer");

                    match strdata {
                        "forward" => {
                            x += intdata;
                            depth += intdata * aim;
                        }

                        "up" => aim -= intdata,
                        "down" => aim += intdata,

                        _ => panic!("Error"),
                    }
                }
                _ => panic!("Invalid input line {}", data),
            };
        }
    }

    let tot: i32 = x * depth;
    println!("Total: {}", tot);
}

use std::fs::File;
use std::io::Read;
use std::ops::Deref;

trait OptionDeref<T: Deref> {
    fn as_deref(&self) -> Option<&T::Target>;
}

impl<T: Deref> OptionDeref<T> for Option<T> {
    fn as_deref(&self) -> Option<&T::Target> {
        self.as_ref().map(Deref::deref)
    }
}

fn compare(x: i32, y: i32) -> bool {
    if x < y {
        return true;
    }

    false
}

fn main() {
    let mut file = File::open("input.txt").unwrap();

    let mut contents = String::new();
    file.read_to_string(&mut contents).unwrap();

    let str_contents = contents.as_str();

    let mut grater: i32 = 0;

    let mut a: i32 = 0;
    let mut b: i32 = 0;
    let mut c: i32 = 0;

    let mut i = 0;
    for line in str_contents.lines() {
        i += 1;

        let line = line.parse::<i32>().unwrap();

        if i < 3 {
            match i % 3 {
                1 => {
                    a += line;
                    b += line;
                }

                2 => a += line,

                _ => println!("Error"),
            }
        } else {
            match i % 3 {
                0 => {
                    a += line;
                    b += line;

                    if i > 3 {
                        if compare(c, a) {
                            grater += 1;
                        }

                        c = 0;
                        c += line;
                    } else {
                        c += line;
                    }
                }

                1 => {
                    b += line;
                    c += line;

                    if compare(a, b) {
                        grater += 1;
                    }

                    a = 0;
                    a += line;
                }

                2 => {
                    a += line;
                    c += line;

                    if compare(b, c) {
                        grater += 1;
                    }

                    b = 0;
                    b += line;
                }

                _ => println!("Error"),
            }
        }
    }

    print!("{}", grater);
}

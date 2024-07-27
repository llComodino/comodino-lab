#![allow(unused)]
use std::io::{Read,Write};
use std::net::{TcpListener, TcpStream};
use http_request_parser::{Request, Response};

fn main() {
    
    let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();
    
    println!("Connected to the server!\n");
    println!("1. Login");
    println!("2. Register");
    println!("3. Exit");
    print!("> ");

    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let input = input.trim();

    match input {

        "1" => {
            println!("Enter your username: ");
            let mut username = String::new();
            std::io::stdin().read_line(&mut username).unwrap();
            let username = username.trim();

            println!("Enter your password: ");
            let mut password = String::new();
            std::io::stdin().read_line(&mut password).unwrap();
            let password = password.trim();

            let request = "POST /login HTTP/1.1\r\nHost:".to_string();
            let mut buffer = [0; 512];

            stream.write(request.as_bytes()).unwrap();
            stream.read(&mut buffer).unwrap();
            
            let response = String::from_utf8_lossy(&buffer);

            println!("{}", response);
        },
        
        "2" => {
            println!("Enter your username: ");
            let mut username = String::new();
            std::io::stdin().read_line(&mut username).unwrap();
            let username = username.trim();

            println!("Enter your password: ");
            let mut password = String::new();
            std::io::stdin().read_line(&mut password).unwrap();
            let password = password.trim();

            let request = "POST /register HTTP/1.1\r\nHost:".to_string();
            let mut buffer = [0; 512];

            stream.write(request.to_string().as_bytes()).unwrap();
            stream.read(&mut buffer).unwrap();

            let response_b = String::from_utf8_lossy(&buffer);

            println!("{}", response_b);
        },
        
        "3" => {
            println!("Exiting...");
            std::process::exit(0);
        },
        
        _ => {
            println!("Invalid input!");
            std::process::exit(0);
        }
    }
}

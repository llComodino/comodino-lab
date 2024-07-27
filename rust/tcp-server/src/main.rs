#![allow(dead_code)]
#![allow(unused_imports)]

use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};

use http_request_parser::{Request, Response};

fn handle_client(mut stream: TcpStream) {
    
    let mut buffer = [0; 512];
    
    stream.read(&mut buffer).expect("Error reading stream");

    let request = String::from_utf8_lossy(&buffer[..]);
    println!("Request: {}", request);

    
    let response = "HTTP/1.1 200 OK\r\n\r\nHello, world!";
    stream.write(response.as_bytes()).expect("Error writing response");
}

fn main() {
    
    let listener = TcpListener::bind("127.0.0.1:8080").expect("Error binding to port 8080");
    println!("Listening on port 8080");
 
     for stream in listener.incoming(){
        let tcp_stream = stream.unwrap();

        let request = Request::from(&tcp_stream);

        println!("Request: {:?}", request);

        let mut response = Response::new();

        if request.path == "/" {
            response.body = "Hello, World!".to_owned();
        } else {
            response.headers = vec!["Content-Type: application/json".to_owned()];
            response.body = format!("{{\n\t\"actualPath\":\"{}\"\n}}", request.path);
        }
        response.send(&tcp_stream)
    }
}

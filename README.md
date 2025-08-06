# myHTTP: A Simple C Web Server

## Overview

`myHTTP` is a lightweight web server implemented in C, designed to handle HTTP requests and serve static files, as well as dynamic content through FastCGI (specifically PHP-CGI). It leverages `epoll` for efficient I/O multiplexing, allowing it to manage multiple client connections concurrently. The project aims to provide a foundational understanding of how web servers operate at a low level.

## Features

*   **HTTP Request Handling:** Parses incoming HTTP GET and POST requests.
*   **Static File Serving:** Serves static HTML, CSS, JavaScript, and image files.
*   **Dynamic Content with PHP-CGI:** Integrates with PHP-CGI to process and serve dynamic PHP pages.
*   **Non-blocking I/O:** Utilizes `epoll` for efficient handling of multiple client connections.
*   **Modular Design:** Includes a custom `libft` library for common utility functions.

## Installation and Setup

To build and run `myHTTP`, you will need a C compiler (like GCC) and `make`.

### Prerequisites

*   `gcc` (GNU Compiler Collection)
*   `make`
*   `php-cgi` (for dynamic PHP content)

### Building the Project

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/your-username/myHTTP.git
    cd myHTTP
    ```
    *(Note: Replace `https://github.com/your-username/myHTTP.git` with the actual repository URL if it's different.)*

2.  **Install build essentials (if not already installed):**
    ```bash
    sudo apt-get update
    sudo apt-get install -y build-essential
    ```

3.  **Install PHP-CGI:**
    ```bash
    sudo apt-get install -y php-cgi
    ```

4.  **Compile the project:**
    ```bash
    make
    ```
    This command will compile the main server executable and the `libft` library.

## Usage

To start the `myHTTP` server, navigate to the project root directory and run the compiled executable:

```bash
./server
```

The server will listen on port `7777` by default. You can then access it from your web browser at `http://localhost:7777`.

### Example Endpoints:

*   **Static HTML:** `http://localhost:7777/index.html` (or any other static file in the `templates` directory)
*   **PHP Script:** `http://localhost:7777/your_script.php` (assuming `your_script.php` is in the web root and handled by PHP-CGI)

## Project Structure

```
myHTTP/
├── Makefile              # Build instructions
├── main.c                # Main server entry point
├── inc/                  # Header files
│   ├── fcgi.h
│   ├── get_next_line.h
│   └── http.h
├── libft/                # Custom utility library
│   ├── Makefile
│   ├── libft.h
│   └── ... (source files for libft functions)
├── src/                  # Server source files
│   ├── body_parser.c
│   ├── epoll_setup.c
│   ├── get_next_line.c
│   ├── get_next_line_utils.c
│   ├── parser.c
│   ├── php_handler.c
│   ├── process.c
│   ├── reader.c
│   ├── response.c
│   ├── server_setup.c
│   └── tree.c
└── fcgi/                 # FastCGI related source files
    ├── fcgi.c
    ├── helpers.c
    └── php_cgi.c
```

## Known Issues and Limitations


Based on a comprehensive code analysis, the `myHTTP` project has several areas that require attention for improved stability, security, and performance. Key issues include:

*   **Security Vulnerabilities:(Working on this at the moment)**
    *   **Injection Risks:** Potential for Path Traversal and Command Injection due to insufficient input validation and sanitization, especially concerning URL handling and PHP-CGI interaction.
    *   **Broken Authentication/Session Management:** Lack of secure cookie handling mechanisms makes the server vulnerable to session hijacking and CSRF.
    *   **Cross-Site Scripting (XSS):** Insufficient output encoding can lead to reflected XSS vulnerabilities.
    *   **Insecure Design:** Fixed-size buffers for form data can lead to buffer overflows, and the extensive use of global state (`serv` struct) complicates concurrency and testing.
      
## Contributing

Contributions are welcome! If you find a bug or have an idea for an improvement, please open an issue or submit a pull request. Please ensure your code adheres to the project's coding style and includes appropriate tests.



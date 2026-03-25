# Banking-Server
High-performance C++ TCP banking server using epoll, multithreading (thread pool), and thread-safe transaction processing. Demonstrates system-level backend engineering, concurrency, and networking.
#  C++ High-Performance Banking Server

A production-style **C++ backend system** demonstrating high-performance networking, multithreading, and system-level programming using `epoll`.

---

##  Overview

This project implements a **TCP banking server** capable of handling multiple concurrent clients efficiently using:

*  `epoll` for scalable I/O
*  Thread pool for concurrency
*  Mutex for thread safety
*  Logging system
*  File-based persistence

It simulates real backend operations such as balance checks and money transfers.

---

##  Architecture

###  Core Components

* **Server (epoll-based)**

  * Handles incoming TCP connections
  * Uses `epoll` for non-blocking I/O

* **Thread Pool**

  * Reuses worker threads
  * Avoids overhead of thread creation

* **Client Handler**

  * Processes client requests
  * Communicates with database layer

* **Database (Singleton)**

  * Stores account balances
  * Thread-safe using mutex

* **Logger**

  * Logs requests and server activity

---

###  Flow

1. Client connects via TCP
2. `epoll` detects incoming data
3. Task is submitted to thread pool
4. Request is processed safely
5. Response is sent back to client

---

##  Tech Stack

* C++17
* Linux sockets (TCP)
* epoll (I/O multiplexing)
* Multithreading (std::thread)
* Synchronization (std::mutex)
* CMake

---

##  Commands (API via TCP)

Connect using:

```bash
telnet localhost 8080
```

---

###  Check Balance

```
BALANCE user1
```

---

###  Transfer Money

```
TRANSFER user1 user2 100
```

---

###  Responses

```
1000
OK
INSUFFICIENT
```

---

## 📸 Example Usage

---

##  How to Run

### 1. Build

```bash
mkdir build
cd build
cmake ..
make
```

---

### 2. Run

```bash
./server
```

---

### 3. Test

```bash
telnet localhost 8080
```

---

##  Features Demonstrated

* High-performance networking with `epoll`
* Thread pool design pattern
* Thread-safe shared state
* Basic persistence
* Clean modular architecture

---

##  Why This Project Matters

This project demonstrates:

* Backend system design
* Concurrent programming
* Networking fundamentals
* Performance-oriented C++ development

 Relevant for roles in:

* Telecom (e.g. Vivacom)
* Backend systems
* High-performance services

---

---

##  Final Note

This project is built to demonstrate **real-world backend engineering skills in C++**, focusing on performance, concurrency, and system-level design.

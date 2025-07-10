# 🚆 SmartRail: Efficient Railway Booking System

[![C++](https://img.shields.io/badge/Language-C++-blue.svg)](https://isocpp.org)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Active-brightgreen)]()

SmartRail is a console-based Railway Booking System written in **C++**, designed with performance in mind. It utilizes efficient data structures like **vectors** and **hash maps (unordered_map)** to optimize **time and space complexity**, making operations like ticket booking, cancellation, and user login highly responsive.

---

## 🚀 Features

- 🛤️ **Train Initialization** – Generates 50 dynamic train entries with random routes and timings.
- 👤 **User Registration & Login** – Secure login and user profile management with hash map storage.
- 🎟️ **Ticket Booking & Cancellation** – Book or cancel tickets using train IDs with real-time seat tracking.
- 🔍 **Search Trains** – Search trains by **source** and **destination**.
- 📜 **View Booked Tickets** – View tickets booked by the currently logged-in user.
- 🔐 **User Profile Update** – Update email and password from the dashboard.
- 🧠 **Shortest Path Suggestion** – Uses **Dijkstra’s algorithm** to find the best route between stations.

---

## 🧠 Time & Space Complexity Analysis

| Operation               | Time Complexity | Space Complexity |
|------------------------|------------------|------------------|
| Train Initialization   | O(n)             | O(n)             |
| Display/Search Trains  | O(n)             | -                |
| Reserve Ticket         | O(n) + O(1)      | O(m)             |
| Cancel Ticket          | O(1)             | -                |
| Edit Ticket            | O(1)             | -                |
| User Auth/Register     | O(1)             | O(u)             |
| **Total**              | -                | O(n + m + u)     |

- `n`: number of trains  
- `m`: number of tickets  
- `u`: number of users

---

## 🔧 Tech Stack

- **Language**: C++
- **Data Structures**: `vector`, `unordered_map`
- **Algorithms**: Dijkstra’s Algorithm (Shortest Path)

---

## 🛠️ How to Run

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/SmartRail.git
   cd SmartRail

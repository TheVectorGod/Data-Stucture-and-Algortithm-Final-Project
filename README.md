# Digital Lost and Found Bulletin

A lightweight, terminal-based C++ application designed to help users report lost or found items and automatically find potential matches between reports.

## 🚀 Features

*   **Report Lost/Found Items:** Categorize items by name, location, and description.
*   **Automated Matching:** The system logic identifies potential matches when a "Found" report shares similarities with a "Lost" report.
*   **Persistent Storage:** Uses JSON to save data, ensuring your reports are still there even after closing the program.
*   **Item Search:** Quickly filter through the bulletin using keywords.

---

## 🛠️ Tech Stack

*   **Language:** C++11 or higher
*   **Data Format:** JSON
*   **Library:** [nlohmann/json](https://github.com/nlohmann/json) (Modern JSON for C++)

---

## 📦 Prerequisites

Before running this project, ensure you have:
1.  A C++ compiler (GCC/Clang/MSVC).
2.  The `json.hpp` header file in your project directory (available from the [nlohmann/json](https://github.com/nlohmann/json/releases) repository).

---

## 🏗️ Installation & Setup

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/your-username/lost-and-found-bulletin.git](https://github.com/your-username/lost-and-found-bulletin.git)
    cd lost-and-found-bulletin
    ```

2.  **Ensure dependencies are present:**
    Place `json.hpp` in the same directory as your `.cpp` file.

3.  **Compile the program:**
    Using g++:
    ```bash
    g++ -o bulletin main.cpp
    ```

4.  **Run the application:**
    ```bash
    ./bulletin
    ```

---

## 📋 How It Works

### The Data Model
Each item is stored in an `unordered_map` and saved into a `data.json` file. 

### Matching Logic
The program automatically triggers a match check whenever a new item is added. It compares:
*   **Item Name** or **Description**
*   **Report Type** (Ensures a 'Lost' item only matches with a 'Found' item)

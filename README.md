# EventPlanner

A simple event management application built with an Angular frontend and a C++/Crow backend. This project allows users to create, read, update, and delete events.

## Features

*   **CRUD Operations:** Full functionality to manage events.
*   **Real-time Filtering:** A search bar to filter events by title as you type.
*   **Event Grouping:** Visual grouping of events by date (e.g., "Past", "Today", "Future"). *(More grouping options will be added in the upcoming versions)*

## Tech Stack

*   **Frontend:** [Angular](https://angular.io/)
*   **Backend:** C++
*   **REST API:** [Crow C++ Microframework](https://crowcpp.org/)
*   **Planned Desktop App:** [Electron](https://www.electronjs.org/)

## Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

*   Node.js and npm
*   A C++ compiler (like GCC)
*   CMake

### Installation

1.  **Clone the repo**
    ```sh
    git clone https://github.com/pterodactylstfw/EventPlanner.git
    ```
2.  **Frontend Setup**
    *   Navigate into frontend/ and install dependencies.
    ```sh
    cd frontend/
    npm install
    ```
3.  **Backend Setup**
    *   Aici descrie pașii pentru a compila și rula backend-ul C++. De exemplu:
    ```sh
    cd backend/
    mkdir build
    cd build
    cmake ..
    make
    ./EventPlannerApi
    ```

## Usage

You can use the application in 2 ways: using either CLI (missing features from the web version), or GUI version.

**Using EventPlanner with CLI**
**Run the ./EventPlanner, found in build/ folder.**

**Using EventPlanner with GUI**

1.  **Run the Backend Server**
    *   Run the ./EventPlannerApi found in /build folder.
    ```sh
    cd build/
    ./EventPlannerAPi
    # backend server will run at http://localhost:18080.
    # If you want to see all the events in .JSON, go to http://localhost:18080/events.
    ```
2.  **Run the Frontend Application**
    *   Run Angular development server.
    ```sh
    # from the frontend folder
    cd frontend/
    ng serve
    ```
3.  Open your browser and navigate to `http://localhost:4200/`.

## License

Distributed under the MIT License. See `LICENSE` for more information.

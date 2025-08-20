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
* A C++ compiler (like GCC or Clang)
*   CMake

### Installation

1.  **Clone the repo**
    ```sh
    git clone https://github.com/pterodactylstfw/EventPlanner.git
    cd EventPlanner
    ```
2. **Backend Setup**
    * Compile the C++ backend. This will create two executables: `EventPlannerApi` (the web server) and `EventPlanner` (
      the CLI version).
    ```sh
    cd backend/
    mkdir build
    cd build
    cmake ..
    make
    ```
3. **Frontend Setup**
    * Navigate to the frontend directory and install npm dependencies.
   ```sh
   # From the root project folder
   cd ../../frontend/
   npm install
   ```

## Usage

The application can be run in two modes: with a full graphical user interface (GUI) or as a command-line interface (
CLI).

### Web Application (GUI)

To use the web version, you need to run both the backend server and the frontend application.

1.  **Run the Backend Server**
    * From the `backend/build` directory, run the API executable. The server will start on `http://localhost:18080`.
    ```sh
    # From the backend/build/ directory
    ./EventPlannerApi
    ```
2.  **Run the Frontend Application**
    * In a new terminal, navigate to the `frontend` directory and start the Angular development server.
    ```sh
    # From the frontend/ directory
    ng serve
    ```
3. **Access the Application**
    * Open your browser and navigate to `http://localhost:4200/`.

### Command-Line Interface (CLI)

The CLI version has fewer features but can be run directly.

* From the `backend/build` directory, run the `EventPlanner` executable.
  ```sh
  # From the backend/build/ directory
  ./EventPlanner
  ```

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any
contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

Distributed under the MIT License. See `LICENSE` for more information.
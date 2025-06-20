# Vue 3 + C++ Demo Project

This project is a simple demonstration of how to build a web application with a Vue 3 frontend and a C++ backend.

## Overview

The project is divided into two main parts:

-   `frontend/`: A Vue 3 application created with Vite. It features a simple UI to fetch and display a message from the backend.
-   `backend/`: A lightweight C++ HTTP server using the [Crow](https://github.com/CrowCpp/Crow) framework. It exposes a single API endpoint.

## How to Run

To run this project, you need to start both the backend server and the frontend development server.

### 1. Backend

The C++ backend needs to be compiled and run first. For detailed instructions, see the backend's README file:

[**Backend Instructions**](./backend/README.md)

In summary, you will need to:
1.  Download the required dependencies (`Crow` and `nlohmann/json`).
2.  Build the project using CMake.
3.  Run the resulting executable.

The backend server will run on `http://localhost:18080`.

### 2. Frontend

The Vue 3 frontend is a standard Node.js project. For detailed instructions, see the frontend's README file:

[**Frontend Instructions**](./frontend/README.md)

In summary, you will need to:
1.  Install dependencies using `npm install`.
2.  Start the development server using `npm run dev`.

The frontend will be accessible at `http://localhost:5173` (or a similar port). API requests will be automatically proxied to the backend.

## Goal

This project aims to provide a clear and minimal example of client-server communication between a modern JavaScript framework and a C++ application, which can be a useful pattern for performance-critical backends or for integrating web UIs with existing C++ codebases. 
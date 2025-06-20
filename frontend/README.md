# Frontend (Vue 3)

This is a Vue 3 application created with Vite.

## Setup

1.  Navigate to the `frontend` directory:
    ```bash
    cd frontend
    ```

2.  Install the dependencies:
    ```bash
    npm install
    ```

## Development Server

To start the development server, run:

```bash
npm run dev
```

The application will be available at `http://localhost:5173` (or another port if 5173 is busy).

The development server is configured to proxy API requests from `/api` to the C++ backend at `http://localhost:18080`.

## Build

To create a production build, run:

```bash
npm run build
```

The production files will be in the `dist` directory. 
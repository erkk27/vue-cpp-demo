#include <iostream>
#include <string>
#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <vector>
#include <signal.h>

#pragma comment(lib, "ws2_32.lib")

class SimpleHTTPServer {
private:
    SOCKET serverSocket;
    bool running;
    std::vector<std::thread> threads;

public:
    SimpleHTTPServer() : serverSocket(INVALID_SOCKET), running(false) {}

    bool initialize() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed" << std::endl;
            return false;
        }

        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Socket creation failed" << std::endl;
            WSACleanup();
            return false;
        }

        // Allow address reuse
        int opt = 1;
        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(18080);

        if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Bind failed" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return false;
        }

        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Listen failed" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return false;
        }

        std::cout << "Server listening on port 18080..." << std::endl;
        return true;
    }

    void start() {
        running = true;
        std::cout << "C++ HTTP Server started on http://localhost:18080" << std::endl;
        std::cout << "Press Ctrl+C to stop the server" << std::endl;
        
        while (running) {
            SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
            if (clientSocket == INVALID_SOCKET) {
                if (running) {
                    std::cerr << "Accept failed" << std::endl;
                }
                break;
            }

            // Handle client in a new thread
            std::thread clientThread(&SimpleHTTPServer::handleClient, this, clientSocket);
            clientThread.detach(); // Detach thread to let it run independently
        }
    }

    void stop() {
        running = false;
        closesocket(serverSocket);
        WSACleanup();
    }

private:
    void handleClient(SOCKET clientSocket) {
        char buffer[4096];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::string request(buffer);
            
            // Debug: print the request
            std::cout << "Received request: " << request.substr(0, request.find('\r')) << std::endl;
            
            // Simple request parsing
            if (request.find("GET /api/message") != std::string::npos) {
                std::string jsonBody = "{\"message\": \"Hello from C++ backend!\"}";
                
                std::string response = "HTTP/1.1 200 OK\r\n";
                response += "Content-Type: application/json\r\n";
                response += "Access-Control-Allow-Origin: *\r\n";
                response += "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n";
                response += "Access-Control-Allow-Headers: Content-Type\r\n";
                response += "Content-Length: " + std::to_string(jsonBody.length()) + "\r\n";
                response += "Connection: close\r\n";
                response += "\r\n";
                response += jsonBody;
                
                std::cout << "Sending response with Content-Length: " << jsonBody.length() << std::endl;
                send(clientSocket, response.c_str(), response.length(), 0);
            } else {
                // Handle CORS preflight
                std::string response = "HTTP/1.1 200 OK\r\n";
                response += "Access-Control-Allow-Origin: *\r\n";
                response += "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n";
                response += "Access-Control-Allow-Headers: Content-Type\r\n";
                response += "Content-Length: 0\r\n";
                response += "Connection: close\r\n";
                response += "\r\n";
                
                send(clientSocket, response.c_str(), response.length(), 0);
            }
        }
        
        closesocket(clientSocket);
    }
};

// Global server instance for signal handling
SimpleHTTPServer* g_server = nullptr;

void signalHandler(int signal) {
    if (g_server) {
        std::cout << "\nShutting down server..." << std::endl;
        g_server->stop();
    }
    exit(0);
}

int main() {
    SimpleHTTPServer server;
    g_server = &server;
    
    // Set up signal handler for Ctrl+C
    signal(SIGINT, signalHandler);
    
    if (!server.initialize()) {
        std::cerr << "Failed to initialize server" << std::endl;
        return 1;
    }

    server.start();
    
    return 0;
} 
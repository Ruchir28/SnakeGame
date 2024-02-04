#ifndef ASYNCLOGGER_H
#define ASYNCLOGGER_H

#include <string>
#include <iostream>
#include "messagequeue.h"
#include <thread>
#include <fstream>


class AsyncLogger {
    public:
        static AsyncLogger& getInstance() {
            static AsyncLogger instance;
            return instance;
        }
        AsyncLogger(AsyncLogger const&) = delete;
        void operator=(AsyncLogger const&) = delete;
        AsyncLogger(AsyncLogger&&) = delete;
        void operator=(AsyncLogger&&) = delete;
        void operator<<(std::string message) {
            _queue.send(message);
        }
   
    private:
        std::thread th;
        MessageQueue<std::string> _queue;
        std::ofstream file;
        std::string QUIT = "$QUIT$";
        void startProcessing() {
            std::cout << "Starting processing" << std::endl;
            // start a thread with lambda function 
            th = std::thread([this]() {
                while (true) {
                    std::string message = _queue.receive();
                    if(message == QUIT) {
                        break;
                    }
                    file << message << std::endl;
                }
            });

        }
        AsyncLogger() {
            file.open("../logger/log.txt", std::ios::out);
            if(!file.is_open()) {
                std::cerr << "Failed to open log.txt" << std::endl;
            }
            file << "Starting log" << std::endl;
            startProcessing();
        }
        ~AsyncLogger() {
            _queue.send(QUIT);
            th.join();
            file.close();
        }
     
};

#endif

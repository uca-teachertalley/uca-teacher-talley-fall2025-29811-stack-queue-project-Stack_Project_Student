/**
* ---------------------------------------------------------------------
* @copyright
* Copyright 2024 Michelle Talley University of Central Arkansas
*
* @author: <student name>
* @course: Data Structures (CSCI 2320)
*
* @file main.cpp
* @brief Driver program for Stack and Queue Lab
-----------------------------------------------------------------------
*/ 
#include <iostream>
#include <string>

#include "Stack.h"
#include "Queue.h"

const std::string movie_history = "movie_history.txt";
const std::string movie_queue = "movie_queue.txt";
const std::string movie_history_updated = "movie_history_updated.txt";
const std::string movie_queue_updated = "movie_queue_updated.txt";


/*
TODO: 
*/


int main()
{
    Stack<std::string> movieHistory;
    Queue<std::string> movieQueue;

    bool done = false;

    // Load movie history and queue from files
    try
    {
        movieHistory.restore(movie_history);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << movie_history << " " << e.what() << '\n';
        exit(EXIT_FAILURE);  // Exit program
    }

    try
    {
        movieQueue.restore(movie_queue);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << movie_queue << " " << e.what() << '\n';
        exit(EXIT_FAILURE); // Exit program
    }

    while (!done && !std::cin.eof())
    {
        std::cout << std::endl << "Menu: " << std::endl;
        std::cout << "\ta: Add a movie to the queue" << std::endl;
        std::cout << "\tw: Watch the next movie in the queue" << std::endl;
        std::cout << "\td: Delete the next movie from the queue" << std::endl;
        std::cout << "\th: print the movie History" << std::endl;
        std::cout << "\tr: print the most Recently watched movie" << std::endl;
        std::cout << "\tq: print the movie Queue" << std::endl;
        std::cout << "\tn: print the Next movie to watch" << std::endl;
        std::cout << "\tx: eXit" << std::endl;

        std::cout << "Enter a command: ";
        std::string command;
        std::getline(std::cin, command);
        std::cout << std::endl << std::endl;

        if (command == "x")
        {
            done = true;
        }
        // using else if statements, implement the menu options here

    }

    // Save movie history and queue to files
    try
    {
        movieHistory.save(movie_history_updated);
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: " << movie_history_updated << " " << e.what() << '\n';
         exit(EXIT_FAILURE);  // Exit program
    }

    try
    {
        movieQueue.save(movie_queue_updated);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << movie_queue_updated << " " << e.what() << '\n';
        exit(EXIT_FAILURE);  // Exit program
    }

    return EXIT_SUCCESS;
}

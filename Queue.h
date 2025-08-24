#ifndef QUEUE_H
#define QUEUE_H

/**
* ---------------------------------------------------------------------
* @copyright
* Copyright 2024 Michelle Talley University of Central Arkansas
*
* @author: <student name>
* @course: Data Structures (CSCI 2320)
*
* @file Queue.h
* @brief Declaration of the Queue class and its methods.
-----------------------------------------------------------------------
*/
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

/**
 * @brief Queue class
 * Internally implemented using STL list.
 * @tparam T The type of elements in the queue.
 */
template <typename T>
class Queue
{
private:
    std::list<T> elements;

public:
    /**
     * @brief Default constructor
     */
    Queue() {}

    /**
     * @brief Copy constructor
     * @param other The other queue to copy from
     */
    Queue(const Queue &other) : elements(other.elements) {}
    
    /**
     * @brief Destructor
     * Clears all elements in the queue.
     */
    ~Queue()
    {
        elements.clear();
    }

    /**
     * @brief Checks if the queue is empty
     * @return True if the queue is empty, false otherwise
     */
    bool empty() const
    {
        return elements.empty();
    }

    /**
     * @brief Get the size of the queue.
     * @return The number of elements in the queue.
     */
    size_t size() const
    {
        return elements.size();
    }

    /**
     * @brief Enqueue the given element value to the end of queue
     * @param value The value of the element to enqueue
     */
    void enqueue(const T &value)
    {
        elements.push_back(value);
    }

    /**
     * @brief Removes the top element from the queue
     */
    void dequeue()
    {
        if (elements.empty())
        {
            throw std::out_of_range("Queue is empty");
        }
        elements.pop_front();
    }

    /**
     * @brief Returns the front element of the queue
     * @return The top element of the queue
     */
    T &front()
    {
        if (elements.empty())
        {
            throw std::out_of_range("Queue is empty");
        }
        return elements.front();
    }

    /**
     * @brief Converts the queue to a string
     * @return A string representation of the queue
     */
    std::string toString(std::string separator = " ") const
    {
        std::ostringstream ss;

        for (const auto &element : elements)
        {
            ss << element << separator;
        }
        std::string str = ss.str();
        if (separator == " ")
        {
            // remove trailing space when returning
            return str.empty() ? str : str.substr(0, str.size() - 1);
        }
        else
        {
            return str;
        }
    }

    /**
     * @brief Prints the queue to the standard output
     */
    void print() const
    {
        std::cout << toString("\n");
    }

    // Access to the underlying list as iterators
    auto begin() { return elements.begin(); }
    auto end() { return elements.end(); }

    // Access to the underlying list as iterators
    auto rbegin() { return elements.rbegin(); }
    auto rend() { return elements.rend(); }

    /**
     * Writes the contents of the given queue to a file.
     *
     * @param filename The name of the file to write the queue contents to.
     * @throws std::runtime_error if the file cannot be opened for writing.
     */
    void save(const std::string &filename)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            for (auto& item : elements)
            {
                file << item << std::endl;
            }

            file.close();
        }
        else
        {
            throw std::runtime_error("Unable to open file for writing");
        }
    }

    /**
     * @brief Reads the contents of a file and constructs a Queue from it.
     *
     * @param filename The name of the file to read the Queue contents from.
     * @throws std::runtime_error if the file cannot be opened for reading or
     * if there is an error while reading the file.
     */
    void restore(const std::string &filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            std::string line;

            // Clear the stack before reading from file
            elements.clear();

            while (std::getline(file, line))
            {
                T value; 

                /*
                Note: The following code only works for C++17 and later

                String stream is used to parse the line into individual
                however, for a string queue, String stream will break
                the line on word boundaries.  If the queue is a string,
                simply use the entire input string as the value.

                see: https://stackoverflow.com/questions/62240203/
                    how-do-i-stdgetline-into-a-template-type

                Enable VS Code to use C++17 by adding the following to
                the .vscode/tasks.json file:
                    "args": ["-std=c++17"]
                or later by using:
                    "args": ["-std=c++20"]
                */
                if constexpr (std::is_same_v<T, std::string>)
                {
                    enqueue(line);
                }
                else
                {
                    T value;

                    std::istringstream iss(line);

                    while (iss >> value)
                    {
                        enqueue(value);
                    }
                }
            }
            file.close();
        }
        else
        {
            throw std::runtime_error("Unable to open file for reading");
        }
    }
};

/**
 * @brief Overloads the << operator to print the queue
 * @param os The output stream
 * @param queue The queue to print
 * @return The output stream
 */
template <typename T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &queue)
{
    os << queue.toString();
    return os;
}

#endif // QUEUE_H
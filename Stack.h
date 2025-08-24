#ifndef STACK_H
#define STACK_H

/**
* ---------------------------------------------------------------------
* @copyright
* Copyright 2024 Michelle Talley University of Central Arkansas
*
* @author: <student name>
* @course: Data Structures (CSCI 2320)
*
* @file Stack.h
* @brief Declaration of the Stack class and its methods.
-----------------------------------------------------------------------
*/

#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <list>
#include <iterator>
#include <stdexcept>

/**
 * @brief Stack class 
 * Internally implemented using STL list
 * @tparam T The type of elements in the stack
 */
template <typename T>
class Stack
{
private:
    std::list<T> data;

public:
    /**
     * @brief Default constructor
     */
    Stack() {}

    /**
     * @brief Construct a new Stack object as a copy of existing Stack
     * @param other The Stack to copy
     */
    Stack(const Stack& other) : data(other.data) {} 

    /**
     * @brief Destructor
     * Frees all stack elements
     */
    ~Stack()
    {
        data.clear();
    }

    /**
     * @brief Check if the stack is empty
     * @return true if the stack is empty, false otherwise
     */
    bool empty() const
    {
        return data.empty();
    }

    /**
     * @brief Get the size of the stack
     * @return The number of elements in the stack
     */
    size_t size() const
    {
        return data.size();
    }

    /**
     * @brief Access the top element of the stack
     * @return A reference to the top element in the stack
     * @throw std::out_of_range if the stack is empty
     */
    T &top()
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        return data.front();
    }

    /**
     * @brief Insert a new element at the top of the stack
     * @param value The value to insert
     */
    void push(const T &value)
    {
        data.push_front(value);
    }

    /**
     * @brief Remove the top element from the stack
     * @throw std::out_of_range if the stack is empty
     */
    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        data.pop_front();
    }

    /**
     * @brief Convert the stack to a string
     * @return A string representation of the stack
     */
    std::string toString(std::string separator = " ") const
    {
        std::ostringstream ss;

        for (auto rev_it = data.begin(); rev_it != data.end(); ++rev_it)
        {
            ss << *rev_it << separator;
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
     * @brief Print the stack to standard output
     */
    void print() const
    {
        std::cout << toString("\n");
    }

    // Reverse iterator more natural for stack traversal
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }

    // Reverse iterator more natural for stack traversal
    auto rbegin() { return data.rbegin(); }
    auto rend() { return data.rend(); }

    /**
     * Writes the contents of the given stack to a file.
     *
     * @param filename The name of the file to write the stack contents to.
     * @throws std::runtime_error if the file cannot be opened for writing.
     */
    void save(const std::string& filename)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            for (auto& item : data)
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
     * @brief Reads the contents of a file and constructs a Stack from it.
     *
     * @param filename The name of the file to read the Stack contents from.
     * @throws std::runtime_error if the file cannot be opened for reading or 
     * if there is an error while reading the file.
     */
    void restore(const std::string& filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            std::string line;

            // Clear the stack before reading from file
            data.clear();

            while (std::getline(file, line))
            {
                T value;

                /*
                Note: The following code only works for C++17 and later

                String stream is used to parse the line into individual
                however, for a string stack, String stream will break
                the line on word boundaries.  If the stack is a string,
                simply use the entire input string as the value.
            
                see: https://stackoverflow.com/questions/62240203/how-do-i-stdgetline-into-a-template-type

                Enable VS Code to use C++17 by adding the following to
                the .vscode/tasks.json file:
                    "args": ["-std=c++17"]
                or later by using:
                    "args": ["-std=c++20"]
                */
                if constexpr (std::is_same_v<T, std::string>)
                {
                    data.push_back(line);
                }
                else
                {
                    T value;

                    std::stringstream iss(line);

                    while (iss >> value)
                    {
                        data.push_back(value);
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
    

    /**
     * @brief Overloads the << operator to print the stack elements
     * @param os The output stream
     * @param stack The stack to be printed
     * @return The output stream
     */
    friend std::ostream &operator<<(std::ostream &os,
                                    const Stack<T> &stack)
    {
        os << stack.toString();
        return os;
    }
};


#endif // STACK_H



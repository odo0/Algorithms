// Definition of Datastructure class for UDS/Tiraka homework 1 -


#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <vector>

const std::string SEPARATOR = " ";

class Datastructure
{
    public:

    Datastructure();

    ~Datastructure();

    // Adds one value to the datastructure
    void add(std::string rank, unsigned int birthYear,
             unsigned int enlistingYear, std::string shirtColor,
             std::string name);

    // Prints sorted crew list
    void print();

    // Finds and prints youngest person
    void youngest();

    // Finds and prints oldest person
    void oldest();

    // Empties the datastructure
    void empty();

    // returns the size of the datastructure
    size_t size();

    // Copy constructor is forbidden
    Datastructure(const Datastructure&) = delete;
    // Assignment operator is forbidden
    Datastructure& operator=(const Datastructure&) = delete;

    private:
    // Osku Haavisto, 229440
    // Add your own implementation here

    struct Personal_information{
        std::string rank;
        unsigned int birthYear;
        unsigned int enlistingYear;
        std::string shirtColor;
        std::string name;
    };
    std::vector<Personal_information> datastructure_;
    int size_;
    int in_order_;



    void quickSort(std::vector<Personal_information>& ds, int left, int right);
};


#endif

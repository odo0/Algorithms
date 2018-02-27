// Definition of Datastructure class for UDS/Tiraka homework 2 -


#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <memory>
#include <array>

const std::string EI_SAATAVILLA = "Tuotetta ei varastossa.";
const std::string EI_VARASTOA = "Varastosaldo ei riittävä.";

class Datastructure
{
    public:

    Datastructure();

    ~Datastructure();

    // Adds candies to the datastructure
    void add(const std::string& ID, const std::string& location,
            unsigned int amount, const std::string& name);
          
    // Removes candies from the datastructure
    void substract(const std::string& ID, unsigned int amount);

    // Finds candy and prints its status 
    void find(const std::string& ID) const;

    // Returns how many different types of candy the datastructure contains 
    size_t count() const;

    // Empties the datastructure
    void empty();
    
    // Saves candy data to file, called when exiting
    void save_to_file(const std::string& filename) const;
   
    // Copy constructor is forbidden
    Datastructure(const Datastructure&) = delete;
    // Assignment operator is forbidden
    Datastructure& operator=(const Datastructure&) = delete;

    private:
    // Osku Haavisto, 229440
    // Add your own implementation here

    struct Karkki{
        std::string id;
        std::string location;
        unsigned int amount;
        std::string name;
        std::shared_ptr<Karkki> seuraava_karkki{nullptr};
        Karkki *edellinen_karkki{nullptr};
    };
    std::array<std::shared_ptr<Karkki>,10091> ds_;
    int erilaisia_karkkeja_;

};

#endif

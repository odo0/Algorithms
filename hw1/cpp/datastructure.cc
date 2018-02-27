// Osku Haavisto, 229440

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "datastructure.hh"

Datastructure::Datastructure():size_{0},in_order_{0}{

}

Datastructure::~Datastructure(){

}
//Siirretään henkilön tiedot Personal_information-tyyppiä olevaan muuttujaan
//ja lisätään se vectoriin.

void Datastructure::add(std::string rank, unsigned int birthYear,
                        unsigned int enlistingYear, std::string shirtColor,
                        std::string name){
    Personal_information information{rank,birthYear,enlistingYear,
                shirtColor,name};
    datastructure_.push_back(information);
    size_++;
    in_order_= 0;
}
//Järjestetään vectori quickSortilla ja sitten tulostetaaan kaikki vectorissa
//olevat henkilötiedot järjestyksessä
void Datastructure::print(){
    if(size_>0){
        quickSort(datastructure_,0,size_-1);

        for(auto info:datastructure_){
            std::cout<<info.rank<<" "<<info.name<<", Born: "
                    <<info.birthYear<<", Joined: "<<info.enlistingYear
                   << ", "<<info.shirtColor<<std::endl;
        }
        in_order_ = 1;
    }
}
//Etsitään ja tulostetaan palveluksessa pisimpään ollut henkilö. Aluksi
//tutkitaan in_order-muuttujan arvoa. Jos se ei ole 0, tiedetään että
//vectori on järjestyksessä ja haluttu henkilö löytyy vectorin
//ensimmäisestä alkiosta.
void Datastructure::oldest(){
    if(size_> 0){
        Personal_information oldest_person(datastructure_[0]);
        if(in_order_ == 0){
            for(int i = -1;i++ < size_-1;){
                if(datastructure_[i].enlistingYear <
                        oldest_person.enlistingYear ||
                        (datastructure_[i].enlistingYear ==
                         oldest_person.enlistingYear &&
                         datastructure_[i].birthYear <=
                         oldest_person.birthYear)){
                    oldest_person = datastructure_[i];
                }
            }
        }
        std::cout<<oldest_person.rank<<" "<<oldest_person.name
                <<", "<<oldest_person.shirtColor<<std::endl;
    }
}
//Etsitään ja tulostetaan palveluksessa lyhimpään ollut henkilö. Aluksi
//tutkitaan in_order-muuttujan arvoa. Jos se ei ole 0, tiedetään että
//vectori on järjestyksessä ja haluttu henkilö löytyy vectorin
//viimeisestä alkiosta.
void Datastructure::youngest(){
    if(size_ > 0){
        Personal_information youngest_person(datastructure_[size_-1]);
        if(in_order_ == 0){
            for(int i = size_;i-- > 0;){
                if(datastructure_[i].enlistingYear >
                        youngest_person.enlistingYear ||
                        (datastructure_[i].enlistingYear ==
                         youngest_person.enlistingYear &&
                         datastructure_[i].birthYear >
                         youngest_person.birthYear)){
                    youngest_person = datastructure_[i];
                }
            }
        }
        std::cout<<youngest_person.rank<<" "<<youngest_person.name
                <<", "<<youngest_person.shirtColor<<std::endl;
    }
}
//Tyhjennetään vectori.
void Datastructure::empty(){
    datastructure_.clear();
    size_ = 0;
}
//Palautetaan tietorakenteen(vectorin) pituus.
size_t Datastructure::size(){
    return size_;
}
//QuickSort-algoritmi.
void Datastructure::quickSort(std::vector<Personal_information>& ds,
                              int left, int right) {

    int i = left;
    int j = right;
    unsigned int pivotE = ds[(left+right)/2].enlistingYear;
    unsigned int pivotB = ds[(left+right)/2].birthYear;
    //Järjestetään vectori yhden vectorin alkion suhteen sitä pienempiin ja
    //sitä suurempiin alkioihin.
    while (i <= j) {
        while(ds[i].enlistingYear < pivotE ||(ds[i].enlistingYear == pivotE &&
                                               ds[i].birthYear < pivotB)){
            i++;
        }
        while(ds[j].enlistingYear > pivotE ||(ds[j].enlistingYear == pivotE &&
                                               ds[j].birthYear > pivotB)){
            j--;
        }
        if (i < j) {
            std::swap(ds[i],ds[j]);
            i++;
            j--;
        }else if(i == j){
            i++;
            j--;
        }
    }
    //Jatketaan vectorin jakamista rekursiivisesti,
    //kunnes vectori on järjestyksessä.
    if (left < j){
        quickSort(ds, left, j);
    }
    if (i < right){
        quickSort(ds, i, right);
    }
}

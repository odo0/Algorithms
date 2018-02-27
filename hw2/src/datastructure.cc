// Osku Haavisto, 229440

#include "datastructure.hh"
#include "utility.hh"
#include <string>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;

Datastructure::Datastructure():erilaisia_karkkeja_{0}{
    ds_.fill(nullptr);
}

Datastructure::~Datastructure(){

}
//Funktio lisää karkin tietorakenteeseen. Ensiksi lasketaan karkin ID:stä
//Hashfunktiolla indeksi. Sen jälkeen tutkitaan onko tietorakenteen kyseisessä
//indeksissä jo tietoa. Jos sama karkki löytyy jo, lisätään ainoastaan sen
//määrä jo olemassa olevaan. Jos indeksissä on muita karkkeja ennestään,
//lisätään uusin viimeiseksi.
void Datastructure::add(const string& ID, const string& location,
                        unsigned int amount, const string& name){

    int indeksi = HashFunktio(ID);
    shared_ptr<Karkki> tutkittava{new Karkki};

    if(ds_.at(indeksi)== nullptr){
        tutkittava->id = ID;
        tutkittava->location = location;
        tutkittava->amount = amount;
        tutkittava->name = name;
        tutkittava->seuraava_karkki = nullptr;
        tutkittava->edellinen_karkki = nullptr;
        ds_.at(indeksi) = tutkittava;
        ++erilaisia_karkkeja_;
    }else {
        tutkittava = ds_.at(indeksi);
        shared_ptr<Karkki> lisattava{new Karkki};
        lisattava->id = ID;
        lisattava->location = location;
        lisattava->amount = amount;
        lisattava->name = name;

        while(true){
            if(tutkittava->id == lisattava->id){
                tutkittava->amount += lisattava->amount;
                break;
            }
            if(tutkittava->seuraava_karkki == nullptr){
                tutkittava->seuraava_karkki = lisattava;
                lisattava->edellinen_karkki = tutkittava.get();
                lisattava->seuraava_karkki = nullptr;
                ++erilaisia_karkkeja_;
                break;
            }else{
                tutkittava = tutkittava->seuraava_karkki;
            }
        }
    }
}
//Vähennetään annettu määrä annettua karkkia. Jos vähennettävä määrä
//on sama kuin karkin määrä tietorakenteessa, poistetaan se. Jos
//vähennettävä määrä on suurempi kuin tietorakenteessa, ilmoitetaan
//tästä eikä vähennettä määrää ollenkaan.
void Datastructure::substract(const string& ID, unsigned int amount){

    int indeksi = HashFunktio(ID);
    shared_ptr<Karkki> tutkittava = ds_.at(indeksi);

    while(true){
        if(tutkittava == nullptr){
            cout<<EI_SAATAVILLA<<endl;
            break;
        }
        if(tutkittava->id == ID){
            if(tutkittava->amount > amount){
                tutkittava->amount -= amount;
                cout<<"Saldo: "<<tutkittava->amount<<" Hylly: "
                   <<tutkittava->location<<endl;
                break;
            }else if(tutkittava->amount == amount){
                if(ds_.at(indeksi) == tutkittava){
                    cout<<"Saldo: 0 Hylly: "<<tutkittava->location<<endl;
                    ds_.at(indeksi) = tutkittava->seuraava_karkki;
                }else{
                    cout<<"Saldo: 0 Hylly: "<<tutkittava->location<<endl;
                    tutkittava->edellinen_karkki->seuraava_karkki =
                            tutkittava->seuraava_karkki;
                    tutkittava->seuraava_karkki->edellinen_karkki =
                            tutkittava->edellinen_karkki;
                }
                --erilaisia_karkkeja_;
                break;
            }else if(tutkittava->amount < amount){
                cout<<EI_VARASTOA<<endl;
                cout<<"Saldo: "<<tutkittava->amount<<" Hylly: "
                   <<tutkittava->location<<endl;
                break;
            }
        }
        tutkittava = tutkittava->seuraava_karkki;
    }
}
//Etsitään haluttu karkki ja tulostetaan sen nimi, määrä ja sijainti.
void Datastructure::find(const string& ID) const{

    int indeksi = HashFunktio(ID);
    shared_ptr<Karkki> tutkittava{ds_.at(indeksi)};

    while(true){
        if(tutkittava == nullptr){
            cout<<EI_SAATAVILLA<<endl;
            break;
        }
        if(tutkittava->id == ID){
            cout<<tutkittava->name<<" "<<tutkittava->amount<<" "
               <<tutkittava->location<<endl;
            break;
        }
        tutkittava = tutkittava->seuraava_karkki;
    }
}
//Palauttaa tietorakenteessa olevien erilaisten karkkien määrän.
size_t Datastructure::count() const{
    return erilaisia_karkkeja_;
}

void Datastructure::empty(){
    for(int i{0};i<=10090;i++){
        ds_.at(i) = nullptr;
    }
    erilaisia_karkkeja_ = 0;
}
//Tallentaa tietorakenteessa olevat karkit haluttuun tiedostoon.
void Datastructure::save_to_file(const string& filename) const{

    ofstream file_stream( filename );

    for(int i{0};i<=10090;i++){
        if(ds_.at(i) != nullptr){
            shared_ptr<Karkki> tallennettava{ds_.at(i)};
            while(tallennettava != nullptr){
                file_stream<<tallennettava->id<<";"<<tallennettava->amount
                          <<";"<<tallennettava->location<<";"
                         <<tallennettava->name<<endl;
                tallennettava = tallennettava->seuraava_karkki;
            }
        }
    }
    file_stream.close();
}

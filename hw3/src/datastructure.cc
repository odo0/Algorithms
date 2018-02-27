// Osku Haavisto, 229440

#include "datastructure.hh"
#include "utility.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;

Datastructure::Datastructure(){

}

Datastructure::~Datastructure(){

}
//Etsitään käyttäjän antamien pysäkkien välille nopein reitti annetun
//ajan jälkeen.
void Datastructure::routeSearch(const std::string& time,
                                const std::string& stop_id1,
                                const std::string& stop_id2 ) const{

    //Tutkitaan löytyykö kysyttyjä pysäkkejä.
    if((pysakit.find(stop_id1) == pysakit.end()) |
            (pysakit.find(stop_id2) == pysakit.end())){
        cout<<VIRHE<<endl;
        return;
    }

    shared_ptr<Pysakin_tiedot> pysakki = pysakit.at(stop_id1);
    pysakki->edellinen_saapui = muunna_minuuteiksi(time+":00");

    //Etsitään lyhin reitti.
    while(pysakki->pysakki_id != stop_id2){

        //Pysäkiltä lähtevien vuorojen seuraavat pysäkit.
        for(auto tietopari : pysakki->vuorot){
            shared_ptr<Pysakin_tiedot> uusi_pysakki =
                    pysakit.at(tietopari.first);

            if(uusi_pysakki->vari == 2)
                continue;

            //Pysäkin ja sitä seuraavan pysäkin väliset vuorot.
            for(auto vuoro : tietopari.second){

                //Valitaan sellaiset vuorot, jotka täyttävät vaatimukset.
                //for-silmukan loputtua tallessa on sopivin matka.
                if((vuoro.lahto >= pysakki->edellinen_saapui)&&
                        ((vuoro.lahto == pysakki->edellinen_saapui)|
                         (pysakki->matka.linja != vuoro.linja))&&
                        ((uusi_pysakki->edellinen_saapui > vuoro.maaranpaa) |
                         (uusi_pysakki->edellinen_saapui == 0) |
                        ((uusi_pysakki->edellinen_saapui ==vuoro.maaranpaa)&&
                         (pysakki->matka.linja == vuoro.linja)))){

                    uusi_pysakki->edellinen_saapui = vuoro.maaranpaa;
                    uusi_pysakki->edellinen_pysakki_id = pysakki;
                    uusi_pysakki->matka = vuoro;
                }
            }

            //Vaihdetaan uuden pysäkin väri harmaaksi ja lisätään se
            //prioriteettijonoon.
            if((uusi_pysakki->vari == 0)&&(pysakki->edellinen_saapui <=
                                           uusi_pysakki->edellinen_saapui)){
                uusi_pysakki->vari = 1;
                pjono2.push(uusi_pysakki);
            }
        } 
        //Jos annettujen pysäkkien välille ei löydetä linjaa.
        if(pjono2.empty()){
                cout<<EI_LINJAA<<endl;
            for(auto tietopari : pysakit){
                tietopari.second->vari = 0;
                tietopari.second->edellinen_pysakki_id = nullptr;
                tietopari.second->edellinen_saapui = 0;
                return;
            }
        }
        //Otetaan uudeksi käsiteltäväksi pysäkiksi prioriteettijonon ensimmäinen
        //alkio ja muutetaan sen väri mustaksi.
        pysakki = pjono2.top();
        pysakki->vari = 2;
        pjono2.pop();
    }

        //Sijoitetaan tulostus-vectoriin pysäkkiä vastaava tuloste.
        while(pysakki != nullptr){

            if(pysakki->edellinen_pysakki_id != nullptr){
                pysakki->edellinen_pysakki_id->seuraava_lahti =
                        pysakki->matka.lahto;
                pysakki->edellinen_pysakki_id->linja = pysakki->matka.linja;
            }
            if(pysakki->pysakki_id == stop_id2){

                tulostus.push_back("Bussi "+pysakki->matka.linja+": "+
                                   muunna_kellonajaksi(pysakki->edellinen_saapui)
                                   +" "+pysakki->pysakki_id+", "+ pysakki->nimi);
            }
            else if(pysakki->pysakki_id == stop_id1){

                tulostus.push_back("Bussi "+pysakki->linja+": "+
                                   muunna_kellonajaksi(pysakki->seuraava_lahti)
                                   +" "+pysakki->pysakki_id+", "+ pysakki->nimi);

            }
            else if(pysakki->edellinen_saapui != pysakki->seuraava_lahti){

                tulostus.push_back("Bussi "+pysakki->linja+": "+
                                   muunna_kellonajaksi(pysakki->seuraava_lahti)
                                   +" "+pysakki->pysakki_id+", "+ pysakki->nimi);

                tulostus.push_back("Bussi "+pysakki->matka.linja+": "+
                                   muunna_kellonajaksi(pysakki->edellinen_saapui)
                                   +" "+pysakki->pysakki_id+", "+ pysakki->nimi);
            }
            else{
                tulostus.push_back("Bussi "+pysakki->linja+": "+
                                   muunna_kellonajaksi(pysakki->edellinen_saapui)
                                   +" "+pysakki->pysakki_id+", "+ pysakki->nimi);
            }

            pysakki = pysakki->edellinen_pysakki_id;
        }

    //Palautetaan tietorakenne sellaiseen tilaan, jotta seuraavat reitinetsinnät
    //ovat mahdollisia.
    for(auto tietopari : pysakit){
        tietopari.second->vari = 0;
        tietopari.second->edellinen_pysakki_id = nullptr;
        tietopari.second->edellinen_saapui = 0;
    }
    //Tyhjennetään prioriteettijono.
    while(!pjono2.empty())
        pjono2.pop();


    //Tulostetaan reitti.
    while(tulostus.size() > 0){

        cout<<tulostus.back()<<endl;
        tulostus.pop_back();
    }
}

//Tulostetaan kysytyn pysäkin kautta kulkevien reittien numerot kasvavassa
//järjestyksessä.
void Datastructure::routesFromStop(const std::string& stop_id) const{

    if(pysakit.find(stop_id) == pysakit.end()){
        cout<<VIRHE<<endl;
        return;
    }
    shared_ptr<Pysakin_tiedot> pysakki = pysakit.at(stop_id);
    //Järjestetään vectorin sisältö pienimmästä suurimpaan.
    sort(pysakki->pysakin_linjat.begin(),pysakki->pysakin_linjat.end());

    for( auto i = pysakki->pysakin_linjat.begin(); i !=
         pysakki->pysakin_linjat.end(); ++i)

        if((i + 1) == pysakki->pysakin_linjat.end())
            cout<< *i<<endl;
        else
            cout << *i <<", ";
}

//Tulostaa pysäkin nimen.
void Datastructure::stopName(const std::string& stop_id) const{

    if(pysakit.find(stop_id) == pysakit.end()){
        cout<<VIRHE<<endl;
        return;
    }
    cout<<pysakit.at(stop_id)->nimi<<endl;
}

//Tulostaa luettujen pysäkkien, linjojen ja vuorojen kokonaismäärän.
void Datastructure::count() const{

    cout<<pysakit.size()<<" pysäkkiä, "<<linjojen_lkm<<" linjaa, "<<
          linjat.size()<<" vuoroa"<<endl;
}

//Tyhjentää tietorakenteen
void Datastructure::empty(){

    pysakit.clear();
    linjat.clear();
    linjojen_lkm = 0;
}

//Luetaan tarvittavat tiedostot ja otetaan niistä talteen halutut arvot.
void Datastructure::loadData(const std::string& directory){

//stops.txt, kaikki pysäkit
    string tiedosto = directory +"/stops.txt";
    ifstream file_stream( tiedosto);
    if( !file_stream )
    {
        file_stream.close();
        cout << "Tiedostoa: "<<tiedosto<<" ei löydy." << endl;
        return;
    }
    string line;
    string pysakki_tunnus;
    string tyhja;
    string pysakki_nimi;

    //Poistetaan otsikkorivi
    getline(file_stream,line);

    while( getline( file_stream, line ))
    {
        istringstream line_stream( line );
        getline(line_stream, pysakki_tunnus,',');
        getline(line_stream, tyhja, ',');
        getline(line_stream, pysakki_nimi, ',');

        shared_ptr<Pysakin_tiedot> pysakki = make_shared<Pysakin_tiedot>
                (Pysakin_tiedot(nullptr,pysakki_tunnus,
                                pysakki_nimi,{},{},0,0,0,{0,0,""},{}));

        pysakit.insert({pysakki_tunnus,pysakki});
    }
    file_stream.close();

//trips.txt, vuoroja vastaavat linjat
     tiedosto = directory +"/trips.txt";
     ifstream file_stream2( tiedosto);
    if( !file_stream2 )
    {
        file_stream2.close();
        cout << "Tiedostoa: "<<tiedosto<<" ei löydy." << endl;
        return;
    }
    string linja_tunnus;
    string vuoro_id;

    getline(file_stream2,line);
    while( getline( file_stream2, line ))
    {
        istringstream line_stream( line );
        getline(line_stream, linja_tunnus,',');
        getline(line_stream, tyhja, ',');
        getline(line_stream, vuoro_id, ',');

        linjat.insert({vuoro_id,linja_tunnus});
    }

    file_stream2.close();

//stop_times.txt, pysäkkien väliset matkat.
     tiedosto = directory +"/stop_times.txt";
     ifstream file_stream3( tiedosto);
    if( !file_stream3 )
    {
        file_stream3.close();
        cout << "Tiedostoa: "<<tiedosto<<" ei löydy." << endl;
        return;
    }
    string aika;
    double aikaL;
    double aikaS;
    string linja;

    getline(file_stream3,line);
    while( getline( file_stream3, line ))
    {
        istringstream line_stream( line );
        getline(line_stream, vuoro_id,',');
        getline(line_stream, tyhja, ',');
        getline(line_stream, aika, ',');
        getline(line_stream, pysakki_tunnus, ',');

        if(trip_id == vuoro_id){
            aikaL = muunna_minuuteiksi(departure_time);
            aikaS = muunna_minuuteiksi(aika);
            linja = linjat.at(trip_id);
            Matka matka{aikaL,aikaS,linja};
            vector<Matka> matkat{matka};
            if(pysakit.at(stop_id)->vuorot.find(pysakki_tunnus) ==
                    pysakit.at(stop_id)->vuorot.end())
            pysakit.at(stop_id)->vuorot.insert({pysakki_tunnus,matkat});
            else
                pysakit.at(stop_id)->vuorot.at(pysakki_tunnus).push_back(matka);
        }
        trip_id = vuoro_id;
        stop_id = pysakki_tunnus;
        departure_time = aika;

        double linja_nro{muuta_string_doubleksi(linjat.at(vuoro_id))};
        if(find(pysakit.at(pysakki_tunnus)->pysakin_linjat.begin(),
                pysakit.at(pysakki_tunnus)->pysakin_linjat.end(), linja_nro) ==
                pysakit.at(pysakki_tunnus)->pysakin_linjat.end())

            pysakit.at(pysakki_tunnus)->pysakin_linjat.push_back(linja_nro);
    }
    file_stream3.close();

//routes.txt, linjojen kokonaislukumäärä
    tiedosto = directory +"/routes.txt";
    ifstream file_stream4( tiedosto);
    if( !file_stream4 )
    {
        file_stream4.close();
        cout << "Tiedostoa: "<<tiedosto<<" ei löydy." << endl;
        return;
    }
    string turhake;
    while (getline(file_stream4, turhake) )
        ++linjojen_lkm;

    linjojen_lkm--;

    file_stream4.close();
}

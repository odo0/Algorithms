#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::istringstream;

#include "utility.hh"

//const string file = "varasto.txt";


using std::string;

void ReadFile( const string& file, Datastructure& DS )
{
    ifstream file_stream( file );
    if( !file_stream )
    {
        file_stream.close();
        cout << "Tiedostoa ei löydy." << endl;
        return;
    }

    DS.empty();

    string line;
    string ID;
    string loc;
    unsigned int amnt;
    string name;
    while( std::getline( file_stream, line ))
    {
        istringstream line_stream( line );
        getline(line_stream, ID, ';');
        line_stream >> amnt;
        line_stream.get();
        getline(line_stream, loc, ';');
        getline(line_stream, name);
        DS.add( ID, loc, amnt, name );
    }
    file_stream.close();
}
// Osku Haavisto, 229440

//Jaetaan annettu ID kolmeen osaan. Muokataan näitä osia siten, että niistä
//saadaan muodostettua yksi uniikki luku. Tästä luvusta lasketaan jakojäännös
//valitun alkuluvun 10091 suhteen. Funktio palauttaa tämän jakojäännöksen.
int HashFunktio(const string& ID){
    int varastotunnus{0};
    int valmistajan_ID{0};
    int tuote_ID{0};
    string varastotunnus_str{""};
    string valmistajan_ID_str{""};
    string tuote_ID_str{""};

    istringstream line_stream( ID );
    getline(line_stream, varastotunnus_str, ':');
    getline(line_stream, valmistajan_ID_str, ':');
    getline(line_stream, tuote_ID_str);

        if( varastotunnus_str== "LKS"){
            varastotunnus = 10000000;
        }
        else if( varastotunnus_str == "GUM"){
            varastotunnus = 20000000;
        }
        else if( varastotunnus_str == "SMK"){
            varastotunnus = 30000000;
        }
        else if( varastotunnus_str == "MIX"){
            varastotunnus = 40000000;
        }
        else if( varastotunnus_str == "SUK"){
            varastotunnus = 50000000;
        }
        else if( varastotunnus_str == "TIK"){
            varastotunnus = 60000000;
        }
        else if( varastotunnus_str == "VHT"){
            varastotunnus = 70000000;
        }
        else if( varastotunnus_str == "WIN"){
            varastotunnus = 80000000;
        }
        istringstream virta(valmistajan_ID_str);
        virta>>std::ws >> valmistajan_ID >> std::ws;
        istringstream virta2(tuote_ID_str);
        virta2>>std::ws >> tuote_ID >> std::ws;

        int tunnistenro{varastotunnus + valmistajan_ID * 1000 + tuote_ID};

        return tunnistenro % 10091;

}

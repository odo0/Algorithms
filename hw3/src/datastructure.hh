// Definition of Datastructure class for UDS/Tiraka homework 3 -

#ifndef _DATASTRUCTURE_HH_
#define _DATASTRUCTURE_HH_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <queue>

const std::string EI_LINJAA = "Virhe: Ei linjaa!";
const std::string VIRHE = "Virhe: Pysäkkiä ei ole!";

using namespace std;

class Datastructure
{
public:

    Datastructure();

    ~Datastructure();

    // N-komento. Tulostaa reitin pysäkkeinen, joka on ensimmäisenä perillä
    // stop_id2:ssa.
    void routeSearch(const std::string& time, const std::string& stop_id1,
                     const std::string& stop_id2 ) const;

    // B-komento. Tulostaa pysäkin kautta kulkevat reitit
    void routesFromStop(const std::string& stop_id) const;

    // P-komento. Tulostaa pysäkin nimen.
    void stopName(const std::string& stop_id) const;

    // C-komento, Tiedot pysäkkien, linjojen ja vuorojen määrästä
    void count() const;

    // Tyhjentää tietorakenteen. E-komento
    void empty();

    // R-komento. Lukee GTFS muotoisen datan hakemistosta tietorakenteeseen.
    void loadData(const std::string& directory);

    // Kopiorakentaja kielletty
    Datastructure(const Datastructure&) = delete;

    // Sijoitusoperaattori kielletty
    Datastructure& operator=(const Datastructure&) = delete;

private:
    // Osku Haavisto, 229440
    // Your implementation here

    //Kuvaa kahden pysäkin välistä matkaa. Lahto on aika, jolloin se lähtee
    //pysäkiltä, maaranpaa on aika, jolloin bussi saapuu seuraavalle pysäkille
    //ja linja sisältää tiedon mikä on matkalla käytettävän bussin linja.
    struct Matka{
        double lahto;
        double maaranpaa;
        string linja;
    };

    //Kuvaa yhtä pysäkkiä. Pysakin_linjat on vectori kaikista pysäkin
    //kautta kulkevista linjoista. Vari on hakualgoritmia varten(0 == valkoinen,
    //1 == harmaa, 2 == musta). Matka sisältää tiedon siitä bussimatkasta, jolla
    //tälle pysäkille on saavuttu. Vuorot-mapissa hakuavaimena ovat kaikki tästä
    //pysäkistä seuraavien pysäkkien pysäkki_id:t ja niiden arvona on näiden kahden
    //pysäkin välillä kulkevat vuorot.
    struct Pysakin_tiedot{

        shared_ptr<Pysakin_tiedot> edellinen_pysakki_id;
        string pysakki_id;
        string nimi;
        string linja;
        vector<double> pysakin_linjat;
        double edellinen_saapui;
        double seuraava_lahti;
        int vari;
        Matka matka;
        map<string, vector<Matka>> vuorot;

        //rakentaja
        Pysakin_tiedot(shared_ptr<Pysakin_tiedot> a,string b,
                       string c,string d,vector<double> e,
                       double f,double g,int h,Matka i,
                       map< string,vector<Matka>> j)
            : edellinen_pysakki_id(a),pysakki_id(b),
              nimi(c),linja(d),pysakin_linjat(e), edellinen_saapui(f),
              seuraava_lahti(g),vari(h), matka(i),vuorot(j){}

    };
    //Luodaan vertailu-operaattori Pysäkin_tiedoille prioriteettijonoa varten.
    struct VertaileAikaa{

        bool operator ()(shared_ptr<Pysakin_tiedot> const& p1,
                         shared_ptr<Pysakin_tiedot> const& p2){
            return p1->edellinen_saapui > p2->edellinen_saapui;
        }
    };

    string trip_id{""};
    string stop_id{""};
    string departure_time{""};

    mutable  vector< string> tulostus{};

    //Kaikki luetun datan pysäkit sisältävä tietorakenne. Avaimena
    //toimii pysakin pysakki_id ja arvona pointteri pysakin tietoihin.
    mutable  map< string, shared_ptr<Pysakin_tiedot>> pysakit;

    map< string, string> linjat;
    int linjojen_lkm{0};

    //Prioriteettijono, jossa ensimmäisenä on se pointteri pysäkkiin, jolla
    //pienin edellinen_saapui-arvo eli mille pysäkille saavuttaessa kello on
    //vähiten.
    mutable priority_queue< shared_ptr<Pysakin_tiedot>,
              vector< shared_ptr<Pysakin_tiedot>>,VertaileAikaa> pjono2;

};

#endif

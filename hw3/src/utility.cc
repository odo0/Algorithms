
#include "utility.hh"
#include <sstream>


void set_limits()
{
#ifndef _WIN32
  #ifndef _NOMEMORYLIMITS
    struct rlimit new_limit;
    struct rlimit *newp;
    new_limit.rlim_cur = _MEMORYLIMITBYTES;
    new_limit.rlim_max = _MEMORYLIMITBYTES;
    newp = &new_limit;
    setrlimit(RLIMIT_AS, newp );
  #endif
#endif
}

double muuta_string_doubleksi(const std::string& mjono) {
    std::istringstream virta(mjono);

    double tulos{0.0};
    virta >> std::ws >> tulos >> std::ws;

    if ( virta.fail() or virta.peek() != EOF ) {
        return std::stod("NaN");
    } else {
        return tulos;
    }
}
//Muunnetaan tekstimuodossa oleva kellonaika minuuteiksi.
double muunna_minuuteiksi(std::string aika){
    std::istringstream line_stream(aika);
    std::string tunnit_str;
    std::string minuutit_str;
    std::string sekunnit_str;

    std::getline(line_stream,tunnit_str,':');
    std::getline(line_stream,minuutit_str,':');
    std::getline(line_stream,sekunnit_str);

    double tunnit = muuta_string_doubleksi(tunnit_str);
    double minuutit = muuta_string_doubleksi(minuutit_str);
    double sekunnit = muuta_string_doubleksi(sekunnit_str);

    return tunnit * 60 + minuutit + sekunnit / 60;

}
//Muunnetaan minuuttimuodossa oleva aika string kellonajaksi.
std::string muunna_kellonajaksi(double aika)
{
    int int_aika =(int) aika;
    int minuutit = int_aika%60;
    int tunnit = aika / 60;
    std::string kello;
    if((minuutit < 10)&&(tunnit < 10))
         kello = "0"+std::to_string(tunnit) + ":0"+std::to_string(minuutit);
    else if(minuutit < 10)
         kello = std::to_string(tunnit) + ":0"+std::to_string(minuutit);
    else if(tunnit < 10)
         kello = "0"+std::to_string(tunnit) + ":"+std::to_string(minuutit);
    else
         kello = std::to_string(tunnit) + ":"+std::to_string(minuutit);

    return kello;
}

#ifndef _UTILITY_HH
#define _UTILITY_HH
#include <string>

#ifndef _WIN32

  #ifndef _MEMORYLIMIT
    #define _MEMORYLIMIT 128
  #endif
  #define _MEMORYLIMITBYTES _MEMORYLIMIT * 1024 * 1024
  #ifndef _NOMEMORYLIMITS
    #include <sys/resource.h>
  #endif
#endif

void set_limits();
double muuta_string_doubleksi(const std::string& mjono);
double muunna_minuuteiksi(std::string aika);
std::string muunna_kellonajaksi(double aika);

#endif

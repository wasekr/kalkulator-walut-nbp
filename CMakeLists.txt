#cmake_minimum_required(VERSION 4.1)
#by dzialalo tez na ubuntu
cmake_minimum_required(VERSION 3.28)

project(projekt_kalkulator_walut)

set(CMAKE_CXX_STANDARD 20)

#to dodalem bo bez tego biblioteki generowaly za duzy plik tymczasowy z informacjami do debuggowania ze sie nie kompilowalo
if(MINGW)
    add_compile_options(-Wa,-mbig-obj)
endif()

#modul by moc pobierac zewnetrzne zasoby (biblioteki) z internetu np github bo c++ nie ma wbudowanego menedzera pakietow
#jak np pip w pythonie
include(FetchContent)

#deklaracja czyli okreslamy ktora paczke bedziemy pobierac
#json to nazwa (nasz wewnetrzny identyfikator na bilbioteke)
#git tag kotra wersja
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

#pobieramy ta zadeklarowana biblioteke
FetchContent_MakeAvailable(json)


FetchContent_Declare(cli11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG v2.4.2
)
FetchContent_MakeAvailable(cli11)

FetchContent_Declare(httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
        GIT_TAG v0.15.3
)
FetchContent_MakeAvailable(httplib)

#dodanie pliku wykonywalnego (koncowo chcemy zbudowac .exe)
#projekt_kalkulator_walut to nazwa programu
#po nazwie programu podajemy pliki zrodlowe z ktoruch ma byc zbudowany program
add_executable(projekt_kalkulator_walut main.cpp)

#linkowanie (dolacza te biblioteki do projektu)
#private - program uzywa tych biblitek tylko dla siebie (bo to aplikacja koncowa a nie kolejna biblioteka)
#po fetch content make available czytany jest cmake pobieranej biblioteki w ktorym sa zdefiniowane te nazwy
# i w dokumentacji pisze np Dla nlohmann/json: "To use this library from CMake, link against the nlohmann_json::nlohmann_json target."
target_link_libraries(projekt_kalkulator_walut PRIVATE
        nlohmann_json::nlohmann_json
        CLI11::CLI11
        httplib::httplib
)

# Pakujemy biblioteki systemowe MinGW do srodka .exe, zeby program dzialal poza CLionem na kazdym Windowsie.
if(MINGW)
    target_link_options(projekt_kalkulator_walut PRIVATE "-static")
endif()

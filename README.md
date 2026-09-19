# -- English version -- 
# NBP Currency Calculator
#### Video Demo: https://youtu.be/Tvw5YFvq44I
#### Description:

The NBP Currency Calculator is a comprehensive, command-line interface (CLI) application written in C++ that allows users to perform real-time currency conversions from source (-z flag) to target (-n flag) currency. By leveraging the official API provided by the National Bank of Poland (Narodowy Bank Polski - NBP), the program fetches up-to-date exchange rates, ensuring highly accurate financial calculations. This tool aims to demonstrate proficiency in C++, network programming, API integration, and file handling within a compiled language environment.

### Motivation and Design Choices
This decision was driven by a desire to explore modern C++ paradigms, package management via CMake, and the integration of third-party header-only libraries. The application is designed to be lightweight, fast, and entirely terminal-based, catering to users who prefer quick, keyboard-driven tools over graphical user interfaces.

To build this, I relied on several highly regarded open-source libraries:
* **CLI11**: Instead of manually parsing `argc` and `argv` arrays (which can quickly become messy and error-prone), I integrated CLI11. It provides a robust, highly customizable framework for defining required arguments, optional flags, and generating automatic help menus.
* **cpp-httplib**: For the networking layer, I needed a reliable way to execute HTTP GET requests without the overhead of massive libraries like libcurl. `cpp-httplib` is a header-only solution that perfectly handles the synchronous API calls to the NBP servers.
* **nlohmann/json**: Often referred to as "JSON for Modern C++", this library makes parsing the HTTP response body incredibly intuitive, mirroring how JSON is handled in dynamic languages like Python or JavaScript.

### Core Features
1. **Real-Time Currency Conversion**: The user can input any numerical amount and specify the source and target currencies using standard three-letter abbreviations (e.g., USD, EUR, PLN). The application dynamically queries the NBP API, retrieves the mid-market exchange rates, and calculates the exact equivalent value.
2. **Currency Abbreviation Lookup**: Users unfamiliar with the exact currency codes can trigger a built-in dictionary flag. The program will fetch the current NBP table and print a formatted list of all available currencies and their corresponding abbreviations directly in the console.
3. **Persistent Local History (CSV Logging)**: Every successful currency conversion is automatically logged into a local file named `history.csv`. By utilizing `std::ofstream` in append mode (`std::ios::app`), the application maintains a persistent record of the user's queries across different sessions. This data includes the initial amount, source currency, target currency, and the calculated result, making it perfectly formatted for importing into spreadsheet software like Excel.
4. **Robust Error Handling**: The application gracefully handles various edge cases, including loss of internet connectivity, invalid currency codes, and malformed API responses, providing clear, user-friendly error messages in the terminal instead of crashing abruptly.

### Project Structure
* `main.cpp`: The core source code file containing the `main()` execution thread, the HTTP request logic (`get_exchange_rate` and `display_list_of_abbreviations` functions), and the file I/O operations for the CSV history logger.
* `CMakeLists.txt`: The configuration file used by the CMake build system to link the necessary libraries and compile the C++ source code into a standalone executable tailored to the host operating system.
* `history.csv`: A dynamically generated text file that stores the chronological log of all successful calculations. Note that this file is created automatically upon the first successful execution of a conversion command.

### Compilation and Usage
To compile the project, you must have a modern C++ compiler and CMake installed. Once built, the application is invoked entirely via the terminal emulator.

**View Help Menu:**
`./projekt_kalkulator_walut --help`

**View Available Currency Codes (abbreviations):**
`./projekt_kalkulator_walut -l`
*This flag bypasses the conversion logic and exclusively prints the supported NBP currency list.*

**Perform a Conversion:**
The application requires three arguments to perform a calculation: `-k` (amount), `-z` (source currency), and `-n` (target currency).
`./projekt_kalkulator_walut -k 100 -z usd -n pln`

*Expected Output:*
```Pobieram kursy walut ....
-----------------WYNIK-----------------
100 w usd jest warte: 400.50 w pln
---------------------------------------
Saved query into history.csv file.
```
### Acknowledgments
During the development of this project, artificial intelligence tools were utilized in a Code Reviewer capacity. AI assistance was instrumental in debugging complex CMake configuration issues, optimizing MinGW compilation on Windows machines, and resolving UTF-8 console output encoding challenges.
# -- Polish version --
# 💱Kalkulator Walutowy NBP

Konsolowa aplikacja napisana w języku C++, służąca do przeliczania walut w czasie rzeczywistym na podstawie aktualnych kursów udostępnianych przez API Narodowego Banku Polskiego (NBP).

## 🚀 Funkcjonalności
- Pobieranie aktualnych kursów walut bezpośrednio z serwerów NBP.

- Wyświetlanie listy wszystkich dostępnych skrótów walut.

- Przeliczanie dowolnych kwot między dwiema różnymi walutami.

- Obsługa błędów (np. brak połączenia z internetem, niepoprawna nazwa waluty).

- Funkcjonalny interfejs wiersza poleceń (CLI) z wbudowanym systemem pomocy.

## 🛠 Wykorzystane technologie i biblioteki
Projekt został zbudowany przy użyciu systemu CMake i korzysta z nowoczesnych bibliotek typu header-only:

- CLI11 - do obsługi argumentów wiersza poleceń.

- nlohmann/json - do parsowania odpowiedzi z API NBP w formacie JSON.

- cpp-httplib - do nawiązywania połączeń HTTP i pobierania danych z sieci.

## 📖 Instrukcja obsługi
Program obsługuje się poprzez przekazywanie argumentów przy uruchamianiu.

Wyświetlenie pomocy:
```
Wyświetlenie tabeli dostępnych walut:
./projekt_kalkulator_walut --help

Wyświetlanie listy jaka waluta jaki ma skrót:
./projekt_kalkulator_walut -l

Przeliczenie kwoty:
(Wymagane parametry: -k kwota, -z waluta źródłowa, -n waluta docelowa)
./projekt_kalkulator_walut -k 100 -z usd -n pln
```

## 🤖 Deklaracja użycia AI
Podczas pisania kodu oraz rozwiązywania problemów ze środowiskiem (takich jak konfiguracja CMake, optymalizacja kompilacji na MinGW czy obsługa kodowania UTF-8 w terminalu Windows). Sztuczna inteligencja pełniła rolę przewodnika (Code Reviewer), pomagając w zrozumieniu błędów kompilatora.

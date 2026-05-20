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
Zgodnie z wytycznymi dotyczącymi realizacji projektu, oświadczam, że podczas pisania kodu oraz rozwiązywania problemów ze środowiskiem (takich jak konfiguracja CMake, optymalizacja kompilacji na MinGW czy obsługa kodowania UTF-8 w terminalu Windows). Sztuczna inteligencja pełniła rolę przewodnika (Code Reviewer), pomagając w zrozumieniu błędów kompilatora.
# Papildoma užduotis – `std::string` ir asociatyvių konteinerių naudojimas

## Programos aprašymas

Šioje programoje panaudoti `std::string` ir asociatyvūs STL konteineriai (`std::map`, `std::set`), skirti teksto analizei atlikti.

Programa leidžia:

* nuskaityti tekstą iš failo
* suskaičiuoti kiekvieno žodžio pasikartojimų skaičių
* ignoruoti skyrybos ženklus
* išvesti žodžius, kurie pasikartojo daugiau nei vieną kartą
* sudaryti žodžių ir jų eilučių numerių tekstinį failą (cross-reference)
* surasti visus URL adresus tekste
* rezultatus išsaugoti atskiruose failuose

---

## Naudoti konteineriai

### `std::map`

Naudojamas žodžių pasikartojimų skaičiavimui.

```cpp
std::map<std::string, int> wordCount;
```

Žodis naudojamas kaip raktas (`key`), o jo pasikartojimų skaičius – kaip reikšmė (`value`).

---

### `std::map<std::string, std::set<int>>`

Naudojamas cross-reference lentelės sudarymui.

```cpp
std::map<std::string, std::set<int>> wordLines;
```

Kiekvienam žodžiui saugomas eilučių numerių rinkinys, kuriuose tas žodis buvo rastas.

---

### `std::set`

Naudojamas eilučių numeriams saugoti.

Privalumai:

* automatinis rūšiavimas
* nėra pasikartojančių reikšmių
* greita paieška

---

## Žodžių pasikartojimų analizė

Programa nuskaito tekstą eilutė po eilutės ir:

1. pašalina skyrybos ženklus;
2. konvertuoja tekstą į mažąsias raides;
3. išskiria atskirus žodžius;
4. skaičiuoja jų pasikartojimus.

### Pavyzdys

Tekstas:

```text
Vilnius yra Lietuvos sostinė.
Vilnius yra didžiausias Lietuvos miestas.
```

Rezultatas:

```text
vilnius : 2
yra : 2
lietuvos : 2
```

---

## Cross-reference lentelė

Programa sukuria failą, kuriame nurodomos eilutės, kuriose pasikartoja žodžiai.

### Pavyzdys

Rezultatas:

```text
vilnius : 1 2
yra : 1 2
lietuvos : 1 2
```

Tai leidžia greitai surasti visas vietas tekste, kuriose buvo panaudotas konkretus žodis.

---

## URL adresų paieška

Programa taip pat analizuoja tekstą ir suranda URL adresus.

Atpažįstami formatai:

```text
https://www.vu.lt
https://vu.lt
www.vu.lt
vu.lt
```

Rasti URL adresai išvedami į atskirą rezultatų failą.

### Pavyzdys

Tekstas:

```text
Daugiau informacijos rasite https://www.vu.lt
arba www.wikipedia.org svetainėse.
```

Rezultatas:

```text
https://www.vu.lt
www.wikipedia.org
```

---

## Rezultatų failai

Programa sugeneruoja šiuos failus:

### Žodžių pasikartojimai

```text
word_count.txt
```

Faile pateikiami visi žodžiai, kurie pasikartojo daugiau nei vieną kartą, bei jų pasikartojimų skaičius.

---

### Cross-reference lentelė

```text
cross_reference.txt
```

Faile pateikiami žodžiai ir eilučių numeriai, kuriuose jie buvo rasti.

---

### URL adresai

```text
found_urls.txt
```

Faile pateikiami visi tekste surasti URL adresai.

---

## Programos veikimo schema

1. Nuskaitomas tekstinis failas.
2. Apdorojami žodžiai ir pašalinami skyrybos ženklai.
3. Skaičiuojami žodžių pasikartojimai.
4. Fiksuojamos eilučių pozicijos.
5. Surenkami URL adresai.
6. Sugeneruojami rezultatų failai.

---

## Išvados

Atliekant užduotį buvo praktiškai pritaikyti:

* `std::string`
* `std::map`
* `std::set`
* failų skaitymas ir rašymas

Asociatyvūs konteineriai leido efektyviai realizuoti žodžių dažnių analizę, cross-reference lentelės sudarymą bei URL adresų paiešką tekste.

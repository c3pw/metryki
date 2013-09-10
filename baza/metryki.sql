BEGIN TRANSACTION;

PRAGMA foreign_keys = ON;

CREATE TABLE slownik_typow
     (
     nazwa varchar(30),
     opis TEXT,
     PRIMARY KEY (nazwa)
     );

CREATE TABLE slownik_stanowisk
     (
     identyfikator_stanowiska varchar(30),
     lokalizacja_stanowiska varchar(30),
     opis_stanowiska TEXT,
     PRIMARY KEY (identyfikator_stanowiska)
     );

CREATE TABLE urzadzenia
     (
     identyfikator_urzadzenia varchar(50),
     typ_urzadzenia varchar(30) not null,
     identyfikator_stanowiska varchar(30) not null,
     opis text,
     PRIMARY KEY (identyfikator_urzadzenia),
     FOREIGN KEY(typ_urzadzenia) REFERENCES slownik_typow(nazwa) ON UPDATE CASCADE,
     FOREIGN KEY(identyfikator_stanowiska) REFERENCES slownik_stanowisk(identyfikator_stanowiska) ON UPDATE CASCADE
     );

CREATE TABLE slownik_atrybutow
     (
     nazwa_atrybutu varchar(30),
     opis TEXT,
     PRIMARY KEY (nazwa_atrybutu)
     );
CREATE TABLE atrybuty_urzadzen 
     (
     identyfikator_urzadzenia varchar(50),
     nazwa_atrybutu varchar(30),
     wartosc varchar(100),
     PRIMARY KEY (identyfikator_urzadzenia, nazwa_atrybutu)
     FOREIGN KEY (identyfikator_urzadzenia) REFERENCES urzadzenia(identyfikator),
     FOREIGN KEY (nazwa_atrybutu) REFERENCES slownik_atrybutow(nazwa_atrybutu)
     );
CREATE TABLE slownik_podzespolow
     (
     nazwa varchar(30),
     PRIMARY KEY (nazwa)
     );
CREATE TABLE podzespoly_urzadzen
     (
     identyfikator INTEGER,
     identyfikator_urzadzenia varchar(50),
     nazwa_podzespolu varchar(30),
     PRIMARY KEY (identyfikator),
     FOREIGN KEY (identyfikator_urzadzenia) REFERENCES urzadzenia(identyfikator),
     FOREIGN KEY (nazwa_podzespolu) REFERENCES slownik_podzespolow(nazwa)
     );
CREATE TABLE awarie 
     (
     id INTEGER,
     identyfikator_urzadzenia varchar(50),
     data_wykrycia date not null,
     opis_awarii TEXT,
     data_naprawy date,
     opis_czynnosci_naprawczych TEXT,
     osoba_wykonujaca varchar(50),
     PRIMARY KEY (id),
     FOREIGN KEY (identyfikator_urzadzenia) REFERENCES urzadzenia(identyfikator)
     );
CREATE TABLE czynnosci_konserwacyjne
     (
     id INTEGER,
     identyfikator_urzadzenia varchar(50) not null,
     data date,
     opis_czynnosci TEXT,
     osoba_wykonujaca varchar(50),
     PRIMARY KEY (id),
     FOREIGN KEY (identyfikator_urzadzenia) REFERENCES urzadzenia(identyfikator)
     );
CREATE TABLE inne_zdarzenia 
     (
     id INTEGER,
     identyfikator_urzadzenia varchar(50) not null,
     data_zdarzenia date,
     opis_zdarzenia TEXT,
     PRIMARY KEY (id),
     FOREIGN KEY (identyfikator_urzadzenia) REFERENCES urzadzenia(identyfikator)
     );
COMMIT;

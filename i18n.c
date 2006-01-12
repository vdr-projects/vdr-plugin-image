/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004-2006 Andreas Brachold    <anbr at users.berlios.de>
 * based on (C) 2003 Kai Tobias Burwieck      <kai-at-burwieck.net>
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * Or, point your browser to http://www.gnu.org/copyleft/gpl.html
 */

#include <vdr/config.h>
#include "i18n.h"

const tI18nPhrase Phrases[] = {
  { "Image", // English
    "Bilder", // German
    "", // Slovenian
    "Immagine", // Italian
    "Beelden", // Dutch
    "Imagens", // Portuguese
    "Images", // French
    "", // Norwegian
    "Kuvat",    // Finnish
    "", // Polish
    "Imágenes",  // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¸×ŞÑàĞÖÕİØï", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "A Image Viewer plugin", // English
    "Ein Bildbetrachter Plugin", // German
    "", // Slovenian
    "Un visore di immagine plugin", // Italian
    "Een Kijker van het Beeld plugin", // Dutch
    "Um visor da imagem plugin", // Portuguese
    "Visualisateur d'images", // French
    "", // Norwegian
    "Katso valokuvia ruudullasi",  // Finnish
    "", // Polish
    "Un espectador de la imagen plugin", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¿ÛĞÓØİ ÔÛï ßàŞáÜŞâàĞ Ø×ŞÑàĞÖÕİØÙ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Image browser", // English
    "Bilder Verzeichnisanzeige", // German
    "Image navigator", // Slovenian
    "Browser di immagine", // Italian
    "Browser van het beeld", // Dutch
    "Browser da imagem", // Portuguese
    "Navigateur images", // French
    "", // Norwegian
    "Kuvat - selain", // Finnish
    "", // Polish
    "Browser de la imagen", // Spanish
    "Image endiksi fakelon", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¿ŞÚĞ×Ğâì ßĞßÚã á Ø×ŞÑàĞÖÕİØïÜØ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Image source", // English
    "Bilder-Datenträger", // German
    "Image izvor", // Slovenian
    "Fonte di immagine", // Italian
    "De bron van het beeld", // Dutch
    "Fonte da imagem", // Portuguese
    "Source images", // French
    "", // Norwegian
    "Kuvat - lähteet", // Finnish
    "", // Polish
    "Fuente de la imagen", // Spanish
    "Pigi Image", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "½ŞáØâÕÛì(source)", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Parent", // English
    "Zurück", // German
    "Nazaj", // Slovenian
    "precursore", // Italian
    "voorloper", // Dutch
    "precursor", // Portuguese
    "", // French
    "", // Norwegian
    "Takaisin", // Finnish
    "", // Polish
    "Predecesor", // Spanish
    "Piso", // Greek
    "Tillbaka", // Swedish
    "", // Romanian
    "", // Hugarian
    "Anterior", // Catalan
    "½Ğ×ĞÔ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Select", // English
    "Auswählen", // German
    "Izberi", // Slovenian
    "Prescelto", // Italian
    "Selecteer", // Dutch
    "Seleto", // Portuguese
    "Sélectionner", // French
    "", // Norwegian
    "Valitse", // Finnish
    "", // Polish
    "Seleccionar", // Spanish
    "Epilogi", // Greek
    "Välj", // Swedish
    "", // Romanian
    "", // Hugarian
    "Escollir", // Catalan
    "²ëÑàĞâì", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Play",
    "Wiedergabe",
    "Predvajaj",
    "Riproduci",
    "Weergeven",
    "",// TODO
    "Lecture",
    "",// TODO
    "Toista",
    "Odtworzenie",
    "Reproducir",
    "ÁíáğáñáãùãŞ",
    "Spela upp",
    "Redare",
    "Lejátszás",
    "Reproduir",
    "²ŞáßàŞØ×ÒÕÔÕİØÕ",
    "Start",
    "Start",
    "Afspil",
  },
  { "Back",
    "Zurück",
    "Nazaj",
    "Indietro",
    "Terug",
    "Voltar",
    "Retour",
    "Tilbake",
    "Takaisin",
    "Wstecz",
    "Retornar",
    "Ğßóù",
    "Tillbaka",
    "Înapoi",
    "Vissza",
    "Retornar",
    "½Ğ×ĞÔ",
    "Nazad",
    "Tagasi",
    "Tilbage",
  },
  { "Error scanning directory!", // English
    "Fehler beim Lesen des Verzeichnisses!", // German
    "Napaka pri pregledovanju direktorija!", // Slovenian
    "Indice di esame di errori!", // Italian
    "Het aftastenfolder van de fout!", // Dutch
    "Diretório da exploração do erro!", // Portuguese
    "Erreur de parcours du répertoire!", // French
    "", // Norwegian
    "Hakemiston selaus epäonnistui!", // Finnish
    "", // Polish
    "¡Error al leer una carpeta!", // Spanish
    "Lathos stin sarosi tou fakelou!", // Greek
    "Kunde inte läsa katalogen!", // Swedish
    "", // Romanian
    "", // Hugarian
    "Error al llegir una carpeta!", // Catalan
    "¾èØÑÚĞ çâÕİØï ÒëÑàĞİİŞÙ ÔØàÕÚâŞàØØ!", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Data medium", // English
    "Datenträger", // German
    "Izvor", // Slovenian
    "Mezzo di dati", // Italian
    "Het middel van gegevens", // Dutch
    "Meio de dados", // Portuguese
    "Source", // French
    "", // Norwegian
    "Lähde", // Finnish
    "", // Polish
    "Medio de datos", // Spanish
    "Pigi", // Greek
    "Källa", // Swedish
    "", // Romanian
    "", // Hugarian
    "Orígen", // Catalan
    "½ŞáØâÕÛì", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Mount", // English
    "Einbinden", // German
    "Priklopi", // Slovenian
    "supporto", // Italian
    "Zet op", // Dutch
    "Montagem", // Portuguese
    "Monter", // French
    "", // Norwegian
    "Kiinnitä", // Finnish
    "", // Polish
    "Montaje", // Spanish
    "Sindesi", // Greek
    "Montera", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¿ŞÔÚÛîçØâì", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Unmount", // English
    "Aushängen", // German
    "Izklopi", // Slovenian
    "smonti", // Italian
    "unmount", // Dutch
    "unmount", // Portuguese
    "Démonter", // French
    "", // Norwegian
    "Irrota", // Finnish
    "", // Polish
    "Unmount", // Spanish
    "Aposindesi", // Greek
    "Avmontera", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¾âÚÛîçâì", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Selected data medium is not mounted!", // English
    "Ausgewählter Datenträger ist nicht eingebunden!", // German
    "Izbran izvor ni prikljucen!", // Slovenian
    "Il mezzo di dati selezionato non è montato!", // Italian
    "Het geselecteerde gegevensmiddel wordt niet opgezet!", // Dutch
    "O meio de dados selecionado não é montado!", // Portuguese
    "Source sélectionnée non montée!", // French
    "", // Norwegian
    "Valittua lähdettä ei ole kiinnitetty!", // Finnish
    "", // Polish
    "¡El origen deseado no està montado!", // Spanish
    "Epilegmeni Pigi den ine sindemeni!", // Greek
    "Den valda källan är inte monterad!", // Swedish
    "", // Romanian
    "", // Hugarian
    "l'Origen sel.leccionat no està muntat!", // Catalan
    "²ëÑàĞİİëÙ İŞáØâÕÛì İÕ ßŞÔÚÛîçÕİ!", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Mount succeeded", // English
    "Einbinden erfolgreich", // German
    "Priklop izveden", // Slovenian
    "Il supporto è riuscito", // Italian
    "Zet volgend op", // Dutch
    "Montagem sucedida", // Portuguese
    "Montage réussi", // French
    "", // Norwegian
    "Kiinnittäminen onnistui", // Finnish
    "", // Polish
    "mount correcto", // Spanish
    "I sindesi petixe", // Greek
    "Monteringen lyckades", // Swedish
    "", // Romanian
    "", // Hugarian
    "mount correcte", // Catalan
    "¿ŞÔÚÛîçÕİØÕ ßàŞèÛŞ ãáßÕèİŞ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Mount failed!", // English
    "Einbinden fehlgeschlagen!", // German
    "Napaka pri priklopu!", // Slovenian
    "Il supporto si guasta!", // Italian
    "Zet ontbroken op!", // Dutch
    "A montagem falha!", // Portuguese
    "Echec du montage!", // French
    "", // Norwegian
    "Kiinnittäminen epäonnistui!", // Finnish
    "", // Polish
    "¡No he podido montar!", // Spanish
    "I sindesi apetixe!", // Greek
    "Monteringen misslyckades!", // Swedish
    "", // Romanian
    "", // Hugarian
    "No he pogut muntar!", // Catalan
    "¾èØÑÚĞ ßŞÔÚÛîçÕİØï!", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Unmount succeeded!", // English
    "Aushängen erfolgreich!", // German
    "Izklop izveden!", // Slovenian
    "Smonti riuscito!", // Italian
    "Volgende Unmount!", // Dutch
    "Unmount sucedido!", // Portuguese
    "Démontage réussi!", // French
    "", // Norwegian
    "Irrottaminen onnistui!", // Finnish
    "", // Polish
    "Éxito al unmount", // Spanish
    "I aposindesi itan epitixisi!", // Greek
    "Avmonteringen lyckades!", // Swedish
    "", // Romanian
    "", // Hugarian
    "unmount amb èxit!", // Catalan
    "¾âÚÛîçÕİØÕ ßàŞèÛŞ ãáßÕèİŞ!", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Unmount failed!", // English
    "Aushängen fehlgeschlagen!", // German
    "Napaka pri izklopu!", // Slovenian
    "Smonti venuto a mancare!", // Italian
    "Ontbroken Unmount!", // Dutch
    "Unmount falhado!", // Portuguese
    "Echec du démontage!", // French
    "", // Norwegian
    "Irrottaminen epäonnistui!", // Finnish
    "", // Polish
    "¡No puedo desmontar!", // Spanish
    "I aposindesi den itan epitixis!", // Greek
    "Avmonteringen misslyckades!", // Swedish
    "", // Romanian
    "", // Hugarian
    "No puc desmontar!",
    "¾èØÑÚĞ ŞâÚÛîçÕİØï!", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Eject failed!", // English
    "Auswerfen fehlgeschlagen!", // German
    "Napaka pri izmetu!", // Slovenian
    "Espella venuto a mancare!", // Italian
    "Werp ontbroken uit!", // Dutch
    "Ejete falhado!", // Portuguese
    "Echec de l'éjection!", // French
    "", // Norwegian
    "Avaaminen epäonnistui!", // Finnish
    "", // Polish
    "¡No puedo expulsar!", // Spanish
    "I apovoli apetixe!", // Greek
    "Mata ut!", // Swedish
    "", // Romanian
    "", // Hugarian
    "No puc expulsar!", // Catalan
    "¾èØÑÚĞ ÒëÑàŞáĞ ÔØáÚĞ!", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Select picture via key 1..9!", // English
    "Bildauswahl über Taste 1..9!", // German
    "", // Slovenian
    "Selezioni l'immagine via il tasto 1..9!", // Italian
    "Selecteer beeld via knoop 1..9!", // Dutch
    "Selecione o retrato através da tecla 1..9!", // Portuguese
    "Selectionner l'image (touches 1..9)!", // French
    "", // Norwegian
    "Valitse kuva näppäimillä 1..9!", // Finnish
    "", // Polish
    "¡Seleccione el cuadro vía el botón 1..9!", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "²ëÑŞà Ø×ŞÑàĞÖÕİİØÙ ßàØ ßŞÜŞéØ ÚİŞßŞÚ 1..9!", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Building slide show...", // English
    "Erzeuge Diavorführung...", // German
    "", // Slovenian
    "Proiezione di diapositive Della Costruzione...", // Italian
    "De Show van de Dia van de bouw...", // Dutch
    "Mostra De Corrediça Do Edifício...", // Portuguese
    "Contruction du SlideShow...", // French
    "", // Norwegian
    "Laaditaan diaesitystä..", // Finnish
    "", // Polish
    "Demostración De Diapositiva Del Edificio...", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "ÁĞ×ÔĞİØÕ ´ØĞäØÛìÜĞ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Scanning directory...", // English
    "Durchsuche Verzeichnis...", // German
    "", // Slovenian
    "Indice di esame...", // Italian
    "De folder van het aftasten...", // Dutch
    "Diretório da exploração...", // Portuguese
    "Scannage du répertoire...", // French
    "", // Norwegian
    "Selataan hakemistoa...", // Finnish
    "", // Polish
    "Leyendo las carpetas..", // Spanish
    "", // Greek
    "Söker igenom katalog...", // Swedish
    "", // Romanian
    "", // Hugarian
    "Revisant les carpetes..", // Catalan
    "¿àŞáÜâà ÔØàÕÚâŞàØØ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "No Files!", // English
    "Keine Dateien!", // German
    "", // Slovenian
    "Nessun lime!", // Italian
    "Geen dossiers!", // Dutch
    "Nenhumas Limas!", // Portuguese
    "Pas de fichiers !", // French
    "", // Norwegian
    "Ei tiedostoja!", // Finnish
    "", // Polish
    "¡Ningunos Archivos!", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "½ØçÕÓŞ İÕ İĞÙÔÕİŞ!", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Slide show", // English
    "Diavorführung", // German
    "", // Slovenian
    "Proiezione di diapositive", // Italian
    "De show van de dia", // Dutch
    "Mostra de corrediça", // Portuguese
    "Projection de diapositives", // French
    "", // Norwegian
    "Käytä diaesitystä", // Finnish
    "", // Polish
    "Demostración de diapositiva", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "´ØĞäØÛìÜ?", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Slide duration (sec)", // English
    "Anzeigedauer (Sek)", // German
    "", // Slovenian
    "Faccia scorrere la durata (sec)", // Italian
    "De duur van de dia (seconde)", // Dutch
    "Deslize a duração (segundo)", // Portuguese
    "Durée entre les images (Sec)", // French
    "", // Norwegian
    "Dian esitysaika (s)", // Finnish
    "", // Polish
    "Resbale la duración (sec)", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "²àÕÜï ŞâŞÑàĞÖÕİØï (áÕÚ)", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Directory with temporary files", // English
    "Verzeichnis mit temporären Dateien", // German
    "", // Slovenian
    "Indice con le lime provvisorie", // Italian
    "Folder met tijdelijke dossiers", // Dutch
    "Diretório com limas provisórias", // Portuguese
    "Répertoire temporaire", // French
    "", // Norwegian
    "Väliaikaistiedostot", // Finnish
    "", // Polish
    "Directorio con los ficheros temporales", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "Â¼À ÔØàÕÚâŞàØï", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Repeat slide show", // English
    "Wiederholung der Diavorführung", // German
    "", // Slovenian
    "Ripeti la proiezione di diapositive", // Italian
    "Herhaal diashow", // Dutch
    "Repita a mostra de corrediça", // Portuguese
    "Répéter le SlideShow", // French
    "", // Norwegian
    "Diaesityksen uudelleentoisto", // Finnish
    "", // Polish
    "Repita la demostración de diapositiva", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¿ŞÒâŞà ÔØĞäØÛìÜĞ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Show numbers on index image", // English
    "Zeige Zahlen im Indexbild", // German
    "", // Slovenian
    "Mostri i numeri sull'immagine di indice", // Italian
    "Toon aantallen op indexbeeld", // Dutch
    "Mostre números na imagem do índice", // Portuguese
    "Afficher nombre sur la page d'index", // French
    "", // Norwegian
    "Näytä numerot indeksikuvassa", // Finnish
    "", // Polish
    "Demuestre los números en imagen del índice", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¿ŞÚĞ×Ğâì İŞÜÕàĞ Ò ØİÔÕÚáÕ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Live Audio from primary Device", // English
    "Live Audio vom primären Gerät", // German
    "", // Slovenian
    "Audio in tensione dal dispositivo primario", // Italian
    "Leef Audio van primair Apparaat", // Dutch
    "Áudio vivo do dispositivo preliminar", // Portuguese
    "Audio en direct", // French
    "", // Norwegian
    "Live-ääni ensisijaiselta sovittimelta", // Finnish
    "", // Polish
    "Audio vivo del dispositivo primario", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¸áßŞÛì×ŞÒĞâì ĞÚâØÒİŞÕ(Live) ×ÒãÚŞÒŞÕ áŞßàŞÒŞÖÔÕİØÕ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Convert...", // English
    "Wandle...", // German
    "", // Slovenian
    "Convertito...", // Italian
    "Zet om...", // Dutch
    "Converso...", // Portuguese
    "Convertion...", // French
    "", // Norwegian
    "Konvertoi...", // Finnish
    "", // Polish
    "Convertido...", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "ÚŞİÒÕàâĞæØï", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },  
  { "Zoom", // English
    "Vergrößere", // German
    "", // Slovenian
    "Zoom", // Italian
    "Gezoem", // Dutch
    "Zumbido", // Portuguese
    "Zoom", // French
    "", // Norwegian
    "Suurenna", // Finnish
    "", // Polish
    "Zumbido", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¿àØÑÛØ×Øâì(Zoom)", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },  
  { "Execute", // English
    "Ausführen", // German
    "", // Slovenian
    "Esegua", // Italian
    "Voer uit", // Dutch
    "Execute", // Portuguese
    "Executer", // French
    "", // Norwegian
    "Suorita", // Finnish
    "", // Polish
    "Ejecútese", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "²ëßŞÛİØâì", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },  
  { "Operation failed", // English
    "Vorgang fehlgeschlagen", // German
    "", // Slovenian
    "Il funzionamento viene a mancare", // Italian
    "Ontbroken verrichting", // Dutch
    "A operação falhou", // Portuguese
    "Opération non réussie", // French
    "", // Norwegian
    "Toiminto epäonnistui", // Finnish
    "", // Polish
    "La operación falló", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¾ßÕàĞæØï ŞáâĞİŞÒÛÕİĞ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Image couldn't load", // English
    "Konnte Bild nicht lesen", // German
    "", // Slovenian
    "L'immagine non ha potuto caricare", // Italian
    "Het beeld kon niet laden", // Dutch
    "A imagem não podia carregar", // Portuguese
    "Impossible de charger l'image", // French
    "", // Norwegian
    "Kuvan lukeminen epäonnistui", // Finnish
    "", // Polish
    "La imagen no podía cargar", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¾èØÑÚĞ çâÕİØï äĞÙÛĞ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Script execution failed", // English
    "Scriptausführung fehlgeschlagen", // German
    "", // Slovenian
    "L'esecuzione dello scritto è venuto a mancare", // Italian
    "Ontbroken de uitvoering van het manuscript", // Dutch
    "A execução do certificado falhou", // Portuguese
    "Impossible d'exécuter le script", // French
    "", // Norwegian
    "Skriptin suoritus epäonnistui", // Finnish
    "", // Polish
    "La ejecución de la escritura falló", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "¾èØÑÚĞ ÒëßŞÛİÕİØï áÚàØßâĞ!", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Remove temporary files", // English
    "Lösche temporäre Dateien", // German
    "", // Slovenian
    "Rimuova le lime provvisorie", // Italian
    "Verwijder tijdelijke dossiers", // Dutch
    "Remova as limas provisórias", // Portuguese
    "Effacer les fichiers temporaires", // French
    "", // Norwegian
    "Tyhjennä väliaikaistiedostot", // Finnish
    "", // Polish
    "Quite los ficheros temporales", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "áâØàĞİØÕ tmp äĞÙÛŞÒ", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Border for Underscan (Height)", // English
    "Rand für Underscan (Höhe)", // German
    "", // Slovenian
    "Bordo per Underscan (altezza)", // Italian
    "Grens voor Underscan (Hoogte)", // Dutch
    "Beira para Underscan (altura)", // Portuguese
    "Frontière pour Underscan (taille)", // French
    "", // Norwegian
    "Reunuksen korkeus keskitykselle", // Finnish
    "", // Polish
    "Frontera para Underscan (altura)", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Border for Underscan (Width)", // English
    "Rand für Underscan (Breite)", // German
    "", // Slovenian
    "Bordo per Underscan (larghezza)", // Italian
    "Grens voor Underscan (Breedte)", // Dutch
    "Beira para Underscan (largura)", // Portuguese
    "Frontière pour Underscan (largeur)", // French
    "", // Norwegian
    "Reunuksen leveys keskitykselle", // Finnish
    "", // Polish
    "Frontera para Underscan (anchura)", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Show exif informations from image", // English
    "Zeigt Exif Informationen zum Bild", // German
    "", // Slovenian
    "Mostri le informazioni del exif dall'immagine", // Italian
    "Toon exif informatie van beeld", // Dutch
    "Mostre a informação do exif da imagem", // Portuguese
    "Montrez l'information d'exif de l'image", // French
    "", // Norwegian
    "", // Finnish
    "", // Polish
    "Demuestre la información del exif de la imagen", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Could not parse exif maker note!", // English
    "Konnte Exif Erstellungsanmerkung nicht analysieren!", // German
    "", // Slovenian
    "Non ha potuto analizzare la nota del creatore del exif!", // Italian
    "Kon exif maker geen nota ontleden!", // Dutch
    "Não podia analisar gramaticalmente a nota do fabricante do exif!", // Portuguese
    "N'a pas pu analyser la note de fabricant d'exif !", // French
    "", // Norwegian
    "", // Finnish
    "", // Polish
    "¡No podía analizar la nota del fabricante del exif!", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { "Could not load exif data from image!", // English
    "Konnte Exif Daten nicht vom Bild laden!", // German
    "", // Slovenian
    "Non ha potuto caricare i dati del exif dall'immagine!", // Italian
    "Kon exif geen gegevens van beeld laden!", // Dutch
    "Não podia carregar dados do exif da imagem!", // Portuguese
    "N'a pas pu charger des données d'exif de l'image !", // French
    "", // Norwegian
    "", // Finnish
    "", // Polish
    "¡No podía cargar datos del exif de imagen!", // Spanish
    "", // Greek
    "", // Swedish
    "", // Romanian
    "", // Hugarian
    "", // Catalan
    "", // Russian
    "", // Hrvatski
    "", // Eesti
    "", // Dansk
  },
  { NULL }
};

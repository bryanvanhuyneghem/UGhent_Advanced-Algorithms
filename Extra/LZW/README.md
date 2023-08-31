# Lempel-Ziv-Welch (LZW)

## Introductie

Lempel-Ziv-Welsch is een compressie-algoritme vernoemd naar zijn drie uitvinders: Abraham Lempel, Jacob Ziv en Terry Welch. 
Deze compressiemethode ligt aan de basis van het GIF-bestandsformaat (meer uitleg: [What's in a GIF](https://giflib.sourceforge.net/whatsinagif/)), 
maar lag ook aan de oorzaak van de controverse rond het GIF-formaat, en het ontstaan van het PNG-bestandsformaat (onofficieel staat het acroniem PNG voor 'PNG's not GIF').

Het LZW compressie-algoritme werd in 1983 namelijk gepatenteerd (patent US4558302), en [hierdoor was voor elk programma dat GIF's kon genereren een licentie vereist
van vaak enkele duizenden dollars](https://en.wikipedia.org/wiki/GIF#Unisys_and_LZW_patent_enforcement). In 2004 is dit patent vervallen, waardoor dit dus niet langer relevant is.

Behalve in het GIF-bestandsformaat kan je LZW-compressie ook terugvinden in TIFF-bestanden en (oude) PDF-bestanden. 
Vanwege het patent werd het LZW compressie-algoritme taande de populariteit ervan, en kwamen er alternatieven
op de proppen zoals [DEFLATE](https://en.wikipedia.org/wiki/Deflate) dewelke LZ77 (een voorloper van LZW) en Huffman-codering combineert. 
## Opgave

Implementeer de volgende functies in [`lzw.cpp`](src/lzw.cpp):

1. `compress_lzw(std::string input)`
1. `decompress_lzw(std::string input)`

Hou voor beide compressietechnieken rekening met het aantal bits dat gebruikt wordt om de data voor te stellen (`DATABITS`) 
en het aantal bits dat gebruikt zal worden om de codewoorden in de compressie voor te stellen (`NUMBITS`).

We werken in dit labo met 7 databits en 12 bits om de codewoorden voor te stellen. Merk op dat een `char` in C++ eigenlijk uit 8 bits bestaat. 
We gaan er in dit labo daarom van uit dat de input ASCII-gecodeerde tekst is: deze codering loopt van 0 tem 127, en past dus in 7 bits.

Het is mogelijk dat tijdens het comprimeren/decomprimeren de tabel met codewoorden zodanig groot wordt dat de index niet meer met 
12 bits kan worden voorgesteld. Als dit voorvalt, dan wordt de tabel terug gereset naar de initiële toestand vooraleer verder te gaan.
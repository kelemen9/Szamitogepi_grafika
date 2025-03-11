#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//téglatest adataihoz: magasság, szélesség, hosszúság
typedef struct
{
    float height;
    float width;
    float length;
} Cuboid;

//függvény a téglatest méreteinek beállítására
void set_size(Cuboid *cuboid, float height, float width, float length)
{
    //minden méret pozitív legyen
    if (height > 0 && width > 0 && length > 0)
    {
        cuboid->length = length;
        cuboid->width = width;
        cuboid->height = height;
    }
    else
    {
        //bármelyik érték nem pozitív, hibaüzenet és kilépés a programból
        printf("Hibás méretek! Minden értéknek pozitívnak kell lennie.\n");
        exit(1);
    }
}

//függvény a téglatest térfogatának kiszámítására
float calc_volume(Cuboid cuboid)
{
    return cuboid.length * cuboid.width * cuboid.height;
}

//függvény a téglatest felszínének kiszámítására
float calc_surface(Cuboid cuboid)
{
    return 2 * (cuboid.width * cuboid.height + cuboid.height * cuboid.length + cuboid.length * cuboid.width);
}

//függvény annak ellenőrzésére, hogy a téglatestnek van-e négyzet alakú lapja
bool has_square_face(Cuboid cuboid)
{
    //ha bármelyik két él egyenlő, akkor van négyzet alakú lap
    return (cuboid.length == cuboid.width || cuboid.width == cuboid.height || cuboid.height == cuboid.length);
}

//függvény egy szám beolvasására, amely biztosítja, hogy csak pozitív számot fogad el
float read_input(char *msg)
{
    float number;
    bool valid = false;
    
    while (!valid)
    {
        printf("%s", msg);
        //beolvasás és ellenőrzés, hogy a szám pozitív-e
        if (scanf("%f", &number) == 1 && number > 0)
        {
            valid = true;
        }
        else
        {
            //hibás bemenet esetén hibaüzenet és újra bekérés
            printf("Hibás bemenet! Pozitív számot adjon meg.\n");
            while (getchar() != '\n'); // Bemeneti puffer ürítése
        }
    }
    return number;
}

//program
int main()
{
    Cuboid cuboid; //téglatest létrehozása

    //bekérjük a méreteket
    float length = read_input("A téglatest hossza: ");
    float width = read_input("A téglatest szélessége: ");
    float height = read_input("A téglatest magassága: ");

    //beállítjuk a téglatest méreteit
    set_size(&cuboid, height, width, length);

    //kiírjuk a térfogatot és a felszínt
    printf("A téglatest térfogata: %.2f\n", calc_volume(cuboid));
    printf("A téglatest felszíne: %.2f\n", calc_surface(cuboid));

    //van-e négyzet alakú lapja
    if (has_square_face(cuboid))
        printf("A téglatestnek van négyzet alakú lapja.\n");
    else
        printf("A téglatestnek nincs négyzet alakú lapja.\n");

    return 0;
}

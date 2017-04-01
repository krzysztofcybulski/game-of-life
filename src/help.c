#include <stdio.h>

void show_gol_help() {
	printf("Info and instuction about available function\n");
    printf("%-20s %s\n","SET_RULE", "set_rule <nazwa>");
    printf("%-20s %s\n","SHOW_RULES", "pokazuje dostepne zasady");
    printf("%-20s %s\n","SET_SIZE", "set_size <x> <y>");
    printf("%-20s %s\n","place", "place <x> <y>");
    printf("%-20s %s\n","GO", "go <n>");
    printf("%-20s %s\n","NEXT OR N", "przychodzi jedna generacje dalej");
    printf("%-20s %s\n","PLAY", "play <n> <delay> <name>");
    printf("%-20s %s\n","SHOW", "wyœwietla okno z wizualizacj¹ planszy");
    printf("%-20s %s\n","SAVE", "zapisuje plik .png o nazwie <name>");
    printf("%-20s %s\n","EXIT", "konczy program");
}
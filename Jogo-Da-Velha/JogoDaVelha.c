#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

GtkLabel *texto;

char str[] = "X";
#define atual str[0]
char label_texto[] = "Vez de 'X'";
char matriz[3][3];
char teve_ganhador = 0;

void inicializa_matriz(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            matriz[i][j] = 0;
        }
    }
    gtk_label_set_text(texto, label_texto);
}

void x_vence(){
    gtk_label_set_text(texto, "'X' GANHOU!!!");
    teve_ganhador = 1;
}

void o_vence(){
    gtk_label_set_text(texto, "'O' GANHOU!!!");
    teve_ganhador = 1;
}

void empate(){
    gtk_label_set_text(texto, "VELHA!!!");
}

void checa_ganhador(){
    int x, o;

    //verificando as linhas
    for(int i = 0; i < 3; i++){
        x = o = 0;
        for(int j = 0; j < 3; j++){
            if(matriz[i][j] == 'X') x++;
            else if(matriz[i][j] == 'O') o++;
        }
        if(x == 3){
            x_vence();
        }
        else if(o == 3){
            o_vence();
        }
    }

    //verificando as colunas
    for(int j = 0; j < 3; j++){
        x = o = 0;
        for(int i = 0; i < 3; i++){
            if(matriz[i][j] == 'X') x++;
            else if(matriz[i][j] == 'O') o++;
        }
        if(x == 3){
            x_vence();
        }
        else if(o == 3){
            o_vence();
        }
    }

    //verificando as diagonais
    if(matriz[0][0] == matriz[1][1] && matriz[0][0] == matriz[2][2]){
        if(matriz[0][0] == 'X')
            x_vence();
        else if(matriz[0][0] == 'O')
            o_vence();
    }

    if(matriz[0][2] == matriz[1][1] && matriz[0][2] == matriz[2][0]){
        if(matriz[0][2] == 'X')
            x_vence();
        else if(matriz[0][2] == 'O')
            o_vence();
    }

    //verificando se tem empate
    x = o = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(matriz[i][j] == 'X')
                x++;
            else if(matriz[i][j] == 'O')
                o++;
        }
    }

    if(x+o == 9 && teve_ganhador == 0){
        empate();
    }
}

void proximo(){
    if(atual == 'X') atual = 'O';
    else atual = 'X';
    
    label_texto[8] = atual;
    gtk_label_set_text(texto, label_texto);
    checa_ganhador();
}

void on_butao_0_0_clicked(GtkButton *button, gpointer data){
    if(matriz[0][0] == 0){
        gtk_button_set_label(button, str);
        matriz[0][0] = atual;
        proximo();
    }
}

void on_butao_0_1_clicked(GtkButton *button, gpointer data){
    if(matriz[0][1] == 0){
        gtk_button_set_label(button, str);
        matriz[0][1] = atual;
        proximo();
    }
}   

void on_butao_0_2_clicked(GtkButton *button, gpointer data){
    if(matriz[0][2] == 0){
        gtk_button_set_label(button, str);
        matriz[0][2] = atual;
        proximo();
    }
}

void on_butao_1_0_clicked(GtkButton *button, gpointer data){
    if(matriz[1][0] == 0){
        gtk_button_set_label(button, str);
        matriz[1][0] = atual;
        proximo();
    }
}

void on_butao_1_1_clicked(GtkButton *button, gpointer data){
    if(matriz[1][1] == 0){
        gtk_button_set_label(button, str);
        matriz[1][1] = atual;
        proximo();
    }
}

void on_butao_1_2_clicked(GtkButton *button, gpointer data){
    if(matriz[1][2] == 0){
        gtk_button_set_label(button, str);
        matriz[1][2] = atual;
        proximo();
    }
}

void on_butao_2_0_clicked(GtkButton *button, gpointer data){
    if(matriz[2][0] == 0){
        gtk_button_set_label(button, str);
        matriz[2][0] = atual;
        proximo();
    }
}

void on_butao_2_1_clicked(GtkButton *button, gpointer data){
    if(matriz[2][1] == 0){
        gtk_button_set_label(button, str);
        matriz[2][1] = atual;
        proximo();
    }
}

void on_butao_2_2_clicked(GtkButton *button, gpointer data){
    if(matriz[2][2] == 0){
        gtk_button_set_label(button, str);
        matriz[2][2] = atual;
        proximo();
    }
}

void on_main_window_destroy(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}

int main(int argc, char* argv[]){

    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new_from_file("JogoDaVelha.glade");

    gtk_builder_add_callback_symbols(
        builder, 
        "on_main_window_destroy",               G_CALLBACK(on_main_window_destroy),
        "on_butao_0_0_clicked",                 G_CALLBACK(on_butao_0_0_clicked),
        "on_butao_0_1_clicked",                 G_CALLBACK(on_butao_0_1_clicked),
        "on_butao_0_2_clicked",                 G_CALLBACK(on_butao_0_2_clicked),
        "on_butao_1_0_clicked",                 G_CALLBACK(on_butao_1_0_clicked),
        "on_butao_1_1_clicked",                 G_CALLBACK(on_butao_1_1_clicked),
        "on_butao_1_2_clicked",                 G_CALLBACK(on_butao_1_2_clicked),
        "on_butao_2_0_clicked",                 G_CALLBACK(on_butao_2_0_clicked),
        "on_butao_2_1_clicked",                 G_CALLBACK(on_butao_2_1_clicked),
        "on_butao_2_2_clicked",                 G_CALLBACK(on_butao_2_2_clicked),
    NULL);

    gtk_builder_connect_signals(builder, NULL);
 
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    texto = GTK_LABEL(gtk_builder_get_object(builder, "texto"));

    inicializa_matriz();

    gtk_widget_show_all(window);
    gtk_main(); 

    return 0;
}
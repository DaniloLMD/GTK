#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

GtkLabel *texto;
GtkLabel *placar;
GtkBuilder *builder;

void usar_estilo(){
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "static/JogoDaVelha.css", FALSE);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider),
     GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

char str[] = "X";
#define atual str[0]
char label_texto[] = "Vez de 'X'";
char matriz[3][3];
char teve_ganhador = 0;
int vitorias_x = 0, vitorias_o = 0;

void inicializa_matriz(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            matriz[i][j] = 0;
        }
    }
    gtk_label_set_text(texto, label_texto);
}

void termina_matriz(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            matriz[i][j] = 1;
        }
    }
}

void atualiza_placar(){
    char texto_placar[20];
    g_snprintf(texto_placar, 20, "PLACAR\nX: %d\nO: %d", vitorias_x, vitorias_o);
    gtk_label_set_text(placar, texto_placar);
}

void x_vence(){
    gtk_label_set_text(texto, "'X' GANHOU!!!");
    teve_ganhador = 1;
    vitorias_x++;
    atualiza_placar();

    termina_matriz();
}

void o_vence(){
    gtk_label_set_text(texto, "'O' GANHOU!!!");
    teve_ganhador = 1;
    vitorias_o++;
    atualiza_placar();

    termina_matriz();
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

void on_reset_clicked(GtkWidget *widget, gpointer data){
    inicializa_matriz();
    teve_ganhador = 0;
    GtkButton *button_0_0 = GTK_BUTTON(gtk_builder_get_object(builder, "butao_0_0"));
    GtkButton *button_0_1 = GTK_BUTTON(gtk_builder_get_object(builder, "butao_0_1"));
    GtkButton *button_0_2 = GTK_BUTTON(gtk_builder_get_object(builder, "butao_0_2"));
    GtkButton *button_1_0 = GTK_BUTTON(gtk_builder_get_object(builder, "butao_1_0"));
    GtkButton *button_1_1 = GTK_BUTTON(gtk_builder_get_object(builder, "butao_1_1"));
    GtkButton *button_1_2 = GTK_BUTTON(gtk_builder_get_object(builder, "butao_1_2"));
    GtkButton *button_2_0 = GTK_BUTTON(gtk_builder_get_object(builder, "butao_2_0"));
    GtkButton *button_2_1 = GTK_BUTTON(gtk_builder_get_object(builder, "butao_2_1"));
    GtkButton *button_2_2 = GTK_BUTTON(gtk_builder_get_object(builder, "butao_2_2"));

    gtk_button_set_label(button_0_0, " ");
    gtk_button_set_label(button_0_1, " ");
    gtk_button_set_label(button_0_2, " ");
    gtk_button_set_label(button_1_0, " ");
    gtk_button_set_label(button_1_1, " ");
    gtk_button_set_label(button_1_2, " ");
    gtk_button_set_label(button_2_0, " ");
    gtk_button_set_label(button_2_1, " ");
    gtk_button_set_label(button_2_2, " ");
}

int main(int argc, char* argv[]){

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("JogoDaVelha.glade");

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
        "on_reset_clicked",                     G_CALLBACK(on_reset_clicked),
    NULL);

    gtk_builder_connect_signals(builder, NULL);
 
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    texto = GTK_LABEL(gtk_builder_get_object(builder, "texto"));
    placar = GTK_LABEL(gtk_builder_get_object(builder, "placar"));

    inicializa_matriz();
    usar_estilo();

    gtk_widget_show_all(window);
    gtk_main(); 


    return 0;
}
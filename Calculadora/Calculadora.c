#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <math.h>

#define true 1
#define false 0
typedef char bool;

GtkEntry *display;
double primeiro_numero, segundo_numero, resultado;
bool limpar_display = false;
char operacao;

void usar_estilo(){
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "static/estilo_calculadora.css", FALSE);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider),
     GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

double ler_display(){
    const gchar *texto = gtk_entry_get_text(display);
    return atof(texto);
}

void on_botao_clicked(GtkButton *button, gpointer data){

    if(limpar_display == true){
        gtk_entry_set_text(display, "0");
        limpar_display = false;
    }

    if(strcmp(gtk_entry_get_text(display), "0") == 0)
        gtk_entry_set_text(display, gtk_button_get_label(button));
    else{
        char texto[100];
        g_snprintf(texto, 100, "%s%s", gtk_entry_get_text(display), gtk_button_get_label(button));
        gtk_entry_set_text(display, texto);
    }

}

void on_main_window_destroy(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}

void on_botao_igual_clicked(GtkWidget *widget, gpointer data){
    char resposta[100];
    resultado = primeiro_numero;

    if(operacao == 'v'){
        resultado = sqrt(primeiro_numero);
    }
    else
        segundo_numero = ler_display();


    if(operacao == '+') resultado += segundo_numero;
    else if(operacao == '-') resultado -= segundo_numero;
    else if(operacao == '*') resultado *= segundo_numero;
    else if(operacao == '/'){
      resultado /= segundo_numero;  
    }
    else if(operacao == '%') resultado = primeiro_numero * segundo_numero / 100;

    sprintf(resposta, "%lf", resultado);
    gtk_entry_set_text(display, resposta);
    limpar_display = true;
}

void on_botao_reset_clicked(GtkWidget *widget, gpointer data){
    gtk_entry_set_text(display, "0");
}

void on_botao_ponto_clicked(GtkWidget *widget, gpointer data){
    char texto[100];
    g_snprintf(texto, 100, "%s,", gtk_entry_get_text(display));
    gtk_entry_set_text(display, texto);
}

void on_botao_soma_clicked(GtkWidget *widget, gpointer data){
    operacao = '+';
    primeiro_numero = ler_display();
    limpar_display = true;
}

void on_botao_subtracao_clicked(GtkWidget *widget, gpointer data){
    operacao = '-';
    primeiro_numero = ler_display();
    limpar_display = true;
}

void on_botao_multiplicacao_clicked(GtkWidget *widget, gpointer data){
    operacao = '*';
    primeiro_numero = ler_display();
    limpar_display = true;
}

void on_botao_divisao_clicked(GtkWidget *widget, gpointer data){
    operacao = '/';
    primeiro_numero = ler_display();
    limpar_display = true;
}


void on_botao_raiz_quadrada_clicked(GtkWidget *widget, gpointer data){
    operacao = 'v';
    primeiro_numero = ler_display();
    on_botao_igual_clicked(widget, data);
    limpar_display = true;
    
}


void on_botao_porcentagem_clicked(GtkWidget *widget, gpointer data){
    operacao = '%';
    primeiro_numero = ler_display();
    limpar_display = true;
}

int main(int argc, char* argv[]){

    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new_from_file("Calculadora.glade");

    gtk_builder_add_callback_symbols(
        builder, 
        "on_botao_clicked",                     G_CALLBACK(on_botao_clicked),
        "on_main_window_destroy",               G_CALLBACK(on_main_window_destroy),
        "on_botao_reset_clicked",               G_CALLBACK(on_botao_reset_clicked),
        "on_botao_raiz_quadrada_clicked",       G_CALLBACK(on_botao_raiz_quadrada_clicked),
        "on_botao_porcentagem_clicked",         G_CALLBACK(on_botao_porcentagem_clicked),
        "on_botao_divisao_clicked",             G_CALLBACK(on_botao_divisao_clicked),
        "on_botao_multiplicacao_clicked",       G_CALLBACK(on_botao_multiplicacao_clicked),
        "on_botao_subtracao_clicked",           G_CALLBACK(on_botao_subtracao_clicked),
        "on_botao_soma_clicked",                G_CALLBACK(on_botao_soma_clicked),
        "on_botao_igual_clicked",               G_CALLBACK(on_botao_igual_clicked),
        "on_botao_ponto_clicked",               G_CALLBACK(on_botao_ponto_clicked),
    NULL);

    usar_estilo();
    gtk_builder_connect_signals(builder, NULL);
 
    display = GTK_ENTRY(gtk_builder_get_object(builder, "display"));
    gtk_entry_set_text(display, "0");
    
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));


    gtk_widget_show_all(window);
    gtk_main(); 

    return 0;
}
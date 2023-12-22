#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>


GtkLabel *resultado;
GtkEntry *peso;
GtkEntry *altura;

void on_botao_clicked(GtkWidget *widget, gpointer data){
    
    const gchar *peso_str = gtk_entry_get_text(peso);
    const gchar *altura_str = gtk_entry_get_text(altura);

    double peso_f = atof(peso_str);
    double altura_f = atof(altura_str);
    double imc = peso_f/(altura_f * altura_f);

    printf("peso = %.2lf e altura = %.2lf\n", peso_f, altura_f);
    printf("imc = %.2lf\n", imc);

    char texto[] = "Seu IMC e: ";
    char result[20];

    g_snprintf(result, 20, "%s%.2lf", texto, imc);

    printf("result = %s\n", result);

    gtk_label_set_text(resultado, result);
    
}

void on_main_window_destroy(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}

int main(int argc, char* argv[]){

    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new_from_file("Projeto2.glade");

    gtk_builder_add_callback_symbols(builder, "on_butao_clicked", G_CALLBACK(on_botao_clicked),
        "on_main_window_destroy", G_CALLBACK(on_main_window_destroy), 
        NULL);

    gtk_builder_connect_signals(builder, NULL);
 
    resultado = GTK_LABEL(gtk_builder_get_object(builder, "resultado"));
    altura = GTK_ENTRY(gtk_builder_get_object(builder, "altura"));
    peso = GTK_ENTRY(gtk_builder_get_object(builder, "peso"));
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    gtk_widget_show_all(window);
    gtk_main(); 

    return 0;
}
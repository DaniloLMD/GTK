#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

GtkLabel *resultado;
GtkEntry *peso;
GtkEntry *altura;

void on_botao_clicked(GtkWidget *widget, gpointer data){
    
    const gchar *peso_str = gtk_entry_get_text(peso);
    const gchar *altura_str_const = gtk_entry_get_text(altura);


    char altura_str[strlen(altura_str_const) + 1];
    for(int i = 0; altura_str[i] != '\0'; i++){
        altura_str[i] = altura_str_const[i];
        if(altura_str[i] == '.'){
            altura_str[i] = ',';
        }
    }
    altura_str[strlen(altura_str_const)] = '\0';

    double peso_f = atof(peso_str);
    double altura_f = atof(altura_str);
    if(altura_f >= 100) 
        altura_f /= 100;

    if(altura_f <= 0 || peso_f <= 0){
        gtk_label_set_text(resultado, "Por favor informe\nvalores validos");
        return;
    }

    double imc = peso_f/(altura_f * altura_f);

    char result[40], imc_str[10], final[50] = "Seu IMC e: ";;

    if(imc < 17){
        strcpy(result, "Muito abaixo do peso");
    }
    else if(imc >= 17 && imc < 18.5){
        strcpy(result, "Abaixo do peso");
    }   
    else if(imc >= 18.5 && imc < 25){
        strcpy(result, "Peso Normal");
    }
    else if(imc >= 25 && imc < 30){
        strcpy(result, "Acima do peso");
    }
    else if(imc >= 30 && imc < 35){
        strcpy(result, "Obesidade grau I  ");
    }   
    else if(imc >= 35 && imc <= 40){
        strcpy(result, "Obesidade grau II");
    }   
    else if(imc > 40){
        strcpy(result, "Obesidade grau III");
    }


    //g_snprintf(final, 50, "%s%.2lf\n%s", texto, imc, result);
    sprintf(imc_str, "%.2lf\n", imc);
    strcat(final, imc_str);
    strcat(final, result);

    gtk_label_set_text(resultado, final);
    
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
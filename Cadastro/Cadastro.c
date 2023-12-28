#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>

GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;
GtkListStore *modelo_armazenamento;

typedef struct usuario{
    int id;
    char nome[100];
    char email[100];
    struct usuario *proximo;
}user;

int id = 1;
user* cabecalho_user;
user* proximo_user;

void mensagem(char *text, char *secondary_text, char *icon_name){
    GtkMessageDialog *mensagem_dialogo = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "mensagem"));

    g_object_set(mensagem_dialogo, "text", text, NULL);
    g_object_set(mensagem_dialogo, "secondary_text", secondary_text, NULL);
    g_object_set(mensagem_dialogo, "icon_name", icon_name, NULL);
    gtk_widget_show_all(GTK_WIDGET(mensagem_dialogo));
    gtk_dialog_run(GTK_DIALOG(mensagem_dialogo));
    gtk_widget_hide(GTK_WIDGET(mensagem_dialogo));

}

void login(const char* email, const char* senha, bool lembrar){
    
    //login bem sucedido
    if(strcmp(email, "admin") == 0 && strcmp(senha, "admin") == 0)   {
        mensagem("Bem Vindo", "Usuario logado com sucesso!", "emblem-default");
        gtk_stack_set_visible_child_name(stack, "view_inicial");   
        g_object_set(window, "icon_name", "avatar-default", NULL);
    } 
    //login mal sucedido
    else{
        mensagem("Aviso", "Email ou senha incorretos!", "dialog-error");
    }
}

void on_login_clicked(){
    const char* email = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "email")));
    const char* senha = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "senha")));
    bool lembrar = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "lembrar")));
    login(email, senha, lembrar);
}   

void on_botao_cadastrar_inicial_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_cadastro");
}

void on_botao_listar_inicial_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_listar");
}

void on_botao_sair_inicial_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_login");
    g_object_set(window, "icon_name", "changes-prevent", NULL);
}

void on_botao_cad_voltar_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_inicial");
}

void on_botao_listar_voltar_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_inicial");
}

void on_botao_cadastrar_clicked(){
    const char* cad_nome = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "cad_nome")));
    const char* cad_email = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "cad_email")));

    if(strlen(cad_nome) == 0){
        mensagem("AVISO", "Campo 'Nome' obrigatorio!", "dialog-error");
        return;
    }
    if(strlen(cad_email) == 0){
        mensagem("AVISO", "Campo 'Email' obrigatorio!", "dialog-error");
        return;
    }

    proximo_user->id = id++;
    strcpy(proximo_user->nome, cad_nome);
    strcpy(proximo_user->email, cad_email);

    char texto[100];
    g_snprintf(texto, 100, "Usuario %s cadastrado", proximo_user->nome);
    mensagem("Aviso", texto, "dialog-emblem-default");

    proximo_user->proximo = (user*) malloc(sizeof(user));
    proximo_user = proximo_user->proximo;   
}

int aa = 0;
void on_botao_listar_clicked(){
    printf("proximo_user = %p\n", proximo_user);                
    proximo_user->proximo = NULL;
    proximo_user = cabecalho_user;

    GtkTreeIter iter;
    gtk_list_store_clear(modelo_armazenamento);
    while(proximo_user->proximo != NULL){
        g_print("id: %d | nome: %s | email: %s\n", proximo_user->id, proximo_user->nome, proximo_user->email);
        //printf("iter = %p\n", iter);
        gtk_list_store_append(modelo_armazenamento, &iter);
        //printf("iter = %p\n", iter);
        gtk_list_store_set(modelo_armazenamento, &iter,
            0, proximo_user->id,
            1, proximo_user->nome,
            2, proximo_user->email,
            -1
        );
        proximo_user = proximo_user->proximo;
    }

    printf("proximo_user = %p\n", proximo_user);

}

void on_main_window_destroy(GtkWidget* widget, gpointer data;){
    gtk_main_quit();
}

int main(){
    
    //alocanco memoria pra lista encadeada
    cabecalho_user = (user*) malloc(sizeof(user));
    proximo_user = cabecalho_user;

    //iniciando o gtk
    gtk_init(NULL, NULL);   
    builder = gtk_builder_new_from_file("Cadastro.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
    modelo_armazenamento = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));

    gtk_builder_add_callback_symbols(
        builder,
        "on_main_window_destroy",               G_CALLBACK(on_main_window_destroy),
        "on_login_clicked",                     G_CALLBACK(on_login_clicked),    
        "on_botao_cadastrar_inicial_clicked",   G_CALLBACK(on_botao_cadastrar_inicial_clicked),
        "on_botao_listar_inicial_clicked",      G_CALLBACK(on_botao_listar_inicial_clicked),
        "on_botao_sair_inicial_clicked",        G_CALLBACK(on_botao_sair_inicial_clicked),
        "on_botao_cad_voltar_clicked",          G_CALLBACK(on_botao_cad_voltar_clicked),
        "on_botao_cadastrar_clicked",           G_CALLBACK(on_botao_cadastrar_clicked),
        "on_botao_listar_voltar_clicked",       G_CALLBACK(on_botao_listar_voltar_clicked),
        "on_botao_listar_clicked",              G_CALLBACK(on_botao_listar_clicked),
        NULL
    );

    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}